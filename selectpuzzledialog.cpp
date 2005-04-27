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
 Author         :   Luc Vo Van
 Original Date  :   22.05.2005
 Description    :   The puzzle selection dialog
*/

#include <qcanvas.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qpixmap.h>
#include <qsettings.h>
#define PUZZLECOUNT 10

#include "selectpuzzledialog.h"
#include "images/checkmark.xpm"

QString SelectPuzzleDialog::m_qsPuzzles[] = {
	"AONAAAKNGLFKI", "AOPAAANOPHLINGC",
	"AOPAAANOPHLINGK", "BBGAAAACDFKNGDHJMM",
	"APNAAAIPAGCMBIO", "AOEAAADDMM",
	"APGAAADAOCIIGBI", "APNAAAMDLHGMJJC",
	"APLAAABAHBPA", "APEAAAIGBEJO",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	};

QPixmap* SelectPuzzleDialog::m_qpmCheckmark = NULL;

QPixmap* SelectPuzzleDialog::m_qpmNoCheckmark = NULL;

SelectPuzzleDialog::SelectPuzzleDialog(QWidget *parent, const char *name,
                                       bool modal, WFlags fl)
    : SelectPuzzleDialogBase(parent, name, modal, fl)
{
		
	if(!m_qpmCheckmark)
		m_qpmCheckmark = new QPixmap(*checkmark);
	if(!m_qpmNoCheckmark)
		m_qpmNoCheckmark = new QPixmap(*checkmark);
		
	QBoxLayout *vl = new QVBoxLayout(previewFrame);
	puzzlePreviewCanvasView = new QCanvasView(previewFrame);
	puzzlePreviewCanvas = new QCanvas(puzzlePreviewCanvasView->width(),
						puzzlePreviewCanvasView->height());
	descriptionLabel = new QLabel("descriptionLabel", previewFrame);
	vl->addWidget(puzzlePreviewCanvasView);
	vl->addWidget(descriptionLabel);
	
	// Loads the settings so that we can set wether or not puzzles have already
	// been solved
	QSettings settings;
	settings.setPath("thelemmings.net", "StroQ");
	
	// Prepares the puzzle code list
	codesListBox->clear();
	codesListBox->setSelectionMode(QListBox::Single);
	for(int i = 0; i<PUZZLECOUNT; i++)
	{
		if(settings.readBoolEntry(m_qsPuzzles[i]))
    		// new QListBoxPixmap(codesListBox, *m_qpmCheckmark, m_qsPuzzles[i] );
			new QListBoxPixmap( codesListBox, *m_qpmCheckmark, m_qsPuzzles[i] );
		else
			new QListBoxPixmap(codesListBox, *m_qpmNoCheckmark, m_qsPuzzles[i] );
			//new QListBoxPixmap( codesListBox, pm, "Blue" );
	}
	codesListBox->setCurrentItem(0);
	
	connect(codesListBox, SIGNAL(highlighted(const QString &)),
		this, SLOT(previewPuzzle(const QString &)));
	
	// Selects a puzzle when double clicking on the list
	// or clicking OK
	connect(codesListBox, SIGNAL(selected(const QString &)),
		this, SLOT(selectPuzzle(const QString &)));
	connect(okButton, SIGNAL(clicked()), this, SLOT(selectPuzzle()));
}

QString SelectPuzzleDialog::getPuzzleCode()
{
	return m_qsSelectedCode;
}

void SelectPuzzleDialog::previewPuzzle(const QString &puzzlecode)
{
	descriptionLabel->setText(puzzlecode);
}

void SelectPuzzleDialog::selectPuzzle()
{
	selectPuzzle(codesListBox->currentText());
}

void SelectPuzzleDialog::selectPuzzle(const QString &puzzlecode)
{
	m_qsSelectedCode = puzzlecode;
	accept();
}
