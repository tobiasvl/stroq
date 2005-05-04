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

#include <qcanvas.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qvalidator.h>
#include <qpoint.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qsettings.h>
#include <qfile.h>
#include <vector>

#include "playarea.h"
#include "playsquare.h"
#include "puzzle.h"
#include "stroqconst.h"

QPixmap* PlayArea::m_qpmBackground = NULL;

PlayArea::PlayArea(QCanvas *c, QWidget* parent,  const char* name, WFlags f)
	: QCanvasView(c, parent, name, f)
{
	m_ppOriginalPuzzle = NULL;
	m_ppPlayPuzzle = NULL;
	m_psHighlightedSquare = NULL;
	m_bButtonPressed = false;
	m_bEditMode = false;
	m_cCanvas = c;
	
	// The background image.
	if(!m_qpmBackground)
	{
		m_qpmBackground = new QPixmap("images/background.png");
		m_cCanvas->setBackgroundPixmap(*m_qpmBackground);
		m_cCanvas->update();
	}
}


PlayArea::~PlayArea()
{	
	if(m_ppOriginalPuzzle)
		delete m_ppOriginalPuzzle;
	
	if(m_ppPlayPuzzle)
		delete m_ppPlayPuzzle;
		
	if(m_qpmBackground)
		delete m_qpmBackground;
}



void PlayArea::contentsMousePressEvent(QMouseEvent* e)
{
	// We're in PLAY mode.
	if(!m_bEditMode)
	{
		if(e->button() == 1)
		{
			// Pick the Square that was under the click and
			// select it.
			QPoint p = inverseWorldMatrix().map(e->pos());
			QCanvasItemList l=m_cCanvas->collisions(p);
			QCanvasItemList::Iterator it;
			for (it=l.begin(); it!=l.end(); ++it)
			{
				// We check the cast of it into a PlaySquare.
				if ( dynamic_cast<PlaySquare*>(*it) != NULL )
				{
					selectPlaySquares((PlaySquare*)(*it));
				}
			}
			m_bButtonPressed = true;
		}
		else if(e->button() == 2)
		{
			// Unlinks all the squares in the stroke and clears
			// the stroke when the right mouse button is clicked.
			resetGrid();
		}
	}
	
	// We're in EDIT mode.
	else
	{
		// We just toggle white to black and vice versa.
		QPoint p = inverseWorldMatrix().map(e->pos());
		QCanvasItemList l=m_cCanvas->collisions(p);
		QCanvasItemList::Iterator it;
		for (it=l.begin(); it!=l.end(); ++it)
		{
			// We check the cast of it into a PlaySquare.
			if ( dynamic_cast<PlaySquare*>(*it) != NULL )
			{
				((PlaySquare*)(*it))->toggle();
				emit puzzleChanged(m_ppPlayPuzzle,
						   sizeHint());
			}
		}
		m_bButtonPressed = true;
	}
}


void PlayArea::contentsMouseMoveEvent(QMouseEvent* e)
{
	if(!m_bEditMode)
	{
		// Pick the Square that was under the cursor and highlight it.
		QPoint p = inverseWorldMatrix().map(e->pos());
		QCanvasItemList l=m_cCanvas->collisions(p);
		if(l.size() > 0) {
			QCanvasItemList::Iterator it;
			for (it=l.begin(); it!=l.end(); ++it)
			{
				if (dynamic_cast<PlaySquare*>(*it) != NULL)
				{
					PlaySquare *ps = (PlaySquare*)(*it);
					highlightPlaySquare(ps);
				}
			
				// If we're already holding the button, make
				// this square the selected square.
				if (m_bButtonPressed)
				{
					selectPlaySquare((PlaySquare*) (*it));
				}
			}
		}
		else
		{
			// No square under the cursor, dehilight the last
			// hovered cursor.
			if(m_psHighlightedSquare)
			{
				m_psHighlightedSquare->setHighlight(false);
				m_psHighlightedSquare = NULL;
			}
		}
	}
	else
	{
	/*
	 *  What would be nice here would be to be allowed to toggle the tiles
	 *  LIVE when holding the mouse button and in edit move. The problem
	 *  implementing that is that we have to store when we leave the
	 *  square, we can't just toggle on every move event :
	 */
	
		// Edit mode.
// 		if(m_bButtonPressed)
// 		{
// 			// We just toggle white to black and vice versa.
// 			QPoint p = inverseWorldMatrix().map(e->pos());
// 			QCanvasItemList l=m_cCanvas->collisions(p);
// 			QCanvasItemList::Iterator it;
// 			for (it=l.begin(); it!=l.end(); ++it)
// 			{
// 				// We check the cast of it into a PlaySquare.
// 				if ( dynamic_cast<PlaySquare*>(*it) != NULL )
// 				{
// 					((PlaySquare*)(*it))->toggle();
// 					emit puzzleChanged(m_ppPlayPuzzle,
// 							   sizeHint());
// 				}
// 			}
// 		}
	}
}


