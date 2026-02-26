#include "DayNightCycleManager.h"

ADayNightCycleManager::ADayNightCycleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADayNightCycleManager::BeginPlay()
{
	Super::BeginPlay();
	
	DayNightWidget = CreateWidget<UDayNightWidget>(GetWorld(), DayNightWidgetClass);

	if (DayNightWidget)
	{
		DayNightWidget->AddToViewport();
	}
}

void ADayNightCycleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime > DayLength)
	{
		CurrentTime = 0.0f;
	}

	float TimePercent = CurrentTime / DayLength;

	if (DayNightCurve)
	{
		float CurveValue = DayNightCurve->GetFloatValue(TimePercent);

		if (DayNightWidget)
		{
			DayNightWidget->UpdateNightAlpha(CurveValue);
		}
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("CurveValue: %f"), CurveValue));
	}
}

