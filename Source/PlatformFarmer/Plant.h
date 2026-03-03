#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "Enums.h"

#include "PaperTileMap.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileLayer.h"
#include "PaperTileSet.h"

#include "Plant.generated.h"

UCLASS()
class PLATFORMFARMER_API APlant : public AActor
{
	GENERATED_BODY()
	
public:	
	APlant();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetupPlant(ESeeds SeedType);
	void Grow();
	void CheckIfIsWatered();
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* PlantSprite;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int32, UPaperSprite*> PlantGrowthSprites;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentGrowthStage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 GrowthStages;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 HP = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESeeds PlantType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EItems Reward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsWatered = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsFullyGrown = false;

	int32 DeathCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileMap")
	UPaperTileMap* TileMap;
	UPROPERTY(EditAnywhere, Category = "TileMap")
	APaperTileMapActor* TileMapActor;
};
