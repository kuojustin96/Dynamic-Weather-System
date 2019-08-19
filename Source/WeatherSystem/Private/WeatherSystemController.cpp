// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherSystemController.h"
#include "Components/BillboardComponent.h"
#include "WeatherZone.h"
#include "WeatherType.h"
#include "WeatherType.h"

// Sets default values
AWeatherSystemController::AWeatherSystemController()
{
	Root = CreateDefaultSubobject<UBillboardComponent>(TEXT("Root"));
	Root->bHiddenInGame = true;
	RootComponent = Root;

	TransitionSpeed = 0.1f;
}


void AWeatherSystemController::BeginPlay()
{
	Super::BeginPlay();

	for (AWeatherZone* Zone : WeatherZones)
	{
		Zone->SetupWeatherZone(this, MinWaitTime, MaxWaitTime, MinWeatherDuration, MaxWeatherDuration);
	}
}


void AWeatherSystemController::SetCurrentWeatherZone(AWeatherZone* Zone)
{
	if (Zone == nullptr)
	{
		if (CurrentWeatherType == nullptr)
		{
			return;
		}
		else
		{
			DeactivateCurrentWeatherEffect();
		}
	}
	else
	{
		UWeatherType* Weather = Zone->GetCurrentWeatherDataAsset();
		if (CurrentWeatherType == Weather)
		{
			return;
		}

		DeactivateCurrentWeatherEffect();

		CurrentWeatherType = Weather;
		if (Weather != nullptr)
		{
			ActivateCurrentWeatherEffect(Weather);
		}
	}

	ActiveWeatherZone = Zone;
}


void AWeatherSystemController::ActivateWeather(UWeatherType* WeatherType)
{
	if (WeatherType != nullptr)
	{
		CurrentWeatherType = WeatherType;
		ActivateCurrentWeatherEffect(WeatherType);
	}
}


void AWeatherSystemController::DeactivateCurrentWeather()
{
	DeactivateCurrentWeatherEffect();
}


AWeatherZone* AWeatherSystemController::GetActiveWeatherZone()
{
	return ActiveWeatherZone;
}