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
 
 Class          :   Main
 Author         :   Luc Vo Van
 Original Date  :   18.05.2005
 Description    :   The main class used to launch the QApplication
 
 */

#include <qapplication.h>
#include <qtranslator.h>
#include <qtextcodec.h>
#include <qapplication.h>

#include "mainwindow.h"
#include "stroqconst.h"

/**
 * This is a message handler that does nothing to hide warning messages
 */
void doNothingMsgHandler( QtMsgType type, const char *msg ) {}

int main(int argc, char *argv[])
{
	qInstallMsgHandler(doNothingMsgHandler);
		
	QApplication app(argc, argv);
	// Selects the locale
	QTranslator translator(0);
	translator.load(QString("StroQ_") + QTextCodec::locale(), ".");
	app.installTranslator(&translator);

	MainWindow mwin;
	app.setMainWidget(&mwin);
	mwin.show();
	return app.exec();
}
