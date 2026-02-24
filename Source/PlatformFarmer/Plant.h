#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "Enums.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* PlantSprite;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPaperSprite*> PlantGrowthSprites;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 GrowthStage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 GrowthSprites;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 GrowthTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 HP = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESeeds PlantType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsWatered = false;
};
