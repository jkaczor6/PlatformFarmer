#include "Plant.h"

#include "Kismet/GameplayStatics.h"

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
	
	TileMapActor = Cast<APaperTileMapActor>(UGameplayStatics::GetActorOfClass(GetWorld(), APaperTileMapActor::StaticClass()));
	
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
			GrowthStages = 3;
			CurrentGrowthStage = 1;
			Reward = EItems::Carrot;
			break;
		case ESeeds::Pumpkin:
			GrowthStages = 7;
			CurrentGrowthStage = 1;
			Reward = EItems::Pumpkin;
			break;
		case ESeeds::Tomato:
			GrowthStages = 5;
			CurrentGrowthStage = 1;
			Reward = EItems::Tomato;
			break;
		case ESeeds::Wheat:
			GrowthStages = 4;
			CurrentGrowthStage = 1;
			Reward = EItems::Wheat;
			break;
		default:
			GrowthStages = 1;
			CurrentGrowthStage = 1;
			break;
	}
}

void APlant::CheckIfIsWatered()
{
	int32 OutTileX;
	int32 OutTileY;
	TileMap->GetTileCoordinatesFromLocalSpacePosition(FVector(GetActorLocation().X, 0.0f, GetActorLocation().Z), OutTileX, OutTileY);
	OutTileY += 1;

	FVector2D Tile = FVector2D(OutTileX, OutTileY);

	FPaperTileInfo TileToCheck = TileMapActor->GetRenderComponent()->GetTile(Tile.X, Tile.Y - 16, 3);
	if (TileToCheck.PackedTileIndex == 1)
	{
		IsWatered = true;
	}
}

void APlant::Grow()
{
	CurrentGrowthStage++;
	if (CurrentGrowthStage < GrowthStages)
	{
		PlantSprite->SetSprite(PlantGrowthSprites[CurrentGrowthStage]);
	}
	else
	{
		CurrentGrowthStage = GrowthStages;
	}
}
