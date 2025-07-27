// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

void UTriggerComponent::AddMover(UMoveActor* InMoveActor)
{
	if (InMoveActor == nullptr)
	{
		return;
	}
	MoveActors.AddUnique(InMoveActor);
}

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappedActors;
	GetOverlappingActors(OverlappedActors);
	for (AActor* OverlappedActor : OverlappedActors)
	{
		if (OverlappedActor != nullptr && OverlappedActor->ActorHasTag(UnlockTag) && !OverlappedActor->ActorHasTag(TEXT("Grabbed")))
		{
			bIsTriggered = true;
			break;
		}
	}

	
	for (const auto& MoveActorPtr : MoveActors)
	{
		if (MoveActorPtr.IsValid())
		{
			MoveActorPtr->SetShouldMove(bIsTriggered);

			if (bIsTriggered)
			{
				AActor* Actor = MoveActorPtr->GetOwner();
				UPrimitiveComponent* PrimitiveComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
				if (PrimitiveComponent)
				{
					PrimitiveComponent->SetSimulatePhysics(false);
					PrimitiveComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
				}
			}
		}
	}
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
	
}





