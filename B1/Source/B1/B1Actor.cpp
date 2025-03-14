// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Actor.h"
#include "B1Object.h"

// Sets default values
AB1Actor::AB1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AB1Actor::BeginPlay()
{
	Super::BeginPlay();
	
	Obj = NewObject<UB1Object>();

	GEngine->ForceGarbageCollection(true);
}

// Called every frame
void AB1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Obj == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Obj Deleted!"));
	}
}

