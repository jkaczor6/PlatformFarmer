#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enums.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "ShopHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopExit);

UCLASS()
class PLATFORMFARMER_API UShopHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* PurchaseButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Item1Icon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Item2Icon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Item3Icon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Item1Amount;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Item2Amount;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Item3Amount;
	
	FOnShopExit OnShopExitDelegate;
	EShopItem PurchaseItem;
	TArray<int32> ItemPrices;
	TArray<EItems> ItemsEnums;
	
	void SetupWidget(EShopType Type, FString Name, TArray<int32> Prices, TArray<UTexture2D*> Sprites, EShopItem Reward, TArray<EItems> Items);
	UFUNCTION()
	void ExitShop();
	UFUNCTION()
	void Purchase();
};
