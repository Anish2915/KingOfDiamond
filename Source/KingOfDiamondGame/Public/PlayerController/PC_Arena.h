// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Arena.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API APC_Arena : public APlayerController
{
	GENERATED_BODY()
public:
	

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	class AArenaHUD* ArenaHUD;
	/////////////////////////////////////
	UFUNCTION(BlueprintCallable)
	void ChoooseNum(int n);
	
	UPROPERTY(ReplicatedUsing = OnRepChooseNum, BlueprintReadWrite);
	int ChoosenNumber=-1;

	UFUNCTION()
	void OnRepChooseNum();
	
	
	UFUNCTION(Server, Reliable)
	void ServerChangedNum(int n);
	///////////////////////////////////////////////
	

	//////////////////////////////////////////
	UPROPERTY(Replicated, BlueprintReadWrite);
	bool bDoesChoose=false;

	void StartHudTime();
	void StopTimer();
	void UpdateTimer();
	void SetArenaTime(int countdown);
    int ChoosingTime = 90;
	FTimerHandle TimerHandle_UpdateTimer;
};
