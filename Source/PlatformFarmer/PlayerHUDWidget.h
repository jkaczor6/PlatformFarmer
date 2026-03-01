#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Enums.h"

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
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CarrotCountText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PumpkinCountText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TomatoCountText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* WheatCountText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* WoodCountText;

	void SetCurrentToolIcon(UTexture2D* ToolIcon);
	void SetCurrentSeedIcon(UTexture2D* SeedIcon);
	void SetMaterialCount(EItems item, int32 Amount);
};
