// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inimigo.h"
#include "TankEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TESTE1_API ATankEnemy : public AInimigo
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	ATankEnemy();

	virtual void Tick(float DeltaTime) override;
	
private:

	UPROPERTY(EditAnywhere, Category = "Flipbook")
		class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
		class UPaperFlipbook* WalkingFlipbook;
	
	void Move();

	void IdleChar();

	bool Idle;

	FTimerHandle IdleTime;
	
	int Direction;

	FVector InitialLocation;


	UPROPERTY(EditAnywhere, Category = "Collision")
		class UBoxComponent* CollisionComp;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
