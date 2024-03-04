// Fill out your copyright notice in the Description page of Project Settings.


#include "AmalgunGameMode.h"
#include "AmalgunPlayerController.h"

AAmalgunGameMode::AAmalgunGameMode()
{
	PlayerControllerClass = AAmalgunPlayerController::StaticClass();
}
