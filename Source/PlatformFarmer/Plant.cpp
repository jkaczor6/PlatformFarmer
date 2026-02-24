#include "Plant.h"

APlant::APlant()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	PlantSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlantSprite"));
	PlantSprite->SetupAttachment(RootComponent);
}

void APlant::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlant::SetupPlant(ESeeds SeedType)
{
	PlantType = SeedType;

	switch (PlantType) 
	{
		case ESeeds::Carrot:
			GrowthSprites = 3;
			GrowthStage = 0;
			GrowthTime = 4;
		case ESeeds::Pumpkin:
			GrowthSprites = 4;
			GrowthStage = 0;
			GrowthTime = 7;
		case ESeeds::Tomato:
			GrowthSprites = 4;
			GrowthStage = 0;
			GrowthTime = 5;
		case ESeeds::Wheat:
			GrowthSprites = 4;
			GrowthStage = 0;
			GrowthTime = 4;
		default:
			GrowthSprites = 0;
			GrowthStage = 0;
			GrowthTime = 0;
	}
}

