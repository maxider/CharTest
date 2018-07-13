// Fill out your copyright notice in the Description page of Project Settings.

#include "TetsCharacter.h"


// Sets default values
ATetsCharacter::ATetsCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("CamComponent"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATetsCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATetsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Acto Rotatoin
	FRotator newYaw = GetActorRotation();
	FRotator newPitch = Camera->GetComponentRotation();
	newYaw.Yaw += MouseInput.X;
	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + MouseInput.Y, -80.f, 80.f);
	SetActorRotation(newYaw);
	Camera->SetWorldRotation(newPitch);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("newRoation Yaw: %f"), newRotation.Pitch));
}

// Called to bind functionality to input
void ATetsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATetsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATetsCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ATetsCharacter::Turn);
	PlayerInputComponent->BindAxis("Pitch", this, &ATetsCharacter::Pitch);

}

void ATetsCharacter::MoveForward(float axis) {
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0;

	FVector ForwardVector = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(ForwardVector, axis * Speed);
}

void ATetsCharacter::MoveRight(float axis) {
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0;

	FVector RightVector = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, axis * Speed);
}

void ATetsCharacter::Turn(float axis) {
	 MouseInput.X = -axis * SensX;
}

void ATetsCharacter::Pitch(float axis) {
	MouseInput.Y = axis * SensY;
}

