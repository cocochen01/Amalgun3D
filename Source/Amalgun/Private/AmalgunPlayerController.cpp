// Fill out your copyright notice in the Description page of Project Settings.


#include "AmalgunPlayerController.h"
#include "WidgetUI/PauseMenu.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerInput.h"
#include "AmalgunGameInstance.h"
//#include "Kismet/GameplayStatics.h"

void AAmalgunPlayerController::BeginPlay()
{
	Super::BeginPlay();
    if (UGameInstance* GameInst = GetGameInstance())
    {
        UAmalgunGameInstance* AGameInstance = Cast<UAmalgunGameInstance>(GameInst);
        if (AGameInstance && AGameInstance->BP_PauseMenu)
        {
            PauseMenu = CreateWidget<UPauseMenu>(this, AGameInstance->BP_PauseMenu);
            if (PauseMenu)
            {
                PauseMenu->AddToViewport(9999);
                PauseMenu->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}

void AAmalgunPlayerController::TogglePauseMenu()
{
    AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
    if (!GameMode || !PauseMenu) return;

    const bool bIsMenuVisible = PauseMenu->IsVisible();
    PauseMenu->SetVisibility(bIsMenuVisible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

    SetPause(!bIsMenuVisible);

    if (bIsMenuVisible)
    {
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    }
    else
    {
        bShowMouseCursor = true;
        SetInputMode(FInputModeUIOnly());
        FVector2D ViewportSize;
        if (GEngine && GEngine->GameViewport) {
            GEngine->GameViewport->GetViewportSize(ViewportSize);
        }
        FVector2D MousePosition(ViewportSize.X / 2, ViewportSize.Y / 2);
        SetMouseLocation(MousePosition.X, MousePosition.Y);
        if (PauseMenu)
        {
            PauseMenu->SetKeyboardFocus();
        }
    }
}

