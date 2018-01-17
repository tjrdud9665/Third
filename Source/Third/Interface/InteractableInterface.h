// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.generated.h"


/*
	인터페이스 콜과 인터페이스 메시지가 있다.
	블루프린트에서 인터페이스 메시지를사용하고싶은경우 다음과 같이 구현하고 
	인터페이스 메시지를 사용할경우 인터페이스의 구현여부를 확인후
	Execute_FunctionName 을 이용해서 호출

	**Interface 의 다형성 확장
	인터페이스 구현여부를 알 필요가 없다면 
	다음과 같이 호출해서 구현이 없다면 없는데로 다음코드를 수행한다.
	

	IInteractableInterface::Execute_GetUseDistance(CurrentTarget);
	WIKI 출처 : https://wiki.unrealengine.com/Interfaces_in_C%2B%2B

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
