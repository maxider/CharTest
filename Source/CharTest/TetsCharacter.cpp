// Fill out your copyright notice in the Description page of Project Settings.

#include "TetsCharacter.h"


// Sets default values
ATetsCharacter::ATetsCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Cam
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CamComponent"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);
	GunMesh->SetRelativeLocation(GunOffset);

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

	//Actor Rotation
	FRotator newYaw = GetActorRotation();
	newYaw.Yaw += MouseInput.X;
	SetActorRotation(newYaw);

	FRotator newPitch = Camera->GetComponentRotation();
	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + MouseInput.Y, -80.f, 80.f);
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

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ATetsCharacter::Shoot);

}

//Movement Functions
void ATetsCharacter::MoveForward(float axis) {
	AddMovementInput(GetActorForwardVector(), axis * Speed);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorForwardVector(), FColor::Red, false, 1.f, 0, 2.f);
}

void ATetsCharacter::MoveRight(float axis) {

	AddMovementInput(GetActorRightVector(), axis * Speed);
}

void ATetsCharacter::Turn(float axis) {
	MouseInput.X = axis;
}

void ATetsCharacter::Pitch(float axis) {
	MouseInput.Y = axis;
}

void ATetsCharacter::Shoot() {
	FVector StartTrace = Camera->GetForwardVector();
	FVector EndTrace = (StartTrace * 5000.f) + StartTrace;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 3.f, 0, 1.f);

	/*
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, *CQP)) {
		DrawDebugLine(GetWorld(), StartTrace,EndTrace,FColor(255,0,0),true))

		if (HitResult->GetActor() != NULL) {
			HitResult->GetActor()->Destroy();
		}

	}
	*/
}
