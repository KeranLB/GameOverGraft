// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TaskDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOVERGRAFT_API UTaskDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TaskName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Caller;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CallTarget;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString SerialNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> CampNames;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> CampStatuses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Dialogue;
};
