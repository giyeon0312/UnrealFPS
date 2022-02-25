// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "../Item/Weapon.h"
#include "../FPSGameInstance.h"
#include "../FPSGameModeBase.h"
#include "../UI/MainWidget.h"
#include "../UI/CharacterStateHUD.h"
#include "../UI/InventoryWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Z축으로 -90도 회전
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	// (씬컴포넌트 이므로)부모컴포넌트를 지정한다.
	m_Arm->SetupAttachment(GetCapsuleComponent());
	m_Camera->SetupAttachment(m_Arm);

	m_Arm->TargetArmLength = 300;
	m_Arm->TargetOffset = FVector(0.f, 0.f, 100.f);
	m_Arm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f)); //피치회전

	m_MoveKey = false;
	m_AttackEnable = true;
	m_Death = false;

	GetCharacterMovement()->JumpZVelocity = 600.f;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	// 데칼 적용이 안되게 한다.
	GetMesh()->SetReceivesDecals(false);

	m_Weapon = nullptr;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// AnimInstance 객체를 얻어온다.
	// UAnimInstance타입을 가져오므로 캐스팅이 필요하다.
	m_AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const FPlayerTableInfo* TableInfo = GameInst->FindPlayerInfo(m_Info.Name);

		if (TableInfo)
		{	
			UE_LOG(LogTemp, Log, TEXT("Table Loaded"));
			m_Info.Name = TableInfo->Name;
			m_Info.Job = TableInfo->Job;
			m_Info.Attack = TableInfo->Attack;
			m_Info.Armor = TableInfo->Armor;
			m_Info.HP = TableInfo->HP;
			m_Info.HPMax = TableInfo->HPMax;
			m_Info.MP = TableInfo->MP;
			m_Info.MPMax = TableInfo->MPMax;
			m_Info.Level = TableInfo->Level;
			m_Info.Gold = TableInfo->Gold;
			m_Info.Exp = TableInfo->Exp;
			m_Info.AttackDistance = TableInfo->AttackDistance;
			m_Info.AttackSpeed = TableInfo->AttackSpeed;
			m_Info.MoveSpeed = TableInfo->MoveSpeed;

			//GetCharacterMovement()->MaxWalkSpeed = m_Info.MoveSpeed;
		}

		//else
		//	m_Info.Attack = 30.f;
	}

	AFPSGameModeBase* GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GetMainWidget()->GetCharacterStateHUD()->SetNameText(m_Info.Name);
		GameMode->GetMainWidget()->GetInventory()->SetGold(m_Info.Gold);
		

	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = DamageAmount - m_Info.Armor; // 데미지 - 몬스터의 방어력

	Dmg = Dmg <= 0.f ? 1.f : Dmg; //최소데미지 1

	Dmg = Super::TakeDamage(Dmg, DamageEvent, EventInstigator, DamageCauser); //Dmg값을 넣어서 0이 나오면 무적이고 아님 원본값이 그대로 나오면 값을 빼줄것이다.

	if (Dmg > 0.f)
	{
		//m_AnimInstance->Hit();
	}

	m_Info.HP -= (int32)Dmg;

	if (m_Info.HP <= 0)
	{
		m_Info.HP = 0;
	}

	PrintViewport(3.f, FColor::Red, FString::Printf(TEXT("Dmg : %.5f HP :%d Percent : %f"),Dmg,m_Info.HP, (float)m_Info.HP / m_Info.HPMax));
	
	AFPSGameModeBase* GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GetMainWidget()->GetCharacterStateHUD()->SetHPPercent((float)m_Info.HP / m_Info.HPMax);
	}

	return Dmg;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 바인드한 순서대로 인식한다.
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &APlayerCharacter::RotationZ);
	PlayerInputComponent->BindAxis(TEXT("CameraLookUp"), this, &APlayerCharacter::CameraLookUp);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &APlayerCharacter::CameraZoom);

	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &APlayerCharacter::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &APlayerCharacter::MoveSide);


	PlayerInputComponent->BindAction(TEXT("NormalAttack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::NormalAttackKey);
	PlayerInputComponent->BindAction(TEXT("JumpKey"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpKey);
	PlayerInputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Skill1Key);

	PlayerInputComponent->BindAction(TEXT("WeaponAttach"), EInputEvent::IE_Pressed, this, &APlayerCharacter::WeaponAttachKey);
	PlayerInputComponent->BindAction(TEXT("WeaponDetach"), EInputEvent::IE_Pressed, this, &APlayerCharacter::WeaponDetachKey);
}


void APlayerCharacter::RotationZ(float Scale)
{
	AddControllerYawInput(Scale);
}

void APlayerCharacter::CameraLookUp(float Scale) // 플레이어에 달린 카메라암을 돌릴것이다.
{
	FRotator Rot = m_Arm->GetRelativeRotation();

	Rot.Pitch += Scale * 20.f * GetWorld()->GetDeltaSeconds(); // 초당 20도만큼 회전

	if (Rot.Pitch > -15.f)
		Rot.Pitch = -15.f;
	else if (Rot.Pitch < -45.f)
		Rot.Pitch = -45.f;

	m_Arm->SetRelativeRotation(Rot);
}


void APlayerCharacter::CameraZoom(float Scale)
{
	m_Arm->TargetArmLength -= Scale * 20.f; //휠의 한 팁당 20정도 이동하도록

	if (m_Arm->TargetArmLength < 30.f)
		m_Arm->TargetArmLength = 30.f;
	else if (m_Arm->TargetArmLength > 300.f)
		m_Arm->TargetArmLength = 300.f;
}



void APlayerCharacter::MoveFront(float Scale)
{	
	// 루트컴포넌트(캡슐)를 움직인다.
	AddMovementInput(GetActorForwardVector(), Scale); //월드디렉션(방향)에 액터의 전방을 가져오는 벡터를 넣고 1이면 앞으로 -1이면 뒤로 움직인다.

	m_MoveKey = false;

	if (Scale == 0.f)	   // 가만히 있을 때
	{
		m_AnimInstance->SetDir(0.f);
	}
	else if (Scale == 1.f) // 앞으로 갈 때
	{
		m_MoveKey = true;
		m_AnimInstance->SetDir(0.f);
	}
	else				   // 뒤로 갈 때
	{
		m_MoveKey = true;
		m_AnimInstance->SetDir(180.f);
	}

}


void APlayerCharacter :: MoveSide(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);

	float Dir = m_AnimInstance->GetDir();

	if (Scale == 1.f)
	{
		// 위에서 앞, 뒤로 이동하는 키를 안눌렀을 경우
		if (!m_MoveKey)
		{
			m_AnimInstance->SetDir(90.f); // 오른쪽
		}
		else
		{
			// 앞으로 갈때 오른쪽으로 간다면 오른쪽 전방 대각선 방향으로 이동하는 것이다.
			if (Dir == 0.f)
				m_AnimInstance->SetDir(45.f);
			else
				m_AnimInstance->SetDir(135.f); // 오른쪽 뒤로 135

		}
	}
	else if (Scale == -1.f)
	{
		// 위에서 앞, 뒤로 이동하는 키를 안눌렀을 경우
		if (!m_MoveKey)
		{
			m_AnimInstance->SetDir(-90.f); // 왼쪽
		}
		else
		{
			// 앞으로 갈때 왼쪽으로 간다면 왼쪽 전방 대각선 방향으로 이동하는 것이다.
			if (Dir == 0.f)
				m_AnimInstance->SetDir(-45.f);
			else
				m_AnimInstance->SetDir(-135.f); // 왼쪽 뒤로 -135

		}
	}

}

