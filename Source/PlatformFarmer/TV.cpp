#include "TV.h"

ATV::ATV()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	
	TVFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TVFlipbook"));
	TVFlipbook->SetupAttachment(RootComponent);

	InteractKeySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("InteractKeySprite"));
	InteractKeySprite->SetupAttachment(RootComponent);

}

void ATV::BeginPlay()
{
	Super::BeginPlay();
	
	InteractKeySprite->SetVisibility(false);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATV::OnComponentOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ATV::OnComponentOverlapEnd);
}

void ATV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATV::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractKeySprite->SetVisibility(true);

	TVFlipbook->SetFlipbook(SunnyWeatherFlipbook);
}

void ATV::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractKeySprite->SetVisibility(false);

	TVFlipbook->SetFlipbook(IdleFlipbook);
}