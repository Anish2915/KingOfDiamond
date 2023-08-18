// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ArenaGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "PlayerController/PC_Arena.h"
#include "TimerManager.h"

void AArenaGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AArenaGameMode::GetInformation, 8.0f, false);
	
}

void AArenaGameMode::GetInformation()
{
	PlayerState = GameState.Get()->PlayerArray;
	NoOfPlayers = GameState.Get()->PlayerArray.Num();
	NoOfPeopleAlive = NoOfPlayers;
	for (auto& it : PlayerState) {
		APC_Arena* PlayerCont = Cast<APC_Arena>(it->GetOwner());
		if (PlayerCont) {
			ControllerArray.Add(PlayerCont);
			PlayerCont->CreateStartingRuleWidget();
			PlayerCont->SetVisibilityOfMain();
			PointsArray.Add(0);
		}
	}
	for (int i = 0; i < NoOfPlayers; i++) {
		for (int j = 0; j < NoOfPlayers; j++) {
			ControllerArray[i]->UpdateNames(FText::FromString(ControllerArray[j]->PlayerState->GetPlayerName()));
		}
	}
	bool DoesRuleChange = false;
	if (!Rule3 && NoOfPeopleAlive <= 2) {
		Rule3 = true;
		DoesRuleChange = true;
	}
	if (!Rule1 && NoOfPeopleAlive <= 4) {
		Rule1 = true;
		DoesRuleChange = true;
	}
	if (!Rule2 && NoOfPeopleAlive <= 3) {
		Rule2 = true;
		DoesRuleChange = true;
	}
	GetWorldTimerManager().ClearTimer(TimerHandle);

	if (DoesRuleChange) {

	}

	GetWorldTimerManager().SetTimer(StartingTimer, this, &AArenaGameMode::StartingTimeFunc, 51.0f, false);
	
}



void AArenaGameMode::StartingTimeFunc()
{
	GetWorldTimerManager().ClearTimer(StartingTimer);
	StartRound();
}



void AArenaGameMode::CheckAverage()
{
	
	float total = 0;
	float NoOfPlayerInGame = 0;
	TArray<float> ChooosenArray;
	WinnerStatus.Empty();
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			WinnerStatus.Add(true);
		}
		else {
			WinnerStatus.Add(false);
		}
	}
	for(int i = 0 ; i < NoOfPlayers ; i ++){
		if (ControllerArray[i]->bIsAlive){
			if (!ControllerArray[i]->bDoesChoose) {
				SomeoneNotChoose();
				StopRound(2, ChooosenArray,0);
				return;
			}
			ChooosenArray.Add(ControllerArray[i]->ChoosenNumber);
			total += ControllerArray[i]->ChoosenNumber;
			NoOfPlayerInGame++;
		}
		else {
			ChooosenArray.Add(-1);
		}
		
	}
	if (Rule1) {
		if (Rule1Check(ChooosenArray)) {
			std::unordered_map<int, int> mp;
			std::vector<bool> loose(NoOfPlayers,false);
			for (int i = 0; i < NoOfPlayers; i++) {
				if (ControllerArray[i]->bIsAlive) {
					if (mp.count(ChooosenArray[i])) {
						loose[i] = true;
						loose[mp[ChooosenArray[i]]] = true;
					}
					else {
						mp[ChooosenArray[i]] = i;
					}
				}
			}

			for(int i = 0 ; i < NoOfPlayers; i ++){
				if (ControllerArray[i]->bIsAlive && loose[i]) {
					ControllerArray[i]->points--;
					PointsArray[i]--;
					WinnerStatus[i] = false;
					for (int j = 0; j < NoOfPlayers; j++) {
						ControllerArray[j]->UpdatePointAtLocation(i, ControllerArray[i]->points);
					}
				}
			}
			StopRound(3, ChooosenArray,0);
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
			PointsArray[Rule3vec[1].second]--;
			WinnerStatus[Rule3vec[1].second] = false;
			for (int j = 0; j < NoOfPlayers; j++) {
				ControllerArray[j]->UpdatePointAtLocation(Rule3vec[1].second, ControllerArray[Rule3vec[1].second]->points);
			}
			StopRound(4, ChooosenArray,0);
			return;
		}
		else if (Rule3vec[0].first == 0 && Rule3vec[1].first == 100) {
			ControllerArray[Rule3vec[0].second]->points--;
			PointsArray[Rule3vec[0].second]--;
			WinnerStatus[Rule3vec[0].second] = false;
			for (int j = 0; j < NoOfPlayers; j++) {
				ControllerArray[j]->UpdatePointAtLocation(Rule3vec[0].second, ControllerArray[Rule3vec[0].second]->points);
			}
			StopRound(4, ChooosenArray,0);
			return;
		}
	}
	float aver = total / NoOfPlayerInGame;
	float average = (total / NoOfPlayerInGame)*0.8;
	float mini = std::abs(ChooosenArray[0] - average);
	TArray<float> choosenArrTemp = ChooosenArray;
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			ChooosenArray[i] = std::abs(ChooosenArray[i] - average)
				
				;
			if (ChooosenArray[i] < mini) {
				mini = ChooosenArray[i];
			}
		}
	}
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			if (ChooosenArray[i] != mini) {
				ControllerArray[i]->points--;
				PointsArray[i]--;
				WinnerStatus[i] = false;
				if (Rule2) {
					ControllerArray[i]->points--;
					PointsArray[i]--;
				}
				for (int j = 0; j < NoOfPlayers; j++) {
					ControllerArray[j]->UpdatePointAtLocation(i, ControllerArray[i]->points);
				}
			}
		}
	}
	StopRound(1, choosenArrTemp,aver);
}



