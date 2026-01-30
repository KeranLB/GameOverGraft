#pragma once

#include "CoreMinimal.h"
#include "DataHolder.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Caller;

	UPROPERTY(BlueprintReadOnly)
	FString CallTarget;
	
	UPROPERTY(BlueprintReadOnly)
	FString SerialNumber;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> CampNames;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> CampStatuses;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Dialogue;
	
};
