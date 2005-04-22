/*
 This file is part of StroQ, Copyright (C) 2005 Luc Vo Van
 
 StroQ is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the
 Free Software Foundation; either version 2, or (at your option) any
 later version.
 
 StroQ is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.
 
 You should have received a copy of the GNU General Public License
 along with StroQ; see the file COPYING.  If not, write to
 the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 Boston, MA 02111-1307, USA.
 
 Class          :   Square
 Author         :   Luc Vo Van
 Original Date  :   18.05.2005
 Description    :   The basic element of which a Puzzle is made up. It can
                    have three different states (white, black, border).
 
 */

#include "square.h"


Square::Square(QPoint pos, States state){
	m_pqpGridPos = pos;
	m_sState = state;
}


Square::~Square()
{

}


void Square::toggle()
{
	switch(m_sState) {
		case White:
			m_sState = Black;
			break;
		case Black:
			m_sState = White;
			break;
		case Border:
			break; // You can't toggle a Border :)
	}
}


void Square::setState(Square::States state)
{
	m_sState = state;
}


bool Square::operator==(Square& square)
{
	return(m_pqpGridPos == square.getGridPos());
}


bool Square::operator!=(Square& square)
{
	return(m_pqpGridPos != square.getGridPos());
}
