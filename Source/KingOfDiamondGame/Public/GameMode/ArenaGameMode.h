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

	int Round = 0;
	int NoOfPeopleAlive = 0;

	TArray<class APlayerState*> PlayerState;
	TArray<class APC_Arena*> ControllerArray;
	TArray<bool> AliveStatus;
	float NoOfPlayers;

	bool Rule1Check(std::vector<float>& TempArray);

	FTimerHandle TimerHandle;

	void SomeoneNotChoose();
	void StartRound(int n);
	void StopRound();

	void StartTimer();
	void StopTimer();
	void UpdateTimer();
	void SetArenaTime(int countdown);
	int ChoosingTime = 30;
	FTimerHandle TimerHandle_UpdateTimer;
};
