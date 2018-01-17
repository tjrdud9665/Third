// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.generated.h"


/*
	�������̽� �ݰ� �������̽� �޽����� �ִ�.
	�������Ʈ���� �������̽� �޽���������ϰ������� ������ ���� �����ϰ� 
	�������̽� �޽����� ����Ұ�� �������̽��� �������θ� Ȯ����
	Execute_FunctionName �� �̿��ؼ� ȣ��

	**Interface �� ������ Ȯ��
	�������̽� �������θ� �� �ʿ䰡 ���ٸ� 
	������ ���� ȣ���ؼ� ������ ���ٸ� ���µ��� �����ڵ带 �����Ѵ�.
	

	IInteractableInterface::Execute_GetUseDistance(CurrentTarget);
	WIKI ��ó : https://wiki.unrealengine.com/Interfaces_in_C%2B%2B

*/


// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UInteractableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()


};

/**
 * 
 */
class THIRD_API IInteractableInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	 bool BeginFocus()									;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	 bool EndFocus()										;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	 float GetUseDistance()								;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	 bool GetIsUsable()									;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	 bool OnUsed(class APlayerController* Controller)	;


	
};
