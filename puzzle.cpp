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

#include <qapplication.h>
#include <qpoint.h>
#include <qcanvas.h>

#include <stdlib.h>

#include "stroqconst.h"
#include "puzzle.h"
#include "playsquare.h"
#include "square.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

/*
 * The code format is as follows:
 *
 * 1) The first 6 bits are reserved for the bitwidth, which is how many bits
 *    are needed to represent the largest of the two coordinates
 *    ie: max(row,column)
 * 2) The next bitwidth bits are the number of columns (width) of the puzzle
 * 3) The next bitwidth bits are the number of height (height) of the puzzle
 * 4) The next 2*bitwidth bits are the row and height of the start of a solution
 *    to the puzzle (hint 1)
 * 5) The next 2*bitwidth bits are the row and height of the end of a solution
 *    to the puzzle (hint 2). This is of course the end of the solution hinted
 *    in the previous step
 * 6) The next width*height bits are the content of the puzzle, 1 for black squares
 *    0 for whites
 * 7) The remaining bits are ignored as the puzzle code is right padded with 0s
 *    until it is a factor of 8.
 *
 * In brief:
 *  [bitwidth][width*][height*][row sol1*][col sol1*][row sol2*][col sol2*][content]
 *  parameters noted with a * use 'bitwidth' bits.
 */
Puzzle::Puzzle(QString code)
{
	QString ucode = code.upper();
	QString bincode = "";
	unsigned int offset = 0;
	for(unsigned int i = 0; i < ucode.length(); i++)
		getBin(bincode, ucode[i].unicode()-65, 4);
	
	unsigned int bitwidth = evalBin(bincode.left(6));
	offset += 6;
	
	m_iWidth  = evalBin(bincode.mid(offset, bitwidth));
	offset += bitwidth;
	m_iHeight = evalBin(bincode.mid(offset, bitwidth));
	offset += bitwidth;
	allocate();
	
	m_qpSolutionStart = QPoint(
					evalBin(bincode.mid(offset, bitwidth)),
					evalBin(bincode.mid(offset + bitwidth, bitwidth)));
	offset += 2* bitwidth;
	m_qpSolutionStart = QPoint(
					evalBin(bincode.mid(offset, bitwidth)),
					evalBin(bincode.mid(offset + bitwidth, bitwidth)));
	offset += 2* bitwidth;

	/*
	printf("puzzlecode: %s bincode: %s  bitwidth: %d\n",
		code.latin1(), bincode.latin1(), bitwidth);
	printSpec();
	*/
	
	// Copies the squares or playsquares, depending
	for(int row = 1; row < getHeight() + 1; row++)
	{
		for(int column = 1; column < getWidth() + 1; column++)
		{
			if(bincode[offset] == QChar('1'))
				setSquare(new Square(QPoint(column, row), Square::Black));
			else
				setSquare(new Square(QPoint(column, row), Square::White));
			
			offset++;
		}
	}
}

Puzzle::Puzzle(int width, int height, QPoint solStart, QPoint solEnd,
		Square::States defaultState /* = Square::Border */ )
{
	m_iWidth = width;
	m_iHeight = height;
	m_qpSolutionStart = solStart;
	m_qpSolutionEnd = solEnd;

	allocate(defaultState);
}

Puzzle::Puzzle(Puzzle* originalPuzzle)
{
	Square *origSquare;
	
	m_iWidth = originalPuzzle->getWidth();
	m_iHeight = originalPuzzle->getHeight();
	m_qpSolutionStart = originalPuzzle->getSolutionStart();
	m_qpSolutionEnd = originalPuzzle->getSolutionEnd();
	
	allocate();
	
	// Copies the squares or playsquares, depending
	for(int row = 0; row < originalPuzzle->getHeight() + 2; row++)
	{
		for(int column = 0; column < originalPuzzle->getWidth() + 2; column++)
		{
			origSquare = originalPuzzle->getSquareAt(row, column);
			setSquare(new Square(origSquare->getGridPos(),
						 origSquare->getState()));
		}
	}
}

