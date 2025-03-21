// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/B1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AB1Player::AB1Player()
{
	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void AB1Player::BeginPlay()
{
	Super::BeginPlay();
}

void AB1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AB1Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
