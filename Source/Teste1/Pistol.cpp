// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistol.h"


void APistol::BeginPlay() {
	Super::BeginPlay();

	TimeCount = 2.0f;
	AmmoAmount = 6;
}

