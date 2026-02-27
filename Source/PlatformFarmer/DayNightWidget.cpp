#include "DayNightWidget.h"

void UDayNightWidget::SetHourText(int NewHour)
{
	FString Str = FString::Printf(TEXT("%d"), NewHour);
	HourText->SetText(FText::FromString(Str));
}
