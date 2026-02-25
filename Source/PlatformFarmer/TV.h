#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSpriteComponent.h"

#include "TV.generated.h"

UCLASS()
class PLATFORMFARMER_API ATV : public AActor
{
	GENERATED_BODY()
	
public:	
	ATV();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* InteractKeySprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* TVFlipbook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* IdleFlipbook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* SunnyWeatherFlipbook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* RainyWeatherFlipbook;
};
