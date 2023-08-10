// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PC_Arena.h"
#include "Net/UnrealNetwork.h"
#include "HUD/ArenaHUD.h"
#include "Widget/W_Arena.h"
#include "Components/TextBlock.h"


void APC_Arena::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APC_Arena, ChoosenNumber, COND_None);
}

void APC_Arena::BeginPlay()
{
	Super::BeginPlay();
	ArenaHUD = Cast<AArenaHUD>(GetHUD());
	StartHudTime();
}

void APC_Arena::ChoooseNum(int n)
{
	if (HasAuthority()) {
		ChoosenNumber = n;
		bDoesChoose = true;
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

void APC_Arena::SetArenaTime(int countdown)
{
	ArenaHUD = ArenaHUD == nullptr ? Cast<AArenaHUD>(GetHUD()) : ArenaHUD;

	bool b = ArenaHUD && ArenaHUD->W_ArenaRef && ArenaHUD->W_ArenaRef->ArenaTimer;
	if (b) {
		FString minute = FString::Printf(TEXT("%d"), countdown / 60);
		FString Second = FString::Printf(TEXT("%02d"),countdown % 60);
		FString CountDown = minute + FString(" : ") + Second;
		ArenaHUD->W_ArenaRef->ArenaTimer->SetText(FText::FromString(CountDown));
	}
}

void APC_Arena::StartHudTime()
{
	GetWorldTimerManager().SetTimer(TimerHandle_UpdateTimer,this,&APC_Arena::UpdateTimer,1.0f,true);
}

void APC_Arena::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_UpdateTimer);
}

void APC_Arena::UpdateTimer()
{
	ChoosingTime--;
	SetArenaTime(ChoosingTime);
	if (ChoosingTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_UpdateTimer);
	}
}
