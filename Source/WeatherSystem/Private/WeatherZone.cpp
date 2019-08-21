// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherZone.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "WeatherSystemController.h"
#include "TimerManager.h"
#include "WeatherType.h"

// Sets default values
AWeatherZone::AWeatherZone()
{
	Root = CreateDefaultSubobject<UBillboardComponent>("Root");
	Root->bHiddenInGame = true;
	RootComponent = Root;

	Zone = CreateDefaultSubobject<UBoxComponent>("Zone");
	Zone->SetMobility(EComponentMobility::Stationary);
	Zone->SetupAttachment(Root);

	bOverrideControllerTimers = false;
	bIsActive = false;
	MinWaitTime = -1.0f;
	MaxWaitTime = -1.0f;
	MinWeatherDuration = -1.0f;
	MaxWeatherDuration = -1.0f;

	NextWeatherTypeInt = 0;
	CurrentWeatherTypeInt = -1;

	bNeedsToDeactivate = true;
}


void AWeatherZone::BeginPlay()
{
	Super::BeginPlay();

	for (UActorComponent* Comp : GetComponents())
	{
		UShapeComponent* Trigger = Cast<UShapeComponent>(Comp);
		if (Trigger != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding component overlaps"));
			Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWeatherZone::OnZoneBeginOverlap);
			Trigger->OnComponentEndOverlap.AddDynamic(this, &AWeatherZone::OnZoneEndOverlap);
		}
	}
}


void AWeatherZone::OnZoneBeginOverlap(class UPrimitiveComponent* OverlapComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (WeatherSystemController == nullptr)
	{
		return;
	}

	if (bIsActive == true)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));

	bIsActive = true;
	WeatherSystemController->SetCurrentWeatherZone(this);
}


void AWeatherZone::OnZoneEndOverlap(class UPrimitiveComponent* OverlapComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (WeatherSystemController == nullptr)
	{
		return;
	}

	if (bNeedsToDeactivate == false)
	{
		bIsActive = false;
		bNeedsToDeactivate = true;
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("End Overlapped"));

	bIsActive = false;
	WeatherSystemController->SetCurrentWeatherZone(nullptr);
}


void AWeatherZone::SetupWeatherZone(AWeatherSystemController* Controller, float MinWaitTime, float MaxWaitTime, float MinWeatherDuration, float MaxWeatherDuration)
{
	WeatherSystemController = Controller;

	if (bOverrideControllerTimers == false)
	{
		this->MinWaitTime = MinWaitTime;
		this->MaxWaitTime = MaxWaitTime;
		this->MinWeatherDuration = MinWeatherDuration;
		this->MaxWeatherDuration = MaxWeatherDuration;
	}

	SetupNextWeatherType();
}


void AWeatherZone::SetupNextWeatherType()
{
	//Replace with -1 for normal behavior
	NextWeatherTypeInt = GetRandomNumberInRange(0, WeatherTypes.Num() - 1);

	float TimeToWeather = GetRandomNumberInRange(MinWaitTime, MaxWaitTime);

	FTimerHandle WaitTimerHandle;
	GetWorldTimerManager().SetTimer(WaitTimerHandle, this, &AWeatherZone::EnableWeatherType, TimeToWeather);
}


void AWeatherZone::EnableWeatherType()
{
	if (NextWeatherTypeInt != CurrentWeatherTypeInt)
	{
		CurrentWeatherTypeInt = NextWeatherTypeInt;

		UWeatherType* Weather;
		if (NextWeatherTypeInt == -1)
		{
			Weather = nullptr;
		}
		else
		{
			Weather = WeatherTypes[CurrentWeatherTypeInt];
		}

		if (bIsActive)
		{
			WeatherSystemController->SetCurrentWeatherZone(this);
		}
	}

	float WeatherDuration = GetRandomNumberInRange(MinWeatherDuration, MaxWeatherDuration);

	FTimerHandle DurationTimerHandle;
	GetWorldTimerManager().SetTimer(DurationTimerHandle, this, &AWeatherZone::DisableWeatherType, WeatherDuration);
}

void AWeatherZone::DisableWeatherType()
{
	SetupNextWeatherType();

	if (bIsActive && NextWeatherTypeInt != CurrentWeatherTypeInt)
	{
		WeatherSystemController->DeactivateCurrentWeather();
	}
}


inline float AWeatherZone::GetRandomNumberInRange(float MinNum, float MaxNum)
{
	return FMath::RandRange(MinNum, MaxNum);
}


UWeatherType* AWeatherZone::GetCurrentWeatherDataAsset()
{
	if (CurrentWeatherTypeInt > -1)
	{
		return WeatherTypes[CurrentWeatherTypeInt];
	}
	else
	{
		return nullptr;
	}
}


inline int AWeatherZone::GetRandomNumberInRange(int MinNum, int MaxNum)
{
	return FMath::RandRange(MinNum, MaxNum);
}