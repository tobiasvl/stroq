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

#include "images/whitesquare.xpm"
#include "images/blacksquare.xpm"
#include "images/bordersquare.xpm"

QPixmap* PlaySquare::m_qpmSquares = NULL;

PlaySquare::PlaySquare(QCanvas *canvas, QPoint pos, Square::States state)
	: QCanvasRectangle(canvas), Square(pos, state)
{
	m_pqpGridPos = pos;
	m_bHighlighted = false;
	m_sState = state;
	unsetLink();
	
	// Loads the pixmaps, if necessary
	if(m_qpmSquares == NULL)
	{
		m_qpmSquares = new QPixmap[3];
		m_qpmSquares[(int) Square::White] = QPixmap(whitesquare);
		m_qpmSquares[(int) Square::Black] = QPixmap(blacksquare);
		m_qpmSquares[(int) Square::Border] = QPixmap(bordersquare);
	}
	
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
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();

}
 

void PlaySquare::setLink(PlaySquare::Links link, int position)
{
	m_lLink = link;
	m_iStrokePosition = position;
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();
}


void PlaySquare::unsetLink()
{
	m_lLink = PlaySquare::None;
	m_iStrokePosition = -1;
	unsetStrokeEnd();
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();
}


void PlaySquare::setStrokeEnd()
{
	m_bStrokeEnd = true;
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();
}


void PlaySquare::unsetStrokeEnd()
{
	m_bStrokeEnd = false;
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();
}


void PlaySquare::setStrokePosition(int position)
{
	m_iStrokePosition = position;
}


void PlaySquare::setHighlight(bool highlight)
{
	m_bHighlighted = highlight;
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();
}


void PlaySquare::toggle()
{
	Square::toggle();
	canvas()->setChanged(QRect((int)x(), (int)y(), width(), height()));
	canvas()->update();
}


void PlaySquare::drawShape(QPainter &painter)
{
	QBrush brush;
	/* painter.fillRect((int)x(), (int)y(), width(), height(),
					 painter.backgroundColor()); */
	
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
						 QBrush(Qt::yellow));
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
  						         QBrush(Qt::yellow));
				break;
			case LeftRight:
			case RightLeft:
				// Horizontal line
				painter.fillRect((int)x(), (int)y() + height()/2 - DEFAULT_BORDER,
								 width(), 2*DEFAULT_BORDER,
								 QBrush(Qt::yellow));
				break;
			case LeftUp:
			case UpLeft:
				// Left to middle
				painter.fillRect((int)x(), (int)y() + height()/2 - DEFAULT_BORDER,
								 width()/2 + DEFAULT_BORDER,  2*DEFAULT_BORDER,
								 QBrush(Qt::yellow));
				// Middle to up
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y(),
								 2*DEFAULT_BORDER,  height()/2 + DEFAULT_BORDER,
								 QBrush(Qt::yellow));				
				break;
			case RightUp:
			case UpRight:
				// Right to middle
				painter.fillRect((int)x() + width()/2 - DEFAULT_BORDER,
								 (int)y() + height()/2 - DEFAULT_BORDER,
								 width(),  2*DEFAULT_BORDER,
								 QBrush(Qt::yellow));
				// Middle to up
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y(),
								 2*DEFAULT_BORDER,  height()/2 + DEFAULT_BORDER,
								 QBrush(Qt::yellow));	
				break;
			case LeftDown:
			case DownLeft:
				// Left to middle
				painter.fillRect((int)x(), (int)y() + height()/2 - DEFAULT_BORDER,
								 width()/2 + DEFAULT_BORDER,  2*DEFAULT_BORDER,
								 QBrush(Qt::yellow));
				// Middle to down
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y() + width() /2 - DEFAULT_BORDER,
								 2*DEFAULT_BORDER,
								 height(),
								 QBrush(Qt::yellow));
				break;
			case RightDown:
			case DownRight:
				// Right to middle
				painter.fillRect((int)x() + width()/2 - DEFAULT_BORDER,
								 (int)y() + height()/2 - DEFAULT_BORDER,
								 width(),  2*DEFAULT_BORDER,
								 QBrush(Qt::yellow));
				// Middle to down
				painter.fillRect((int)x() + width() /2 - DEFAULT_BORDER,
								 (int)y() + width() /2 - DEFAULT_BORDER,
								 2*DEFAULT_BORDER,
								 height(),
								 QBrush(Qt::yellow));
				break;
			case None:
				break;
		}
	}
}

