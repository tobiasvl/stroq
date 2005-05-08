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
#include <qhbox.h>
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

/*
QString SelectPuzzleDialog::m_qsPuzzles[] = {
	// 00 - 09
	"AONAAAKNGLFKI", "Nintendo/Mitchell",
	"AOPAAANOPHLINGC", "Nintendo/Mitchell",
	"AOPAAANOPHLINGK", "Nintendo/Mitchell",
	"BBGAAAACDFKNGDHJMM", "Nintendo/Mitchell",
	"APNAAAIPAGCMBIO", "Nintendo/Mitchell",
	"AOEAAADDMM", "Nintendo/Mitchell",
	"APGAAADAOCIIGBI", "Nintendo/Mitchell",
	"APNAAAMDLHGMJJC", "Nintendo/Mitchell",
	"APLAAABAHBPA", "Nintendo/Mitchell",
	"APEAAAIGBEJO", "Nintendo/Mitchell",
	
	// 10 - 19
	"AOEAAAGJJG", "Nintendo/Mitchell",
	"APMAAAIDFGKMB", "Nintendo/Mitchell",
	"APGAAAFFFKKKFFF", "Nintendo/Mitchell",
	"AOLAAAHGNM", "Nintendo/Mitchell",
	"AONAAAILJEOII", "Nintendo/Mitchell",
	"AONAAAPAFMBPA", "Nintendo/Mitchell",
	"AONAAACFFFFCA", "Nintendo/Mitchell",
	"APLAAADINIOA", "Nintendo/Mitchell",
	"ANOAAAFHDKI", "Nintendo/Mitchell",
	"AOEAAADFKM", "Nintendo/Mitchell",
	
	// 20 - 29
	"BCCAAAADIPAGACADNPNPFPBM", "Nintendo/Mitchell",
	"APPAAAMBBKDPMPJBDDA", "Nintendo/Mitchell",
	"BCCAAAAAMBODGDOAGAMNJNPM", "Nintendo/Mitchell",
	"BCCAAAADMHNFMAGMAOBPHPDM", "Nintendo/Mitchell",
	"BCBEAAABPLGOLPHFJI", "Nintendo/Mitchell",
	"BCCAAAABPJAJAJPKAEJBMAII", "Nintendo/Mitchell",
	"BCCAAAACADOPOOCCDCACACPI", "Nintendo/Mitchell",
	"BCBEAAAADNKJDFPEAE", "Nintendo/Mitchell",
	"BCBEAAADMDBIHJNICA", "Nintendo/Mitchell",
	"BCCAAAADADABABABIFMNPJEA", "Nintendo/Mitchell",
	
	// 30 - 39
	"BBOAAAABPCCFEIJBCKEEPI", "Nintendo/Mitchell",
	"BCBEAAABALJNGLJNAI", "Nintendo/Mitchell",
	"APLAAALKKKOI", "Nintendo/Mitchell",
	"AOEAAABIBI", "Nintendo/Mitchell",
	"AONAAAHFFNFHA", "Nintendo/Mitchell",
	"APPAAAHNAGONFLLAFPA", "Nintendo/Mitchell",
	"APGAAALFCIGBEKN", "Nintendo/Mitchell",
	"BCAMAAACJFPKJE", "Nintendo/Mitchell",
	"AONAAAFGNEENI", "Nintendo/Mitchell",
	"AONAAAHGOLLHA", "Nintendo/Mitchell",
	
	// 40 - 49
	"BBGAAAABNLNLJIOGDI", "Nintendo/Mitchell",
	"BCCAAAADAOEEBBAAPCPGPGAE", "Nintendo/Mitchell",
	"BCCAAAADLPJPIPLPLMDCAHAM", "Nintendo/Mitchell",
	"BCCAAAADBOKPLPBOAKICACAI", "Nintendo/Mitchell",
	"BCCAAAADLLKLLIOBLJPMHMPM", "Nintendo/Mitchell",
	"APPAAAICHAOEBNLGPGI", "Nintendo/Mitchell",
	"BCBEAAADAOJEJAAKGE", "Nintendo/Mitchell",
	"APPAAAICKFEBAAEPKAI", "Nintendo/Mitchell",
	"BCCAAAABMAMBMAODOAOBPBHM", "Nintendo/Mitchell",
	"BCCAAAAAPBAJAKJGAFPIJBJI", "Nintendo/Mitchell",
	
	// 50 - 59
	"BCBEAAAAPAPDIPKPIM", "Nintendo/Mitchell",
	"BCBEAAADJNAJAIGAGA", "Nintendo/Mitchell",
	"BCBEAAACPFGJPLJPJM", "Nintendo/Mitchell",
	"BCBEAAAAGCPHNPIPKM", "Nintendo/Mitchell",
	"BCBEAAAAGDHKPHJOJE", "Nintendo/Mitchell",
	"BCBEAAACPEGCPHPLAM", "Nintendo/Mitchell",
	"BCBEAAACONFHPLBLBM", "Nintendo/Mitchell",
	"BCBEAAADDEAEMAMEMA", "Nintendo/Mitchell",
	"BCBEAAADIGKEAEMIMI", "Nintendo/Mitchell",
	"BCBEAAAAGBAIGDPHBM", "Nintendo/Mitchell",
	
	// 60-69
	"BCCAAAADJPAPAPAOAGBECDJM", "Nintendo/Mitchell",
	"BCCAAAADHGCCIKAAHMFEHOAA", "Nintendo/Mitchell",
	"BCCAAAADJPAPJKAAJPIPKOCE", "Nintendo/Mitchell",
	"BCCAAAAAEBMDEDMFOEPMPJJM", "Nintendo/Mitchell",
	"APGAAAIFOFBOHKB", "Nintendo/Mitchell",
	"BCCAAAABPLAPGNDJJLGPANPI", "Nintendo/Mitchell",
	"BCCAAAADJPNPNPOPHPLPLPJM", "Nintendo/Mitchell",
	"BCCAAAADAOAFAJAIGAPCAEGA", "Nintendo/Mitchell",
	"APPAAAECPNALPECPNAI", "Nintendo/Mitchell",
	"BCCAAAAAHEMJPDHKPKPLPJPA", "Nintendo/Mitchell",
	
	// 70-79
	"BCCAAAACIBECKBFAKIFECIBE", "Nintendo/Mitchell",
	"BBKAAAABOIEMIFOMNOIE", "Nintendo/Mitchell",
	"BCCAAAACJEJDGMJAJDGMJCJE", "Nintendo/Mitchell",
	"BCCAAAACJEPDANGJGLAMPCJE", "Nintendo/Mitchell",
	"BCCAAAAAPBPLAPGPGPANPIPA", "Nintendo/Mitchell",
	"BCCAAAAAPAJDGOJGJHGMJAPA", "Nintendo/Mitchell",
	"APPAAAGNKOAKKIDKNLA", "Nintendo/Mitchell",
	"APPAAACINLBIIMGNIKA", "Nintendo/Mitchell",
	"BCCAAAABAKJFGIJAJBGKJFAI", "Nintendo/Mitchell",
	"BCCAAAABAKGEJBAJAIJCGFAI", "Nintendo/Mitchell",
	
	// 80-89
	"APPAAAICHBBCAEEHCAI", "Nintendo/Mitchell",
	"BBOAAAACANNLLHGEMBJDAE", "Nintendo/Mitchell",
	"BBOAAAACANNKLBGEMBJDAE", "Nintendo/Mitchell",
	"APPAAADIFDBMBOOCAOA", "Nintendo/Mitchell",
	"APPAAAGNCGAMBEEFAEA", "Nintendo/Mitchell",
	"APPAAAOPKOOLOJDNPBI", "Nintendo/Mitchell",
	"APPAAABAFBBEBEEFAEA", "Nintendo/Mitchell",
	"APPAAALLKPLMBOPAHLI", "Nintendo/Mitchell",
	"APPAAAOPAGPMBPLAHLI", "Nintendo/Mitchell",
	"APPAAADMIHOCAPIIEPA", "Nintendo/Mitchell",
	0,
	
	"", "",
	"", "",
	"", "",
	"", "",
	"", "",
	0
	};
*/

