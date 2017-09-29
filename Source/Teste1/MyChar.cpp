// Fill out your copyright notice in the Description page of Project Settings.

#include "MyChar.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ChildActorComponent.h"
#include "Gun.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"


AMyChar::AMyChar() {
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComp->OrthoWidth = 800.0f;
	CameraComp->SetupAttachment(CameraBoom);

	GunInUse = -1;

	Life = 3;
/*
	UClass* Pis = StaticLoadClass(AGun::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/PistolBP.PistolBP_C' "));
	if (Pis) {
		if (Pis->IsChildOf(AGun::StaticClass())) {
			AGun* AddGun = Cast<AGun>(Pis);
			Guns.Add(AddGun);
		}
	}

	UClass* Snip = StaticLoadClass(AGun::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/SniperBP.SniperBP_C' "));
	if (Snip) {
		if (Snip->IsChildOf(AGun::StaticClass())) {
			AGun* AddGun = Cast<AGun>(Snip);
			Guns.Add(AddGun);
		}
	}
	

*/

//	Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("Gun"));
//	Gun->SetupAttachment(GetSprite());
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyChar::BeginPlay() {
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	Life = 3;
	/*
	UClass* Pis = StaticLoadClass(AGun::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/PistolBP.PistolBP_C' "));
	UClass* Snip = StaticLoadClass(AGun::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/SniperBP.SniperBP_C' "));
	UWorld* World = GetWorld();

	if (World != nullptr) {
		FActorSpawnParameters SpawnParameters;
			Guns[0] = World->SpawnActor<AGun>(Pis, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation(), SpawnParameters);
			Guns[1] = World->SpawnActor<AGun>(Snip, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation(), SpawnParameters);
	}

	FAttachmentTransformRules TR(EAttachmentRule::KeepWorld, true);
	for (int i = 0; i < Guns.Num(); i++) {
		if (Guns[i] != nullptr) {
			Guns[i]->AttachToComponent(GetSprite(), TR);
			if (i != 0) {
				Guns[i]->SetActorHiddenInGame(true);
			}
		}
	}
	*/
	if (Idle) {
		GetSprite()->SetFlipbook(Idle);
	}
	if (HUDMobile != NULL) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
			if (Controller != nullptr) {
				UUserWidget* UserWidget = UWidgetBlueprintLibrary::Create(World, HUDMobile, Controller);
				if (UserWidget != nullptr) {
					UserWidget->AddToViewport();
				}
			}
		}
	}
}

void AMyChar::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &AMyChar::Move);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyChar::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyChar::TouchStopped);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyChar::StartFire);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyChar::StopFire);
	PlayerInputComponent->BindAction("Drop/Take", IE_Pressed, this, &AMyChar::DropAndTake);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &AMyChar::DropWeapon);

}

AGun* AMyChar::GetGun()
{
	return Guns[GunInUse];
}

TArray<class AGun*> AMyChar::GetGuns()
{
	return Guns;
}

void AMyChar::SetCollected(int NewCollected)
{
	Collected = NewCollected;

}

int AMyChar::GetCollected()
{
	return Collected;
}

void AMyChar::StartFire()
{

	UE_LOG(LogTemp, Warning, TEXT("%d"), Guns.Num());

	/*
	if (Gun != nullptr && Gun->GetChildActor() != nullptr) {
		if (Gun->GetChildActor()->IsA(AGun::StaticClass())) {
			AGun* MyGun = Cast<AGun>(Gun->GetChildActor());
			MyGun->StartFire();
		}
	}*/
	if (Guns.Num() > 0 && GunInUse >= 0) {
		Guns[GunInUse]->StartFire();
	}
}

void AMyChar::StopFire()
{
	/*if (Gun != nullptr && Gun->GetChildActor() != nullptr) {
		if (Gun->GetChildActor()->IsA(AGun::StaticClass())) {
			AGun* MyGun = Cast<AGun>(Gun->GetChildActor());
			MyGun->StopFire();
		}
	}*/
	if (Guns.Num() > 0 && GunInUse >= 0) {
		Guns[GunInUse]->StopFire();
	}
}

void AMyChar::Move(float Value) {
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);


	if (Value != 0) {
			GetSprite()->SetFlipbook(Walk);
		if (Value < 0) {
			GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else {
			GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
		}

	}
	else {
			GetSprite()->SetFlipbook(Idle);
	}
}

void AMyChar::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Jump();
}

void AMyChar::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AMyChar::DropAndTake()
{
	if (GunInUse == Guns.Num() - 1) {
		GunInUse = -1;
	}
	else {
		GunInUse++;
	}

	if (GunInUse >= 0) {
		Guns[GunInUse]->SetActorHiddenInGame(false);
		if (GunInUse > 0) {
			Guns[GunInUse - 1]->SetActorHiddenInGame(true);
		}
	}
	else if (Guns.Num() > 0) {
		Guns[Guns.Num() - 1]->SetActorHiddenInGame(true);
	}

	/*if (!Guns[GunInUse]->IsTaken()) {
		for (int i = 0; i < Guns.Num(); i++) {
			int Aux = GunInUse + i;

			if (Aux >= Guns.Num()) {
				Aux = Aux - Guns.Num();
			}
			GunInUse = Aux;
			if (GunInUse == Guns.Num() - 1) {
				Aux = -1;
				GunInUse = -1;
			}
			if (GunInUse != -1) {
				if (Guns[GunInUse]->IsTaken()) {
					break;
				}
			}
			else {
				break;
			}
		}
	}*/
	/*if (Gun != nullptr) {
		if (Gun->GetChildActor() == nullptr) {
			Gun->CreateChildActor();
		}
		else {
			Gun->DestroyChildActor();
		}
	}*/


}


void AMyChar::AddGunToArray(AGun * Gun)
{
	Gun->SetActorRelativeRotation(GetActorRotation());
	Guns.Add(Gun);
	Gun->GetCollisionComp()->SetCollisionProfileName("NoCollision");
	FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, true);
	Gun->AttachToComponent(GetSprite(), TransformRules);
	Gun->SetActorRelativeLocation(FVector(10.0f, 0.0f, 5.0f));
	Gun->SetActorRelativeRotation(GetSprite()->GetComponentRotation());
	int LastSelected = GunInUse;
	GunInUse = Guns.Num() - 1;
	if (LastSelected >= 0) {
		Guns[LastSelected]->SetActorHiddenInGame(true);
	}
}

void AMyChar::SetLife(int NewLife)
{
	Life = NewLife;
}

int AMyChar::GetLife()
{
	return Life;
}

void AMyChar::TakeHit() {

	UE_LOG(LogTemp, Warning, TEXT("%d"), Life);

	Life = Life - 1;

	if (Life <= 0) {
		Life = 3;
		SetActorLocation(InitialLocation);
	}

}


void AMyChar::DropWeapon() {
	if (GunInUse >= 0) {
		Guns[GunInUse]->Destroy();
		GunInUse = -1;
	}
}