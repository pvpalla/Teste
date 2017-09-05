// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TESTE1_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int AmmoAmount;

	UPROPERTY(EditAnywhere)
		float TimeCount;

	void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartFire();

	virtual void StopFire();

	void SetAmmoAmount(int NewAmmo);

	int GetAmmoAmount();
	
	class UBoxComponent* GetCollisionComp();


private:


	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> BulletBP;

	FTimerHandle ShootDelay;



	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
