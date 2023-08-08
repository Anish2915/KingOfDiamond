// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_MainMenu.generated.h"


class UW_MainMenu;

UCLASS()
class KINGOFDIAMONDGAME_API AHUD_MainMenu : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UW_MainMenu* W_MainMenuRef;

	void AddWidgetToScreen();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_MainMenu> SelectedWid;
};
