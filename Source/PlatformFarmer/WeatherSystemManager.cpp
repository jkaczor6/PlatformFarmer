#include "WeatherSystemManager.h"
#include "Kismet/KismetMathLibrary.h"

AWeatherSystemManager::AWeatherSystemManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeatherSystemManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeatherSystemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EWeatherType AWeatherSystemManager::GetNextWeatherType()
{
	return NextWeatherType;
}

void AWeatherSystemManager::SetWeather()
{
	CurrentWeatherType = NextWeatherType;
}

void AWeatherSystemManager::SetNextWeather()
{
	int NextWeatherIndex = UKismetMathLibrary::RandomIntegerInRange(1,2);
	if (NextWeatherIndex == 1)
	{
		NextWeatherType = EWeatherType::Sunny;
	}
	else
	{
		NextWeatherType = EWeatherType::Rainy;
	}
}

