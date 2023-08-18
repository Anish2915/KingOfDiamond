// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PC_Arena.h"
#include "Net/UnrealNetwork.h"
#include "HUD/ArenaHUD.h"
#include "Widget/W_Arena.h"
#include "Components/TextBlock.h"
#include "Misc/W_Points.h"
#include "Components/Image.h"
#include "Misc/W_CalculatingAverage.h"

void APC_Arena::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APC_Arena, ChoosenNumber, COND_None);
	DOREPLIFETIME_CONDITION(APC_Arena, points, COND_None);
	DOREPLIFETIME_CONDITION(APC_Arena, bDoesChoose, COND_None);
	DOREPLIFETIME_CONDITION(APC_Arena, bIsAlive, COND_None);
}

void APC_Arena::BeginPlay()
{
	Super::BeginPlay();
	ArenaHUD = Cast<AArenaHUD>(GetHUD());
	bShowMouseCursor = true;
}

void APC_Arena::ChoooseNum(int n)
{
	if (HasAuthority()) {
		ChoosenNumber = n;
		bDoesChoose = true;
		if (ArenaHUD && ArenaHUD->W_ArenaRef) {
			ArenaHUD->W_ArenaRef->ChoosenNumbertext->SetText(FText::FromString(FString::Printf(TEXT("%d"), n)));
		}
	}
	else {
		ServerChangedNum(n);
	}
}

void APC_Arena::OnRepChooseNum()
{
	if (ArenaHUD && ArenaHUD->W_ArenaRef) {
		ArenaHUD->W_ArenaRef->ChoosenNumbertext->SetText(FText::FromString(FString::Printf(TEXT("%d"), ChoosenNumber)));
	}
}


void APC_Arena::ServerChangedNum_Implementation(int n)
{
	ChoosenNumber = n;
	bDoesChoose = true;
}

void APC_Arena::SetArenaTimePC(int countdown)
{
	FString minute = FString::Printf(TEXT("%d"), countdown / 60);
	FString Second = FString::Printf(TEXT("%02d"), countdown % 60);
	FString CountDown = minute + FString(" : ") + Second;
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	bool b = ArenaHUD && ArenaHUD->W_ArenaRef && ArenaHUD->W_ArenaRef->ArenaTimer;
	if (b) {
		ArenaHUD->W_ArenaRef->ArenaTimer->SetText(FText::FromString(CountDown));
	}
	else {
		Client_UpdateArenaTimer(FText::FromString(CountDown));
	}
	
}

void APC_Arena::Client_UpdateNames_Implementation(const FText& NameVar)
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	if (ArenaHUD) {
		ArenaHUD->AddPointsView(NameVar);
	}
}

void APC_Arena::UpdateNames(const FText& NameVar)
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	if (ArenaHUD) {
		ArenaHUD->AddPointsView(NameVar);
	}
	else {
		Client_UpdateNames(NameVar);
	}
}

void APC_Arena::UpdatePointAtLocation(int i, int value)
{
	if (ArenaHUD) {
		ArenaHUD->PointsArray[i]->PoitsText->SetText(FText::FromString(FString::Printf(TEXT("%d"), value)));
	}
	else {
		Client_UpdatePointAtLocation(i, value);
	}
}

void APC_Arena::Client_UpdateLooseOrWin_Implementation(bool b1)
{
	if (ArenaHUD) {
		if (b1)
			ArenaHUD->W_ArenaRef->WinOrLoose->SetText(FText::FromString("Winner"));
		else ArenaHUD->W_ArenaRef->WinOrLoose->SetText(FText::FromString("Looser"));
		ArenaHUD->W_ArenaRef->WinOrLoose->SetVisibility(ESlateVisibility::Visible);
		ArenaHUD->W_ArenaRef->ImageBlack->SetVisibility(ESlateVisibility::Visible);
	}
}

void APC_Arena::UpdateLooseOrWin(bool b1)
{
	if (ArenaHUD) {
		if (b1) {
			ArenaHUD->W_ArenaRef->WinOrLoose->SetText(FText::FromString("Winner"));
			
		}
		else { 
			ArenaHUD->W_ArenaRef->WinOrLoose->SetText(FText::FromString("Looser")); 
		}
		ArenaHUD->W_ArenaRef->WinOrLoose->SetVisibility(ESlateVisibility::Visible);
		ArenaHUD->W_ArenaRef->ImageBlack->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Client_UpdateLooseOrWin(b1);
	}
}