Puzzle::Puzzle(Puzzle* originalPuzzle, QCanvas *canvas)
{
	PlaySquare *origSquare;
	
	m_iWidth = originalPuzzle->getWidth();
	m_iHeight = originalPuzzle->getHeight();
	m_qpSolutionStart = originalPuzzle->getSolutionStart();
	m_qpSolutionEnd = originalPuzzle->getSolutionEnd();
	
	allocate();
	
	// Copies the squares or playsquares, depending
	for(int column = 0; column < originalPuzzle->getWidth() + 2; column++)
	{
		for(int row = 0; row < originalPuzzle->getHeight() + 2; row++)
		{
			origSquare = (PlaySquare*)originalPuzzle->getSquareAt(column, row);
			setSquare(new PlaySquare(canvas,
						 origSquare->getGridPos(),
						 origSquare->getState()));
		}
	}
}

Puzzle::Puzzle(QString code, QCanvas *canvas)
{
	Puzzle *originalPuzzle = new Puzzle(code);
	PlaySquare *origSquare;
	
	m_iWidth = originalPuzzle->getWidth();
	m_iHeight = originalPuzzle->getHeight();
	m_qpSolutionStart = originalPuzzle->getSolutionStart();
	m_qpSolutionEnd = originalPuzzle->getSolutionEnd();
	
	allocate();
	
	// Copies the squares or playsquares, depending
	for(int column = 0; column < originalPuzzle->getWidth() + 2; column++)
	{
		for(int row = 0; row < originalPuzzle->getHeight() + 2; row++)
		{
			origSquare = (PlaySquare*)originalPuzzle->getSquareAt(column, row);
			setSquare(new PlaySquare(canvas,
						 origSquare->getGridPos(),
						 origSquare->getState()));
		}
	}
	
	delete originalPuzzle;
}

void Puzzle::allocate(Square::States filler /* = Square::Border*/ )
{
	// Allocate the bidimensional array, including the Squares on the borders
	// Allocate the row array
	m_pArray = new Square**[getWidth()+2];
	
	// Allocate the column array for each row
	for (int column = 0; column < getWidth()+2; column++)
		m_pArray[column] = new Square*[getHeight()+2];
	
	// If filling with Border states, fill everything
	// For each column in a row : allocate the Square
	for (int column = 0; column < getWidth()+2; column++)
		for (int row = 0; row < getHeight()+2; row++)
			m_pArray[column][row] = new Square(QPoint(column, row),
							Square::Border);
	
	// If we want to fill with something other than a Border,
	// the inside of the puzzle with the given State
	if(filler != Square::Border)
	{
		// For each column in a row : allocate the Square
		for (int column = 1; column < getWidth()+1; column++)
			for (int row = 1; row < getHeight()+1; row++)
				m_pArray[column][row] = new Square(QPoint(column, row),
								filler);
	}

}

Puzzle::~Puzzle()
{
	// For each column in each row : delete the Square
	for (int column = 0; column < getWidth()+2; column++)
		for (int row = 0; row < getHeight()+2; row++)
			delete m_pArray[column][row];

	// Free the columns
	for (int column = 0; column < getWidth()+2; column++)
		delete m_pArray[column];

	// Free the bidimensional array
	delete m_pArray;
}


void Puzzle::setSquare(Square* square)
{
	// If the square is already set, delete the previous square
	int x = square->getGridPos().x();
	int y = square->getGridPos().y();
	if(m_pArray[x][y])
		delete m_pArray[x][y];
	
	m_pArray[x][y] = square;
}


Square* Puzzle::getSquareAt(int x, int y)
{
	return m_pArray[x][y];
}


int Puzzle::getWidth()
{
	return m_iWidth;
}


int Puzzle::getHeight()
{
	return m_iHeight;
}


