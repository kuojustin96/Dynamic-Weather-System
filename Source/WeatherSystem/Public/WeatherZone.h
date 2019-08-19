// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherZone.generated.h"

UCLASS()
class WEATHERSYSTEM_API AWeatherZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeatherZone();

	class UWeatherType* GetCurrentWeatherDataAsset();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Zone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	TArray<class UWeatherType*> WeatherTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
	bool bOverrideControllerTimers;

	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather", meta = (EditCondition = "bOverrideControllerTimers"))
	float MinWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather", meta = (EditCondition = "bOverrideControllerTimers"))
	float MaxWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather", meta = (EditCondition = "bOverrideControllerTimers"))
	float MinWeatherDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather", meta = (EditCondition = "bOverrideControllerTimers"))
	float MaxWeatherDuration;

	class AWeatherSystemController* WeatherSystemController;

	UFUNCTION()
	void OnZoneBeginOverlap(class UPrimitiveComponent* OverlapComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnZoneEndOverlap(class UPrimitiveComponent* OverlapComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetupNextWeatherType();

	UFUNCTION()
	void EnableWeatherType();

	UFUNCTION()
	void DisableWeatherType();

	int CurrentWeatherTypeInt;

	int NextWeatherTypeInt;

	inline float GetRandomNumberInRange(float MinNum, float MaxNum);

	inline int GetRandomNumberInRange(int MinNum, int MaxNum);

public:
	void SetupWeatherZone(class AWeatherSystemController* Controller, float MinWaitTime, float MaxWaitTime, float MinWeatherDuration, float MaxWeatherDuration);
};