// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "WidgetUI/PauseMenu.h"

#include "AmalgunGameInstance.generated.h"

class UPauseMenu;

UCLASS()
class AMALGUN_API UAmalgunGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPauseMenu> BP_PauseMenu;
};
