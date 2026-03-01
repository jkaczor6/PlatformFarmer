#include "PlayerHUDWidget.h"

void UPlayerHUDWidget::SetCurrentToolIcon(UTexture2D* ToolIcon)
{
	CurrentToolIcon->SetBrushFromTexture(ToolIcon, true);
}

void UPlayerHUDWidget::SetCurrentSeedIcon(UTexture2D* SeedIcon)
{
	CurrentSeedIcon->SetBrushFromTexture(SeedIcon, true);
}

void UPlayerHUDWidget::SetMaterialCount(EItems item, int32 Amount)
{
	int32 NewCount = Amount;
	FString Str = FString::Printf(TEXT("%d"), NewCount);
	switch (item)
	{
		case EItems::Carrot:
			CarrotCountText->SetText(FText::FromString(Str));
		case EItems::Pumpkin:
			PumpkinCountText->SetText(FText::FromString(Str));
		case EItems::Tomato:
			TomatoCountText->SetText(FText::FromString(Str));
		case EItems::Wheat:
			WheatCountText->SetText(FText::FromString(Str));
		case EItems::Wood:
			WoodCountText->SetText(FText::FromString(Str));
	}
}
