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
 
 Class          :   AboutDialog
 Author         :   Luc Vo Van
 Original Date  :   28.05.2005
 Description    :   The About dialog
 */

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <qcanvas.h>

#include "aboutdialogbase.h"

class QCanvasView;

class AboutDialog : public AboutDialogBase
{
	Q_OBJECT
	
public:
	AboutDialog(QWidget *parent = 0, const char *name = 0,
				bool modal = true, WFlags fl = 0);
	
	QCanvas *aboutCanvas;
	QCanvasView *aboutCanvasView;
};

#endif