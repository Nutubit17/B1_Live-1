// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B1Actor.generated.h"

UCLASS()
class B1_API AB1Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AB1Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class UB1Object* Obj;

	UPROPERTY(VisibleAnywhere)
	int32 Hp = 100;

	UPROPERTY(EditAnywhere)
	int32 Mp = 50;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 3.5f;
};
