// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "King.h"
#include "Board.h"

TArray<ATile*> AKnight::GetPossibleMoves()
{
	TArray<ATile*> moves = TArray<ATile*>();
	if (!(m_board->hasPiece(m_x + 1, m_y + 2)) || m_board->GetPiece(m_x + 1, m_y + 2)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y + 2))
		{
			moves.Add(m_board->GetTile(m_x + 1, m_y + 2));
		}
		
	}
	if (!(m_board->hasPiece(m_x + 2, m_y + 1)) || m_board->GetPiece(m_x + 2, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 2, m_y + 1))
		{
			moves.Add(m_board->GetTile(m_x + 2, m_y + 1));
		}	
	}
	if (!(m_board->hasPiece(m_x - 1, m_y - 2)) || m_board->GetPiece(m_x - 1, m_y - 2)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y - 2))
		{
			moves.Add(m_board->GetTile(m_x - 1, m_y - 2));
		}	

	}
	if (!(m_board->hasPiece(m_x - 2, m_y - 1)) || m_board->GetPiece(m_x - 2, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 2, m_y - 1))
		{
			moves.Add(m_board->GetTile(m_x - 2, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x + 1, m_y - 2)) || m_board->GetPiece(m_x + 1, m_y - 2)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y - 2))
		{
			moves.Add(m_board->GetTile(m_x + 1, m_y - 2));
		}
	}
	if (!(m_board->hasPiece(m_x + 2, m_y - 1)) || m_board->GetPiece(m_x + 2, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 2, m_y - 1))
		{
			moves.Add(m_board->GetTile(m_x + 2, m_y - 1));
		}	
	}
	if (!(m_board->hasPiece(m_x - 1, m_y + 2)) || m_board->GetPiece(m_x - 1, m_y + 2)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y + 2))
		{
			moves.Add(m_board->GetTile(m_x - 1, m_y + 2));
		}	
	}
	if (!(m_board->hasPiece(m_x - 2, m_y + 1)) || m_board->GetPiece(m_x - 2, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 2, m_y + 1))
		{
			moves.Add(m_board->GetTile(m_x - 2, m_y + 1));
		}
	}
	TArray<ATile*> f_moves = filterForNoCheck(moves, m_color);
	return f_moves;
}


TArray<ATile*> AKnight::GetPossibleMovesPrimitive() const
{
	TArray<ATile*> moves = TArray<ATile*>();
	if (!(m_board->hasPiece(m_x + 1, m_y + 2)) || m_board->GetPiece(m_x + 1, m_y + 2)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y + 2))
		{
			moves.Add(m_board->GetTile(m_x + 1, m_y + 2));
		}

	}
	if (!(m_board->hasPiece(m_x + 2, m_y + 1)) || m_board->GetPiece(m_x + 2, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 2, m_y + 1))
		{
			moves.Add(m_board->GetTile(m_x + 2, m_y + 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y - 2)) || m_board->GetPiece(m_x - 1, m_y - 2)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y - 2))
		{
			moves.Add(m_board->GetTile(m_x - 1, m_y - 2));
		}

	}
	if (!(m_board->hasPiece(m_x - 2, m_y - 1)) || m_board->GetPiece(m_x - 2, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 2, m_y - 1))
		{
			moves.Add(m_board->GetTile(m_x - 2, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x + 1, m_y - 2)) || m_board->GetPiece(m_x + 1, m_y - 2)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y - 2))
		{
			moves.Add(m_board->GetTile(m_x + 1, m_y - 2));
		}
	}
	if (!(m_board->hasPiece(m_x + 2, m_y - 1)) || m_board->GetPiece(m_x + 2, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 2, m_y - 1))
		{
			moves.Add(m_board->GetTile(m_x + 2, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y + 2)) || m_board->GetPiece(m_x - 1, m_y + 2)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y + 2))
		{
			moves.Add(m_board->GetTile(m_x - 1, m_y + 2));
		}
	}
	if (!(m_board->hasPiece(m_x - 2, m_y + 1)) || m_board->GetPiece(m_x - 2, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 2, m_y + 1))
		{
			moves.Add(m_board->GetTile(m_x - 2, m_y + 1));
		}
	}
	return moves;
}