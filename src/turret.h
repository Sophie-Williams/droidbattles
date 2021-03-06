/***************************************************************************
                          turret.h  -  description
                             -------------------
    begin                : Mon Apr 17 2000
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

#ifndef TURRET_H
#define TURRET_H

#include "device.h"

/**Turns "turretable" devices to an offset of the heading of the bot
  *@author Andreas Agorander
  */

class Turret : public Device
{

public:
    Turret(ScreenObject &, int, int);
    ~Turret() override;
    int readPort(uint8_t) override;
    void execute() override;

private:
    int ourdev;
    int wantedoffset;
    int offset;
};

#endif
