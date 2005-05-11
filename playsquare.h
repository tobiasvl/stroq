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
 
 Class          :   PlaySquare
 Author         :   Luc Vo Van
 Original Date  :   18.05.2005
 Description    :   A graphical representation of a Square on the canvas.
 
 */

#ifndef PLAYSQUARE_H
#define PLAYSQUARE_H

#include <qcanvas.h>
#include <qvaluevector.h>
#include <qpoint.h>
#include <qpixmap.h>
#include <qimage.h>

#include "square.h"

class PlaySquare : public QCanvasRectangle, public Square
{
public:
	/**
	 * The orientation of the PlaySquare when linking. This is
	 * useful to know in which direction the stroke was going
	 * when the player drew the stroke.
	 */
	enum Links {
		None,                               /**< Not in the stroke */
		UpDown, UpLeft, UpRight,            /**< starting from up */
		LeftDown, LeftRight, LeftUp,        /**< starting from the left */
		RightDown, RightLeft, RightUp,      /**< starting from the right */
		DownLeft, DownUp, DownRight         /**< starting from down */
		};

	enum Theme {
		ThemeClassic, /**< Classic theme */
		ThemeClassicSquare, /**< Classic theme with sharp squares */
		ThemeOceanBarbeQ /**< Cartoon theme with animals */
	};
		
	/**
	 * Constructs a PlaySquare given a canvas, position, and a State
	 *
	 * @param canvas canvas on which to draw
	 * @param pos Position in the puzzle
	 * @param state State to which to set the PlaySquare to
	 */
	PlaySquare(QCanvas *canvas, QPoint pos, Square::States state);
	
	/**
	 * Destructor
	 */
	~PlaySquare();
	
protected:
	void drawShape(QPainter &);
	
public:
	/**
	 * Returns the link currently active on the PlaySquare, if any
	 * @see Links
	 *
	 * @return the Link if the PlaySquare is in the stroke, and PlaySquare::None if not.
	 */
	PlaySquare::Links getLink();
	
	/**
	 * Returns the position in the stroke
	 *
	 * @return the position of the square in the stroke, -1 if not in the stroke
	 */
	int getStrokePosition();
	
	/**
	 * Sets or unsets  the highlight on the PlaySquare, used when hovering
	 * the cursor over the PlaySquare.
	 *
	 * @param highlight True to highlight the square, false otherwise
	 */
	void setHighlight(bool highlight);
	
	/**
	 * Sets the link on the PlaySquare
	 * @see setLink()
	 *
	 * @param link the link to set on the PlaySquare
	 */
	void setLink(PlaySquare::Links link);
	
	/**
	 * Sets the link and position of the PlaySquare in the stroke
	 * @see setLink()
	 *
	 * @param link the link to set on the PlaySquare
	 * @param pos position of the PlaySquare in the stroke
	 */
	void setLink(PlaySquare::Links link, int pos);
	
	/**
	 * Sets the PlaySquare as unlinked. Prefer this to setLink(PlaySquare::None)
	 */
	void unsetLink();
	
	/**
	 * Sets the square as and end of the stroke (first or last indifferently)
	 */
	void setStrokeEnd();
	
	/**
	 * Sets the square as a non ending part of the stroke, or not in the stroke
	 * at all
	 */
	void unsetStrokeEnd();
	
	/**
	 *  Sets the position of the PlaySquare in the stroke
	 */
	void setStrokePosition(int);
	
	/**
	 * Overrides Square::toggle
	 * Updates the canvas.
	 * @see Square::toggle()
	 */
	void toggle();
	
	/**
	 * Changes the current theme
	 * @param themenum Theme to use
	 */
	static void changeTheme(int themenum);
	
private:
	bool m_bHighlighted;  /**< true if the Square is currently highlighted */
	PlaySquare::Links m_lLink; /**< The link set on the PlaySquare */
	int m_iStrokePosition;     /**< position in the stroke */
	bool m_bStrokeEnd;         /**< wether or not this PlaySquare is an end of the stroke */
	static Theme m_tCurrentTheme; /**< current theme for pixmaps */
	static QPixmap *m_qpmSquares;  /**< Square images, in the same order as the Square::States enum */
};

#endif
