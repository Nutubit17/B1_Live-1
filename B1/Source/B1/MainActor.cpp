// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "B1Actor.h"

// Sets default values
AMainActor::AMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AB1Actor> FindClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_B1Actor.BP_B1Actor_C'"));

	if (FindClassRef.Succeeded())
	{
		ActorClass = FindClassRef.Class;
	}
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	//B1Actor = GetWorld()->SpawnActor<AB1Actor>(Location, Rotation);

	B1Actor = Cast<AB1Actor>(GetWorld()->SpawnActor(ActorClass));

	if (B1Actor)
	{
		B1Actor->SetLifeSpan(5.0f);
	}

	//GetWorld()->DestroyActor(B1Actor);
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

