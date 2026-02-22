#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "Components/BoxComponent.h"

#include "Kismet/GameplayStatics.h"

#include "PaperZDAnimInstance.h"

#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class Tools : uint8
{
	Axe,
	Hoe,
	Seeds,
	Sword,
	Water,
	COUNT
};
UENUM(BlueprintType)
enum class Seeds : uint8
{
	Carrot,
	Pumpkin,
	Tomato,
	Wheat,
	COUNT
};


UCLASS()
class PLATFORMFARMER_API APlayerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* HitBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* SwitchToolsAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* SwitchSeedsAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* UseToolAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	Tools CurrentTool = Tools::Axe;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	Seeds CurrentSeed = Seeds::Carrot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* AxeAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* UseAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* SwordAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequence;

	bool IsAlive = true;
	bool CanMove = true;
	bool CanUse = true;

	FZDOnAnimationOverrideEndSignature OnUseOverrideEndDelegate;

	APlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void UpdateDirection(float MoveDirection);
	void Move(const FInputActionValue& Value);
	void JumpStarted(const FInputActionValue& Value);
	void JumpEnded(const FInputActionValue& Value);
	void SwitchTools(const FInputActionValue& Value);
	void SwitchSeeds(const FInputActionValue& Value);
	void UseTool(const FInputActionValue& Value);
	void Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnUseOverrideAnimEnd(bool Completed);
};
