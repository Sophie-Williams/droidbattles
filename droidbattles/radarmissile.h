/***************************************************************************
                          radarmissile.h  -  description
                             -------------------
    begin                : Fri Aug 11 2000
    copyright            : (C) 2000 by Andreas Agorander
    email                : Bluefire@linux.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef RADARMISSILE_H
#define RADARMISSILE_H

#include "screenobject.h"
#include "battlearea.h"
#include "ram.h"
#include "robcpu.h"
#include "steering.h"
#include "scanner.h"
#include "device.h"
/**
	* A programmable missile
  *@author Andreas Agorander
  */

class radarmissile : public screenobject
{

	Q_OBJECT

	public:

		radarmissile( int,int,int,int,int,int,battlearea &,RAM *,int owner );
		~radarmissile( );
		int execute( );
		void eraseobject( QWidget *buffer );
		void showobject( QWidget *buffer, int opt = 0 );
		int returntype( );
		int getcollisiontype( );
		int getcollisionstrength( );
		int changepos( double X,double Y );
		int objhit( int type,int strength );
		int getsize( );
		int getdevport( unsigned char port );
		void putdevport( unsigned char port,unsigned short value );
		int iodevtobatt( int bot,int dev,int choice,int arg1,int arg2 );
		int returnradar( );
    void createDbgWindow(int, QMultiLineEdit*, int*, int*);

	private:

		battlearea *ourarea;
		int strength;
		RAM *ramdevice;
		device *devices[3];
    debugwindow* dbgWindow;
};

#endif