#include "ShopHUD.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UShopHUD::SetupWidget(EShopType Type, FString Name, TArray<int32> Prices, TArray<UTexture2D*> Sprites, EShopItem Reward, TArray<EItems> Items)
{
	
	FString ShopItemName = FString::Printf(TEXT("%s"), *Name);
	
	FString Price1 = FString::Printf(TEXT("%d"), Prices[0]);
	FString Price2 = FString::Printf(TEXT("%d"), Prices[1]);
	FString Price3 = FString::Printf(TEXT("%d"), Prices[2]);
	
	ItemName->SetText(FText::FromString(ShopItemName));
	
	Item1Amount->SetText(FText::FromString(Price1));
	Item2Amount->SetText(FText::FromString(Price2));
	Item3Amount->SetText(FText::FromString(Price3));
	
	Item1Icon->SetBrushFromTexture(Sprites[0], true);
	Item1Icon->SetDesiredSizeOverride(FVector2D(64.0f, 64.0f));
	Item2Icon->SetBrushFromTexture(Sprites[1], true);
	Item2Icon->SetDesiredSizeOverride(FVector2D(64.0f, 64.0f));
	Item3Icon->SetBrushFromTexture(Sprites[2], true);
	Item3Icon->SetDesiredSizeOverride(FVector2D(64.0f, 64.0f));
	
	PurchaseItem = Reward;
	ItemPrices = Prices;
	ItemsEnums = Items;
	
	ExitButton->OnClicked.Clear();
	ExitButton->OnClicked.AddDynamic(this, &UShopHUD::ExitShop);
	
	PurchaseButton->OnClicked.Clear();
	PurchaseButton->OnClicked.AddDynamic(this, &UShopHUD::Purchase);
}

void UShopHUD::ExitShop()
{
	OnShopExitDelegate.Broadcast();
	RemoveFromParent();
}

void UShopHUD::Purchase()
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (Player->Materials[ItemsEnums[0]] >= ItemPrices[0] && 
			Player->Materials[ItemsEnums[1]] >= ItemPrices[2] && 
			Player->Materials[ItemsEnums[2]] >= ItemPrices[2])
		{
			Player->RemoveFromEquipment(ItemsEnums[0], ItemPrices[0]);
			Player->RemoveFromEquipment(ItemsEnums[1], ItemPrices[1]);
			Player->RemoveFromEquipment(ItemsEnums[2], ItemPrices[2]);
			
			Player->AddPurchasedItem(PurchaseItem);
			
			ExitShop();
		}
	}
}