bool AArenaGameMode::Rule1Check(TArray<float> TempArray)
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
			PointsArray[i]--;
			WinnerStatus[i] = false;
			for (int j = 0; j < NoOfPlayers; j++) {
				ControllerArray[j]->UpdatePointAtLocation(i, ControllerArray[i]->points);
			}
		}
	}
}

void AArenaGameMode::StartRound()
{
	ChoosingTime = 40;
	StartTimer();
}

void AArenaGameMode::StopRound(int n, TArray<float> ChooosenArr,float aver)
{
	bool DoesSOmeOneDied = false;
	for(int i=0;i<NoOfPlayers;i++){
		if (ControllerArray[i]->bIsAlive) {
			if (ControllerArray[i]->points <= -10) {
				DoesSOmeOneDied = true;
				ControllerArray[i]->bIsAlive = false;
				NoOfPeopleAlive--;
				ControllerArray[i]->UpdateLooseOrWin(false);
			}
			ControllerArray[i]->bDoesChoose = false;
			ControllerArray[i]->ChoosenNumber = -1;
			ControllerArray[i]->DontShowChoosen();
		}
	}
	
	


	TArray<bool> tempDead;
	for (int i = 0; i < NoOfPlayers; i++) {
		tempDead.Add(ControllerArray[i]->bIsAlive);
	}

	/////////////////
	TArray<int> RuleToAdd;
	if (!Rule3 && NoOfPeopleAlive <= 2) {
		RuleToAdd.Add(3);
		Rule3 = true;
	}
	if (!Rule1 && NoOfPeopleAlive <= 4) {
		RuleToAdd.Add(1);
		Rule1 = true;
	} 
	if (!Rule2 && NoOfPeopleAlive <= 3) {
		RuleToAdd.Add(2);
		Rule2 = true;
	}
	/////////////////////////

	for (auto& it : ControllerArray) {
		it->ShowCalcAverWidget(n,ChooosenArr,PointsArray,aver,WinnerStatus,tempDead,DoesSOmeOneDied,RuleToAdd);
	}

	float tempTime = 16.0f;
	if (n == 1) tempTime = tempTime + 10.0f;
	if (DoesSOmeOneDied) tempTime = tempTime + 5.0f;
	if (!RuleToAdd.IsEmpty())  tempTime = tempTime + 4.5f + 8 * RuleToAdd.Num();
	if (NoOfPeopleAlive <= 1) {
		GetWorldTimerManager().SetTimer(FinalTime, this, &AArenaGameMode::GameFinsih, tempTime-3, false);
		return;
	}

	GetWorldTimerManager().SetTimer(NewTime, this, &AArenaGameMode::ShowAverageBP, tempTime+1, false);
	
}


void AArenaGameMode::GameFinsih()
{
	for (int i = 0; i < NoOfPlayers; i++) {
		if (ControllerArray[i]->bIsAlive) {
			ControllerArray[i]->UpdateLooseOrWin(true);
		}
	}
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


void AArenaGameMode::ShowAverageBP()
{
	GetWorldTimerManager().ClearTimer(NewTime);
	StartRound();
}

