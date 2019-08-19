// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherType.h"


UWeatherType::UWeatherType()
{
	WeatherName = FString("None");
	MPC_ParamName = FName("None");
	MPC_TransitionTime = 10.0f;
	SunBrightness = 75.0f;
	CloudSpeed = 2.0f;
	CloudOpacity = 1.0f;
	HorizonFalloff = 3.0f;
}