// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "PistolBullet.generated.h"

/**
 * 
 */
UCLASS()
class TESTE1_API APistolBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	
};
