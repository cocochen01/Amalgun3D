// Fill out your copyright notice in the Description page of Project Settings.

// Header Files
#include "WidgetUI/GameHUD.h"

#include "WidgetUI/MainMenu.h"
#include "WidgetUI/InteractionWidget.h"
#include "Interfaces/InteractionInterface.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AGameHUD::DisplayMenu()
{
	if (!MainMenuWidget)
		return;

	bIsMenuVisible = true;
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void AGameHUD::HideMenu()
{
	if (!MainMenuWidget)
		return;

	bIsMenuVisible = false;
	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AGameHUD::ShowInteractionWidget() const
{
	if (!InteractionWidget)
		return;

	InteractionWidget->SetVisibility(ESlateVisibility::Visible);
}

void AGameHUD::HideInteractionWidget() const
{
	if (!InteractionWidget)
		return;

	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AGameHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (!InteractionWidget)
		return;
	if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
	InteractionWidget->UpdateWidget(InteractableData);
}
