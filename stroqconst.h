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
 
 Class          :   --
 Author         :   Luc Vo Van
 Original Date  :   19.05.2005
 Description    :   This file contains global constants
 
 */

#ifndef STROQCONST_H
#define STROQCONST_H
  
	const QString VERSION = "0.2"; /**< StroQ's version string */

	/**
	* URL to the puzzle of the day
	*/
	const QString POTD_HOST = "stroq.sourceforge.net";
	const QString POTD_FILE = "/potd.php";
	
	const unsigned int MAX_SIDE = 63; /**< Maximum size number of
					       squares on the side of a
					       Puzzle (max squares is
					       pow(MAX_SIDE, 2) */
					       
	const unsigned int DEFAULT_SIDE = 50;  /**< Default size of a square,
						    in pixels */
						    
	const unsigned int DEFAULT_BORDER = 2; /**< Default border for each
						    square in pixels */

#endif
