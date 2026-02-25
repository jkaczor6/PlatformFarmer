#include "Bed.h"

ABed::ABed()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BedSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BedSprite"));
	BedSprite->SetupAttachment(RootComponent);

	InteractKeySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("InteractKeySprite"));
	InteractKeySprite->SetupAttachment(RootComponent);
}

void ABed::BeginPlay()
{
	Super::BeginPlay();
	
	InteractKeySprite->SetVisibility(false);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABed::OnComponentOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ABed::OnComponentOverlapEnd);
}

void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABed::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractKeySprite->SetVisibility(true);

	//GM->Sleep();
}

void ABed::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractKeySprite->SetVisibility(false);
}

