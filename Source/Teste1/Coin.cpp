// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "MyChar.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,
		&ACoin::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyChar::StaticClass())) {
		AMyChar* Char = Cast<AMyChar>(OtherActor);
		int Coins = Char->GetCollected();
		Char->SetCollected(Coins + 1);
	
		UE_LOG(LogTemp, Warning, TEXT("Collected: %d"), Char->GetCollected());
		Destroy();
	}
}

