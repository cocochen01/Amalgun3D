// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameHUD.generated.h"

class UMainMenu;
class UInteractionWidget;
struct FInteractableData;

UCLASS()
class AMALGUN_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	/////// Variables ///////
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	bool bIsMenuVisible;

	/////// Functions ///////
	AGameHUD();

	void DisplayMenu();
	void HideMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

protected:
	/////// Variables ///////
	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	/////// Functions ///////
	virtual void BeginPlay() override;
};
