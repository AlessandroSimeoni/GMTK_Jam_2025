// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/GMTKSave.h"

void UGMTKSave::SaveTimeToLevel(FString LevelName, float Time)
{
	if (TimeInLevels.Find(LevelName))
	{
		float OldTime = TimeInLevels[LevelName];
		if (Time < OldTime)
		{
			TimeInLevels[LevelName] = Time;
		}
	}
	else
	{
		TimeInLevels.Add(LevelName, Time);
	}
}

void UGMTKSave::GetLevelNames(TArray<FString>& Keys)
{
	TimeInLevels.GetKeys(Keys);
}
