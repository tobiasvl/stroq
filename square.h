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


#ifndef SQUARE_H
#define SQUARE_H

#include <qpoint.h>

class Square
{
public:
	/**
	 * The states that a Square can be in
	 */
	enum States {
		White, /**< A white square */
		Black, /**< A black square */
		Border /**< A border square */
	};
	
	/**
	 * Constructs a Square from a position and a state
	 *
	 * @param pos the position of the Square
	 * @param state the State of the Square
	 */
	Square(QPoint pos, States state);
	
	/**
	 * Virtual destructor
	 */
	virtual ~Square();
	
	/**
	 * Compares the equality for two Squares.
	 *
	 * @return True if they have the same position, false otherwise
	 */
	bool operator==(Square&);
	
	/**
	 * Compares the difference of two squares
	 *
	 * @return True if the two squares have different positions, false otherwise
	 */
	bool operator!=(Square&);
	
public:
	/**
	 * Returns the position of the Square in the puzzle
	 *
	 * @return the position of the Square in the puzzle
	 */
	QPoint getGridPos() { return m_pqpGridPos; }
	
	/**
	 * Returns the state of the Square
	 *
	 * @return the State of the Square
	 */
	Square::States getState() { return m_sState; }
	
	/**
	 * Sets the state of the Square
	 *
	 * @param state the State to which to set the Square to
	 */
	void setState(Square::States state);
	
	/**
	 * Toggles the square (white to black, black to white, border to border)
	 * Doesn't change Squares that are in Border state
	 */
	void toggle();
	
protected:
	States m_sState;      /**< State the Square is in */
	QPoint m_pqpGridPos;  /**< Position of the Square in the puzzle  */
};

#endif
