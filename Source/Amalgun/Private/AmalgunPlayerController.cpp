// Fill out your copyright notice in the Description page of Project Settings.


#include "AmalgunPlayerController.h"
#include "WidgetUI/PauseMenu.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerInput.h"
//#include "Kismet/GameplayStatics.h"

void AAmalgunPlayerController::BeginPlay()
{
	Super::BeginPlay();

    PauseMenu = CreateWidget<UPauseMenu>(this, UPauseMenu::StaticClass());
    //FInputModeGameAndUI Mode;
    //Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
    //Mode.SetHideCursorDuringCapture(false);
    //SetInputMode(Mode);
    if (PauseMenu)
    {
        PauseMenu->AddToViewport(9999);
        PauseMenu->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AAmalgunPlayerController::TogglePauseMenu()
{
    AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
    if (!GameMode || !PauseMenu) return;

    PauseMenu->SetVisibility(PauseMenu->IsVisible() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

    SetPause(PauseMenu->IsVisible());
}

