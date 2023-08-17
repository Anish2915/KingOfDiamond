// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ArenaHUD.h"
#include "PlayerController/PC_Arena.h"
#include "Widget/W_Arena.h"
#include "Misc/W_HorizontalCPP.h"
#include "Misc/W_ButtonCPP.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Misc/W_Points.h"
#include "GameFramework/PlayerState.h"
#include "Misc/W_StartingRule.h"
#include "Misc/W_CalculatingAverage.h"

void AArenaHUD::BeginPlay()
{
	Super::BeginPlay();
	AddWidgetToScreen();
	AddButtons();
}

void AArenaHUD::AddWidgetToScreen()
{
	PC_Arena = Cast<APC_Arena>(GetOwningPlayerController());
	if (PC_Arena && SelectedWid) {
		W_ArenaRef = CreateWidget<UW_Arena>(PC_Arena, SelectedWid);
		W_ArenaRef->AddToViewport();
		W_ArenaRef->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AArenaHUD::AddButtons()
{
	if (W_ArenaRef && SelectHorizontal && SelectButton) {
		
		for (int i = 0; i < 10; i++) {
			int r = i;
			UW_HorizontalCPP* Hor = CreateWidget<UW_HorizontalCPP>(PC_Arena, SelectHorizontal);
			for (int j = 0; j < 10; j++) {
				UW_ButtonCPP* Butt = CreateWidget<UW_ButtonCPP>(PC_Arena, SelectButton);
				Butt->Text->SetText(FText::FromString(FString::Printf(TEXT("%d"),r)));
				Butt->value = r;
				Hor->MyVerticalBox->AddChild(Butt);
				r = r + 10;
			}
			if (i == 0) {
				UW_ButtonCPP* Butt = CreateWidget<UW_ButtonCPP>(PC_Arena, SelectButton);
				Butt->Text->SetText(FText::FromString(FString::Printf(TEXT("%d"), r)));
				Butt->value = r;
				Hor->MyVerticalBox->AddChild(Butt);
			}
			W_ArenaRef->MyHorizontalBox->AddChild(Hor);
			
		}
	}
}

void AArenaHUD::AddPointsView(const FText& NameVar)
{

	if (W_ArenaRef && SelectPoints && PC_Arena && W_ArenaRef) {
		UW_Points* PointsRef = CreateWidget<UW_Points>(PC_Arena, SelectPoints);
		PointsRef->NameText->SetText(NameVar);
		PointsRef->PoitsText->SetText(FText::FromString("0"));
		W_ArenaRef->PointsBox->AddChild(PointsRef);
		PointsArray.Add(PointsRef);
		
		if (PointsArray.Num() == 1) {
			CalcAverageWidget->Name1->SetText(NameVar);
			CalcAverageWidget->point1->SetText(FText::FromString("0"));
		}
		else if (PointsArray.Num() == 2) {
			CalcAverageWidget->Name2->SetText(NameVar);
			CalcAverageWidget->point2->SetText(FText::FromString("0"));
		}
		else if (PointsArray.Num() == 3) {
			CalcAverageWidget->Name3->SetText(NameVar);
			CalcAverageWidget->point3->SetText(FText::FromString("0"));
		}
		else if (PointsArray.Num() == 4) {
			CalcAverageWidget->Name4->SetText(NameVar);
			CalcAverageWidget->point4->SetText(FText::FromString("0"));
		}
		else if (PointsArray.Num() == 5) {
			CalcAverageWidget->Name5->SetText(NameVar);
			CalcAverageWidget->point5->SetText(FText::FromString("0"));
		}
		
	}
}

void AArenaHUD::AddStartingWidgetArena()
{
	UW_StartingRule* StartingRUle = CreateWidget<UW_StartingRule>(PC_Arena, SelectStartingRule);
	CalcAverageWidget = CreateWidget<UW_CalculatingAverage>(PC_Arena, SelectCalculatingAverage);
	CalcAverageWidget->AddToViewport(10);
	CalcAverageWidget->SetVisibility(ESlateVisibility::Hidden);
	StartingRUle->AddToViewport(5);
}
