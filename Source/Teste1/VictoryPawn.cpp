// Fill out your copyright notice in the Description page of Project Settings.

#include "VictoryPawn.h"
#include "MyChar.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/World.h"

// Sets default values
AVictoryPawn::AVictoryPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AVictoryPawn::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AVictoryPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(true);

	UWorld* World = GetWorld();
	if (World) {

		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller) {
			APawn* Pawn = Controller->GetControlledPawn();
			if (Pawn) {
				if (Pawn->IsA(AMyChar::StaticClass())) {
					AMyChar* Char = Cast<AMyChar>(Pawn);
					if (Char) {
						MyCharacter = Char;
					}
				}
			}
		}

	}

	
}

// Called every frame
void AVictoryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyCharacter->GetCollected() >= 5) {
		SetActorHiddenInGame(false);
	}

}


void AVictoryPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(AMyChar::StaticClass())) {
		AMyChar* Char = Cast<AMyChar>(OtherActor);

		if (Char->GetCollected() >= 5) {
			UE_LOG(LogTemp, Warning, TEXT("YEY!"));
		}
	
	}
}

