// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "B1PlayerController.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class B1_API AB1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AB1PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Input_Attack(const FInputActionValue& InputValue);
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_StopJump(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;
};
