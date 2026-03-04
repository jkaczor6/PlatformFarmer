#include "TV.h"

#include "PlayerCharacter.h"
#include "WeatherSystemManager.h"
#include "Kismet/GameplayStatics.h"

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
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		InteractKeySprite->SetVisibility(true);
		PlayerOverlapping = true;
	}
}

void ATV::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractKeySprite->SetVisibility(false);
	PlayerOverlapping = false;
	TVFlipbook->SetFlipbook(IdleFlipbook);
}

void ATV::ShowForecast()
{
	AWeatherSystemManager* WeatherSystemManager = Cast<AWeatherSystemManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWeatherSystemManager::StaticClass()));
	if (WeatherSystemManager->GetNextWeatherType() == EWeatherType::Rainy)
	{
		TVFlipbook->SetFlipbook(RainyWeatherFlipbook);
	}
	else
	{
		TVFlipbook->SetFlipbook(SunnyWeatherFlipbook);
	}
}
