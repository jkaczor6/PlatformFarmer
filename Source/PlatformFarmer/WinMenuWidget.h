#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"

#include "WinMenuWidget.generated.h"

UCLASS()
class PLATFORMFARMER_API UWinMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RestartGameButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitGameButton;
	
	void SetupWidget();
	UFUNCTION()
	void OnRestartGameButtonClicked();
	UFUNCTION()
	void OnQuitGameButtonClicked();
};
