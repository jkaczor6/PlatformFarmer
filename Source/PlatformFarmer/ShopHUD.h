#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enums.h"
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
	
	UPROPERTY(BlueprintAssignable)
	FOnShopExit OnShopExitDelegate;
	
	void SetupWidget(EShopType Type, FString Name, TMap<EItems, int32> Price, EShopItem Reward);
	UFUNCTION()
	void ExitShop();
};
