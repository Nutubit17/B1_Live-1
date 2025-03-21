// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "B1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UB1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UB1AnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
