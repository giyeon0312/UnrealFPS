// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "EngineGlobals.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/WidgetComponent.h"
#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

// ������ ����Ʈ ��� 
void PrintViewport(float Time, const FColor& Color, const FString& Text);


DECLARE_LOG_CATEGORY_EXTERN(FPS, Log, All);
#define LOG_CALLINFO	(FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")")) // �Լ������� ���ڿ��� ��Ÿ���� �Լ�
#define LOG(Format, ...) UE_LOG(FPS,Warning,TEXT("%s : %s"),*LOG_CALLINFO,*FString::Printf(Format,##__VA_ARGS__)) // �������ڷ� ���ڸ� ������


UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	Knight,
	Archer,
	Magicion
};


USTRUCT(BlueprintType)
struct FPlayerTableInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EPlayerJob		Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		MoveSpeed;
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,	// ����
	Armor,  // ��
	HPPotion,
	MPPotion
};

UENUM(BlueprintType)
enum class EItemOption :uint8
{
	Attack,
	Armor,
	HP,
	MP,
	Critical,
	HPRecovery,
	MPRecovery
};

USTRUCT(BlueprintType)
struct FItemOptionInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EItemOption OptionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Option;
};


USTRUCT(BlueprintType)
struct FItemTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EItemType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	//FItemOptionInfo Option;
	TArray< FItemOptionInfo> OptionArray;
};


USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EPlayerJob		Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		MoveSpeed;
};


USTRUCT(BlueprintType) // �������Ʈ������ ����Ҽ� �մ� ����ü�� �߰��Ͽ���.
struct FMonsterTableInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	FString Name;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)); // ���ݷ�
	int32 Attack;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)); // ����
	int32 Armor;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	int32 HP;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	int32 HPMax;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	int32 MP;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	int32 MPMax;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	int32 Level;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))	// ����� �� ȹ���� �� �ִ� ����ġ
	int32		Exp;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true));
	float AttackDistance;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)); // Player �߰� �� �Ѿư� �� �ִ� �����Ÿ�
	float TraceDistance;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)); // ���ݼӵ�
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)); // �̵� �ӵ�
	float MoveSpeed;
};


USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32		Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float		MoveSpeed;

};

UENUM(BlueprintType)
enum class EPlayerAnim : uint8
{
	Ground,
	Jump,
	Fall,
	Hit,
	Death
};

UENUM(BlueprintType)
enum class EMonsterAnim : uint8
{
	Idle,
	Run,
	Attack,
	Death,
	Skill1,
	Skill2,
	Skill3,
	Skill4

};

UENUM(BlueprintType)
enum class EMonsterPatrolType : uint8
{
	Loop,
	Inverse
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Collection, 	// ������
	Hunt,	  	// �����
	Communication    // ��ȭ��
};

UENUM(BlueprintType)
enum class EQuestCategory : uint8
{
	Part1,
	Part2,
	Part3
};

//���� ������ ����
USTRUCT(BlueprintType)
struct FQuestInfo
{
	GENERATED_BODY()

public:
	FQuestInfo()
	{
		Type = EQuestType::Collection;
		Count = 0;
		CountMax = 0;
		Complete = false;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EQuestType		Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString			Dest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32			Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32			CountMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool			Complete;
};

UENUM(BlueprintType)
enum class EQuest_Compensation : uint8
{
	Gold,
	Exp,
	Item
};

USTRUCT(BlueprintType)
struct FQuestCompensation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EQuest_Compensation	Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString				Name;
};

USTRUCT(BlueprintType)
struct FQuestTableInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString		Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EQuestCategory		Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString			QuestDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<FQuestInfo>	InfoArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<FQuestCompensation>	CompensationArray;
};

enum class EListSelect : uint8
{
	None,
	MouseOn,
	Select
};

UCLASS()
class FPS_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
