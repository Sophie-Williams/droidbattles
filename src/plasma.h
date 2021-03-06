/***************************************************************************
                          plasma.h  -  description
                             -------------------
    begin                : Mon Apr 3 2000
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

#ifndef PLASMA_H
#define PLASMA_H

#include "device.h"
#include "screenobject.h"
/**
	* shoots the plasmashots
  *@author Andreas Agorander
  */

class Plasma : public Device
{

public:
    Plasma(ScreenObject &object, int arg1, int offset);
    ~Plasma() override;
    void execute() override;

private:
    int readiness;
};

#endif
