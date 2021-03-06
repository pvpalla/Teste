// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBullet.h"
#include "MyChar.h"



void AEnemyBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor != nullptr && OtherActor->IsA(AMyChar::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Destroy"));
		AMyChar* Char = Cast<AMyChar>(OtherActor);

		Char->TakeHit();
		Destroy();
	}
}

