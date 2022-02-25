// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterAIController.h"
#include "NormalMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ANormalMonsterAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
public:
	ANormalMonsterAIController();

protected:
	virtual void OnPossess(APawn* InPawn); //AI��Ʈ�ѷ��� ���� ���ǵǰ� ���� �����ɶ� ȣ��Ǵ� �Լ�
	virtual void OnUnPossess();
};

