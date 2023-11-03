// Fill out your copyright notice in the Description page of Project Settings.

#include "Soldier.h"
#include "ChessPiece.h"
#include "Board.h"

void ASoldier::BeginPlay()
{
	Super::BeginPlay();
}

TArray<ATile*> ASoldier::GetPossibleMoves() 
{
	TArray<ATile*> moves = TArray<ATile*>();
	TArray<ATile*> moves_p = GetPeacfulMoves();
	TArray<ATile*> moves_a = GetAttackingMoves();
	for (ATile* tile : moves_p)
	{
		moves.Add(tile);
	}
	for (ATile* tile : moves_a)
	{
		moves.Add(tile);
	}
	TArray<ATile*> f_moves = filterForNoCheck(moves, m_color);
	return f_moves;
}

TArray<ATile*> ASoldier::GetPeacfulMoves() const
{
	TArray<ATile*> moves = TArray<ATile*>();
	if (m_color == EColor::Black)
	{
		if (m_board->hasPiece(m_x, m_y - 1) == false && inBorder(m_x, m_y - 1))
		{
			moves.Add(m_board->GetTile(m_x, m_y - 1));
		}
		if (b_first_move && m_board->hasPiece(m_x, m_y - 2) == false && inBorder(m_x, m_y - 2))
		{
			moves.Add(m_board->GetTile(m_x, m_y - 2));
		}
	}
	if (m_color == EColor::White)
	{
		if (m_board->hasPiece(m_x, m_y + 1) == false && inBorder(m_x, m_y + 1))
		{
			moves.Add(m_board->GetTile(m_x, m_y + 1));
		}
		if (b_first_move && m_board->hasPiece(m_x, m_y + 2) == false && inBorder(m_x, m_y + 2))
		{
			moves.Add(m_board->GetTile(m_x, m_y + 2));
		}
	}
	return moves;

}

TArray<ATile*> ASoldier::GetAttackingMoves() const
{
	TArray<ATile*> moves = TArray<ATile*>();
	if (m_color == EColor::Black)
	{
		if (m_board->hasPiece(m_x - 1, m_y - 1) && m_board->GetPiece(m_x - 1, m_y - 1)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(m_x - 1, m_y - 1));

		}
		if (m_board->hasPiece(m_x + 1, m_y - 1) && m_board->GetPiece(m_x + 1, m_y - 1)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(m_x + 1, m_y - 1));
		}
	}
	if (m_color == EColor::White)
	{
		if (m_board->hasPiece(m_x - 1, m_y + 1) && m_board->GetPiece(m_x - 1, m_y + 1)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(m_x - 1, m_y + 1));

		}
		if (m_board->hasPiece(m_x + 1, m_y + 1) && m_board->GetPiece(m_x + 1, m_y + 1)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(m_x + 1, m_y + 1));

		}
	}
	return moves;
}

void ASoldier::SetFirstMoveToFalse()
{
	b_first_move = false;
}

TArray<ATile*> ASoldier::GetPossibleMovesPrimitive() const
{
	TArray<ATile*> moves = TArray<ATile*>();
	TArray<ATile*> moves_p = GetPeacfulMoves();
	TArray<ATile*> moves_a = GetAttackingMoves();
	for (ATile* tile : moves_p)
	{
		moves.Add(tile);
	}
	for (ATile* tile : moves_a)
	{
		moves.Add(tile);
	}
	return moves;
}