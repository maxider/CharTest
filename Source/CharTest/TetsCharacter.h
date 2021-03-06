// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TetsCharacter.generated.h"

UCLASS()
class CHARTEST_API ATetsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATetsCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Gun")
		UStaticMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere, Category = "Gun")
		FVector GunOffset;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float SensX = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float SensY = 5.0f;

	
	
	FVector2D MouseInput;

	
	UFUNCTION()
		void MoveForward(float axis);
	UFUNCTION()
		void MoveRight(float axis);
	UFUNCTION()
		void Turn(float axis);
	UFUNCTION()
		void Pitch(float axis);
	UFUNCTION()
		void Shoot();
};
