#include "DayNightCycleManager.h"

ADayNightCycleManager::ADayNightCycleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADayNightCycleManager::BeginPlay()
{
	Super::BeginPlay();
	
	Sleep();

	if (DayNightWidgetClass)
	{
		DayNightWidget = CreateWidget<UDayNightWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DayNightWidgetClass);
		if (DayNightWidget)
		{
			DayNightWidget->AddToPlayerScreen();
		}
	}
}

void ADayNightCycleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorldTimerManager().IsTimerActive(DayPassTimer))
	{
		CurrentTime += DeltaTime;

		if (CurrentTime >= DayLength)
		{
			CurrentTime = 0.0f;
		}

		float TimePercent = CurrentTime / DayLength;


		if (DayNightCurve)
		{
			float CurveValue;
			if (DayNightCurve->GetFloatValue(TimePercent) < 0.7f)
			{
				CurveValue = DayNightCurve->GetFloatValue(TimePercent);
			}
			else
			{
				CurveValue = 0.7f;
			}

			DayNightWidget->UpdateNightAlpha(CurveValue);
		}
	}
}

void ADayNightCycleManager::OnDayPassTimerTimeout()
{
	GetWorldTimerManager().ClearTimer(HourPassTimer);
	GetWorldTimerManager().SetTimer(DayEndTimer, this, &ADayNightCycleManager::OnDayEndTimerTimeout, 1.0f, false, DayEndDelay);
}

void ADayNightCycleManager::OnHourPassTimerTimeout()
{
	CurrentHour++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("CurrentHour: %d"), CurrentHour));
}

void ADayNightCycleManager::OnDayEndTimerTimeout()
{
	Sleep();
}

void ADayNightCycleManager::Sleep() 
{
	CurrentHour = 6;
	CurrentTime = FMath::Fmod(CurrentTime, DayLength);
	float HourPassTimerDelay = DayLength / 18;
	GetWorldTimerManager().SetTimer(HourPassTimer, this, &ADayNightCycleManager::OnHourPassTimerTimeout, HourPassTimerDelay, true, HourPassTimerDelay);
	GetWorldTimerManager().SetTimer(DayPassTimer, this, &ADayNightCycleManager::OnDayPassTimerTimeout, 1.0f, false, DayLength);

	//for each Plant->Grow();
}