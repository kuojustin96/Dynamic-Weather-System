// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeatherType.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WEATHERSYSTEM_API UWeatherType : public UDataAsset
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UWeatherType();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString WeatherName;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* WeatherParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialParameterCollection* MaterialParamCollection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MPC_ParamName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MPC_TransitionTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor SceneLightingColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SunBrightness;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CloudSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin="0.0", ClampMax="2"))
	float CloudOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HorizonFalloff;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor ZenithColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor HorizonColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor CloudColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor OverallSkyColor;
};
