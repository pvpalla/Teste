// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "MyChar.h"
#include "Runtime/Engine/Public/TimerManager.h"


// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,
		&ABomb::OnOverlapBegin);
	RootComponent = CollisionComp;

	ExplosionSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollectSphere"));
	ExplosionSphereComp->InitSphereRadius(200.0f);
	ExplosionSphereComp->SetupAttachment(RootComponent);

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->SetupAttachment(RootComponent);

	PlayerInside = false;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(AMyChar::StaticClass())) {
		//AMyChar* Personagem = Cast<AMyChar>(OtherActor);

		GetWorldTimerManager().SetTimer(XPlosionDelay, this, &ABomb::Explode, 2.0f, true); 
		UE_LOG(LogTemp, Warning, TEXT("Hit"));

	}
}


void ABomb::Explode() {

	TArray<AActor*> AtoresIn;
	ExplosionSphereComp->GetOverlappingActors(AtoresIn);

	for (int i = 0; i < AtoresIn.Num(); i++) {
		if (AtoresIn[i]->IsA(AMyChar::StaticClass())) {
			AMyChar* Personagem = Cast<AMyChar>(AtoresIn[i]);
			Personagem->TakeHit();


			UE_LOG(LogTemp, Warning, TEXT("Life: %d"), Personagem->GetLife());
			
		}
	}
	Destroy();
}