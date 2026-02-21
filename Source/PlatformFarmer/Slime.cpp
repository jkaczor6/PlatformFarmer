#include "Slime.h"

ASlime::ASlime()
{
	PrimaryActorTick.bCanEverTick = true;

	WallDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("WallDetector"));
	WallDetector->SetupAttachment(RootComponent);

	LedgeDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("LedgeDetector"));
	LedgeDetector->SetupAttachment(RootComponent);
}

void ASlime::BeginPlay()
{
	Super::BeginPlay();

	WallDetector->OnComponentBeginOverlap.AddDynamic(this, &ASlime::OverlapBegin);
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

void ASlime::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UpdateDirection();
}