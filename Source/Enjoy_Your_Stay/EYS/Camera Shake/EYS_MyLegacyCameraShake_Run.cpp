// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Camera Shake/EYS_MyLegacyCameraShake_Run.h"

UEYS_MyLegacyCameraShake_Run::UEYS_MyLegacyCameraShake_Run(const FObjectInitializer& Obj)
{

	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.2;

	bSingleInstance = true;
	RotOscillation.Pitch.Amplitude = 0.8f;
	RotOscillation.Pitch.Frequency = 18.0f;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Pitch.Waveform = EOscillatorWaveform::SineWave;

	RotOscillation.Yaw.Amplitude = 0.6f;
	RotOscillation.Yaw.Frequency = 9.0f;
	RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Yaw.Waveform = EOscillatorWaveform::SineWave;

	RotOscillation.Roll.Amplitude = 0.4f;
	RotOscillation.Roll.Frequency = 7.0f;
	RotOscillation.Roll.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Yaw.Waveform = EOscillatorWaveform::SineWave;
}
