// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MyChar.generated.h"


/**
 * 
 */
UCLASS()
class TESTE1_API AMyChar : public APaperCharacter
{
	GENERATED_BODY()
	
	
public:
	AMyChar();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class AGun* GetGun();

	TArray <class AGun*> GetGuns();

	void SetCollected(int NewCollected);

	int GetCollected();

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void StopFire();
	UFUNCTION(BlueprintCallable, Category = "TakeGun")
	void DropAndTake();
	UFUNCTION(BlueprintCallable, Category = "DropWeapon")
		void DropWeapon();

	void AddGunToArray(AGun * Gun);

	void SetLife(int NewLife);
	int GetLife();

	void TakeHit();

private:

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
		class UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere)
		class UPaperFlipbook* Walk;

	void Move(float Value);
	
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	int Collected;
	
	UPROPERTY(EditAnywhere)
		class UChildActorComponent* Gun;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDMobile;

	int GunInUse;

	TArray <class AGun*> Guns;

	int Life;

	float KnockBack;

	FVector InitialLocation;
	
};
