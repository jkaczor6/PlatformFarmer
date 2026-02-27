#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "DayNightWidget.generated.h"

UCLASS()
class PLATFORMFARMER_API UDayNightWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* HourText;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateNightAlpha(float Value);
	void SetHourText(int NewHour);
};
