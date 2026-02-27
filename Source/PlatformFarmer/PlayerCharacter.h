#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "Enums.h"
#include "Plant.h"
#include "Bed.h"
#include "DayNightCycleManager.h"
#include "PlayerHUDWidget.h"

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

#include "Engine/Texture2D.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SwitchToolsAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SwitchSeedsAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UseToolAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileMap")
	UPaperTileMap* TileMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileMap")
	UPaperTileSet* GroundTileSet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileMap")
	UPaperTileSet* WaterTileSet;
	UPROPERTY(EditAnywhere, Category = "TileMap")
	APaperTileMapActor* TileMapActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UPlayerHUDWidget* PlayerHUDWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	ETools CurrentTool = ETools::Axe;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	ESeeds CurrentSeed = ESeeds::Carrot;

	UPROPERTY(EditDefaultsOnly, Category = "Plants")
	TMap<ESeeds, TSubclassOf<APlant>> PlantClasses;
	TMap<FIntPoint, APlant*> PlantedTiles;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequences")
	UPaperZDAnimSequence* AxeAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequences")
	UPaperZDAnimSequence* HoeAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequences")
	UPaperZDAnimSequence* UseAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequences")
	UPaperZDAnimSequence* SwordAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequences")
	UPaperZDAnimSequence* WaterAnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icons")
	TMap<ETools, UTexture2D*> ToolIcons;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icons")
	TMap<ESeeds, UTexture2D*> SeedIcons;

	bool IsAlive = true;
	bool CanMove = true;
	bool CanUse = true;

	FZDOnAnimationOverrideEndSignature OnUseOverrideEndDelegate;
	FRotator CurrentRotation;
	ABed* Bed;
	ADayNightCycleManager* DayNightCycleManager;

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
	void Use(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnUseOverrideAnimEnd(bool Completed);
	FVector2D GetTile();
	void UseHoe();
	void UseWater();
	void UseSeed();
	void ChangeTile(int32 X, int32 Y, UPaperTileSet* CorrectTileSet, int32 NewTileIndex, int32 LayerIndex);
};
