// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMoveActor::UMoveActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveActor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OriginLocation = GetOwner()->GetActorLocation();
	DestinationLocation = OriginLocation + MoveOffset;
	ElapsedTime = 0.0f;
	MoveSpeed = MoveOffset.Length() / MoveTime;
}


// Called every frame
void UMoveActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		// 向终点移动
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= MoveTime)
		{
			ElapsedTime = MoveTime;
		}
	}
	else
	{
		// 向起点移动
		ElapsedTime -= DeltaTime;
		if (ElapsedTime <= 0.0f)
		{
			ElapsedTime = 0.0f;
		}
	}

	float Alpha = FMath::Clamp(ElapsedTime / MoveTime, 0.0f, 1.0f);
	FVector NewLocation = FMath::Lerp(OriginLocation, DestinationLocation, Alpha);
	GetOwner()->SetActorLocation(NewLocation);
}

void UMoveActor::SetShouldMove(bool bMove)
{
	ShouldMove = bMove;

	UPrimitiveComponent* PrimitiveComponent =GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if (PrimitiveComponent)
	{
		PrimitiveComponent->WakeAllRigidBodies();
	}
}
