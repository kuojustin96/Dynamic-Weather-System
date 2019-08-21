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
	CurrentWeatherType = DefaultWeatherType;
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
	if (ActiveWeatherZone != nullptr)
	{
		if (Zone != nullptr)
		{
			//Player moving from one zone to another
			UWeatherType* Weather = Weather = Zone->GetCurrentWeatherDataAsset();
			if (CurrentWeatherType != Weather)
			{
				if (Weather == nullptr)
				{
					Weather = DefaultWeatherType;
				}

				ActiveWeatherZone->bNeedsToDeactivate = false;
				CurrentWeatherType = Weather;
				TransitionBetweenWeatherEffects();
			}
		}
		else
		{
			//Player leaving for a non-zoned area
			DeactivateCurrentWeather();
		}
	}
	else
	{
		//Can assume that zone is not null here
		UWeatherType* Weather = Weather = Zone->GetCurrentWeatherDataAsset();
		if (CurrentWeatherType != Weather)
		{
			if (Weather == nullptr)
			{
				Weather = DefaultWeatherType;
			}

			ActivateWeather(Weather);
		}
	}

	ActiveWeatherZone = Zone;
}


void AWeatherSystemController::ActivateWeather(UWeatherType* WeatherType)
{
	if (WeatherType != nullptr)
	{
		CurrentWeatherType = WeatherType;
		ActivateCurrentWeatherEffect();
	}
}


void AWeatherSystemController::DeactivateCurrentWeather()
{
	CurrentWeatherType = DefaultWeatherType;
	DeactivateCurrentWeatherEffect();
}


AWeatherZone* AWeatherSystemController::GetActiveWeatherZone()
{
	return ActiveWeatherZone;
}