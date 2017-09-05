// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "PaperSpriteComponent.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "MyChar.h"
#include "Components/BoxComponent.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGun::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->SetupAttachment(RootComponent);
	TimeCount = 0.07f;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	AmmoAmount = 200;

	GetWorldTimerManager().SetTimer(ShootDelay, this, &AGun::Shoot, TimeCount, true);
	
	GetWorldTimerManager().PauseTimer(ShootDelay);
	

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("START FIRE"));
	Shoot();
	GetWorldTimerManager().UnPauseTimer(ShootDelay);

}

void AGun::StopFire()
{
	GetWorldTimerManager().PauseTimer(ShootDelay);

}

void AGun::SetAmmoAmount(int NewAmmo)
{
	AmmoAmount = NewAmmo;
}

int AGun::GetAmmoAmount()
{
	return AmmoAmount;
}

void AGun::Shoot()
{
	if (AmmoAmount > 0) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FActorSpawnParameters SpawnParameters;
			ABullet* Bullet = World->SpawnActor<ABullet>(BulletBP, RootComponent->GetComponentLocation(),
				RootComponent->GetComponentRotation(), SpawnParameters);
			UE_LOG(LogTemp, Warning, TEXT("DO FIRE"));
			AmmoAmount--;
		}
	}
}


void AGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("YEP2"));
	if (OtherActor != nullptr && OtherActor->IsA(AMyChar::StaticClass())) {
		AMyChar* Personagem = Cast<AMyChar>(OtherActor);
		Personagem->AddGunToArray(this);
		UE_LOG(LogTemp, Warning, TEXT("YEP"));
	}

}


UBoxComponent* AGun::GetCollisionComp() {
	return CollisionComp;
}