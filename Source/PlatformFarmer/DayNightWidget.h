#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DayNightWidget.generated.h"

UCLASS()
class PLATFORMFARMER_API UDayNightWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateNightAlpha(float Value);
};
