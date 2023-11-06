// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "ChessPiece.h"
#include "PlayerController_C.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = APlayerController_C::StaticClass();
}
/**
void AMyGameModeBase::SetActivePiece(AChessPiece* Piece)
{
	m_ActivePiece = Piece;
}

AChessPiece* AMyGameModeBase::GetActivePiece() const
{
	return m_ActivePiece;
}
*/
