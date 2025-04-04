// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/B1AttackInterface.h"
#include "B1CharacterBase.generated.h"

UCLASS()
class B1_API AB1CharacterBase : public ACharacter, public IB1AttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AB1CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

#pragma region Attack
public:
	virtual void ProcessAttack();
	virtual void ProcessComboAttack();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded);

	void SetComboCheckTimer();
	void ComboCheck();

	virtual void SetDead();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> ComboAttackMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UB1ComboActionData> ComboAttackData;

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboAttack = false;
#pragma endregion


public:
	// Inherited via IB1AttackInterface
	virtual void AttackHitCheck() override;
};
