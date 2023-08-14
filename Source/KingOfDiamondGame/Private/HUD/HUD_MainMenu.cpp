// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUD_MainMenu.h"
#include "Widget/W_MainMenu.h"
#include "PlayerController/PC_MainMenu.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"

void AHUD_MainMenu::BeginPlay()
{
	Super::BeginPlay();
	AddWidgetToScreen();
}

void AHUD_MainMenu::AddWidgetToScreen()
{
	APC_MainMenu* PC_MainMenu = Cast<APC_MainMenu>(GetOwningPlayerController());
	if (PC_MainMenu && SelectedWid) {
		W_MainMenuRef = CreateWidget<UW_MainMenu>(PC_MainMenu,SelectedWid);
		W_MainMenuRef->AddToViewport();
		APlayerState* PlayerState = PC_MainMenu->GetPlayerState<APlayerState>();

		if(W_MainMenuRef->NameBlock)
		W_MainMenuRef->NameBlock->SetText(FText::FromString(FString::Printf(TEXT("WELCOME %s"), *PlayerState->GetPlayerName())));
	}
}
