#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enums.h"

#include "WeatherSystemManager.generated.h"

UCLASS()
class PLATFORMFARMER_API AWeatherSystemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeatherSystemManager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	EWeatherType GetNextWeatherType();
	void SetWeather();
	void SetNextWeather();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EWeatherType NextWeatherType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EWeatherType CurrentWeatherType;
};