void PlayArea::contentsMouseReleaseEvent (QMouseEvent* e)
{
	if (e->button() == 1)
		m_bButtonPressed = false;
}

void PlayArea::contentsMouseDoubleClickEvent(QMouseEvent* e)
{
	if (!m_bEditMode && e->button() == 1)
	{
		QPoint p = inverseWorldMatrix().map(e->pos());
		QCanvasItemList l=m_cCanvas->collisions(p);
		QCanvasItemList::Iterator it;
		for (it=l.begin(); it!=l.end(); ++it)
		{
			// We check the cast of it into a PlaySquare.
			if (dynamic_cast<PlaySquare*>(*it) != NULL)
			{
				// Is it the last square in the stroke?
				if (((PlaySquare*)(*it))->getGridPos() ==
				m_vStroke[m_vStroke.size()-1]->getGridPos())
					toggleStroke();
			}
		}
	}
}


void PlayArea::highlightPlaySquare(PlaySquare *playSquare)
{
	// We're on a square.
	// Dehilight the previously selected square (if any).
	// Highlight the new one.
	if (m_psHighlightedSquare)
	{
		if (playSquare == m_psHighlightedSquare)
			return;
		m_psHighlightedSquare->setHighlight(false);
	}
	m_psHighlightedSquare = playSquare;
	playSquare->setHighlight(true);
}


void PlayArea::selectPlaySquares(PlaySquare *playSquare)
{
	int i;
	
	if (m_vStroke.size() == 0 ||
	    playSquare->getLink() != PlaySquare::None)
	{
		selectPlaySquare(playSquare);
		return;
	}
	
	PlaySquare* last = m_vStroke[m_vStroke.size()-1];
	if(getAlignment(playSquare, last) == ROW_ALIGNED)
	{
		// Check if any already linked PlaySquares are in the way.
		i = last->getGridPos().x();
		if (i < playSquare->getGridPos().x()) i++;
		else i--;
		while (i != playSquare->getGridPos().x())
		{
			// Do we encounter an already linked square?
			if (((PlaySquare*) m_ppPlayPuzzle
			    ->getSquareAt(i, playSquare->getGridPos().y()))
			    ->getLink() != PlaySquare::None)
				return;
			
			// Get closer to last.
			if (i < playSquare->getGridPos().x())
				i++;
			else
				i--;
		}
		
		// Selects the squares on the way.
		i = last->getGridPos().x();
		if (i < playSquare->getGridPos().x()) i++;
		else i--;
		
		while (i != playSquare->getGridPos().x())
		{
			// Do we encounter an already linked square?
			selectPlaySquare((PlaySquare*) m_ppPlayPuzzle
			      ->getSquareAt(i, playSquare->getGridPos().y()));
			
			// Get closer to last.
			if (i < playSquare->getGridPos().x())
				i++;
			else
				i--;
		}
		
		selectPlaySquare(playSquare);
	}
	else if (getAlignment(playSquare, last) == COLUMN_ALIGNED)
	{
		// Check if any already linked PlaySquares are in the way.
		i = last->getGridPos().y();
		if (i < playSquare->getGridPos().y()) i++;
		else i--;
		while (i != playSquare->getGridPos().y())
		{
			// Do we encounter an already linked square?
			if (((PlaySquare*) m_ppPlayPuzzle
			    ->getSquareAt(playSquare->getGridPos().x(), i))
			    ->getLink() != PlaySquare::None)
				return;
			
			// Get closer to last.
			if (i < playSquare->getGridPos().y())
				i++;
			else
				i--;
		}
		
		// Selects the squares on the way.
		i = last->getGridPos().y();
		if (i < playSquare->getGridPos().y()) i++;
		else i--;
		while (i != playSquare->getGridPos().y())
		{
			// Do we encounter an already linked square?
			selectPlaySquare((PlaySquare*) m_ppPlayPuzzle
			      ->getSquareAt(playSquare->getGridPos().x(), i));
			
			// Get closer to last.
			if (i < playSquare->getGridPos().y())
				i++;
			else
				i--;
		}
		
		selectPlaySquare(playSquare);
	}
}


