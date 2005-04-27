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

 Class          :   SelectPuzzleDialog
 Author         :   Ahmed Aït Mouss
 Original Date  :   22.05.2005
 Description    :   The puzzle selection dialog
*/

#ifndef SELECTPUZZLEDIALOG_H
#define SELECTPUZZLEDIALOG_H

#include <qcanvas.h>

#include "selectpuzzledialogbase.h"

class QCanvasView;
class QLabel;

class SelectPuzzleDialog : public SelectPuzzleDialogBase
{
	Q_OBJECT

public:
	static QString m_qsPuzzles[];
	SelectPuzzleDialog(QWidget *parent = 0, const char *name = 0,
			   bool modal = true, WFlags fl = 0);

	QCanvas *puzzlePreviewCanvas;
	QCanvasView *puzzlePreviewCanvasView;
	QLabel *descriptionLabel;

	QString getPuzzleCode();

signals:
	/**
	 * Emitted when we want to reload the puzzle list
	 */
	void reloadPuzzleList();
	
public slots:
	/**
	* Previews a puzzle given a code
	*
	* @param puzzlecode Code of the puzzle to preview
	*/
	void previewPuzzle(const QString &puzzlecode);
	
	/**
	* Selects a puzzle using the currently selected puzzle
	* in the QListBox
	*/
	void selectPuzzle();

	
	/**
	* Selects a puzzle given its code
	*
	* @param puzzlecode Code of the puzzle to select
	*/
	void selectPuzzle(const QString &puzzlecode);
	
	/**
	 * Loads the puzzle list into the dialog (with checkmarks
	 * and all from the settings file)
	 */
	void loadPuzzleList();
	
	/**
	 * Resets all puzzles to unsolved in the settings file 
	 */
	void resetSave();

private:
	QString m_qsSelectedCode; /**< The code that was selected (if any) */
	QPixmap m_qpmCheckmark;
	QPixmap m_qpmNoCheckmark;
};

#endif
