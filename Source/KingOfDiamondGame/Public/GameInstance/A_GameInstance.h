// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "A_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UA_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings")
	int NoOfPlayer = 5;
};
