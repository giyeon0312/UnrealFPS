// Fill out your copyright notice in the Description page of Project Settings.


#include "HitCamera.h"

UHitCamera::UHitCamera()
{
	OscillationDuration = 0.8f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.1f;

	LocOscillation.Y.Amplitude = 2.f;
	LocOscillation.Y.Frequency = 100.f;
	LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;

	LocOscillation.Z.Amplitude = 2.f;
	LocOscillation.Z.Frequency = 100.f;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;

	bSingleInstance = true;
}
