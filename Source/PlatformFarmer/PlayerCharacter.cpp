#include "PlayerCharacter.h"

#include "Slime.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* Player = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}

	OnUseOverrideEndDelegate.BindUObject(this, &APlayerCharacter::OnUseOverrideAnimEnd);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::Attack);
	HitBox->SetActive(false);
	HitBox->SetHiddenInGame(true);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::JumpEnded);

		EnhancedInputComponent->BindAction(SwitchToolsAction, ETriggerEvent::Started, this, &APlayerCharacter::SwitchTools);
		EnhancedInputComponent->BindAction(SwitchSeedsAction, ETriggerEvent::Started, this, &APlayerCharacter::SwitchSeeds);
		EnhancedInputComponent->BindAction(UseToolAction, ETriggerEvent::Started, this, &APlayerCharacter::UseTool);
	}
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	float MoveActionValue = Value.Get<float>();

	if (IsAlive && CanMove)
	{
		FVector Direction = FVector(1.0f, 0.0f, 0.0f);
		AddMovementInput(Direction, MoveActionValue);
		UpdateDirection(MoveActionValue);
	}
	
}

void APlayerCharacter::JumpStarted(const FInputActionValue& Value)
{
	if(IsAlive && CanMove) Jump();
}

void APlayerCharacter::JumpEnded(const FInputActionValue& Value)
{
	StopJumping();
}

void APlayerCharacter::SwitchTools(const FInputActionValue& Value)
{
	int MoveActionValue = Value.Get<float>();
	int NextTool = ((int)CurrentTool + MoveActionValue + (int)Tools::COUNT) % (int)Tools::COUNT;
	CurrentTool = (Tools)NextTool;
}

void APlayerCharacter::SwitchSeeds(const FInputActionValue& Value)
{
	int MoveActionValue = Value.Get<float>();
	int NextSeed = ((int)CurrentSeed + MoveActionValue + (int)Seeds::COUNT) % (int)Seeds::COUNT;
	CurrentSeed = (Seeds)NextSeed;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("CurrentSeed: %s"), *UEnum::GetValueAsString(CurrentSeed)));
}

void APlayerCharacter::UseTool(const FInputActionValue& Value)
{
	UPaperZDAnimSequence* AnimToPlay;

	if (IsAlive && CanUse)
	{
		CanUse = false;
		CanMove = false;

		switch (CurrentTool)
		{
		case Tools::Axe:
			AnimToPlay = AxeAnimSequence;
			break;
		case Tools::Hoe:
			AnimToPlay = HoeAnimSequence;
			break;
		case Tools::Seeds:
			AnimToPlay = UseAnimSequence;
			break;
		case Tools::Sword:
			AnimToPlay = SwordAnimSequence;
			HitBox->SetActive(true);
			HitBox->SetHiddenInGame(false);
			break;
		case Tools::Water:
			AnimToPlay = WaterAnimSequence;
			break;
		default:
			AnimToPlay = AxeAnimSequence;
		}

		GetAnimInstance()->PlayAnimationOverride(AnimToPlay, FName("DefaultSlot"), 1.0f, 0.0f, OnUseOverrideEndDelegate);
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Using tool: %s"), *UEnum::GetValueAsString(CurrentTool)));
}

void APlayerCharacter::Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Attacking enemy: %s"), *OtherActor->GetActorNameOrLabel()));
}

void APlayerCharacter::OnUseOverrideAnimEnd(bool Completed)
{
	if (IsAlive)
	{
		CanMove = true;
		CanUse = true;
	}
	if (HitBox->IsActive())
	{
		HitBox->SetActive(false);
		HitBox->SetHiddenInGame(true);
	}
}

void APlayerCharacter::UpdateDirection(float MoveDirection)
{
	FRotator CurrentRotation = Controller->GetControlRotation();

	if (MoveDirection < 0.0f)
	{
		if (CurrentRotation.Yaw != 180.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 180.0f, CurrentRotation.Roll));
		}
	}
	else if (MoveDirection > 0.0f)
	{
		if (CurrentRotation.Yaw != 0.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 0.0f, CurrentRotation.Roll));
		}
	}
}