#include "DayNightCycleManager.h"

#include "PlayerCharacter.h"

ADayNightCycleManager::ADayNightCycleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADayNightCycleManager::BeginPlay()
{
	Super::BeginPlay();
	

	if (DayNightWidgetClass)
	{
		DayNightWidget = CreateWidget<UDayNightWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DayNightWidgetClass);
		if (DayNightWidget)
		{
			DayNightWidget->AddToPlayerScreen();
		}
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATree::StaticClass(), Trees);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASlime::StaticClass(), Slimes);
	WeatherSystemManager = Cast<AWeatherSystemManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWeatherSystemManager::StaticClass()));
	
	Sleep();
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
	DayNightWidget->SetHourText(CurrentHour);
}

void ADayNightCycleManager::OnDayEndTimerTimeout()
{
	Sleep();
}

void ADayNightCycleManager::Sleep() 
{
	CurrentHour = 6;
	DayNightWidget->SetHourText(CurrentHour);
	CurrentTime = FMath::Fmod(CurrentTime, DayLength);
	float HourPassTimerDelay = DayLength / 18;
	GetWorldTimerManager().SetTimer(HourPassTimer, this, &ADayNightCycleManager::OnHourPassTimerTimeout, HourPassTimerDelay, true, HourPassTimerDelay);
	GetWorldTimerManager().SetTimer(DayPassTimer, this, &ADayNightCycleManager::OnDayPassTimerTimeout, 1.0f, false, DayLength);
	CurrentTime = 0;
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));

	for (AActor* TreeActor : Trees)
	{
		ATree* Tree = Cast<ATree>(TreeActor);
		if (Tree)
		{
			Tree->Regrow();
		}
	}
	for (AActor* SlimeActor : Slimes)
	{
		ASlime* Slime = Cast<ASlime>(SlimeActor);
		if (Slime)
		{
			Slime->Respawn();
		}
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plants);
	for (AActor* PlantActor : Plants)
	{
		APlant* Plant = Cast<APlant>(PlantActor);
		if (Plant)
		{
			 Plant->Grow();
		}
	}
	for (FIntPoint WateredTile : Player->WateredTiles)
	{
		Player->ChangeTile(WateredTile.X, WateredTile.Y, Player->WaterTileSet, -1, 1);
	}
	
	WeatherSystemManager->SetWeather();
	WeatherSystemManager->SetNextWeather();
}