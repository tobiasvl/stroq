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
#include <qmessagebox.h>
#include <qwmatrix.h>

#include "selectpuzzledialog.h"
#include "stroqconst.h"

#include "images/checkmark.xpm"

QString SelectPuzzleDialog::m_qsPuzzles[] = {
	// 00 - 09
	"AONAAAKNGLFKI", "AOPAAANOPHLINGC",
	"AOPAAANOPHLINGK", "BBGAAAACDFKNGDHJMM",
	"APNAAAIPAGCMBIO", "AOEAAADDMM",
	"APGAAADAOCIIGBI", "APNAAAMDLHGMJJC",
	"APLAAABAHBPA", "APEAAAIGBEJO",
	
	// 10 - 19
	"AOEAAAGJJG", "APMAAAIDFGKMB",
	"APGAAAFFFKKKFFF", "AOLAAAHGNM",
	"AONAAAILJEOII", "AONAAAPAFMBPA",
	"AONAAACFFFFCA", "APLAAADINIOA",
	"ANOAAAFHDKI", "AOEAAADFKM",
	
	// 20 - 29
	"BCCAAAADIPAGACADNPNPFPBM", "APPAAAMBBKDPMPJBDDA",
	"BCCAAAAAMBODGDOAGAMNJNPM", "BCCAAAADMHNFMAGMAOBPHPDM",
	"BCBEAAABPLGOLPHFJI", "BCCAAAABPJAJAJPKAEJBMAII",
	"BCCAAAACADOPOOCCDCACACPI", "BCBEAAAADNKJDFPEAE",
	"BCBEAAADMDBIHJNICA", "BCCAAAADADABABABIFMNPJEA",
	
	// 30 - 39
	"BBOAAAABPCCFEIJBCKEEPI", "BCBEAAABALJNGLJNAI",
	"APLAAALKKKOI", "AOEAAABIBI",
	"AONAAAHFFNFHA", "APPAAAHNAGONFLLAFPA",
	"APGAAALFCIGBEKN", "BCAMAAACJFPKJE",
	"AONAAAFGNEENI", "AONAAAHGOLLHA",
	
	// 40 - 49
	"BBGAAAABNLNLJIOGDI", "BCCAAAADAOEEBBAAPCPGPGAE",
	"BCCAAAADLPJPIPLPLMDCAHAM", "BCCAAAADBOKPLPBOAKICACAI",
	"BCCAAAADLLKLLIOBLJPMHMPM", "APPAAAICHAOEBNLGPGI",
	"BCBEAAADAOJEJAAKGE", "APPAAAICKFEBAAEPKAI",
	"BCCAAAABMAMBMAODOAOBPBHM", "BCCAAAAAPBAJAKJGAFPIJBJI",
	
	// 50 - 59
	"BCBEAAAAPAPDIPKPIM", "BCBEAAADJNAJAIGAGA",
	"BCBEAAACPFGJPLJPJM", "BCBEAAAAGCPHNPIPKM",
	"BCBEAAAAGDHKPHJOJE", "BCBEAAACPEGCPHPLAM",
	"BCBEAAACONFHPLBLBM", "BCBEAAADDEAEMAMEMA",
	"BCBEAAADIGKEAEMIMI", "BCBEAAAAGBAIGDPHBM",
	
	// 60-69
	"BCCAAAADJPAPAPAOAGBECDJM", "BCCAAAADHGCCIKAAHMFEHOAA",
	"BCCAAAADJPAPJKAAJPIPKOCE", "BCCAAAAAEBMDEDMFOEPMPJJM",
	"APGAAAIFOFBOHKB", "BCCAAAABPLAPGNDJJLGPANPI",
	"BCCAAAADJPNPNPOPHPLPLPJM", "BCCAAAADAOAFAJAIGAPCAEGA",
	"APPAAAECPNALPECPNAI", "BCCAAAAAHEMJPDHKPKPLPJPA",
	
	// 70-79
	"BCCAAAACIBECKBFAKIFECIBE", "BBKAAAABOIEMIFOMNOIE",
	"BCCAAAACJEJDGMJAJDGMJCJE", "BCCAAAACJEPDANGJGLAMPCJE",
	"BCCAAAAAPBPLAPGPGPANPIPA", "BCCAAAAAPAJDGOJGJHGMJAPA",
	"APPAAAGNKOAKKIDKNLA", "APPAAACINLBIIMGNIKA",
	"BCCAAAABAKJFGIJAJBGKJFAI", "BCCAAAABAKGEJBAJAIJCGFAI",
	
	// 80-89
	"APPAAAICHBBCAEEHCAI", "BBOAAAACANNLLHGEMBJDAE",
	"BBOAAAACANNKLBGEMBJDAE", "APPAAADIFDBMBOOCAOA",
	"APPAAAGNCGAMBEEFAEA", "APPAAAOPKOOLOJDNPBI",
	"APPAAABAFBBEBEEFAEA", "APPAAALLKPLMBOPAHLI",
	"APPAAAOPAGPMBPLAHLI", "APPAAADMIHOCAPIIEPA",
	0,
	
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	0
	};

