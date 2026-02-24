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