void APC_Arena::CreateStartingRuleWidget()
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	if (ArenaHUD) {
		ArenaHUD->AddStartingWidgetArena();
	}
	else {
		Client_CreateStartingRuleWidget();
	}
}



void APC_Arena::Client_CreateStartingRuleWidget_Implementation()
{
	if (ArenaHUD) {
		ArenaHUD->AddStartingWidgetArena();
	}
}


void APC_Arena::SetVisibilityOfMain()
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	if (ArenaHUD && ArenaHUD->W_ArenaRef) {
		ArenaHUD->W_ArenaRef->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Client_SetVisibilityOfMain();
	}
}



void APC_Arena::Client_SetVisibilityOfMain_Implementation()
{
	if (ArenaHUD && ArenaHUD->W_ArenaRef) {
		ArenaHUD->W_ArenaRef->SetVisibility(ESlateVisibility::Visible);
	}
}


void APC_Arena::Client_UpdatePointAtLocation_Implementation(int i, int value)
{
	if (ArenaHUD) {
		ArenaHUD->PointsArray[i]->PoitsText->SetText(FText::FromString(FString::Printf(TEXT("%d"), value)));
	}
}

void APC_Arena::Client_UpdateArenaTimer_Implementation(const FText& TimerText)
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	bool b = ArenaHUD && ArenaHUD->W_ArenaRef && ArenaHUD->W_ArenaRef->ArenaTimer;
	if (b) {
		ArenaHUD->W_ArenaRef->ArenaTimer->SetText(TimerText);
	}
}

void APC_Arena::ShowCalcAverWidget(int n, const TArray<float>& choosenArr, const TArray<int>& PointsArr, float avera,const TArray<bool>& winnerStat, const TArray<bool>& DeadStatus,bool b, const TArray<int>& RuleToAdd)
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	if (ArenaHUD) {
		if (ArenaHUD->CalcAverageWidget) {
			ArenaHUD->CalcAverageWidget->Global = n;
			ArenaHUD->CalcAverageWidget->choosenArr = choosenArr;
			ArenaHUD->CalcAverageWidget->PointsArr = PointsArr;
			ArenaHUD->CalcAverageWidget->averag = avera;
			ArenaHUD->CalcAverageWidget->SetVisibility(ESlateVisibility::Visible);
			ArenaHUD->CalcAverageWidget->WinnerStatsWid = winnerStat;
			ArenaHUD->CalcAverageWidget->DeadStats = DeadStatus;
			ArenaHUD->CalcAverageWidget->DoesSomeoneDiedNow = b;
			ArenaHUD->CalcAverageWidget->RuleAddArr = RuleToAdd;
			ArenaHUD->CalcAverageWidget->Calc2();
		}
	}
	else {
		Client_ShowCalcAverWidget(n, choosenArr, PointsArr, avera,winnerStat,DeadStatus,b,RuleToAdd);
	}
}

void APC_Arena::DontShowChoosen()
{
	if (ArenaHUD && ArenaHUD->W_ArenaRef) {
		ArenaHUD->W_ArenaRef->ChoosenNumbertext->SetText(FText::FromString(FString::Printf(TEXT("%d"), -1)));
	}
}

void APC_Arena::Client_ShowCalcAverWidget_Implementation(int n,const TArray<float>& choosenArr,const TArray<int>& PointsArr, float avera,const TArray<bool>& winnerStat, const TArray<bool>& DeadStatus,bool b, const TArray<int>& RuleToAdd)
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;
	if (ArenaHUD) {
		if (ArenaHUD->CalcAverageWidget) {
			UE_LOG(LogTemp, Warning, TEXT("client call"));
			ArenaHUD->CalcAverageWidget->Global = n;
			ArenaHUD->CalcAverageWidget->choosenArr = choosenArr;
			ArenaHUD->CalcAverageWidget->PointsArr = PointsArr;
			ArenaHUD->CalcAverageWidget->averag = avera;
			ArenaHUD->CalcAverageWidget->SetVisibility(ESlateVisibility::Visible);
			ArenaHUD->CalcAverageWidget->WinnerStatsWid = winnerStat;
			ArenaHUD->CalcAverageWidget->DeadStats = DeadStatus;
			ArenaHUD->CalcAverageWidget->DoesSomeoneDiedNow = b;
			ArenaHUD->CalcAverageWidget->RuleAddArr = RuleToAdd;
			ArenaHUD->CalcAverageWidget->Calc2();
		}
	}
}






