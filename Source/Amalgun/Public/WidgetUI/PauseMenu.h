// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class AMALGUN_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* MainMenuButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

public:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnResumeClicked();

    UFUNCTION()
    void OnSettingsClicked();

    UFUNCTION()
    void OnMainMenuClicked();

    UFUNCTION()
    void OnQuitClicked();
};

