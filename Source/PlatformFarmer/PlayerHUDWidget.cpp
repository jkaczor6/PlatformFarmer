#include "PlayerHUDWidget.h"

void UPlayerHUDWidget::SetCurrentToolIcon(UTexture2D* ToolIcon)
{
	CurrentToolIcon->SetBrushFromTexture(ToolIcon, true);
}

void UPlayerHUDWidget::SetCurrentSeedIcon(UTexture2D* SeedIcon)
{
	CurrentSeedIcon->SetBrushFromTexture(SeedIcon, true);
}