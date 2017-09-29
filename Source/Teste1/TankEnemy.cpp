// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "PaperFlipbookComponent.h"
#include "MyChar.h"
#include "Components/BoxComponent.h"


ATankEnemy::ATankEnemy() {
	Direction = 1;

	

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("BlockAllDynamic");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATankEnemy::OnHit);
	RootComponent = CollisionComp;

	GetFlipbookComp()->SetupAttachment(CollisionComp);
}

void ATankEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(IdleTime, this, &ATankEnemy::IdleChar, 4, true);

}

void ATankEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Idle) {
		Move();
	}
}

void ATankEnemy::Move()
{
	FVector ActualLocation = GetActorLocation();
	ActualLocation.X += (1.0f*Direction);
	SetActorLocation(ActualLocation);
	if (ActualLocation.X >= InitialLocation.X + 100.0f ||
		ActualLocation.X <= InitialLocation.X - 100.0f) {
		Direction *= -1.0f;

		if (Direction > 0) {
			GetFlipbookComp()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
		else {
			GetFlipbookComp()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
	}
}

void ATankEnemy::IdleChar() {
	if (Idle) {
		GetFlipbookComp()->SetFlipbook(WalkingFlipbook);
	}
	else {
		GetFlipbookComp()->SetFlipbook(IdleFlipbook);
	}

	Idle = !Idle;
}

void ATankEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor != nullptr && OtherActor->IsA(AMyChar::StaticClass())) {

		AMyChar* Char = Cast<AMyChar>(OtherActor);

		Char->TakeHit();

		

	}
}