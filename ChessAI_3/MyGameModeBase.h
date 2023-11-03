// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
class AChessPiece;
UCLASS()
class CHESSAI_3_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/**
	UFUNCTION(BlueprintCallable)
	void SetActivePiece(AChessPiece* Piece);
	UFUNCTION(BlueprintCallable)
	AChessPiece* GetActivePiece() const;

	UPROPERTY(BlueprintReadWrite)
	AChessPiece* m_ActivePiece;

	**/
	AMyGameModeBase();
};
