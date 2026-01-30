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
	OutData.Name = JsonObject->GetStringField(TEXT("name"));
	OutData.SerialNumber = JsonObject->GetStringField(TEXT("SerialNumber"));
	OutData.Status = JsonObject->GetStringField(TEXT("Status"));

	// Optional array
	OutData.Dialogue.Empty();
	const TArray<TSharedPtr<FJsonValue>>* DialogueArray;

	if (JsonObject->TryGetArrayField(TEXT("Dialogue"), DialogueArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *DialogueArray)
		{
			OutData.Dialogue.Add(Value->AsString());
		}
	}

	return true;
}


bool UFileReader::LoadData(	const FString& LocationName, FDialogueData& OutData)
{
	const FString FilePath =
		FPaths::FPaths::ProjectContentDir() +
		TEXT("Data/JsonFiles/") +
		LocationName +
		TEXT(".json");

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *FilePath);
		return false;
	}

	return ParseDialogueJson(JsonText, OutData);
}