// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inimigo.h"
#include "ShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TESTE1_API AShooterEnemy : public AInimigo
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;

public:

	AShooterEnemy();

private:

	UPROPERTY(EditAnywhere, Category = "Flipbook")
		class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
		class UPaperFlipbook* ShootingFlipbook;

	void IdleChar();

	bool Idle;

	FTimerHandle ShootTime;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> BulletBP;

	void Shoot();


	UPROPERTY(EditAnywhere, Category = "Collision")
		class UBoxComponent* CollisionComp;

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
