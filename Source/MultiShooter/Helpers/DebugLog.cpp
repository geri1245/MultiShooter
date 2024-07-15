// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugLog.h"

void DebugLog::LogFLoat(float F)
{
	UE_LOG(LogTemp, Warning, TEXT("Float = %f"), F);
}

void DebugLog::LogUint(uint64 U)
{
	UE_LOG(LogTemp, Warning, TEXT("Uint = %u"), U);
}

void DebugLog::LogVector(const FVector& Vector)
{
	UE_LOG(LogTemp, Warning, TEXT("X = %f, Y = %f, Z = %f"), Vector.X, Vector.Y, Vector.Z);
}

void DebugLog::DebugAssert(const std::source_location& assert_location)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 20.0f, FColor::Magenta,
			FString::Format(
				TEXT("Assert in file: {0}, function: {1}, line: {2}"), {assert_location.file_name(), assert_location.function_name(), assert_location.line()}));
	}
}
