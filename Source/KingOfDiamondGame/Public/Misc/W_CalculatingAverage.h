// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_CalculatingAverage.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UW_CalculatingAverage : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* choosen1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* choosen2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* choosen3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* choosen4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* choosen5;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* average;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* final;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* point1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* point2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* point3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* point4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* point5;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name5;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Winner1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Winner2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Winner3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Winner4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Winner5;

	UFUNCTION(BlueprintImplementableEvent)
	void Calc();

	void Calc2();

	UPROPERTY(BlueprintReadWrite)
	int Global;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> choosenArr;

	UPROPERTY(BlueprintReadWrite)
	TArray<int> PointsArr;

	UPROPERTY(BlueprintReadWrite)
	TArray<bool> WinnerStatsWid;

	UPROPERTY(BlueprintReadWrite)
	float averag;

	UFUNCTION(BlueprintCallable)
	void UpdatePoints();


	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	void UpdatePoint2();

	UFUNCTION(BlueprintCallable)
	void UpdateWinnerStatus();


	UFUNCTION(BlueprintCallable)
	void RemoveWinnerStat();

	UPROPERTY(BlueprintReadWrite)
	TArray<bool> DeadStats;

	UPROPERTY(BlueprintReadWrite)
	bool DoesSomeoneDiedNow;

	UPROPERTY(BlueprintReadWrite)
	TArray<int> RuleAddArr;

	UFUNCTION(BlueprintCallable)
	void CheckDead();
};

