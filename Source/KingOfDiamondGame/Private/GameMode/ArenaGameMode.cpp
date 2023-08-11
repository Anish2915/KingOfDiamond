// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ArenaGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "PlayerController/PC_Arena.h"
#include "TimerManager.h"

void AArenaGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AArenaGameMode::GetInformation, 10.0f, false);
}

void AArenaGameMode::CheckAverage()
{
	float total = 0;
	float NoOfPlayerInGame = 0;
	std::vector<float> ChooosenArray;
	for (auto& it : ControllerArray) {
		if (it->bIsAlive){
			if (!it->bDoesChoose) {
				SomeoneNotChoose();
				StopRound();
				return;
			}
			ChooosenArray.push_back(it->ChoosenNumber);
			total += it->ChoosenNumber;
			NoOfPlayerInGame++;
		}
		else {
			ChooosenArray.push_back(-1);
		}
	}
	if (Rule1) {
		if (Rule1Check(ChooosenArray)) {
			for(int i = 0 ; i < NoOfPlayers; i ++){
				if (ControllerArray[i]->bIsAlive) {
					ControllerArray[i]->points--;
					for (int j = 0; j < NoOfPlayers; j++) {
						ControllerArray[j]->UpdatePointAtLocation(i, ControllerArray[i]->points);
					}
				}
			}
			StopRound();
			return;
		}
	}
	if (Rule3) {
		std::vector<std::pair<int,int>> Rule3vec;
		for (int i = 0; i < NoOfPlayers; i++) {
			if (ControllerArray[i]->bIsAlive) {
				Rule3vec.push_back({ ChooosenArray[i],i });
			}
		}
		if (Rule3vec[0].first == 100 && Rule3vec[1].first == 0) {
			ControllerArray[Rule3vec[1].second]->points--;
			for (int j = 0; j < NoOfPlayers; j++) {
				ControllerArray[j]->UpdatePointAtLocation(Rule3vec[1].second, ControllerArray[Rule3vec[1].second]->points);
			}
			StopRound();
			return;
		}
		else if (Rule3vec[0].first == 0 && Rule3vec[1].first == 100) {
			ControllerArray[Rule3vec[0].second]->points--;
			for (int j = 0; j < NoOfPlayers; j++) {
				ControllerArray[j]->UpdatePointAtLocation(Rule3vec[0].second, ControllerArray[Rule3vec[0].second]->points);
			}
			StopRound();
			return;
		}
	}
	float average = (total / NoOfPlayerInGame)*0.8;
	float mini = std::abs(ChooosenArray[0] - average);
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			ChooosenArray[i] = std::abs(ChooosenArray[i] - average);
			if (ChooosenArray[i] < mini) {
				mini = ChooosenArray[i];
			}
		}
	}
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			if (ChooosenArray[i] != mini) {
				ControllerArray[i]->points--;
				if (Rule2) {
					ControllerArray[i]->points--;
				}
				for (int j = 0; j < NoOfPlayers; j++) {
					ControllerArray[j]->UpdatePointAtLocation(i, ControllerArray[i]->points);
				}
			}
		}
	}
	StopRound();
}

void AArenaGameMode::GetInformation()
{
	PlayerState = GameState.Get()->PlayerArray;
	NoOfPlayers = GameState.Get()->PlayerArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("%f"), NoOfPlayers);
	NoOfPeopleAlive = NoOfPlayers;
	for (auto it : PlayerState) {
		APC_Arena* PlayerCont = Cast<APC_Arena>(it->GetOwner());
		if (PlayerCont) {
			ControllerArray.Add(PlayerCont);
		}
	}
	for (int i = 0; i < NoOfPlayers; i++) {
		for (int j = 0; j < NoOfPlayers; j++) {
			ControllerArray[i]->UpdateNames(FText::FromString(ControllerArray[j]->PlayerState->GetPlayerName()));
		}
	}
	StartRound(1);
}

bool AArenaGameMode::Rule1Check(std::vector<float>& TempArray)
{
	std::unordered_map<float, int> mp;
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			if (mp.count(TempArray[i])) {
				return true;
			}
			mp[TempArray[i]] = 1;
		}
	}
	return false;
}

void AArenaGameMode::SomeoneNotChoose()
{
	
	for(int i=0;i<NoOfPlayers;i++){
		if (ControllerArray[i]->bIsAlive && !ControllerArray[i]->bDoesChoose) {
			ControllerArray[i]->points--;
			for (int j = 0; j < NoOfPlayers; j++) {
				ControllerArray[j]->UpdatePointAtLocation(i, ControllerArray[i]->points);
			}
		}
	}
}

void AArenaGameMode::StartRound(int n)
{
	UE_LOG(LogTemp, Warning, TEXT("%d : round"),n);
	ChoosingTime = 20;
	if (NoOfPeopleAlive==2) {
		Rule3 = true;
	}
	if (NoOfPeopleAlive < 5) {
		Rule1 = true;
	}
	if (NoOfPeopleAlive == 3) {
		Rule2 = true;
	}
	else {
		Rule2 = false;
	}
	StartTimer();
}

void AArenaGameMode::StopRound()
{
	
	for(int i=0;i<NoOfPlayers;i++){
		if (ControllerArray[i]->bIsAlive) {
			if (ControllerArray[i]->points <= -10) {
				ControllerArray[i]->bIsAlive = false;
				NoOfPeopleAlive--;
				ControllerArray[i]->UpdateLooseOrWin(false);
			}
			ControllerArray[i]->bDoesChoose = false;
			ControllerArray[i]->ChoosenNumber = -1;
		}
	}
	Round++;
	if (NoOfPeopleAlive <= 1) {
		UE_LOG(LogTemp, Warning, TEXT("GameFinish"));
		for (int i = 0; i < NoOfPlayers; i++) {
			if (ControllerArray[i]->bIsAlive) {
				ControllerArray[i]->UpdateLooseOrWin(true);
			}
		}
		return;
	}
	StartRound(Round);
}

void AArenaGameMode::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle_UpdateTimer, this, &AArenaGameMode::UpdateTimer, 1.0f, true);
}

void AArenaGameMode::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_UpdateTimer);
	CheckAverage();
}

void AArenaGameMode::UpdateTimer()
{
	ChoosingTime--;
	SetArenaTime(ChoosingTime);
	if (ChoosingTime <= 0){
		StopTimer();
	}
}

void AArenaGameMode::SetArenaTime(int countdown)
{
	for (auto &it : ControllerArray) {
		if (it) {
			it->SetArenaTimePC(countdown);
		}
	}
}




