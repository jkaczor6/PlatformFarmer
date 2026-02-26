#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Curves/CurveFloat.h"
#include "Blueprint/UserWidget.h"
#include "DayNightWidget.h"

#include "DayNightCycleManager.generated.h"

UCLASS()
class PLATFORMFARMER_API ADayNightCycleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADayNightCycleManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DayLength = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveFloat* DayNightCurve;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDayNightWidget* DayNightWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UDayNightWidget> DayNightWidgetClass;

	float CurrentTime = 0.0f;
};
