#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"

#include "PlayerHUDWidget.generated.h"

UCLASS()
class PLATFORMFARMER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* CurrentToolIcon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* CurrentSeedIcon;
	

	void SetCurrentToolIcon(UTexture2D* ToolIcon);
	void SetCurrentSeedIcon(UTexture2D* SeedIcon);
};
