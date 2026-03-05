#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Enums.h"

#include "ShopKeeper.generated.h"

UCLASS()
class PLATFORMFARMER_API AShopKeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AShopKeeper();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* ShopKeeperFlipbook;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* InteractKeySprite;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PlayerOverlapping = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EShopType ShopType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EItems, int32> ItemPrice;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EShopItem ItemReward;
};