QString SelectPuzzleDialog::m_qsPuzzles[] = {
	// 00-09
	"AONAAANNFFFNI", "Lemming",
	"BCCAAAACLGLHIHLGLGLADEDE", "Herb007",
	"BBKAAAACODLCFJGMPKCM", "Herb007",
	"BCCAAAAAAMDMPPPIAMDIODIA", "Herb007",
	"BCCAAAADMDIDAHMHIHBOHMPM", "Herb007",
	"BCCAAAAADADADAHAOBODMPIM", "Herb007",
	"BCCAAAADPLIHIPHODODPHPHM", "Herb007",
	"BCBAAAACKOOLDDLI", "Herb007",
	"BCCAAAADFLJDOOAHBNADOMAM", "Herb007",

	// 10-19
	"BCBIAAABPJANOJCJDNPA", "Herb007",
	"BBOAAAADBODOPNPFODMHIM", "Herb007",
	"APOAAAGNAEKBEJCFA", "Herb007",
	"BCCAAAADAOBMDMBMJJMHODPA", "Herb007",
	"BCCAAAACPFGKJFPIPBPKGHJM", "Herb007",
	"BCBEAAAAHPEIHBKPKA", "Herb007",
	"BCBMAAADJNAJGJGJAIJCGE", "Herb007",
	"BBKAAAADIBOOKDOBOOKI", "Herb007",
	"BCBMAAABJLGPANGJGKJGPE", "Herb007",
	"BCCAAAADMAAFMAAMMABMEADM", "Herb007",
	
	// 20-29
	"BCCAAAACAFPJGLCPEPGNPKAE", "Herb007",
	"BBGAAAAAJOBKPMFPGM", "Herb007",
	"BCBMAAABKCKPLNAPNPFEFI", "Herb007",
	"BCBEAAAAJBPJGJPIJA", "Herb007",
	"BBGAAAADFDHNHNHMKM", "Herb007",
	"BCCAAAAAPDMPDMPPPDNPDMPA", "Herb007",
	"BCCAAAACJGPFJKPHJNPKJHJM", "Herb007",
	"APOAAAMGNLBMJIDIM", "Herb007",
	"BCBIAAACGGGFJKPEPDAM", "Herb007",
	"BBGAAAADEFJBPABONE","Avalanche",

	// 30-39
	"BCCAAAACAHPHPHPHPHOPNPDM","originalcracker",
	"BCCAAAADOECECHOGHOECECHM","originalcracker",
	"BCCAAAACPMAOPOAPOPOPOOAM","originalcracker",
	"AOOAAAOPDLAKME","originalcracker",
	"AONAAAHIECBDI","originalcracker",
	"BCCAAAABGBADOBCBCBCBCBCA","originalcracker",
	"BCCAAAABPNPNPNPMHNHNHNBM","originalcracker",
	"BCCAAAACPOPOAOPOPOPPHPIM","originalcracker",
	"BCCAAAABABABABPBABABABAA","originalcracker",
	"BCCAAAADPIAHPICECAEAIBAA","originalcracker",

	// 40-49
	"BCCAAAABPPMFBBGPGMBDJBPM","TS2Master",
	"BCBEAAADAKPFECPKAE","TS2Master",
	"BCCAAAAAPAJALAIABANAJAPA","skarmachild5000",
	"BCBMAAADGOGGGFPIPCPGAE","skarmachild5000",
	"BCCAAAADOMBLAFABAFAFDOFM","skarmachild5000",
	"BCCAAAABPJPJPJPJPIGBAIGA","skarmachild5000",
	"BCCAAAAAGBAIGCDGIEGBAIGA","nonexistinghero",
	"BCCAAAABPMPEHMDMBMANAEAE","pikaafro",
	"BCCAAAACPFGKPHNPJPAPGPAM","pikaafro",
	"BCCAAAACAFJJAIGAGBAJJKAE","skarmachild5000",

	// 50-...
	"BCCAAAAAOAOAKAEDPIEAKBLA","skarmachild5000",
	"BCCAAAADAPIPMPOPHPDPBPAM","skarmachild5000",
	"BCCAAAABPPMFBBGPGMBDJBPM","skarmachild5000",
	"BCCAAAAAEBDFLEDEHFDFDEEE","skarmachild5000",
	"BCCAAAACKOFIJNEDDFIDEBHA","LLCoolDave",
	"BCCAAAACCGCCCBPPPGIAICIA","klasoen",
	"BCBMAAADKPKPKPKOPKPLAE","menmanelf",
	"APPAAAJABAAIBADOPMA","Evan1109",
	"APOAAADAAFIBBBIHA","Evan1109",
	"BCCAAAACHGAAMJJLILOCPAOA","Evan1109",
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

	codesListBox->setSelectionMode(QListBox::Single);

	QBoxLayout *vl = new QVBoxLayout(previewFrame);
	puzzlePreviewCanvasView = new PreviewCanvasView(previewFrame);
	puzzlePreviewCanvasView->setVScrollBarMode(QScrollView::AlwaysOff);
	puzzlePreviewCanvasView->setHScrollBarMode(QScrollView::AlwaysOff);
	puzzlePreviewCanvas = new QCanvas(MAX_SIDE*DEFAULT_SIDE,
					  MAX_SIDE*DEFAULT_SIDE);
	puzzlePreviewCanvas->setDoubleBuffering(true);

	puzzlePreviewCanvasView->setCanvas(puzzlePreviewCanvas);

	descriptionBox = new QHBox(previewFrame);
	indexLabel = new QLabel("indexLabel", descriptionBox);
	indexLabel->setTextFormat(Qt::RichText);
	indexLabel->setAlignment(Qt::AlignLeft);
	indexLabel->setText(tr("<u>Puzzle</u>:"));
	indexLabelValue = new QLabel("indexLabelValue", descriptionBox);
	indexLabelValue->setTextFormat(Qt::RichText);
	indexLabelValue->setAlignment(Qt::AlignLeft);
	
	authorLabel = new QLabel("indexLabel", descriptionBox);
	authorLabel->setTextFormat(Qt::RichText);
	authorLabel->setAlignment(Qt::AlignLeft);
	authorLabel->setText(tr("<u>Author</u>:"));
	authorLabelValue = new QLabel("indexLabelValue", descriptionBox);
	authorLabelValue->setTextFormat(Qt::RichText);
	authorLabelValue->setAlignment(Qt::AlignLeft);

	sizeLabel = new QLabel("sizeLabel", descriptionBox);
	sizeLabel->setTextFormat(Qt::RichText);
	sizeLabel->setAlignment(Qt::AlignHCenter);
	sizeLabel->setText(tr("<u>Dimensions</u>:"));
	sizeLabelValue = new QLabel("sizeLabelValue", descriptionBox);
	sizeLabelValue->setTextFormat(Qt::RichText);
	sizeLabelValue->setAlignment(Qt::AlignHCenter);

	
	bestStrokeLabel = new QLabel("bestStrokeLabel", descriptionBox);
	bestStrokeLabel->setTextFormat(Qt::RichText);
	bestStrokeLabel->setAlignment(Qt::AlignRight);
	bestStrokeLabel->setText(tr("<u>Best stroke</u>:"));
	bestStrokeLabelValue = new QLabel("bestStrokeLabelValue",
					   descriptionBox);
	bestStrokeLabelValue->setTextFormat(Qt::RichText);
	bestStrokeLabelValue->setAlignment(Qt::AlignRight);

	vl->addWidget(puzzlePreviewCanvasView);
	vl->addWidget(descriptionBox);

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
	
	connect(puzzlePreviewCanvasView, SIGNAL(shown()),
		this, SLOT(calibratePreviewCanvasView()));

	// Locks the canvasview so that we can't scroll it
	puzzlePreviewCanvasView->setEnabled(false);
	
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

int SelectPuzzleDialog::getPuzzleNumber()
{
	return m_iSelectedIndex;
}

void SelectPuzzleDialog::previewPuzzle(int i)
{
	QString puzzlecode = m_qsPuzzles[2*i];
	QString labelText;
	QSettings settings;
	settings.setPath("thelemmings.net", "StroQ");
	QStringList puzzles = settings.entryList("/puzzles");
	int solutionLength = 0;

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

	// Sets the description labels.
	indexLabelValue->setText(QString("%1").arg(i));
	authorLabelValue->setText(m_qsPuzzles[(2*i)+1]);

	sizeLabelValue->setText(QString("%1x%2")
			   .arg(m_ppPreviewPuzzle->getWidth())
			   .arg(m_ppPreviewPuzzle->getHeight()));
	
	QStringList::Iterator it;
	for (it = puzzles.begin() ; it != puzzles.end() ; ++it)
		if (puzzlecode == QStringList::split('-', (*it))[1])
			solutionLength = settings.readNumEntry("/puzzles/" +
					 (*it), 0);
	if (solutionLength != 0)
		bestStrokeLabelValue->setText(
			QString("<font color=\"red\"><b>%1</b></font>")
			.arg(solutionLength));
	else
		bestStrokeLabelValue->setText(
			QString("<font color=\"red\"><b>Unsolved</b></font>"));
	
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
	m_qsSelectedCode = m_qsPuzzles[2*selectedIndex];
	m_iSelectedIndex = selectedIndex;
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
							   QString::number(i/2));
		}
		else
			new QListBoxPixmap(codesListBox, m_qpmNoCheckmark,
							   QString::number(i/2));
		
		i+=2;
	}
	codesListBox->setCurrentItem(0);
}

void SelectPuzzleDialog::resetSave()
{
	// If the user pressed Yes, clear the content of the settings file.
	if(QMessageBox::question(
							 this,
							 tr("StroQ - Reset confirmation"),
							 tr("Set all puzzles to unsolved state?"),
							 tr("&Yes"), tr("&No")) == 0)
	{
		QSettings settings;
		settings.setPath("thelemmings.net", "StroQ");
		
		// Get a list of the puzzles in the settings.
		QStringList puzzles = settings.entryList("/puzzles");
		
		// Remove all the entries. Will be populated again when
		// next reloading the list.
		QStringList::Iterator it;
		for (it = puzzles.begin() ; it != puzzles.end() ; ++it)
			settings.removeEntry("/puzzles/" + (*it));
		
		emit reloadPuzzleList();
	}
}

QString SelectPuzzleDialog::getPuzzleCode(int puzzlenumber)
{
	// Counts how many puzzles we have in order to do boundaries check
	int i = 0;
	while(m_qsPuzzles[i])
		i++;
	
	if(puzzlenumber < (i/2)-1)
		return m_qsPuzzles[puzzlenumber*2];
	else
		return QString("");
}
