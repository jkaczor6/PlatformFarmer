#include "ShopHUD.h"

void UShopHUD::SetupWidget(EShopType Type, FString Name, TMap<EItems, int32> Price, EShopItem Reward)
{
	FString ShopItemName = FString::Printf(TEXT("%s"), *Name);
	ItemName->SetText(FText::FromString(ShopItemName));
	
	ExitButton->OnClicked.Clear();
	ExitButton->OnClicked.AddDynamic(this, &UShopHUD::ExitShop);
}

void UShopHUD::ExitShop()
{
	OnShopExitDelegate.Broadcast();
	RemoveFromParent();
}
