#include "Slime.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

ASlime::ASlime()
{
	PrimaryActorTick.bCanEverTick = true;

	WallDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("WallDetector"));
	WallDetector->SetupAttachment(RootComponent);

	LedgeDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("LedgeDetector"));
	LedgeDetector->SetupAttachment(RootComponent);

	PlayerChecker = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerChecker"));
	PlayerChecker->SetupAttachment(RootComponent);

	CapsuleComp = FindComponentByClass<UCapsuleComponent>();
	Flipbook = FindComponentByClass<UPaperFlipbookComponent>();
}

void ASlime::BeginPlay()
{
	Super::BeginPlay();

	WallDetector->OnComponentBeginOverlap.AddDynamic(this, &ASlime::OverlapBegin);
	PlayerChecker->OnComponentBeginOverlap.AddDynamic(this, &ASlime::OverlapBegin);
}

void ASlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckLedge();
}

void ASlime::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASlime::UpdateDirection()
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = CurrentRotation + FRotator(0.0f, 180.0f, 0.0f);
	SetActorRotation(NewRotation);
}

void ASlime::CheckLedge()
{
	UCharacterMovementComponent* CharMoveComp = GetCharacterMovement();
	if (CharMoveComp->CurrentFloor.bWalkableFloor)
	{
		TArray<AActor*> OverlappingActors;
		LedgeDetector->GetOverlappingActors(OverlappingActors);
		int ArrayLength = OverlappingActors.Num();
		if (!(ArrayLength > 0))
		{
			UpdateDirection();
		}
	}
}

void ASlime::Die()
{
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Flipbook->SetVisibility(false);
	Flipbook->SetActive(false);
}

void ASlime::Respawn()
{
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Flipbook->SetVisibility(true);
	Flipbook->SetActive(true);
}

void ASlime::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UpdateDirection();

	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		if (Player->IsAlive)
		{
			Player->Die();
		}
	}
}