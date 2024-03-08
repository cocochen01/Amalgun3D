// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetUI/PauseMenu.h"
#include "AmalgunPlayerController.h"
//Components
#include "Components/Button.h"

void UPauseMenu::NativeConstruct()
{
    Super::NativeConstruct();
    bIsFocusable = true;

    if (SettingsButton)
    {
        SettingsButton->OnClicked.AddDynamic(this, &UPauseMenu::OnSettingsClicked);
    }

    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::OnMainMenuClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::OnQuitClicked);
    }
}

FReply UPauseMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Escape)
    {
        if (APlayerController* PlayerController = GetOwningPlayer())
        {
            if (AAmalgunPlayerController* APlayerController = Cast<AAmalgunPlayerController>(PlayerController))
            {
                APlayerController->TogglePauseMenu();
            }
        }
        return FReply::Handled();
    }

    return FReply::Unhandled();
}

void UPauseMenu::OnResumeClicked()
{
    // Implement resume functionality
    // For example:
    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        //PlayerController->TogglePauseMenu();
    }
}

void UPauseMenu::OnSettingsClicked()
{
    // Implement settings functionality
}

void UPauseMenu::OnMainMenuClicked()
{
    // Implement main menu functionality
}

void UPauseMenu::OnQuitClicked()
{
    // Implement quit functionality
}