// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UW_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SessionJoinButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SessionButton; 


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* InputNoOfPlayer;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* ChangingName;

	////// ip address
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* ChangeIpAddress;

	FString IP_Address;

	UFUNCTION()
	void OnIPAddressChange(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* IpAddressText;

	////////

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int32 NoOfPlayer=5; 


	UFUNCTION(BlueprintCallable)
	void UpdateNoOfPlayers(const FText& NewText, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void UpdateName(const FText& NewText);

	FString GetComputerNameFunc();

	UFUNCTION()
	void OnChangingNameTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameBlock;

	UFUNCTION()
	void CreateSession();
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION()
	void JoinSession();

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

};
