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
	}
}
