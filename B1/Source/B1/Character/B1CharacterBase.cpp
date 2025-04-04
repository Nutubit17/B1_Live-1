// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/B1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "B1ComboActionData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AB1CharacterBase::AB1CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Forge.SK_CharM_Forge'"));

	if (FindMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FindMeshRef.Object);
	}

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ABP_Player.ABP_Player_C'"));
	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	// Attack Montage 
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Attack.AM_Attack'"));
	if (AttackMontageRef.Succeeded())
	{
		AttackMontage = AttackMontageRef.Object;
	}

	// ComboAttack Montage 
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboAttackMontageRef.Succeeded())
	{
		ComboAttackMontage = ComboAttackMontageRef.Object;
	}

	// Dead Montage 
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Succeeded())
	{
		DeadMontage = DeadMontageRef.Object;
	}

	// ComboAttack Data
	static ConstructorHelpers::FObjectFinder<UB1ComboActionData> ComboActionDataRef(TEXT("/Script/B1.B1ComboActionData'/Game/CharacterAction/DA_ComboAttack.DA_ComboAttack'"));
	if (ComboActionDataRef.Succeeded())
	{
		ComboAttackData = ComboActionDataRef.Object;
	}
}

// Called when the game starts or when spawned
void AB1CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AB1CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AB1CharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return DamageAmount;
}

void AB1CharacterBase::ProcessAttack()
{
	if (GetCurrentMontage() == AttackMontage)
		return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		int32 Index = FMath::RandRange(1, 4);
		FString SectionName = FString::Printf(TEXT("Attack%d"), Index);
		AnimInstance->Montage_Play(AttackMontage, 1.0f);
		AnimInstance->Montage_JumpToSection(FName(*SectionName));

		//PlayAnimMontage(AttackMontage, 1.0f, FName(*SectionName));
	}
}

void AB1CharacterBase::ProcessComboAttack()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (ComboTimerHandle.IsValid())
	{
		HasNextComboAttack = true;
	}
	else
	{
		HasNextComboAttack = false;
	}
}

void AB1CharacterBase::ComboActionBegin()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	// Animation Setting
	CurrentCombo = 1;
	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
		return;
	
	// Montage Play -> ComboAttack1
	AnimInstance->Montage_Play(ComboAttackMontage, AttackSpeedRate);

	// Montage End Delegate
	FOnMontageEnded EndDelegete;
	EndDelegete.BindUObject(this, &AB1CharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegete, ComboAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void AB1CharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropertyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	CurrentCombo = 0;
}

void AB1CharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboAttackData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (ComboAttackData->EffectiveFrameCount[ComboIndex] / ComboAttackData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AB1CharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void AB1CharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboAttack)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance == nullptr)
			return;

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboAttackData->MaxComboCount);

		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboAttackData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);

		SetComboCheckTimer();
		HasNextComboAttack = false;
	}
}

void AB1CharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(false);
		AnimInstance->Montage_Play(DeadMontage, 1.0f);
	}

	SetActorEnableCollision(false);
}

void AB1CharacterBase::AttackHitCheck()
{
	const float AttackRange = 120.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;

	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);

		//UGameplayStatics::ApplyDamage(OutHitResult.GetActor(), AttackDamage, GetController(), this, nullptr);
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}

