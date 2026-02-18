#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataHolder.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "FileReader.generated.h"


/**
 * 
 */
UCLASS()
class GAMEOVERGRAFT_API UFileReader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Data")
	static bool FromFileToString(const FString FileName, FString& Text);
	UFUNCTION(BlueprintCallable, Category = "Data")
	static bool LoadData( const FString& LocationName, FDialogueData& OutData );
};
