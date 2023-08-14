// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PC_Arena.h"
#include "Net/UnrealNetwork.h"
#include "HUD/ArenaHUD.h"
#include "Widget/W_Arena.h"
#include "Components/TextBlock.h"
#include "Misc/W_Points.h"


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
		UE_LOG(LogTemp, Warning, TEXT("%d"), ChoosenNumber);
	}
	else {
		ServerChangedNum(n);
	}
}

void APC_Arena::OnRepChooseNum()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"),ChoosenNumber);
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
	}
}

void APC_Arena::UpdateLooseOrWin(bool b1)
{
	if (ArenaHUD) {
		if(b1)
		ArenaHUD->W_ArenaRef->WinOrLoose->SetText(FText::FromString("Winner"));
		else ArenaHUD->W_ArenaRef->WinOrLoose->SetText(FText::FromString("Looser"));
	}
	else {
		Client_UpdateLooseOrWin(b1);
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