QPoint Puzzle::getSolutionStart()
{
	return m_qpSolutionStart;
}


QPoint Puzzle::getSolutionEnd()
{
	return m_qpSolutionEnd;
}

void Puzzle::invert()
{
	// Copies the squares or playsquares, depending
	for(int row = 1; row <= getHeight(); row++)
	{
		for(int column = 1; column <= getWidth(); column++)
		{
			getSquareAt(row, column)->toggle();
		}
	}
}


QString Puzzle::getCode()
{
	/*
	* Returns the code corresponding to this puzzle
	* This is not really efficient, but keeps away from endian problems
	* (ppc/x86), and I'm no super l337 hacker (far from it).
	* Until some code checks are performed it's really easy to break
	* the program here and in the constructor using the code
	*/
	int x = -1;
	int y = -1;
	int codewidth = 1;
	QString code, tmpcode;
	code = "";
	tmpcode = "";

	// Determine the code width (how many bits are needed to represent the width
	x = MAX(getWidth(), getHeight());
	while(x > (pow(2, codewidth)-1))
		codewidth++;
	// printf("We need %d bits\n", codewidth);
	
	
	getBin(code, codewidth, 6);
	// We reserve 6 bits for the width
	getBin(code, getWidth(), codewidth);
	getBin(code, getHeight(), codewidth);
	
	// printf("width                    : %s\n", code.latin1());
	
	// For the solutions
	// Goes through every square and puts 0s until the solution where we
	// put a 1
	getBin(code, getSolutionStart().x(), codewidth);
	getBin(code, getSolutionStart().y(), codewidth);
	getBin(code, getSolutionEnd().x(), codewidth);
	getBin(code, getSolutionEnd().y(), codewidth);
	
	//printf("width,puzzle,sols1, sols2: %s\n", code.latin1());

	
	for(y = 1; y<=getHeight() ; y++)
	{
		for(x = 1; x < getWidth() + 1; x++)
		{
			if(getSquareAt(x, y)->getState() == Square::Black)
				code = code + "1";
			else
				code = code + "0";
		}
	}
	
	// printf("width,puzzle             : %s\n", code.latin1());
	
	// 4 bits per letter
	QString finalcode;
	QString tmp;
	unsigned int index = 0;
	//printf("%s\n", code.latin1());

	while(code.length() % 4 != 0)
		code = code + "0";
	
	// printf("%s (padded)\n", code.latin1());
	while(index < code.length()-1)
	{
		finalcode = finalcode + QChar(65 + evalBin(code.mid(index, 4)));
		index+=4;
	}
	// printf("%s => %s\n", code.latin1(), finalcode.latin1());
	
	return finalcode;
}

void Puzzle::getBin(QString& res, int n)
{
	QString tmpn;
	
	if ((n == 0) || (n==1))
	{
		/* base case */
		tmpn = tmpn.setNum(n);
		res = res +  tmpn;
	}
	else
	{
		/* recursive call */
		getBin(res, n/2);
		tmpn = tmpn.setNum(n%2);
		res = res + tmpn;
	}
}

void Puzzle::getBin(QString& res, int n, unsigned int length)
{
	QString tmp = "";
	getBin(tmp, n);
	res = res + tmp.rightJustify(length, QChar('0'));
}

int Puzzle::evalBin(QString toeval)
{
	int res = 0;
	for(unsigned int i = 0; i<toeval.length(); i++)
	{
		if(toeval[toeval.length()-i-1] == QChar('1'))
			res += (int) pow(2, i);
	}
	return res;
}

void Puzzle::printSpec()
{
	printf("Puzzle spec:  width:%d height:%d solstart:%d,%d  solend:%d,%d\n",
		getWidth(), getHeight(),
		m_qpSolutionStart.x(), m_qpSolutionStart.y(),
		m_qpSolutionEnd.x(), m_qpSolutionEnd.y());
}
