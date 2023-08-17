// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArenaHUD.generated.h"

class UW_Arena;
class UW_HorizontalCPP;
class UW_ButtonCPP;
class UW_Points;
UCLASS()
class KINGOFDIAMONDGAME_API AArenaHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UW_Arena* W_ArenaRef;

	void AddWidgetToScreen();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_Arena> SelectedWid;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_HorizontalCPP> SelectHorizontal;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_ButtonCPP> SelectButton;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_Points> SelectPoints;
	TArray<UW_Points*> PointsArray;

	class APC_Arena* PC_Arena;

	void AddButtons();
	void AddPointsView(const FText& NameVar);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UW_StartingRule> SelectStartingRule;

	void AddStartingWidgetArena();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UW_CalculatingAverage> SelectCalculatingAverage;

	TArray<FText> NameText;

	class UW_CalculatingAverage* CalcAverageWidget;
};
