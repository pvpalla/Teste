// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "MyChar.h"
#include "Gun.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,
		&AAmmo::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	Amount = FMath::FRandRange(20, 40);
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmo::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyChar::StaticClass())) {

		AMyChar* Char = Cast<AMyChar>(OtherActor);


		for (int i = 0; i < Char->GetGuns().Num(); i++) {
			if (Char->GetGuns()[i]->IsA(AmmoType)) {
				Char->GetGuns()[i]->SetAmmoAmount(Char->GetGuns()[i]->GetAmmoAmount() + Amount);
				Destroy();
			}
		}

		/*if (Char->GetGun() != nullptr) {
			if (Char->GetGun()->IsA(AGun::StaticClass())) {
				
				AGun* Gun = Cast<AGun>(Char->GetGun());

				Gun->SetAmmoAmount(Gun->GetAmmoAmount() + Amount);
				UE_LOG(LogTemp, Warning, TEXT("Add: %d"), Amount);
				Destroy();
			}
		}
		*/
		//if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		//	APersonagem* Personagem = Cast<APersonagem>(OtherActor);
			
		//}
		/*
		/\Verificar nulidade, verificar se existem atores filhos, 
		verificar se o ator filho (se existir) é um AGun::StaticClass;

		\/Errado
		
		if (Char->GetGun() != nullptr) {
			if (Char->GetGun()->IsA(AMyChar::StaticClass())) { <<Erro por verificar se o Char->GetGun() é um AMyChar (AGun);
				AGun* Gun = Cast<AGun>(Char->GetGun()->GetChildActor());
				
			}
		}*/
	}
}