SelectPuzzleDialog::SelectPuzzleDialog(QWidget *parent, const char *name,
                                       bool modal, WFlags fl)
	: SelectPuzzleDialogBase(parent, name, modal, fl)
{
	m_ppPreviewPuzzle = NULL;
	
	m_qpmCheckmark = QPixmap((const char**) checkmark_xpm);
	m_qpmNoCheckmark = QPixmap(12, 12);
	m_qpmNoCheckmark.fill(Qt::white);

	QBoxLayout *vl = new QVBoxLayout(previewFrame);
	puzzlePreviewCanvasView = new PreviewCanvasView(previewFrame);
	puzzlePreviewCanvasView->setVScrollBarMode(QScrollView::AlwaysOff);
	puzzlePreviewCanvasView->setHScrollBarMode(QScrollView::AlwaysOff);
	puzzlePreviewCanvas = new QCanvas(MAX_SIDE*DEFAULT_SIDE,
					  MAX_SIDE*DEFAULT_SIDE);
	puzzlePreviewCanvas->setDoubleBuffering(true);

	puzzlePreviewCanvasView->setCanvas(puzzlePreviewCanvas);

	descriptionLabel = new QLabel("descriptionLabel", previewFrame);
	descriptionLabel->setTextFormat(Qt::RichText);
	vl->addWidget(puzzlePreviewCanvasView);
	vl->addWidget(descriptionLabel);

	connect(codesListBox, SIGNAL(highlighted(int)),
		this, SLOT(previewPuzzle(int)));
	connect(m_pbReset, SIGNAL(clicked()), this, SLOT(resetSave()));
	connect(this, SIGNAL(reloadPuzzleList()),
		this, SLOT(loadPuzzleList()));

	// Selects a puzzle when double clicking on the list
	// or clicking OK.
	connect(codesListBox, SIGNAL(selected(int)),
		this, SLOT(selectPuzzle(int)));
	connect(m_pbOK, SIGNAL(clicked()),  this, SLOT(selectPuzzle()));
	
	connect(puzzlePreviewCanvasView, SIGNAL(shown()), this, SLOT(calibratePreviewCanvasView()));

	// Loads the settings so that we can set wether or not puzzles have
	// already been solved.
	loadPuzzleList();
}

SelectPuzzleDialog::~SelectPuzzleDialog()
{
	if (m_ppPreviewPuzzle)
		delete m_ppPreviewPuzzle;
}

QString SelectPuzzleDialog::getPuzzleCode()
{
	return m_qsSelectedCode;
}

