// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <source_location>

/**
 *
 */
class MULTISHOOTER_API DebugLog
{
public:
	static void LogFLoat(float F);
	static void LogUint(uint64 U);
	static void LogVector(const FVector& Vector);
	static void DebugAssert(const std::source_location& assert_location = std::source_location::current());
};
