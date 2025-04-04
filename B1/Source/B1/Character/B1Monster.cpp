// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/B1Monster.h"
#include "Components/CapsuleComponent.h"

AB1Monster::AB1Monster()
{
	// Capsule
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Monster"));

	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
}

void AB1Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AB1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AB1Monster::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
