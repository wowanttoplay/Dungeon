// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveActor.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEON_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FName UnlockTag;

public:
	UTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddMover(UMoveActor* InMoveActor);



	virtual void BeginPlay() override;


private:
	TArray<TWeakObjectPtr<UMoveActor>> MoveActors;
	bool bIsTriggered = false;
};
