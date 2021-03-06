/***************************************************************************
                          beam.h  -  description
                             -------------------
    begin                : Tue Oct 31 2000
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

#ifndef BEAM_H
#define BEAM_H

#include "screenobject.h"
#include "textmodebattlearea.h"
/**
	* The "beam" screenobject, (lazerlike shot)
  *@author Andreas Agorander
  */

class Beam : public ScreenObject
{

public:
    Beam(int X, int Y, int dir, int l, TextmodeBattleArea &area, int owner, bool ui = true);
    ~Beam() override;
    int execute() override;
    void eraseObject(QPainter *painter) override;
    void drawObject(QPainter *painter, int opt = 0) override;
    int objectHit(int type, int strength) override;
    ObjectType type() override;
    int collisionStrength() override;
    int collisionType() override;

private:
    int length;
    int effect;
    bool ispainted;
    TextmodeBattleArea *ourarea;
    int uX;
    int uY;
};

#endif
