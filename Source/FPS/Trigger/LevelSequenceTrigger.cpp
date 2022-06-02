// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceTrigger.h"

ALevelSequenceTrigger::ALevelSequenceTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SequencePlayer = nullptr;
	m_SequenceAsset = nullptr;

	m_Once = true;
	m_Play = false;
}

void ALevelSequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelSequenceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSequenceTrigger::BeginOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_SequenceAsset)
	{
		if (!m_SequencePlayer)
		{
			/*
			* FMovieSceneSequencePlaybackSettings 구조체로 세팅할 수 있는것 들
			bAutoPlay(false)
			PlayRate(1.f)
			StartTime(0.f)
			bRandomStartTime(false)
			bRestoreState(false)
			bDisableMovementInput(false)
			bDisableLookAtInput(false)
			bHidePlayer(false)
			bHideHud(false)
			bDisableCameraCuts(false)
			bPauseAtEnd(false)
			*/
			FMovieSceneSequencePlaybackSettings	PlaybackSetting;
			//PlaybackSetting.bAutoPlay = true;
			PlaybackSetting.bDisableMovementInput = true;	// 입력을 막는다.
			PlaybackSetting.bHidePlayer = true;				// 플레이어가 보이거나 움직이지 않도록 한다.
			PlaybackSetting.bRestoreState = true;			// 시퀀스 종료 후 상태 복구
			m_SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), m_SequenceAsset, PlaybackSetting, m_SequenceActor);

			m_SequencePlayer->OnFinished.AddDynamic(this, &ALevelSequenceTrigger::SequenceFinish);
		}

		if (m_Once)
		{
			if (!m_Play)
			{
				m_Play = true;
				m_SequencePlayer->Play();
			}
		}
		else
			m_SequencePlayer->Play();
	}
}

void ALevelSequenceTrigger::EndOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void ALevelSequenceTrigger::SequenceFinish()
{
	SequenceFinishOverride();
}

void ALevelSequenceTrigger::SequenceFinishOverride()
{
	for (auto& actor : m_DeleteActorArray)
	{
		actor->Destroy();
	}
}