void PlayArea::selectPlaySquare(PlaySquare *playSquare)
{
	// Checks if playSquare is selectable by verifying the last PlaySquare
	// of the stroke.
	if (m_vStroke.size() > 0) // Is there something in the stroke?
	{
		// Is this PlaySquare already part of the stroke? We just
		// check its link to know!
		if (playSquare->getLink() != PlaySquare::None
		   && (*playSquare != (*m_vStroke[m_vStroke.size()-1])))
		{
			std::vector<PlaySquare*>::const_iterator i;
			for (i = m_vStroke.begin() +
			    playSquare->getStrokePosition()+1;
			    i!=m_vStroke.end(); i++)
				(*i)->unsetLink();
			// Resizes the stroke to go only up to playSquare.
			m_vStroke.resize(playSquare->getStrokePosition());
			canvas()->setAllChanged();
			canvas()->update();
		}
		// If playSquare's position is not a valid neighbour, don't
		// do a thing.
		else
		{
			PlaySquare* last = m_vStroke[m_vStroke.size()-1];
			if (getAlignment(playSquare, last) == NOT_ALIGNED)
				return;
			if (!(abs(playSquare->getGridPos().x() -
				 last->getGridPos().x()) == 1
			  || abs(playSquare->getGridPos().y() -
				 last->getGridPos().y()) == 1))
				return;
		}
	}
	
	m_vStroke.push_back(playSquare); // Add to the stroke.
	playSquare->setStrokePosition(m_vStroke.size()-1);
	if (m_vStroke.size() == 1)
		playSquare->setStrokeEnd();
	else
		updateStrokeLinks();
}


void PlayArea::loadPuzzle(Puzzle *puzzle) {
	if (m_ppOriginalPuzzle)
	{
		// printf("Deleting m_ppOriginalPuzzle\n");
		delete m_ppOriginalPuzzle;
	}
	
	m_ppOriginalPuzzle = puzzle;
	m_cCanvas->resize((puzzle->getWidth() + 2) * DEFAULT_SIDE +\
		                                    DEFAULT_BORDER,
			  (puzzle->getHeight() + 2) * DEFAULT_SIDE +\
						      DEFAULT_BORDER);
	emit puzzleChanged(m_ppOriginalPuzzle, m_cCanvas->size());
	resetGrid();
}


void PlayArea::resetGrid() {
	emit clearStroke();
	m_psHighlightedSquare = NULL;
	viewport()->setMouseTracking(false);

	// Copies qvlOriginalPuzzle into qvlPlayPuzzle replacing all Squares
	// by PlaySquares.
	setCanvas(0);
	if (m_ppPlayPuzzle)
		delete m_ppPlayPuzzle;
	
	m_ppPlayPuzzle = new Puzzle(m_ppOriginalPuzzle, m_cCanvas);
	viewport()->setMouseTracking(true);

	m_cCanvas->update();
	setCanvas(m_cCanvas);
}


void PlayArea::toggleStroke()
{	
	// Toggles the stroke.
	for (unsigned int i = 0; i < m_vStroke.size(); i++)
		m_vStroke[i]->toggle();
	
	// Runs the puzzle.
	int row, col, countwhite, countblack;
	bool win = true;
	
	for (row = 1; row <= m_ppOriginalPuzzle->getHeight(); row++)
	{
		countwhite = 0;
		countblack = 0;
		for (col = 1; col <= m_ppOriginalPuzzle->getWidth(); col++)
		{
			if (m_ppPlayPuzzle->getSquareAt(col, row)->getState()
			    == Square::White)
				countwhite++;
			else
				countblack++;
		}
		
		// Row cleared, one color was absent, the other color filled
		// the row.
		if (!(countwhite == 0 || countblack == 0))
			win = false;
	}
	
	m_cCanvas->setAllChanged();
	m_cCanvas->update();
	
	if (win)
	{
		QMessageBox::information(this, tr("Congratulations"),
					 QString(tr("You solved this puzzle with a %1 strokes!")
					  .arg((int) m_vStroke.size())),
					 QMessageBox::Ok);
		
		// Store the success in the settings.
		QSettings settings;
		settings.setPath("thelemmings.net", "StroQ");
		QString settingkey = "/puzzles/" +
				     m_ppOriginalPuzzle->getCode();
		
		// Save the length of the solution, if this one is shorter
		int solutionLength = settings.readNumEntry(settingkey, -1);
		if(solutionLength == -1
		||
		    (int) m_vStroke.size() < solutionLength)
		{
			settings.writeEntry(settingkey, (int) m_vStroke.size());
		}
	}
	else
		QMessageBox::information(this, tr("Sorry"),
					 tr("The run was unsuccessful," \
					    " reset it to try again!"),
					 QMessageBox::Ok);
	m_cCanvas->update();
}


