// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/W_ButtonCPP.h"
#include "Components/Button.h"
#include "PlayerController/PC_Arena.h"

void UW_ButtonCPP::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this,&UW_ButtonCPP::OnClick);
}

void UW_ButtonCPP::OnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), value);

	APlayerController* OwningPlayerController = GetOwningPlayer();

	if (OwningPlayerController) {
		APC_Arena* PlayerController = Cast<APC_Arena>(OwningPlayerController);
		if (PlayerController) {
			
			if (PlayerController->bIsAlive && !PlayerController->bDoesChoose) {
				PlayerController->ChoooseNum(this->value);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("You are dead"));
			}
		}
	}
}
