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

#include "puzzle.h"
#include "playsquare.h"

#include "selectpuzzledialogbase.h"
#include "previewcanvasview.h"

class QCanvasView;
class QLabel;
class QHBox;

class SelectPuzzleDialog : public SelectPuzzleDialogBase
{
	Q_OBJECT

public:
	SelectPuzzleDialog(QWidget *parent = 0, int currentpuzzle = 0,
					   const char *name = 0,
					   bool modal = true, WFlags fl = 0);
	~SelectPuzzleDialog();
	
	QCanvas *puzzlePreviewCanvas;
	PreviewCanvasView *puzzlePreviewCanvasView;
	QHBox *descriptionBox;
	QLabel *indexLabel;
	QLabel *indexLabelValue;
	QLabel *authorLabel;
	QLabel *authorLabelValue;
	QLabel *sizeLabel;
	QLabel *sizeLabelValue;
	QLabel *bestStrokeLabel;
	QLabel *bestStrokeLabelValue;

	/**
	 * Returns the code of the puzzle which's number is given
	 * @param puzzlenumber Number of the puzzle to get the code for
	 */
	static QString getPuzzleCode(int puzzlenumber);
	
	// The following two methods are used to get the results of the dialog
	QString getPuzzleCode();
	int SelectPuzzleDialog::getPuzzleNumber();

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
	void previewPuzzle(int);
	
	/**
	 *
	 */
	 void calibratePreviewCanvasView();
	
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
	void selectPuzzle(int selectedIndex);
	
	/**
	 * Loads the puzzle list into the dialog (with checkmarks
	 * and all from the settings file)
	 */
	void loadPuzzleList();
	
	/**
	 * Resets all puzzles to unsolved in the settings file 
	 */
	void resetSave();
	
	/**
	 * Changes the current theme
	 * @param themenum Theme to use
	 */
	void changeTheme(int themenum);

private:
	QString m_qsSelectedCode; /**< The code that was selected (if any) */
	int m_iSelectedPuzzle; /**< The selected puzzle number */
	
	QPixmap m_qpmCheckmark;
	QPixmap m_qpmNoCheckmark;
	Puzzle *m_ppPreviewPuzzle;

	static QString m_qsPuzzles[];

};

#endif