void PlayArea::clearStroke()
{
	std::vector<PlaySquare*>::const_iterator i;
	for (i = m_vStroke.begin(); i!=m_vStroke.end(); i++)
		(*i)->unsetLink();
	
	m_vStroke.clear();
	canvas()->setAllChanged();
	canvas()->update();
}


void PlayArea::updateStrokeLinks()
{
	if (m_vStroke.size() <= 1)
		return;
	else if (m_vStroke.size() == 2)
	{
		// Determine the link of the second PlaySquare in the stroke.
		if (getAlignment(m_vStroke[0], m_vStroke[1]) == ROW_ALIGNED)
		{
			// Horizontal alignment.
			if (m_vStroke[0]->getGridPos().x() <
			    m_vStroke[1]->getGridPos().x())
			{
				m_vStroke[0]->setLink(PlaySquare::LeftRight);
				m_vStroke[1]->setLink(PlaySquare::LeftRight);
			}
			else
			{
				m_vStroke[0]->setLink(PlaySquare::RightLeft);
				m_vStroke[1]->setLink(PlaySquare::RightLeft);
			}
		}
		else
		{
			// Vertical alignment.
			if (m_vStroke[0]->getGridPos().y() <
			    m_vStroke[1]->getGridPos().y())
			{
				m_vStroke[0]->setLink(PlaySquare::UpDown);
				m_vStroke[1]->setLink(PlaySquare::UpDown);
			}
			else
			{
				m_vStroke[0]->setLink(PlaySquare::DownUp);
				m_vStroke[1]->setLink(PlaySquare::DownUp);
			}
		}
		m_vStroke[1]->setStrokeEnd();
	}
	else
	{
		PlaySquare* secondlast = m_vStroke[m_vStroke.size()-2];
		PlaySquare* last =  m_vStroke[m_vStroke.size()-1];
		/* printf("secondlast:%d,%d last:%d,%d\n",
			   secondlast->getGridPos().x(),
			   secondlast->getGridPos().y(),
			   last->getGridPos().x(),
			   last->getGridPos().y()
			    ); */

		// Horizontal neighbours.
		if (getAlignment(last, secondlast) == ROW_ALIGNED)
		{
			if (secondlast->getLink() == PlaySquare::RightLeft)
				last->setLink(PlaySquare::RightLeft);
			else if (secondlast->getLink() ==
				 PlaySquare::LeftRight)
				last->setLink(PlaySquare::LeftRight);
			else if (secondlast->getLink() == PlaySquare::DownUp)
			{
				if (secondlast->getGridPos().x() <
				    last->getGridPos().x())
				{ // secondlast is left of last.
				   secondlast->setLink(PlaySquare::DownRight);
				   last->setLink(PlaySquare::LeftRight);
				}
				else
				{ // secondlast is right of secondlast.
				   secondlast->setLink(PlaySquare::DownLeft);
				   last->setLink(PlaySquare::RightLeft);
				}
			}
			else if (secondlast->getLink() == PlaySquare::UpDown)
			{
				if (secondlast->getGridPos().x() <
				   last->getGridPos().x())
				{ // secondlast is left of secondlast.
				     secondlast->setLink(PlaySquare::UpRight);
				     last->setLink(PlaySquare::LeftRight);
				}
				else
				{ // secondlast is right of secondlast.
				     secondlast->setLink(PlaySquare::UpLeft);
				     last->setLink(PlaySquare::RightLeft);
				}
			}
			else // Second last is a 'turn' in the stroke, this
			     // is possible when going back in the stroke
			     // (reclicking on a part of the stroke. We
			     // don't change second last, only last.
			{
				if (secondlast->getGridPos().x() <
				   last->getGridPos().x())
				{ // secondlast is left of secondlast.
					last->setLink(PlaySquare::LeftRight);
				}
				else
				{ // secondlast is right of secondlast.
					last->setLink(PlaySquare::RightLeft);
				}
			}
		}
		else // Vertical alignment.
		{
			if (secondlast->getLink() == PlaySquare::UpDown)
				last->setLink(PlaySquare::UpDown);
			else if (secondlast->getLink() == PlaySquare::DownUp)
				last->setLink(PlaySquare::DownUp);
			else if (secondlast->getLink() ==
				 PlaySquare::LeftRight)
			{
				if (secondlast->getGridPos().y() <
				    last->getGridPos().y())
				{ // last is below secondlast.
				    secondlast->setLink(PlaySquare::LeftDown);
				    last->setLink(PlaySquare::UpDown);
				}
				else
				{ // last is above secondlast.
				    secondlast->setLink(PlaySquare::LeftUp);
				    last->setLink(PlaySquare::DownUp);
				}
			}
			else if (secondlast->getLink() ==
				 PlaySquare::RightLeft)
			{
				if (secondlast->getGridPos().y() <
				    last->getGridPos().y())
				{ // last is below secondlast.
				   secondlast->setLink(PlaySquare::RightDown);
				   last->setLink(PlaySquare::UpDown);
				}
				else
				{ // last is above secondlast.
				   secondlast->setLink(PlaySquare::RightUp);
				   last->setLink(PlaySquare::DownUp);
				}
			}
			else
			{
				if (secondlast->getGridPos().y() <
				    last->getGridPos().y())
				{ // last is below secondlast.
					last->setLink(PlaySquare::UpDown);
				}
				else
				{ // last is above secondlast.
					last->setLink(PlaySquare::DownUp);
				}
			}
		}
		
		// Sets the ends.
		secondlast->unsetStrokeEnd();
		last->setStrokeEnd();
	}
}


