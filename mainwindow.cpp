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
 
 Class          :   MainWindow
 Author         :   Luc Vo Van
 Original Date  :   18.05.2005
 Description    :   The main game window.
 
 */

#include <qmainwindow.h>
#include <qaction.h>
#include <qcanvas.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qstatusbar.h>
#include <qcanvas.h>
#include <qapplication.h>
#include <qclipboard.h>
#include <qcstring.h>
#include <qbuffer.h>
#include <qtextstream.h>
#include <qhttp.h>

#include "stroqconst.h"
#include "aboutdialog.h"
#include "selectpuzzledialog.h"
#include "mainwindow.h"
#include "playarea.h"
#include "square.h"

MainWindow::MainWindow(QWidget *parent, const char *name)
	: QMainWindow(parent, name, 0)
{
	// Screws up on fluxbox??
	// statusBar()->setSizeGripEnabled(false);
	m_sCurrentCode = tr("(No puzzle loaded)");
	m_bFirstDisplay = true;

	createGameArea();
	createActions();
	createMenus();
	loadFirstPuzzle();
}

MainWindow::~MainWindow()
{
	delete potdBuffer;
}

void MainWindow::about()
{
	AboutDialog *ad = new AboutDialog(this);
	ad->exec();
}

void MainWindow::aboutQt()
{
	QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::selectPuzzle()
{
	SelectPuzzleDialog *spd = new SelectPuzzleDialog(this);
	if(spd->exec() == QDialog::Accepted)
		playArea->loadPuzzle(new Puzzle(spd->getPuzzleCode()));
}

void MainWindow::toggleEditMode()
{
	playArea->toggleEditMode();
	newEditPuzzleAct->setEnabled(playArea->getEditMode());
	invertPuzzleAct->setEnabled(playArea->getEditMode());
	
	if(playArea->getEditMode())
		setCaption("StroQ: Edit mode");
	else
		setCaption("StroQ");
}

void MainWindow::copyPuzzleCode()
{
	QClipboard *cb = QApplication::clipboard();

	if(cb->supportsSelection())
	{
		// In X11, copy to the middle mouse button clipboard as well
		cb->setText(m_sCurrentCode, QClipboard::Selection);
	}
	
	cb->setText(m_sCurrentCode, QClipboard::Clipboard);
}

void MainWindow::puzzleChanged(Puzzle* puzzle, QSize sizeHint)
{
	// Changes the window's caption
	QString caption = "StroQ";
	m_sCurrentCode = puzzle->getCode();
	
	if (playArea->getEditMode())
		caption += " : Edit";
	caption += ": " + m_sCurrentCode;
	setCaption(caption);
	
	// Changes the window's size
	sizeHint.setHeight(sizeHint.height() + menuBar()->height());
	resize(sizeHint);
}

void MainWindow::enterPuzzleCode()
{
	bool ok;
	QString code = QInputDialog::getText("Puzzle Code",
					     "Enter the puzzle code:",
					     QLineEdit::Normal,
					     QString::null, &ok, this );
	code = code.upper();
	if (ok && !code.isEmpty())
	{
		if (Puzzle::isCodeValid(code))
			playArea->loadPuzzle(new Puzzle(code));
		else
		{
			QString errmsg = QString("%1 is not a valid StroQ "\
						 "puzzle code").arg(code);
			QMessageBox::warning(this, tr("Code input error"),
					     errmsg, QMessageBox::Ok, 0, 0);
		}
	}
}

/* Networking code follows */

void MainWindow::downloadPuzzleOfTheDay()
{
	potdBuffer = new QBuffer(QByteArray());
	potdBuffer->open(IO_ReadWrite);
	potdHttp.setHost(POTD_HOST);
	potdHttp.get(POTD_FILE, potdBuffer);
}

void MainWindow::downloadPuzzleOfTheDayFinished(bool error)
{
	potdBuffer->close();
	if (error)
	{
		QMessageBox::warning(this, tr("Puzzle of the day"),
				     tr("Error while fetching the puzzle "\
				     	"of the day:\n%1")
				     .arg(potdHttp.errorString()));
	}
	else
	{
		// Read the puzzle from the buffer and load it.
		potdBuffer->open(IO_ReadOnly);
		QTextStream ts(potdBuffer);
		QString potd = ts.readLine();
		playArea->loadPuzzle(new Puzzle(potd));
		potdBuffer->close();
	}
	potdHttp.abort();
}

void MainWindow::quit()
{
	close();
}

/* End of networking code */

void MainWindow::createActions()
{
	// About menu
	aboutStroQAct = new QAction(tr("&About"), 0, this);
	aboutStroQAct->setStatusTip(tr("About StroQ"));
	connect(aboutStroQAct, SIGNAL(activated()), this, SLOT(about()));
	
	aboutQtAct = new QAction(tr("&About Qt"), 0, this);
	aboutQtAct->setStatusTip(tr("About the Qt toolkit"));
	connect(aboutQtAct, SIGNAL(activated()), this, SLOT(aboutQt()));
	
	// Puzzle menu
	selectPuzzleAct = new QAction(tr("&Select puzzle"), Key_F2, this);
	selectPuzzleAct->setStatusTip(tr("Select a puzzle!"));
	connect(selectPuzzleAct, SIGNAL(activated()),
		this, SLOT(selectPuzzle()));
	
	enterPuzzleCodeAct = new QAction(tr("&Enter puzzle code"),
					 Key_F3, this);
	enterPuzzleCodeAct->setStatusTip(tr("Enter a puzzle code!"));
	connect(enterPuzzleCodeAct, SIGNAL(activated()),
		this, SLOT(enterPuzzleCode()));
	
	downloadPuzzleOfTheDayAct = new QAction(tr("&Puzzle of the Day"),
						0, this);
	downloadPuzzleOfTheDayAct->setStatusTip(tr("Download the puzzle" \
			"of the day from the official StroQ site!"));
	connect(downloadPuzzleOfTheDayAct, SIGNAL(activated()),
		this, SLOT(downloadPuzzleOfTheDay()));
	
	// Play menu
	resetPuzzleAct = new QAction(tr("&Reset puzzle"), Key_F4, this);
	resetPuzzleAct->setStatusTip(tr("Reset the puzzle!"));
	connect(resetPuzzleAct, SIGNAL(activated()),
		playArea, SLOT(resetGrid()));
	
	runPuzzleAct = new QAction(tr("&Run puzzle"), Key_F5, this);
	runPuzzleAct->setStatusTip(tr("Run the puzzle!"));
	connect(runPuzzleAct, SIGNAL(activated()),
		playArea, SLOT(toggleStroke()));
	
	editPuzzleAct = new QAction(tr("&Edit mode"), CTRL + Key_E, this);
	editPuzzleAct->setStatusTip(tr("Edit a new puzzle!"));
	editPuzzleAct->setToggleAction(true);
	connect(editPuzzleAct, SIGNAL(activated()),
		this, SLOT(toggleEditMode()));
	
	newEditPuzzleAct = new QAction("New puzzle...", 0, this);
	newEditPuzzleAct->setStatusTip(tr("Edit a new puzzle"));
	connect(newEditPuzzleAct, SIGNAL(activated()),
			playArea, SLOT(editModeSetDimensions()));
	
	invertPuzzleAct = new QAction("Invert", 0, this);
	invertPuzzleAct->setStatusTip(tr("Invert the puzzle"));
	connect(invertPuzzleAct, SIGNAL(activated()),
		playArea, SLOT(invertPuzzle()));
	
	copyPuzzleCodeAct = new QAction("Copy puzzle code",
					CTRL + Key_C, this);
	copyPuzzleCodeAct->setStatusTip(tr("Copy puzzle code to clipboard"));
	connect(copyPuzzleCodeAct, SIGNAL(activated()),
		this, SLOT(copyPuzzleCode()));
	
	quitAct = new QAction(tr("&Quit"), 0, this);
	quitAct->setStatusTip(tr("Quit StroQ"));
	connect(quitAct, SIGNAL(activated()), this, SLOT(quit()));
	
	connect(playArea, SIGNAL(puzzleChanged(Puzzle*, QSize)),
		this, SLOT(puzzleChanged(Puzzle*, QSize)));

	connect(&potdHttp, SIGNAL(done(bool)),
		this, SLOT(downloadPuzzleOfTheDayFinished(bool)));
}

void MainWindow::createMenus()
{
	aboutMenu = new QPopupMenu(this);
	aboutStroQAct->addTo(aboutMenu);
	aboutQtAct->addTo(aboutMenu);
	
	puzzleMenu = new QPopupMenu(this);
	selectPuzzleAct->addTo(puzzleMenu);
	enterPuzzleCodeAct->addTo(puzzleMenu);
	downloadPuzzleOfTheDayAct->addTo(puzzleMenu);
	puzzleMenu->insertSeparator();
	quitAct->addTo(puzzleMenu);
	
	playMenu = new QPopupMenu(this);
	resetPuzzleAct->addTo(playMenu);
	runPuzzleAct->addTo(playMenu);
	playMenu->insertSeparator();
	copyPuzzleCodeAct->addTo(playMenu);
	
	editMenu = new QPopupMenu(this);
	editPuzzleAct->addTo(editMenu);
	newEditPuzzleAct->addTo(editMenu);
	invertPuzzleAct->addTo(editMenu);
	
	newEditPuzzleAct->setEnabled(false);
	invertPuzzleAct->setEnabled(false);
	
	menuBar()->insertItem(tr("&Puzzle"), puzzleMenu); // 0
	menuBar()->insertItem(tr("&Play"), playMenu);     // 1
	menuBar()->insertItem(tr("&Edit"), editMenu);     // 2
	menuBar()->insertItem(tr("&About"), aboutMenu);   // 3
}

void MainWindow::createGameArea()
{
	mainCanvas = new QCanvas(width(), height());
	mainCanvas->setDoubleBuffering(true);
	playArea = new PlayArea(mainCanvas, this, "playGrid", 0);
	playArea->setVScrollBarMode(QScrollView::AlwaysOff);
	playArea->setHScrollBarMode(QScrollView::AlwaysOff);
	setCentralWidget(playArea);
	
	mainCanvas->update();
}

void MainWindow::loadFirstPuzzle()
{
	playArea->loadPuzzle(new Puzzle("AONAAAKNGLFKI"));
	playArea->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	if (m_bFirstDisplay)
	{
		m_bFirstDisplay = false;
		resize(event->size().width(),
			event->size().height() + menuBar()->height());
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
}

