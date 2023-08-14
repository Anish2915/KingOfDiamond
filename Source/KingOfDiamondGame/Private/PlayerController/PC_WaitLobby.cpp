// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PC_WaitLobby.h"
#include "HUD/HUD_WaitLobby.h"
#include "TimerManager.h"
#include "GameFramework/PlayerState.h"

void APC_WaitLobby::BeginPlay()
{
	Super::BeginPlay();
	waitLobby = Cast<AHUD_WaitLobby>(GetHUD());
}




