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
#ifndef SELECTPUZZLEDIALOG_H
#define SELECTPUZZLEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QSplitter;
class QListBox;
class QListBoxItem;
class QCanvasView;
class QLabel;

class SelectPuzzleDialog : public QDialog
{
    Q_OBJECT

public:
    SelectPuzzleDialog( QWidget* parent = 0, const char* name = 0, bool modal = TRUE, WFlags fl = 0 );
    ~SelectPuzzleDialog();

    QPushButton* m_pbCancel;
    QPushButton* m_pbOK;
    QSplitter* m_sTopSplitter;
    QListBox* m_lbPuzzleList;
    QCanvasView* m_cvPuzzlePreview;
    QLabel* m_tlPuzzleDescription;

protected:
    QHBoxLayout* m_lBottomLayout;
    QSpacerItem* m_isSpacer;
    QVBoxLayout* m_lPreviewLayout;

protected slots:
    virtual void languageChange();

};

#endif // SELECTPUZZLEDIALOG_H
