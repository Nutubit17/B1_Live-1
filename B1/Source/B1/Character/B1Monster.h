// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/B1CharacterBase.h"
#include "B1Monster.generated.h"

/**
 * 
 */
UCLASS()
class B1_API AB1Monster : public AB1CharacterBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AB1Monster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
