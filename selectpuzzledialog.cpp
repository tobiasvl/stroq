
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
#include "selectpuzzledialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qlistbox.h>
#include <qcanvas.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a SelectPuzzleDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SelectPuzzleDialog::SelectPuzzleDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
		setName( "SelectPuzzleDialog" );

    QWidget* privateLayoutWidget = new QWidget( this, "m_lBottomLayout" );
    privateLayoutWidget->setGeometry( QRect( 12, 404, 560, 33 ) );
    m_lBottomLayout = new QHBoxLayout( privateLayoutWidget, 11, 6, "m_lBottomLayout"); 
    m_isSpacer = new QSpacerItem( 350, 31, QSizePolicy::Expanding, QSizePolicy::Minimum );
    m_lBottomLayout->addItem( m_isSpacer );

    m_pbCancel = new QPushButton( privateLayoutWidget, "m_pbCancel" );
    m_lBottomLayout->addWidget( m_pbCancel );

    m_pbOK = new QPushButton( privateLayoutWidget, "m_pbOK" );
    m_lBottomLayout->addWidget( m_pbOK );

    m_sTopSplitter = new QSplitter( this, "m_sTopSplitter" );
    m_sTopSplitter->setGeometry( QRect( 12, 12, 560, 390 ) );
    m_sTopSplitter->setOrientation( QSplitter::Horizontal );

    m_lbPuzzleList = new QListBox( m_sTopSplitter, "m_lbPuzzleList" );

    QWidget* privateLayoutWidget_2 = new QWidget( m_sTopSplitter, "m_lPreviewLayout" );
    m_lPreviewLayout = new QVBoxLayout( privateLayoutWidget_2, 11, 6, "m_lPreviewLayout"); 

    m_cvPuzzlePreview = new QCanvasView( privateLayoutWidget_2, "m_cvPuzzlePreview" );
    m_lPreviewLayout->addWidget( m_cvPuzzlePreview );

    m_tlPuzzleDescription = new QLabel( privateLayoutWidget_2, "m_tlPuzzleDescription" );
    m_lPreviewLayout->addWidget( m_tlPuzzleDescription );
    languageChange();
    resize( QSize(583, 447).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    
    connect(m_pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_pbOK, SIGNAL(clicked()), this, SLOT(accept()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
SelectPuzzleDialog::~SelectPuzzleDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SelectPuzzleDialog::languageChange()
{
    setCaption( tr( "SelectPuzzleDialog" ) );
    m_pbCancel->setText( tr( "Cancel" ) );
    m_pbOK->setText( tr( "OK" ) );
    m_lbPuzzleList->clear();
    m_lbPuzzleList->insertItem( tr( "New Item" ) );
    m_tlPuzzleDescription->setText( tr( "textLabel1" ) );
}

