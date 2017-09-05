// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterEnemy.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "PaperFlipbookComponent.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "MyChar.h"
#include "Components/BoxComponent.h"


AShooterEnemy::AShooterEnemy() {
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AShooterEnemy::OnOverlapBegin);
	RootComponent = CollisionComp;

	GetFlipbookComp()->SetupAttachment(RootComponent);
}
void AShooterEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ShootTime, this, &AShooterEnemy::Shoot, 0.5f, true);
	GetWorldTimerManager().PauseTimer(ShootTime);
}

void AShooterEnemy::IdleChar() {
	if (Idle) {
		GetFlipbookComp()->SetFlipbook(ShootingFlipbook);
	}
	else {
		GetFlipbookComp()->SetFlipbook(IdleFlipbook);
	}

	Idle = !Idle;
}

void AShooterEnemy::Shoot()
{
	UWorld* World = GetWorld();
	if (World != nullptr) {
		FActorSpawnParameters SpawnParameters;
		ABullet* Bullet = World->SpawnActor<ABullet>(BulletBP, RootComponent->GetComponentLocation(),
			RootComponent->GetComponentRotation(), SpawnParameters);
		UE_LOG(LogTemp, Warning, TEXT("DO FIRE"));
	}
}

void AShooterEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(AMyChar::StaticClass())) {
		AMyChar* Char = Cast<AMyChar>(OtherActor);

		if ((((Char->GetActorLocation().X - GetActorLocation().X) >= -200) && ((Char->GetActorLocation().X - GetActorLocation().X) <= 200)) && 
			 (((Char->GetActorLocation().Y - GetActorLocation().Y) >= -200) && ((Char->GetActorLocation().Y - GetActorLocation().Y) <= 200))) 
		{

				GetWorldTimerManager().UnPauseTimer(ShootTime);
				if (Char->GetActorLocation().X > GetActorLocation().X) {
					SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
				}
				else {
					SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
				}
		}
		else {
			GetWorldTimerManager().UnPauseTimer(ShootTime);
		}
	}
}