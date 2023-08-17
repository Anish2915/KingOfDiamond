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
	
	void ChoooseNum(int n);
	
	UPROPERTY(ReplicatedUsing = OnRepChooseNum, BlueprintReadWrite);
	int ChoosenNumber=-1;

	UFUNCTION()
	void OnRepChooseNum();
	
	
	UFUNCTION(Server, Reliable)
	void ServerChangedNum(int n);
	///////////////////////////////////////////////
	

	//////////////////////////////////////////
	UPROPERTY(Replicated);
	bool bDoesChoose=false;

	UPROPERTY(Replicated);
	bool bIsAlive = true;

	UPROPERTY(Replicated);
	int points = 0;


	//////////////////////////
	 

	///////////////////////////////////////
	void SetArenaTimePC(int countdown);


	UFUNCTION(Client, Reliable)
	void Client_UpdateArenaTimer(const FText& TimerText);


	UFUNCTION(Client, Reliable)
    void Client_UpdateNames(const FText& NameVar);

	void UpdateNames(const FText& NameVar);
	void UpdatePointAtLocation(int i,int value);


	UFUNCTION(Client, Reliable)
	void Client_UpdatePointAtLocation(int i,int value);


	UFUNCTION(Client, Reliable)
	void Client_UpdateLooseOrWin(bool b1);
	void UpdateLooseOrWin(bool b1);

	void CreateStartingRuleWidget();

	UFUNCTION(Client,Reliable)
	void Client_CreateStartingRuleWidget();

	void SetVisibilityOfMain();

	UFUNCTION(Client, Reliable)
	void Client_SetVisibilityOfMain();


	void ShowCalcAverWidget(int n,const TArray<float>& choosenArr,const TArray<int>& PointsArr,float avera,const TArray<bool>& winnerStat,const TArray<bool>& DeadStatus,bool b,const TArray<int>& RuleToAdd);

	UFUNCTION(Client, Reliable)
	void Client_ShowCalcAverWidget(int n,const TArray<float>& choosenArr,const TArray<int>& PointsArr,float avera,const TArray<bool>& winnerStat, const TArray<bool>& DeadStatus,bool b, const TArray<int>& RuleToAdd);
};
