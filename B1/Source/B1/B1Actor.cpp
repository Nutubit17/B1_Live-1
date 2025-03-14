// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Actor.h"
#include "B1Object.h"

// Sets default values
AB1Actor::AB1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetRelativeScale3D(FVector(4.0f, 1.0f, 0.5f));

	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(RootComponent);
	Head->SetRelativeLocation(FVector(150.0f, 0.0f, 0.0f));
	Head->SetRelativeScale3D(FVector(0.1875f, 0.5f, 0.5f));

	Wing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing"));
	Wing->SetupAttachment(RootComponent);
	Wing->SetRelativeLocation(FVector(17.5f, 0.0f, 0.0f));
	Wing->SetRelativeScale3D(FVector(0.25f, 3.5f, 0.5f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> FindMeshRef(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));

	if (FindMeshRef.Succeeded())
	{
		Box->SetStaticMesh(FindMeshRef.Object);
		Head->SetStaticMesh(FindMeshRef.Object);
		Wing->SetStaticMesh(FindMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void AB1Actor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AB1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Speed = 50.0f;
	float Distance = Speed * DeltaTime;

	FVector Location = GetActorLocation();
	FVector NewLocation = Location + FVector::ForwardVector * Distance;
	//SetActorLocation(NewLocation);

	AddActorWorldOffset(FVector::ForwardVector * Distance);

	float RotationRate = 45.0f;
	FRotator Rotation = GetActorRotation();
	FRotator NewRotation = FRotator(Rotation.Pitch, Rotation.Yaw + RotationRate * DeltaTime, Rotation.Roll);
	//SetActorRotation(NewRotation);

	AddActorWorldRotation(FRotator(0.0f, RotationRate * DeltaTime, 0.0f));
}

