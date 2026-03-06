#include "Door.h"

#include "PlayerCharacter.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	DoorSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DoorSprite"));
	DoorSprite->SetupAttachment(RootComponent);

	InteractKeySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("InteractKeySprite"));
	InteractKeySprite->SetupAttachment(RootComponent);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractKeySprite->SetVisibility(false);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnComponentOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnComponentOverlapEnd);
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		InteractKeySprite->SetVisibility(true);
		PlayerOverlapping = true;
	}
}

void ADoor::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractKeySprite->SetVisibility(false);
	PlayerOverlapping = false;
}

