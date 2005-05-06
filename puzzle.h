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
 
 Class          :   Puzzle
 Author         :   Luc Vo Van
 Original Date  :   18.05.2005
 Description    :   A Puzzle contains dimensions, Squares, hint positions
                    and can return a unique code which can be used for
                    its reconstruction. It is what the player will try to
					solve.
 
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <qpoint.h>
#include <vector>

#include "square.h"

class Puzzle
{
public:
	/**
	 * Builds a Puzzle from its code
	 *
	 * @param code the Puzzle code from which to build
	 */
	Puzzle(QString code); 
	
	/**
	 * Builds a Puzzle
	 *
	 * @param width number of columns
 	 * @param width number of rows
 	 * @param sol1 Coordinate of the start of a solution
	 * @param sol2 Coordinate of the end of a solution
	 * @param state State to which to set the Squares of this puzzle
	 */
	Puzzle(int width, int height, QPoint sol1, QPoint sol2,
		   Square::States state = Square::Border);
	
	/**
	 * Builds a Puzzle by making an exact copy of the given puzzle. Even
	 * the Squares present in the given Puzzle are copied, so that
	 * changing the resulting Puzzle will NOT modify the original one.
	 *
	 * @param srcpuzzle Puzzle to copy from
	 */
	Puzzle(Puzzle* srcpuzzle);

	/**
	 * Builds a puzzle made of PlaySquares that represent the same Puzzle
	 * as the given parameter. This is used to copy a Puzzle loaded from a
	 * code to a displayable Puzzle.
	 *
	 * @param srcpuzzle Puzzle to copy from
	 * @param canvas QCanvas on which to display the resulting puzzle
	 */
	Puzzle(Puzzle* srcpuzzle, QCanvas* canvas);
	
	/**
	 * Builds a puzzle made of PlaySquares given a code. See previous
	 * method.
	 */
	Puzzle::Puzzle(QString code, QCanvas *canvas);
	
	/**
	 * Class destructor
	 */
	~Puzzle();
	
	/**
	 * Returns true if the given code is valid, false otherwise
	 *
	 * @param code the code to check
	 */
	static bool isCodeValid(QString code);

	
	/**
	 * Sets a Square on the Puzzle. The Square contains the coordinates
	 * for which it will be stored. The previous square at that position
	 * is deleted.
	 * Caller should pass the Square object and not delete it. (Pass and
	 * forget)
	 *
	 * @param square Square to set
	 */
	void setSquare(Square* square);
	
	/**
	 * Returns the Square present at the given position in the Puzzle
	 *
	 * @param x row number of the wanted Square (borders start at 0)
 	 * @param y column number of the wanted Square (borders start at 0)
	 * @return the Square at (x, y) on the Puzzle
	 */
	Square* getSquareAt(int x, int y);
	
	/**
	 * Returns the number of squares making up the width of the Puzzle
	 * (number of columns)
	 * @see getHeight()
	 *
	 * @return number of columns in the Puzzle
	 */
	int getWidth();
	
	/**
	 * Returns the number of squares making up the height of the Puzzle
	 * (number of rows)
	 * @see getWidth()
	 *
	 * @return number of rows in the Puzzle
	 */
	int getHeight();
	
	/**
	 * Returns the coordinate of the start of a solution
	 * @see getSolutionEnd()
	 *
	 * @return the coordinate of the end of a solution
	 */
	QPoint getSolutionStart();
	
	/**
	 * Returns the coordinate of the end of a solution
	 * @see getSolutionStart()
	 *
	 * @return the coordinate of the end of a solution
	 */
	QPoint getSolutionEnd();
	
	/**
	 * Returns the code associated with this puzzle
	 *
	 * @return the Puzzle's code
	 */
	QString getCode();
	
	
	/**
	 * Returns this puzzle's number if this puzzle is a stock puzzle. Returns
	 * -1 otherwise
	 *
	 * @return the puzzle's number if puzzle is a stock puzzle, -1 otherwise.
	 */
	int getPuzzleNumber();
	
	
	/**
	 * Sets the puzzle number value of a puzzle
	 *
	 * @param puzzlenumber Number to give this puzzle
	 */
	void setPuzzleNumber(int puzzlenumber);
	
	/**
	 * Inverts white and black squares
	 */
	void invert();
	
private:
	/**
	 * Allocates the memory to store the Squares making up the puzzle
	 *
	 * @param state the default state of the Squares in the puzzle
	 */
	void allocate(Square::States state = Square::Border);

	/**
	 * DEBUG: Prints out the given integer in binary base to standard
	 *        output.
	 *
	 * @param number number to print out
	 */
	static void printbin(int number);
	
	/**
	 * Concatenates the binary representation of a number to a QString
	 *
	 * @param dest the QString to which to concatenate
	 * @param number the number to calculate the binary value of
	 */
	static void getBin(QString& dest, int number);
	
	/**
 	 * Concatenates the binary representation of a number to a QString and
	 * pads the rest of the string with 0's until the destination QString
	 * has the given length.
	 * @see getBin()
	 *
	 * @param dest the QString to which to concatenate
	 * @param number the number to calculate the binary value of
	 * @param length length up to which to pad with 0s (0s added at the
	 *               end)
	 */
	static void getBin(QString& dest, int number, unsigned int length);
	
	/**
	 * Returns the integer value of a given QString made up of 0s and 1s
	 * The given QString has to be made up of 0s and 1s, no error checking
	 * is currently performed.
	 *
	 * @param binstring Binary string to evaluate
	 * @return the integer value of binstring
	 */
	static unsigned int evalBin(QString binstring);
	
	
	/**
	 * DEBUG: Prints out the specs of the puzzle to standard output
	 */
	void printSpec();
	
	int m_iWidth;    /**< Number of columns */
	int m_iHeight;   /**< Number of rows */
	QPoint m_qpSolutionStart; //!< Coordinate of the start of a solution
	QPoint m_qpSolutionEnd;   //!< Coordinate of the end of a solution
	Square*** m_pArray;  /**< The bidimensional array where the Squares
				  are stored. */
};

#endif
