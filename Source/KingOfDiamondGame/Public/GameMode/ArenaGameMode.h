// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ArenaGameMode.generated.h"


UCLASS()
class KINGOFDIAMONDGAME_API AArenaGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	void CheckAverage();
	void GetInformation();

	bool Rule1 = false;
	bool Rule2 = false;
	bool Rule3 = false;

	int NoOfPeopleAlive = 0;

	TArray<class APlayerState*> PlayerState;
	TArray<class APC_Arena*> ControllerArray;
	TArray<bool> WinnerStatus;
	float NoOfPlayers;

	bool Rule1Check(TArray<float> TempArray);
	TArray<int> PointsArray;

	void SomeoneNotChoose();
	void StartRound();
	void StopRound(int n, TArray<float> ChooosenArr,float aver );

	void StartTimer();
	void StopTimer();
	void UpdateTimer();
	void SetArenaTime(int countdown);
	int ChoosingTime = 20;
	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle_UpdateTimer;
	FTimerHandle StartingTimer;
	FTimerHandle NewTime;
	FTimerHandle FinalTime;

	void GameFinsih();
	void StartingTimeFunc();
	void ShowAverageBP();
};
