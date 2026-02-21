#include "Spring.h"

ASpring::ASpring()
{
	PrimaryActorTick.bCanEverTick = true;

	CharCheck = CreateDefaultSubobject<UBoxComponent>(TEXT("CharCheck"));
	SetRootComponent(CharCheck);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);
}

void ASpring::BeginPlay()
{
	Super::BeginPlay();
	
	CharCheck->OnComponentBeginOverlap.AddDynamic(this, &ASpring::OverlapBegin);
	Flipbook->OnFinishedPlaying.AddDynamic(this, &ASpring::OnFlipbookFinishedPlaying);
}

void ASpring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpring::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		FVector LaunchVelocity = Player->GetActorUpVector() * FVector(0.0f, 0.0f, LaunchPower);

		Player->LaunchCharacter(LaunchVelocity, false, true);

		Flipbook->SetLooping(false);
		Flipbook->SetFlipbook(ActiveFlipbook);
		Flipbook->Play();
	}
}

void ASpring::OnFlipbookFinishedPlaying()
{
	Flipbook->SetFlipbook(IdleFlipbook);
}