void APlayerCharacter::NormalAttackKey()
{
	if (m_AttackEnable)
	{
		m_AttackEnable = false;
		NormalAttack();
	}

}

void APlayerCharacter::NormalAttack()
{

}

void APlayerCharacter::AttackEnd()
{
	m_AttackEnable = true;
}

void APlayerCharacter::JumpKey()
{
	if (m_Death)
		return;

	if (GetCharacterMovement()->IsMovingOnGround()) // 땅 위에 있으면 true 아니면 false
	{
		Jump();										// 부모인 캐릭터 클래스에 이미 점프가 만들어져 있다.

		m_AnimInstance->ChangeAnim(EPlayerAnim::Jump);

		//PrintViewport(1.f, FColor::Red, TEXT("jump!"));
	}
}

void APlayerCharacter::PlayFallRecovery()
{
	if (!m_FallRecoveryMontage) // 없으면 return
		return;

	//if (!m_AnimInstance->Montage_IsPlaying(m_FallRecoveryMontage))
	{
		m_AnimInstance->Montage_SetPosition(m_FallRecoveryMontage, 0.f);//몽타주의 플레이 위치를 처음으로 되돌려준다.

		m_FallRecoveryMontage->BlendIn.SetBlendTime(0.1f);
		m_FallRecoveryMontage->BlendOut.SetBlendTime(0.1f);

		m_AnimInstance->Montage_Play(m_FallRecoveryMontage);
		m_AttackEnable = true;
	}
}

void APlayerCharacter::Skill1Key()
{
	if (!m_SkillMontageArr[0] || !GetCharacterMovement()->IsMovingOnGround())
		return;

	//if (!m_AnimInstance->Montage_IsPlaying(m_FallRecoveryMontage))
	{
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArr[0], 0.f);//몽타주의 플레이 위치를 처음으로 되돌려준다.

		m_SkillMontageArr[0]->BlendIn.SetBlendTime(0.1f);
		m_SkillMontageArr[0]->BlendOut.SetBlendTime(0.1f);

		m_AnimInstance->Montage_Play(m_SkillMontageArr[0]);
		m_AttackEnable = true;
	}
}

void  APlayerCharacter::Skill1()
{

}


void APlayerCharacter::SetWeapon(UStaticMesh* WeaponMesh)
{
	if (!m_Weapon)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		m_Weapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		m_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SideWeapon"));
	}

	m_Weapon->SetMesh(WeaponMesh);
}

void APlayerCharacter::AddHP(int32 HP)
{
	m_Info.HP += HP;

	if (m_Info.HP > m_Info.HPMax)
		m_Info.HP = m_Info.HPMax;
}

void APlayerCharacter::AddMP(int32 MP)
{
	m_Info.MP += MP;

	if (m_Info.MP > m_Info.MPMax)
		m_Info.MP = m_Info.MPMax;

}

void APlayerCharacter::WeaponAttachKey()
{
	if (!m_Weapon)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		m_Weapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		////m_Weapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform,	TEXT("SideWeapon"));
		m_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SideWeapon"));

		m_Weapon->SetMesh(TEXT("StaticMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SM_Blade_BlackKnight.SM_Blade_BlackKnight'"));
	}

}

void APlayerCharacter::WeaponDetachKey()
{
	if (m_Weapon)
	{
		PrintViewport(1.f, FColor::Red, TEXT("DetachKeyPressed"));
		m_Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); // 무기의 위치 world 정보를 유지하면서 무기를 때겠다.
		//m_Weapon->SimulatePhysics(true); // 무기를 떼기 위해 물리를 넣었다.
	}
}

void APlayerCharacter::AttackEnable()
{

}