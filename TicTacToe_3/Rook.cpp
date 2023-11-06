// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"
#include "Board.h"

TArray<ATile*> ARook::GetPossibleMoves()
{
	TArray<ATile*> moves = TArray<ATile*>();
	int running_x = this->getX();
	int running_y = this->getY();
	running_x++;
	while (running_x < 8)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_x++;
	}
	running_x = this->getX();
	running_y++;
	while (running_y < 8)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_y++;
	}
	running_y = this->getY();
	running_x--;
	while (running_x >= 0)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_x--;
	}
	running_x = this->getX();
	running_y--;
	while (running_y >= 0)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_y--;
	}
	TArray<ATile*> f_moves = filterForNoCheck(moves, m_color);
	return f_moves;
}


TArray<ATile*> ARook::GetPossibleMovesPrimitive() const
{
	TArray<ATile*> moves = TArray<ATile*>();
	int running_x = this->getX();
	int running_y = this->getY();
	running_x++;
	while (running_x < 8)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_x++;
	}
	running_x = this->getX();
	running_y++;
	while (running_y < 8)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_y++;
	}
	running_y = this->getY();
	running_x--;
	while (running_x >= 0)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_x--;
	}
	running_x = this->getX();
	running_y--;
	while (running_y >= 0)
	{
		if ((!(m_board->hasPiece(running_x, running_y))) || m_board->GetPiece(running_x, running_y)->getColor() != m_color)
		{
			moves.Add(m_board->GetTile(running_x, running_y));
		}
		if (m_board->hasPiece(running_x, running_y))
		{
			break;
		}
		running_y--;
	}
	return moves;
}