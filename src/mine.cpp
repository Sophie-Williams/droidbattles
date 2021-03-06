/***************************************************************************
                          mine.cpp  -  description
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

#include "mine.h"
//Added by qt3to4:
#include <QPixmap>

/**
	* Init position and load gfx
	*/
Mine::Mine(int x, int y, TextmodeBattleArea &area, int owner, bool ui)
{
    useUI = ui;
    myowner = owner;
    time1 = 0;
    ourarea = &area;
    Xpos = x;
    Ypos = y;
    m_size = 8;
    noncollid = 256;
    if (useUI) {
        erasegfx = new QPixmap(8, 8);
        erasegfx->fill(Qt::black);
        graphics = PixmapHolder::getpmp(PixmapHolder::Mine);
    }
}

/**
	* delete the graphics used
	*/
Mine::~Mine()
{
    if (useUI) {
        delete erasegfx;
    }
    //	delete graphics;
}

/**
	* Returns damage inflicted
	*/
int Mine::collisionStrength()
{
    return 70;
}

int Mine::collisionType()
{
    return 2;
}

/**
	* If time < 100 cycles mine is "noncolliding"
	* ie doesn't explode
	*/
ScreenObject::ObjectType Mine::type()
{
    if (time1 < 100) {
        return ScreenObject::NonCollidable;
    }
    return ScreenObject::Collidable;
}

int Mine::objectHit(int /*type*/, int /*strength*/)
{
    return objhitdestroyed;
}

/**
	* Show the graphics on the battlefield
	*/
void Mine::drawObject(QPainter *painter, int opt)
{
    if (opt > 0) {
        return;
    }
    painter->drawPixmap((xPos() >> 6) - 4, (yPos() >> 6) - 4, *graphics);

    oldX = int(Xpos);
    oldY = int(Ypos);
}

/**
	* Paint it black
	*/
void Mine::eraseObject(QPainter *painter)
{
    painter->drawPixmap((oldX >> 6) - 4, (oldY >> 6) - 4, *erasegfx);
}

/**
	* It only lives for 1000 cycles...
	*/
int Mine::execute()
{
    if (time1++ > 1000) {
        return destroyself;
    }
    return 0;
}

int Mine::returnRadar()
{
    return 3;
}