void SelectPuzzleDialog::previewPuzzle(int i)
{
	QString puzzlecode = m_qsPuzzles[i];
	QString labelText;
	QSettings settings;
	settings.setPath("thelemmings.net", "StroQ");
	int solutionLength;

	// Don't display the canvas while we delete the old puzzle
	// and load the new one.
	puzzlePreviewCanvasView->setCanvas(0);
	
	if (m_ppPreviewPuzzle)
		delete m_ppPreviewPuzzle;
	
	// Load the puzzle into a temporary variable.
	Puzzle *tmpPuzzle = new Puzzle(puzzlecode);
	
	// Load the puzzle in the canvasview.
	m_ppPreviewPuzzle = new Puzzle(tmpPuzzle, puzzlePreviewCanvas);
	
	calibratePreviewCanvasView();
	
	// Sets the label
	solutionLength = settings.readNumEntry("/puzzles/" + puzzlecode, -1);
	if(solutionLength != -1)
	{
		// Puzzle has been solved in the past
		labelText = QString(" #%1  Dimensions: %2x%3  Best stroke: <font color=\"red\"><b>%4</b></font>")
			.arg(i)
			.arg(m_ppPreviewPuzzle->getWidth())
			.arg(m_ppPreviewPuzzle->getHeight())
			.arg(solutionLength);
	}
	else
	{
		labelText = QString(" #%1  Dimensions: %2x%3  <font color=\"red\"><b>Not solved yet!</b></font>")
			.arg(i)
			.arg(m_ppPreviewPuzzle->getWidth())
			.arg(m_ppPreviewPuzzle->getHeight());
	}
	descriptionLabel->setText(labelText);

	
	// Delete the temporary variable.
	delete tmpPuzzle;
	
	puzzlePreviewCanvasView->setCanvas(puzzlePreviewCanvas);
}

void SelectPuzzleDialog::calibratePreviewCanvasView()
{
	// Set the transformation matrix so that it centers the
	// puzzle preview in puzzlePreviewCanvasView.
	QWMatrix m;
	m.scale(0.5, 0.5); // Zoom out by 2.
	m.translate(puzzlePreviewCanvasView->visibleWidth()
		- ((DEFAULT_SIDE * (m_ppPreviewPuzzle->getWidth() + 2))) / 2,
		puzzlePreviewCanvasView->visibleHeight()
		- ((DEFAULT_SIDE * (m_ppPreviewPuzzle->getHeight() + 2))) / 2);
	puzzlePreviewCanvasView->setWorldMatrix(m);

}

void SelectPuzzleDialog::selectPuzzle()
{
	selectPuzzle(codesListBox->currentItem());
}

void SelectPuzzleDialog::selectPuzzle(int selectedIndex)
{
	m_qsSelectedCode = m_qsPuzzles[selectedIndex];
	accept();
}

void SelectPuzzleDialog::loadPuzzleList()
{
	int i = 0;
	QSettings settings;
	settings.setPath("thelemmings.net", "StroQ");
	
	// Prepares the puzzle code list.
	codesListBox->clear();
	codesListBox->setSelectionMode(QListBox::Single);
	
	while(m_qsPuzzles[i])
	{
		// If entry exists, the puzzle was already solved.
		if(settings.readNumEntry("/puzzles/" + m_qsPuzzles[i]))
		{
			new QListBoxPixmap(codesListBox, m_qpmCheckmark,
					   QString::number(i));
		}
		else
			new QListBoxPixmap(codesListBox, m_qpmNoCheckmark,
					   QString::number(i));
		
		i++;
	}
	codesListBox->setCurrentItem(0);
}

void SelectPuzzleDialog::resetSave()
{
	int i = 0;
	
	// If the user pressed Yes, clear the content of the settings file.
	if(QMessageBox::question(
				this,
				tr("StroQ - Reset confirmation"),
				tr("Set all puzzles to unsolved state?"),
				tr("&Yes"), tr("&No")) == 0)
	{
		QSettings* settings = new QSettings();
		settings->setPath("thelemmings.net", "StroQ");
		while(m_qsPuzzles[i])
		{
			// If entry exists, the puzzle was already solved.
			settings->removeEntry("/puzzles/" + m_qsPuzzles[i]);
			i++;
		}
		// Writes the settings to disk (or wherever).
		delete settings;
		
		emit reloadPuzzleList();
	}
}
