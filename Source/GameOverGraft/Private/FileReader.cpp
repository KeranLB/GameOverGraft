// Fill out your copyright notice in the Description page of Project Settings.


#include "FileReader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

bool UFileReader::FromFileToString(FString FileName, FString& Text)
{
	const FString FullPath = FPaths::ProjectContentDir() + FileName;

	if (!FPaths::FileExists(FullPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("File not found: %s"), *FullPath);
		return false;
	}

	return FFileHelper::LoadFileToString(Text, *FullPath);
}

static bool ParseDialogueJson(const FString& JsonString, FDialogueData& OutData)
{
	TSharedPtr<FJsonObject> JsonObject;

	TSharedRef<TJsonReader<>> Reader =
		TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON"));
		return false;
	}

	// Required fields
	OutData.Caller = JsonObject->GetStringField(TEXT("Caller"));
	OutData.CallTarget = JsonObject->GetStringField(TEXT("CallTarget"));
	OutData.SerialNumber = JsonObject->GetStringField(TEXT("SerialNumber"));
	

	// Optional array
	OutData.Dialogue.Empty();
	OutData.CampStatuses.Empty();
	OutData.CampNames.Empty();
	const TArray<TSharedPtr<FJsonValue>>* DialogueArray;
	const TArray<TSharedPtr<FJsonValue>>* CampStatusesArray;
	const TArray<TSharedPtr<FJsonValue>>* CampNamesArray;

	if (JsonObject->TryGetArrayField(TEXT("Dialogue"), DialogueArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *DialogueArray)
		{
			OutData.Dialogue.Add(Value->AsString());
		}
	}
	
	if (JsonObject->TryGetArrayField(TEXT("CampStatuses"), CampStatusesArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *CampStatusesArray)
		{
			OutData.CampStatuses.Add(Value->AsString());
		}
	}

	if (JsonObject->TryGetArrayField(TEXT("CampNames"), CampNamesArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *CampNamesArray)
		{
			OutData.CampNames.Add(Value->AsString());
		}
	}
	
	return true;
}


bool UFileReader::LoadData(	const FString& FileName, FDialogueData& OutData)
{
	const FString FilePath =
		FPaths::FPaths::ProjectContentDir() +
		TEXT("Data/JsonFiles/") +
		FileName +
		TEXT(".json");

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *FilePath);
		return false;
	}

	return ParseDialogueJson(JsonText, OutData);
}

