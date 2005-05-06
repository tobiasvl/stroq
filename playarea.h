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
 
 Class          :   PlayArea
 Author         :   Luc Vo Van
 Original Date  :   18.05.2005
 Description    :   The QCanvasView on which the player plays and inputs
                    most commands.
 
 */

#ifndef PLAYGRID_H
#define PLAYGRID_H

#include <qcanvas.h>
#include <qpixmap.h>
#include <vector>

#include "playsquare.h"
#include "puzzle.h"

class PlayArea : public QCanvasView
{
	Q_OBJECT

public:
	PlayArea(QCanvas *canvas, QWidget *parent = 0, const char *name = 0,
		 WFlags f=0);
  	~PlayArea();

	/**
	* Returns wether or not we're currently in Puzzle Edit mode.
	* @return true if we're in edit mode, false otherwise.
	*/
	bool getEditMode();
	
	/**
	* Switches to or off of edit mode
	*/
	void toggleEditMode();

protected:
	void contentsMousePressEvent(QMouseEvent*);
	void contentsMouseMoveEvent(QMouseEvent*);
	void contentsMouseReleaseEvent(QMouseEvent*);
	void contentsMouseDoubleClickEvent(QMouseEvent*);

signals:
	/**
	* Emitted when the (original) puzzle has changed. For example
	* when loadPuzzle is called.
	* @param puzzle Puzzle that was just loaded.
	* @param size The size, in pixels, of the Canvas needed to
	*             display the whole puzzle at once.
	*/
	void puzzleChanged(Puzzle* puzzle, QSize size);
	
	/**
	 * Emitted when we need to load the next puzzle. Happens when the user
	 * solves the current puzzle.
	 */
	void loadNextPuzzle();
  
public slots:
	/**
	* Loads a puzzle.
	* @param puzzle Puzzle to load. It will be deleted by the
	*               PlayArea when needed, the caller should
	*               therefore not delete the passed object.
	*/
	void loadPuzzle(Puzzle* puzzle);
	
	/**
	* Toggles the squares under the stroke. This is the
	* validating action from the player. Once the stroke is
	* toggled, the game ends (and win or loss is determined)
	* This is also called 'running' the Puzzle.
	*
	* If the puzzle was solved, store in the settings
	* that it was successful.
	*/
	void toggleStroke();
	
	/**
	* Resets the playing grid to the original puzzle settings.
	*/
	void resetGrid();
	
	/**
	* When in edit mode, pops a dialog asking to sets the dimensions
	* of the puzzle to edit and deletes any currently loaded puzzle if
	* the input is valid.
	*/
	void editModeSetDimensions();
	
	/**
	* Inverts the whole play puzzle (white to black, black to white).
	*/
	void invertPuzzle();

private:
	/**
	* Selects all the PlaySquares between playSquare and the stroke's end
	* only if they are aligned, and no linked playsquares in between.
	*
	* @see selectPlaySquare()
	* @param playsquare PlaySquare up to which to select.
	*/
	void selectPlaySquares(PlaySquare* playsquare);
	
	/**
	* Selects a single PlaySquare if it is horizontally or vertically
	* adjacent to the current stroke end's (always added if the
	* current stroke is empty).
	*
	* @see selectPlaySquares()
	* @param playsquare PlaySquare to add to the stroke.
	*/
	void selectPlaySquare(PlaySquare* playsquare);
	
	/**
	* Highlights the given PlaySquare
	*
	* @param playsquare the PlaySquare to highlight.
	*/
	void highlightPlaySquare(PlaySquare* playsquare);
	
	/**
	* Verifies the alignment of two Squares.
	*
	* @param s1 the first square.
	* @param s2 the second square.
	* @return NOT_ALIGNED if s1 and s2 are not aligned.
		  ROW_ALIGNED if s1 and s2 are on the same row.
		  COLUMN_ALIGNED if s1 and s2 are on the same column.
	*/
	static int getAlignment(Square* s1, Square* s2);
	
	/**
	* Updates the last two squares in the stroke. This is
	* useful when a new square is added to the stroke in order
	* to turn the previous square into an angle.
	*/
	void updateStrokeLinks();
	
	/**
	* Clears the current stroke.
	*/
	void clearStroke();
	
	/**
	* DEBUG: Prints out the stroke to standard output.
	*/
	void printStroke();
	
	bool m_bButtonPressed; /**< true if mouse button 1 is pressed, false
				    otherwise */
	bool m_bEditMode; /**< true if in edit mode, false otherwise */
	
	bool m_bGameOver; /**< true if in gameover state, next click reinits */
	
	PlaySquare* m_psHighlightedSquare; /**<  The last highlighted square,
						 in order to dehilight
						 it when focus changes. */
	Puzzle* m_ppOriginalPuzzle; /**< The original loaded puzzle,
				         containing Squares (and
					 notPlaySquares). */
	Puzzle* m_ppPlayPuzzle; /**< The "playing" puzzle on which the
				     user acts. */
	std::vector<PlaySquare*> m_vStroke; //!< the current stroke

	QCanvas* m_cCanvas;

	static const  int NOT_ALIGNED = 0; //!< no alignment
	static const  int ROW_ALIGNED = 1; //!< horizontal alignment
	static const  int COLUMN_ALIGNED = 2; //!< column alignment
	static QPixmap *m_qpmBackground; //!< The background image
};

#endif
