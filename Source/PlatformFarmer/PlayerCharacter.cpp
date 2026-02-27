#include "PlayerCharacter.h"

#include "Slime.h"
#include "Tree.h"

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

	TileMapActor = Cast<APaperTileMapActor>(UGameplayStatics::GetActorOfClass(GetWorld(), APaperTileMapActor::StaticClass()));

	if (TileMapActor)
	{
		TileMapActor->GetRenderComponent()->MakeTileMapEditable();
	}
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
	int NextTool = ((int)CurrentTool + MoveActionValue + (int)ETools::COUNT) % (int)ETools::COUNT;
	CurrentTool = (ETools)NextTool;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Current Tool: %s"), *UEnum::GetValueAsString(CurrentTool)));
}

void APlayerCharacter::SwitchSeeds(const FInputActionValue& Value)
{
	int MoveActionValue = Value.Get<float>();
	int NextSeed = ((int)CurrentSeed + MoveActionValue + (int)ESeeds::COUNT) % (int)ESeeds::COUNT;
	CurrentSeed = (ESeeds)NextSeed;
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
		case ETools::Axe:
			AnimToPlay = AxeAnimSequence;
			HitBox->SetCollisionResponseToChannel(ECC_Tree, ECollisionResponse::ECR_Overlap);
			break;
		case ETools::Hoe:
			AnimToPlay = HoeAnimSequence;
			UseHoe();
			break;
		case ETools::Seeds:
			AnimToPlay = UseAnimSequence;
			UseSeed();
			break;
		case ETools::Sword:
			AnimToPlay = SwordAnimSequence;
			HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
			break;
		case ETools::Water:
			AnimToPlay = WaterAnimSequence;
			UseWater();
			break;
		default:
			AnimToPlay = AxeAnimSequence;
		}

		GetAnimInstance()->PlayAnimationOverride(AnimToPlay, FName("DefaultSlot"), 1.0f, 0.0f, OnUseOverrideEndDelegate);
	}
	
}

void APlayerCharacter::Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%s"), *OtherActor->GetActorNameOrLabel()));
	ASlime* Slime = Cast<ASlime>(OtherActor);
	if (Slime)
	{
		Slime->Destroy();
	}
	ATree* Tree = Cast<ATree>(OtherActor);
	if (Tree)
	{
		Tree->TreeSprite->SetVisibility(false);
		Tree->StumpSprite->SetVisibility(true);
		Tree->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APlayerCharacter::OnUseOverrideAnimEnd(bool Completed)
{
	if (IsAlive)
	{
		CanMove = true;
		CanUse = true;
	}
	
	HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	HitBox->SetCollisionResponseToChannel(ECC_Tree, ECollisionResponse::ECR_Ignore);
}

FVector2D APlayerCharacter::GetTile()
{
	int32 OutTileX;
	int32 OutTileY;
	TileMap->GetTileCoordinatesFromLocalSpacePosition(FVector(GetActorLocation().X, 0.0f, GetActorLocation().Z), OutTileX, OutTileY);
	if (CurrentRotation.Yaw == 180.0f)
	{
		OutTileX -= 1;
	}
	else if (CurrentRotation.Yaw == 0.0f)
	{
		OutTileX += 1;
	}
	OutTileY += 1;
	
	FVector2D Tile = FVector2D(OutTileX, OutTileY);
	return Tile;
}

void APlayerCharacter::UseHoe()
{
	FVector2D Tile = GetTile();

	FPaperTileInfo TileToBeHoed = TileMapActor->GetRenderComponent()->GetTile(Tile.X, Tile.Y, 2);
	if (TileToBeHoed.PackedTileIndex == 0)
	{
		ChangeTile(Tile.X, Tile.Y, GroundTileSet, 48, 2);
	}
	else if (TileToBeHoed.PackedTileIndex == 1)
	{
		ChangeTile(Tile.X, Tile.Y, GroundTileSet, 49, 2);
	}
	else if (TileToBeHoed.PackedTileIndex == 2)
	{
		ChangeTile(Tile.X, Tile.Y, GroundTileSet, 50, 2);
	}
}

void APlayerCharacter::UseWater()
{
	FVector2D Tile = GetTile();
	FPaperTileInfo TileInfo;
	TileInfo.TileSet = GroundTileSet;
	
	FPaperTileInfo TileToBeWatered = TileMapActor->GetRenderComponent()->GetTile(Tile.X, Tile.Y, 2);
	if (TileToBeWatered.PackedTileIndex == 48)
	{
		ChangeTile(Tile.X, Tile.Y, WaterTileSet, 0, 1);
	}
	else if (TileToBeWatered.PackedTileIndex == 49)
	{
		ChangeTile(Tile.X, Tile.Y, WaterTileSet, 1, 1);
	}
	else if (TileToBeWatered.PackedTileIndex == 50)
	{
		ChangeTile(Tile.X, Tile.Y, WaterTileSet, 2, 1);
	}
}

void APlayerCharacter::UseSeed()
{
	FVector2D Tile = GetTile();

	FPaperTileInfo TileToPlantOn = TileMapActor->GetRenderComponent()->GetTile(Tile.X, Tile.Y, 2);
	if (TileToPlantOn.PackedTileIndex != 49) return;
	if (!PlantClasses.Contains(CurrentSeed)) return;

	UPaperTileMapComponent* TileMapComp = TileMapActor->GetRenderComponent();

	FVector WorldLocation = TileMapComp->GetTileCenterPosition(Tile.X, Tile.Y, 2, true);
	FVector SpawnLocation = FVector(WorldLocation.X, 0.0f, WorldLocation.Z + 12);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	TSubclassOf<APlant> PlantToSpawn = PlantClasses[CurrentSeed];
	FIntPoint PlantedTile = FIntPoint(Tile.X, Tile.Y);
	if (PlantedTiles.Contains(PlantedTile)) return;

	APlant* Plant = GetWorld()->SpawnActor<APlant>(PlantToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnInfo);
	PlantedTiles.Add(PlantedTile, Plant);

	if (Plant)
	{
		Plant->SetupPlant(CurrentSeed);
	}
}

void APlayerCharacter::ChangeTile(int32 X, int32 Y, UPaperTileSet* CorrectTileSet, int32 NewTileIndex, int32 LayerIndex)
{
	UPaperTileMapComponent* TileMapComponent = TileMapActor->GetRenderComponent();
	if (!TileMapComponent) return;

	FPaperTileInfo NewTile;
	NewTile.TileSet = CorrectTileSet;
	NewTile.PackedTileIndex = NewTileIndex;

	TileMapComponent->SetTile(X, Y, LayerIndex, NewTile);
	TileMapComponent->RebuildCollision();
}

void APlayerCharacter::UpdateDirection(float MoveDirection)
{
	CurrentRotation = Controller->GetControlRotation();

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