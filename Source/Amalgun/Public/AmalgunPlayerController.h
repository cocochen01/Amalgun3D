// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AmalgunPlayerController.generated.h"

/**
 * 
 */
class UPauseMenu;

UCLASS()
class AMALGUN_API AAmalgunPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPauseMenu* PauseMenu;

public:
    void TogglePauseMenu();
};
