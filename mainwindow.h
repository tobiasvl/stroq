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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qcanvas.h>

#include "playarea.h"

class QLabel;
class QProgressBar;
class QPopupMenu;
class QAction;

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  /**
   * Creates the main window, with no border
   */
  MainWindow(QWidget *parent = 0, const char *name = 0);
  ~MainWindow();

 protected:
  void closeEvent(QCloseEvent *event);
  
 public slots:
  /**
  * Emitted when the puzzle is changed, usually after a call to PlayArea.loadPuzzle()
  * @param puzzle The puzzle that was just loaded
  * @param canvasSize Size of the canvas used to display the puzzle
  */
  void puzzleChanged(Puzzle* puzzle, QSize canvasSize);
  
 private slots:
  // Puzzle stuff
  /**
   * To be called when a the player wants to select a new puzzle
   */
  void selectPuzzle();
  
  /**
   * To be called when the player wants to enter a puzzle code
   */
  void enterPuzzleCode();
  
  /**
   * To be called when the player wants to download a puzzle from
   * the Internet
   */
  void downloadPuzzleOfTheDay();
  
  /**
   * To be called when switching from/to puzzle edit mode
   */
  void toggleEditMode();
  
  /**
   * To be called to copy the current puzzle's code to the system's
   * clipboard
   */
  void copyPuzzleCode();
  
  /**
   * To be called to quit the game
   */
  void quit();

  // About stuff
  /**
   * To be called to display StroQ's about window
   */
  void about();
  
  /**
   * To be called to displays Qt's about window
   */
  void aboutQt();

 private:
  void createActions();
  void createMenus();
  void createGameArea();
  
  /**
   * Loads the first puzzle into the PlayArea
   */
  void loadFirstPuzzle();
  
  // About menu
  QPopupMenu *aboutMenu;
  QAction *aboutStroQAct;
  QAction *aboutQtAct;


  // Puzzle menu
  QPopupMenu *puzzleMenu;
  QAction *selectPuzzleAct;
  QAction *enterPuzzleCodeAct;
  QAction *downloadPuzzleOfTheDayAct;
  QAction *editPuzzleAct;
  QAction *quitAct;

  // Play menu
  QPopupMenu *playMenu;
  QAction *resetPuzzleAct;
  QAction *runPuzzleAct;
  
  // Edit menu
  QPopupMenu *editMenu;
  QAction *newEditPuzzleAct;
  QAction *invertPuzzleAct;
  QAction *copyPuzzleCodeAct;
  
  // Game area
  QCanvas *mainCanvas;
  PlayArea *playArea;
  
  QString m_sCurrentCode;

};

#endif
