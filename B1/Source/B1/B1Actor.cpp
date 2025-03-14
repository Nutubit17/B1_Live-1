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

	ConstructorHelpers::FObjectFinder<UStaticMesh> FindMeshRef(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));

	if (FindMeshRef.Succeeded())
	{
		Box->SetStaticMesh(FindMeshRef.Object);
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
}

