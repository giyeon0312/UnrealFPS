// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	m_ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

	m_StartButton->OnClicked.AddDynamic(this, &UStartWidget::StartClick);
	m_ExitButton->OnClicked.AddDynamic(this, &UStartWidget::ExitClick);

	m_StartButton->OnHovered.AddDynamic(this, &UStartWidget::StartMouseOn);
	m_ExitButton->OnHovered.AddDynamic(this, &UStartWidget::ExitMouseOn);

	BindingAnimations();
}

void UStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartWidget::BindingAnimations()
{
	UProperty* Prop = GetClass()->PropertyLink;

	// �̱۸���Ʈ�� ����� ���·� ������ �ִ�.
	while (Prop != nullptr)
	{
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				// ValueAddress�� �ָ� UWidgetAnimation�� UObjectŸ������ �����´�.
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);

				UWidgetAnimation* Anim = Cast<UWidgetAnimation>(Obj);

				if (Anim != nullptr)
				{
					if (Anim->MovieScene->GetFName() == TEXT("StartScale"))
					{
						m_StartScaleAnim = Anim;
					}

					else if (Anim->MovieScene->GetFName() == TEXT("ExitScale"))
					{
						m_ExitScaleAnim = Anim;
					}
				}
			}
		}

		Prop = Prop->PropertyLinkNext;
	}
}

void UStartWidget::StartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(),
		TEXT("CharacterSelect"));
}

void UStartWidget::ExitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),	GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}



void UStartWidget::StartMouseOn()
{
	PlayAnimation(m_StartScaleAnim);
}

void UStartWidget::ExitMouseOn()
{
	PlayAnimation(m_ExitScaleAnim);
}
