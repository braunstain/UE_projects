// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Tile.generated.h"

UENUM(BlueprintType)
enum class EColor : uint8{
		White,
		Red,
		Blue
	};

UCLASS()
class TICTACTOE_3_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	EColor GetColor() const;

	UFUNCTION(BlueprintCallable)
	void SetColor(EColor new_color);

	UFUNCTION(BlueprintCallable)
	void setOptions();

	UFUNCTION(BlueprintCallable)
	ATile* selectTile();


	UFUNCTION(BlueprintCallable)
	ATile* selectTile2();


	UFUNCTION(BlueprintCallable)
	void PlayerChooseTile();

	UFUNCTION(BlueprintCallable)
	void AIChooseTile();

	UFUNCTION(BlueprintCallable)
	bool Won(EColor color) const;

	int ScoreBoard() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_mesh;

	UPROPERTY(EditAnywhere)
	int m_x;

	UPROPERTY(EditAnywhere)
	int m_y;

	UPROPERTY(BlueprintReadWrite)
	TArray<ATile*> m_board;

	UPROPERTY(EditAnywhere)
	EColor m_color = EColor::White;


	TArray<ATile*> m_options;

	UPROPERTY(BlueprintReadWrite)
	int options_size;

};
