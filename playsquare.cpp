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

#include <qcanvas.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qimage.h>

#include "square.h"
#include "playsquare.h"
#include "stroqconst.h"

#include "images/classic/white.xpm"
#include "images/classic/black.xpm"
#include "images/classic/border.xpm"
#include "images/classic/background.xpm"

#include "images/classicsquare/white.xpm"
#include "images/classicsquare/black.xpm"
#include "images/classicsquare/border.xpm"
#include "images/classicsquare/background.xpm"

#include "images/oceanbarbeq/white.xpm"
#include "images/oceanbarbeq/black.xpm"
#include "images/oceanbarbeq/border.xpm"
#include "images/oceanbarbeq/background.xpm"


#define DEFAULT_UPDATED_RECT QRect((int)x(), (int)y(), width(), height())

PlaySquare::Theme PlaySquare::m_tCurrentTheme = PlaySquare::ThemeClassic;

QPixmap* PlaySquare::m_qpmSquares = NULL;

PlaySquare::PlaySquare(QCanvas *canvas, QPoint pos, Square::States state)
	: QCanvasRectangle(canvas), Square(pos, state)
{
	m_pqpGridPos = pos;
	m_bHighlighted = false;
	m_sState = state;
	unsetLink();

	if(!m_qpmSquares)
		changeTheme(0);
		
	// Sets the pixel position on the canvas
	setX(m_pqpGridPos.x() * DEFAULT_SIDE);
	setY(m_pqpGridPos.y() * DEFAULT_SIDE);
	setSize(DEFAULT_SIDE, DEFAULT_SIDE);
	
	show();
}


PlaySquare::~PlaySquare()
{

}


PlaySquare::Links PlaySquare::getLink()
{
	return m_lLink;
}
 

int PlaySquare::getStrokePosition()
{
	return m_iStrokePosition;
}


void PlaySquare::setLink(PlaySquare::Links link)
{
	m_lLink = link;
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();

}
 

void PlaySquare::setLink(PlaySquare::Links link, int position)
{
	m_lLink = link;
	m_iStrokePosition = position;
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();
}


void PlaySquare::unsetLink()
{
	m_lLink = PlaySquare::None;
	m_iStrokePosition = -1;
	unsetStrokeEnd();
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();
}


void PlaySquare::setStrokeEnd()
{
	m_bStrokeEnd = true;
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();
}


void PlaySquare::unsetStrokeEnd()
{
	m_bStrokeEnd = false;
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();
}


void PlaySquare::setStrokePosition(int position)
{
	m_iStrokePosition = position;
}


void PlaySquare::setHighlight(bool highlight)
{
	m_bHighlighted = highlight;
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();
}


void PlaySquare::toggle()
{
	Square::toggle();
	canvas()->setChanged(DEFAULT_UPDATED_RECT);
	canvas()->update();
}


