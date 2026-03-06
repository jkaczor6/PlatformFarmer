#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Slime.generated.h"

UCLASS()
class PLATFORMFARMER_API ASlime : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	ASlime();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void UpdateDirection();
	void CheckLedge();
	void Die();
	void Respawn();

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* WallDetector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* LedgeDetector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* PlayerChecker;

	UCapsuleComponent* CapsuleComp;
	UPaperFlipbookComponent* Flipbook;
	
	bool IsAlive = true;

};
