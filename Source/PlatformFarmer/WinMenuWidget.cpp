#include "WinMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UWinMenuWidget::SetupWidget()
{
	RestartGameButton->OnClicked.AddDynamic(this, &UWinMenuWidget::OnRestartGameButtonClicked);
	
	QuitGameButton->OnClicked.AddDynamic(this, &UWinMenuWidget::OnQuitGameButtonClicked);
}

void UWinMenuWidget::OnRestartGameButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MAP_Main"));
	
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PlayerController->SetShowMouseCursor(false);
		
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
	}
}

void UWinMenuWidget::OnQuitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}
