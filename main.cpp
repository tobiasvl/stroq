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

#include "mainwindow.h"
#include "stroqconst.h"

int main(int argc, char *argv[])
{
  printf("StroQ version %s\n", VERSION.latin1());
  printf("Copyright (C) 2005 Luc Vo Van\n");
  printf("This program is free software; you can redistribute it and/or modify\n");
  printf("it under the terms of the GNU General Public License as published by\n");
  printf("the Free Software Foundation; either version 2 of the License, or\n");
  printf("any later version.\n\n");
  printf("This program is distributed in the hope that it will be useful,\n");
  printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
  printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
  printf("GNU General Public License for more details.\n\n");
  printf("You should have received a copy of the GNU General Public License\n");
  printf("along with this program; if not, write to the Free Software\n");
  printf("Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n\n");

  QApplication app(argc, argv);
  MainWindow mwin;
  app.setMainWidget(&mwin);
  mwin.show();
  return app.exec();
}
