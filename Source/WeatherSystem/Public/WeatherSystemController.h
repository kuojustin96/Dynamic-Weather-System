// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherSystemController.generated.h"

UCLASS()
class WEATHERSYSTEM_API AWeatherSystemController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherSystemController();

	void SetCurrentWeatherZone(class AWeatherZone* Zone);

	void ActivateWeather(class UWeatherType* WeatherType);

	void DeactivateCurrentWeather();

	class AWeatherZone* GetActiveWeatherZone();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBillboardComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	TArray<class AWeatherZone*> WeatherZones;

	UPROPERTY(BlueprintReadOnly, Category = "Weather")
	class AWeatherZone* ActiveWeatherZone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	class UWeatherType* DefaultWeatherType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	float TransitionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	float MinWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	float MaxWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	float MinWeatherDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	float MaxWeatherDuration;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ActivateCurrentWeatherEffect();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DeactivateCurrentWeatherEffect();

	UFUNCTION(BlueprintImplementableEvent)
	void TransitionBetweenWeatherEffects();

	UPROPERTY(BlueprintReadOnly, Category = "Weather")
	class UWeatherType* CurrentWeatherType;
};
