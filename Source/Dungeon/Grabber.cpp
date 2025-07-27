// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("GrabObjects called but no PhysicsHandleComponent found!"));
		return;
	}
}


void UGrabber::GrabObjects()
{
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("GrabObjects called but no PhysicsHandleComponent found!"));
		return;
	}
	
	FVector Start = GetComponentLocation();
	FVector End = GetComponentLocation() + GetForwardVector() * 300;

	FCollisionShape GrabShape = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, GrabShape);
	if (!HasHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("GrabObjects: No object hit within the grab radius."));
		return;
	}
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	HitComponent->WakeAllRigidBodies();
	HitComponent->SetSimulatePhysics(true);
	HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, GetComponentLocation() + GetForwardVector() * GrabedObjectDistance, GetComponentRotation());
	HitResult.GetActor()->Tags.Add(TEXT("Grabbed"));
	
}

void UGrabber::ReleaseObjects()
{
	if (!PhysicsHandle || !PhysicsHandle->GrabbedComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReleaseObjects called but no object is currently grabbed!"));
		return;
	}

	AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
	GrabbedActor->Tags.Remove(TEXT("Grabbed"));
	PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocationAndRotation(GetComponentLocation() + GetForwardVector() * GrabedObjectDistance, GetComponentRotation());
	}
}

