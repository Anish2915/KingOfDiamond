// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_WaitLobby.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API APC_WaitLobby : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	class AHUD_WaitLobby* waitLobby;
};
