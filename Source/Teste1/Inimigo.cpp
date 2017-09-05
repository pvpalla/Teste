// Fill out your copyright notice in the Description page of Project Settings.

#include "Inimigo.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "MyChar.h"


// Sets default values
AInimigo::AInimigo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AInimigo::BeginPlay()
{
	Super::BeginPlay();
	
}

UPaperFlipbookComponent * AInimigo::GetFlipbookComp()
{
	return Flipbook;
}

void AInimigo::SetFlipbookComp(UPaperFlipbookComponent* FlipComp)
{
	Flipbook = FlipComp;
}

// Called every frame
void AInimigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInimigo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