int PlayArea::getAlignment(Square* s1, Square* s2)
{
	if (s1->getGridPos().x() == s2->getGridPos().x())
		return COLUMN_ALIGNED;
	else if (s1->getGridPos().y() == s2->getGridPos().y())
		return ROW_ALIGNED;
	
	return NOT_ALIGNED;
}


bool PlayArea::getEditMode()
{
	return m_bEditMode;
}

void PlayArea::toggleEditMode()
{
	m_bEditMode = !m_bEditMode;
	resetGrid();
}

void PlayArea::invertPuzzle()
{
	m_ppOriginalPuzzle->invert();
	m_ppPlayPuzzle->invert();
	m_cCanvas->setAllChanged();
	m_cCanvas->update();
}

void PlayArea::editModeSetDimensions()
{
	bool ok;
	QString dims = QInputDialog::getText(tr("Dimensions"),
						 tr("Enter the desired "\
						    "dimensions for your "\
						    "puzzle [width]x[height]"\
						    " (eg: 10x5)"),
						 QLineEdit::Normal,
						 QString::null, &ok, this );
	// Cancel pressed.
	if (!ok)
		return;
	
	QStringList ql = QStringList::split(QChar('x'), dims);
	// There has to be exactly two dimensions.
	if (ql.count() != 2)
	{
		QMessageBox::warning(this, tr("Invalid dimensions"),
				     tr("The format of the dimensions must "\
					"be [width]x[height] (eg: 10x5)"));
		return;
	}
	
	QRegExp rx("[0-9]{1,2}");
	int pos = 0;
	QRegExpValidator v( rx, 0 );
	if (v.validate( ql[0], pos ) && v.validate( ql[1], pos ))
	{
		int width =  ql[0].toInt();
		int height = ql[1].toInt();
		loadPuzzle(new Puzzle(width, height, QPoint(0, 0),
				      QPoint(0, 0), Square::Black));
	}
	else
	{
		QMessageBox::warning(this, tr("Invalid dimensions"),
				     tr("The dimensions you provided are "\
				        "invalid"));
		return;
	}
}


void PlayArea::printStroke()
{
	std::vector<PlaySquare*>::const_iterator i;
	printf("Stroke: ");
	for (i = m_vStroke.begin(); i!=m_vStroke.end(); i++)
		printf("%d:[%d, %d]; ", (*i)->getStrokePosition(),
					(*i)->getGridPos().x(),
					(*i)->getGridPos().y());
	printf("\n");
}
