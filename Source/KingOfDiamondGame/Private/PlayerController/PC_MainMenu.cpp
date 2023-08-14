// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PC_MainMenu.h"
#include "HUD/HUD_MainMenu.h"
#include "Widget/W_MainMenu.h"
void APC_MainMenu::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
}
