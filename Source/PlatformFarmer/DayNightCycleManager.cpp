#include "DayNightCycleManager.h"

ADayNightCycleManager::ADayNightCycleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADayNightCycleManager::BeginPlay()
{
	Super::BeginPlay();
	
	float HourPassTimerDelay = DayLength / 18;

	GetWorldTimerManager().SetTimer(HourPassTimer, this, &ADayNightCycleManager::OnHourPassTimerTimeout, HourPassTimerDelay, true, HourPassTimerDelay);
	GetWorldTimerManager().SetTimer(DayPassTimer, this, &ADayNightCycleManager::OnDayPassTimerTimeout, 1.0f, false, DayLength);
}

void ADayNightCycleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADayNightCycleManager::OnDayPassTimerTimeout()
{
	GetWorldTimerManager().ClearTimer(HourPassTimer);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Day ended")));
	GetWorldTimerManager().SetTimer(DayEndTimer, this, &ADayNightCycleManager::OnDayEndTimerTimeout, 1.0f, false, DayEndDelay);
}

void ADayNightCycleManager::OnHourPassTimerTimeout()
{
	CurrentHour++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("CurrentHour: %d"), CurrentHour));
}

void ADayNightCycleManager::OnDayEndTimerTimeout()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Sleeping")));
}

