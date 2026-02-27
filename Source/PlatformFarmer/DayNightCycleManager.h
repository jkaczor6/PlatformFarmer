#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Curves/CurveFloat.h"
#include "Blueprint/UserWidget.h"

#include "Engine/TimerHandle.h"
#include "Kismet/GameplayStatics.h"

#include "DayNightCycleManager.generated.h"

UCLASS()
class PLATFORMFARMER_API ADayNightCycleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADayNightCycleManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void OnDayPassTimerTimeout();
	void OnHourPassTimerTimeout();
	void OnDayEndTimerTimeout();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DayLength = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveFloat* DayNightCurve;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DayEndDelay = 30.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentHour = 6;

	FTimerHandle DayPassTimer;
	FTimerHandle HourPassTimer;
	FTimerHandle DayEndTimer;

	
};
