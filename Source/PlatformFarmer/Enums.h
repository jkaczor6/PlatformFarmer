#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class ETools : uint8
{
	Axe,
	Hoe,
	Seeds,
	Sword,
	Water,
	COUNT
};

UENUM(BlueprintType)
enum class ESeeds : uint8
{
	Carrot,
	Pumpkin,
	Tomato,
	Wheat,
	COUNT
};

UENUM(BlueprintType)
enum class EItems : uint8
{
	Carrot,
	Pumpkin,
	Tomato,
	Wheat,
	Wood
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	Sunny,
	Rainy,
	COUNT
};

UENUM(BlueprintType)
enum class EShopType: uint8
{
	Upgrade,
	Key
};

UENUM(BlueprintType)
enum class EShopItem: uint8
{
	DoubleJumpUpgrade,
	DoorKey
};