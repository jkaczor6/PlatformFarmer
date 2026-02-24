#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "Enums.h"
#include "Plant.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "Components/BoxComponent.h"
#include "PaperTileMap.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileLayer.h"
#include "PaperTileSet.h"

#include "Kismet/GameplayStatics.h"

#include "PaperZDAnimInstance.h"

#include "PlayerCharacter.generated.h"

#define ECC_Tree ECC_GameTraceChannel1

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperTileMap* TileMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperTileSet* GroundTileSet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperTileSet* WaterTileSet;

	UPROPERTY(EditAnywhere)
	APaperTileMapActor* TileMapActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ETools CurrentTool = ETools::Axe;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESeeds CurrentSeed = ESeeds::Carrot;

	UPROPERTY(EditDefaultsOnly)
	TMap<ESeeds, TSubclassOf<APlant>> PlantClasses;
	TMap<FIntPoint, APlant*> PlantedTiles;

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
	FRotator CurrentRotation;

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

	UFUNCTION()
	void Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnUseOverrideAnimEnd(bool Completed);
	FVector2D GetTile();
	void UseHoe();
	void UseWater();
	void UseSeed();
	void ChangeTile(int32 X, int32 Y, UPaperTileSet* CorrectTileSet, int32 NewTileIndex, int32 LayerIndex);
};
