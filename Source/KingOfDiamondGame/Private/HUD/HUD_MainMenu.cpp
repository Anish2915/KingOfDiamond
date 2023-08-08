// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUD_MainMenu.h"
#include "Widget/W_MainMenu.h"
#include "PlayerController/PC_MainMenu.h"

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
	}
}
