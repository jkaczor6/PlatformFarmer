#include "WinCrown.h"

#include "PlayerCharacter.h"

AWinCrown::AWinCrown()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	CrownSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CrownSprite"));
	CrownSprite->SetupAttachment(RootComponent);

	InteractKeySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("InteractKeySprite"));
	InteractKeySprite->SetupAttachment(RootComponent);
}

void AWinCrown::BeginPlay()
{
	Super::BeginPlay();
	
	InteractKeySprite->SetVisibility(false);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AWinCrown::OnComponentOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AWinCrown::OnComponentOverlapEnd);
}

void AWinCrown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWinCrown::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		InteractKeySprite->SetVisibility(true);
		PlayerOverlapping = true;
	}
}

void AWinCrown::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractKeySprite->SetVisibility(false);
	PlayerOverlapping = false;
}

