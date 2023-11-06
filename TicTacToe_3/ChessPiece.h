// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EColor.h"
#include "Kismet/GameplayStatics.h"
#include "ChessPiece.generated.h"


class ATile;

UCLASS()
class CHESSAI_3_API AChessPiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChessPiece();

	virtual void Tick(float DeltaTime) override;
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	bool inBorder(int x, int y) const;
	TArray<ATile*> filterForNoCheck(TArray<ATile*> tiles, EColor color);
	EColor getColor() const;
	virtual TArray<ATile*> GetPossibleMovesPrimitive() const;
	virtual TArray<ATile*> GetPossibleMoves();

	UFUNCTION(BlueprintCallable)
	void PieceClicked();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	EColor m_color;

	UPROPERTY(EditAnywhere)
	int m_x;

	UPROPERTY(EditAnywhere)
	int m_y;


	class ABoard* m_board;
	UPROPERTY(BlueprintReadWrite)
	class AMyGameModeBase* GameModeRef1;
};
