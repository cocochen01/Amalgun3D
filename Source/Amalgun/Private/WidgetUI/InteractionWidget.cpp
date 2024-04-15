// Fill out your copyright notice in the Description page of Project Settings.

// Header Files
#include "WidgetUI/InteractionWidget.h"

#include "Character/CharacterBase.h"
#include "Interfaces/InteractionInterface.h"

// Components
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InteractionProgressBar->PercentDelegate.BindUFunction(this, TEXT("UpdateInteractionProgress"));
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KeyPressText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = .0f;
}

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData)
{
	switch (InteractableData->InteractableType)
	{
	case EInteractableType::Pickup:
		KeyPressText->SetText(FText::FromString("Press"));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		/*
		if (InteractableData->Quantity < 2)
			QuantityText->SetVibility(ESlateVisibility::Collapsed);
		else
		{
			QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"), InteractableData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		*/
		break;
	case EInteractableType::NonPlayerCharacter:
		break;
	case EInteractableType::Interactable:
		break;
	default: ;
	}
	ActionText->SetText(InteractableData->Action);
	NameText->SetText(InteractableData->Name);
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.0f;
}
