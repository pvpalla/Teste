// Fill out your copyright notice in the Description page of Project Settings.

#include "Sniper.h"




void ASniper::BeginPlay() {
	Super::BeginPlay();

	TimeCount = 2.0f;
	AmmoAmount = 6;
}


void ASniper::StartFire() {
	Shoot();
}