void PlaySquare::drawShape(QPainter &painter)
{
	QBrush brush;
	QColor pathcolor(240, 122, 28, QColor::Rgb) ;
	
	// The highlight
	if(m_bHighlighted)
	{
		painter.fillRect((int)x(), (int)y(), width(), height(),
						 QBrush(Qt::red));
	}
	
	// The borders
	/*
	painter.setBrush(brush);
	painter.drawRect((int)x() + DEFAULT_BORDER, (int)y() + DEFAULT_BORDER,
					 width() - 2*DEFAULT_BORDER, height() - 2*DEFAULT_BORDER);
	*/
	
	// The actual square
	switch(m_sState)
	{
		case White:
			painter.fillRect((int)x() + DEFAULT_BORDER,
					 (int)y() + DEFAULT_BORDER,
					 width() - 2*DEFAULT_BORDER,
					 height() - 2*DEFAULT_BORDER,
					 QBrush(Qt::gray));
			break;
		case Black:
			painter.fillRect((int)x() + DEFAULT_BORDER,
					 (int)y() + DEFAULT_BORDER,
					 width() - 2*DEFAULT_BORDER,
					 height() - 2*DEFAULT_BORDER,
					 QBrush(Qt::black));
			break;
		case Border:
			painter.fillRect((int)x() + DEFAULT_BORDER,
					 (int)y() + DEFAULT_BORDER,
					 width() - 2*DEFAULT_BORDER,
					 height() - 2*DEFAULT_BORDER,
					 QBrush(QColor(100, 50, 20)));
			break;
	}
	
	painter.drawPixmap((int)x() + DEFAULT_BORDER,
			(int)y() + DEFAULT_BORDER,
			m_qpmSquares[(int) m_sState], 0, 0,
			width() - 2*DEFAULT_BORDER,
			height() - 2*DEFAULT_BORDER);
 
	// If the square is at an end of the stroke
	if(m_bStrokeEnd)
	{
		painter.fillRect((int)x() + 5*DEFAULT_BORDER,
						 (int)y() + 5*DEFAULT_BORDER,
						 width() - 10*DEFAULT_BORDER,
						 height() - 10*DEFAULT_BORDER,
						 QBrush(pathcolor));
	}
	// Link
	else if(m_lLink != PlaySquare::None)
	{
		switch(m_lLink)
		{
			
			case UpDown:
			case DownUp:
				// Vertical line
				painter.fillRect((int)x() + width()/2 - DEFAULT_BORDER, (int)y(),
						         2*DEFAULT_BORDER, height(),
  						         QBrush(pathcolor));
				break;
			case LeftRight:
			case RightLeft:
				// Horizontal line
				painter.fillRect((int)x(), (int)y() + height()/2 - DEFAULT_BORDER,
								 width(), 2*DEFAULT_BORDER,
								 QBrush(pathcolor));
				break;
			case LeftUp:
			case UpLeft:
				// Left to middle
				painter.fillRect((int)x(), (int)y() + height()/2 - DEFAULT_BORDER,
								 width()/2 + DEFAULT_BORDER,  2*DEFAULT_BORDER,
								 QBrush(pathcolor));
				// Middle to up
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y(),
								 2*DEFAULT_BORDER,  height()/2 + DEFAULT_BORDER,
								 QBrush(pathcolor));				
				break;
			case RightUp:
			case UpRight:
				// Right to middle
				painter.fillRect((int)x() + width()/2 - DEFAULT_BORDER,
								 (int)y() + height()/2 - DEFAULT_BORDER,
								 width(),  2*DEFAULT_BORDER,
								 QBrush(pathcolor));
				// Middle to up
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y(),
								 2*DEFAULT_BORDER,  height()/2 + DEFAULT_BORDER,
								 QBrush(pathcolor));	
				break;
			case LeftDown:
			case DownLeft:
				// Left to middle
				painter.fillRect((int)x(), (int)y() + height()/2 - DEFAULT_BORDER,
								 width()/2 + DEFAULT_BORDER,  2*DEFAULT_BORDER,
								 QBrush(pathcolor));
				// Middle to down
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y() + width() /2 - DEFAULT_BORDER,
								 2*DEFAULT_BORDER,
								 height(),
								 QBrush(pathcolor));
				break;
			case RightDown:
			case DownRight:
				// Right to middle
				painter.fillRect((int)x() + width()/2 - DEFAULT_BORDER,
								 (int)y() + height()/2 - DEFAULT_BORDER,
								 width(),  2*DEFAULT_BORDER,
								 QBrush(pathcolor));
				// Middle to down
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y() + width() /2 - DEFAULT_BORDER,
								 2*DEFAULT_BORDER,
								 height(),
								 QBrush(pathcolor));
				break;
			case None:
				break;
		}
	}
}

void PlaySquare::changeTheme(int themenum)
{
	// Loads the pixmaps, if necessary
	if(!m_qpmSquares)
	{
		m_qpmSquares = new QPixmap[3];		
	}
	
	switch(themenum)
	{
		case 0:
			m_tCurrentTheme = PlaySquare::ThemeClassic;
			m_qpmSquares[(int) Square::White] = QPixmap(classic_whitesquare);
			m_qpmSquares[(int) Square::Black] = QPixmap(classic_blacksquare);
			m_qpmSquares[(int) Square::Border] = QPixmap(classic_bordersquare);
			break;
		case 1:
			m_tCurrentTheme = PlaySquare::ThemeClassicSquare;
			m_qpmSquares[(int) Square::White] = QPixmap(classicsquare_whitesquare);
			m_qpmSquares[(int) Square::Black] = QPixmap(classicsquare_blacksquare);
			m_qpmSquares[(int) Square::Border] = QPixmap(classicsquare_bordersquare);
			break;
		case 2:
			m_tCurrentTheme = PlaySquare::ThemeOceanBarbeQ;
			m_qpmSquares[(int) Square::White] = QPixmap(oceanbarbeq_whitesquare);
			m_qpmSquares[(int) Square::Black] = QPixmap(oceanbarbeq_blacksquare);
			m_qpmSquares[(int) Square::Border] = QPixmap(oceanbarbeq_bordersquare);
			break;
	}
}
