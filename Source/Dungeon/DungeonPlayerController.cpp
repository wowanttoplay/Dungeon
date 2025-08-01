// Copyright Epic Games, Inc. All Rights Reserved.


#include "DungeonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "DungeonCameraManager.h"

ADungeonPlayerController::ADungeonPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ADungeonCameraManager::StaticClass();
}

void ADungeonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
