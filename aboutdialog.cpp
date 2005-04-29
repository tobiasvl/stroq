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

#include <qcanvas.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpixmap.h>

#include "stroqconst.h"
#include "aboutdialog.h"

#include "images/aboutimage.xpm"

AboutDialog::AboutDialog(QWidget *parent, const char *name, bool modal, WFlags fl)
			: AboutDialogBase(parent, name, modal, fl)
{
	m_plAboutIcon->setPixmap(QPixmap((const char**) aboutimage_xpm));
	QString aboutString = "<b>StroQ " + VERSION + "</b><br/><br/>" +
				"StroQ - A Polarium/Chokkan Hitofude Clone<br/><br/>" +
				"Copyright (C) 2005 Luc Vo Van<br/>" +
				"This program is free software; you can redistribute it and/or modify " +
				"it under the terms of the GNU General Public License as published by " +
				"the Free Software Foundation; either version 2 of the License, or " +
				"any later version.<br/>";

	m_plAboutText->setTextFormat(Qt::RichText);
	m_plAboutText->setText(aboutString);
	setCaption(tr("About StroQ "));
	m_pbOK->setText(tr("OK"));
	
	connect(m_pbOK, SIGNAL(clicked()), this, SLOT(accept()));
}
