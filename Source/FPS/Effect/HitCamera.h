// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Camera/CameraShake.h"
#include "HitCamera.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UHitCamera : public UMatineeCameraShake
{
	GENERATED_BODY()
public:
	UHitCamera();
};
