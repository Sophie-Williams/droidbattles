/***************************************************************************
                          rocketlauncher.h  -  description
                             -------------------
    begin                : Wed Nov 1 2000
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

#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H

#include "screenobject.h"
#include "device.h"

/**
	* Device that fires AS-rockets
  *@author Andreas Agorander
  */

class RocketLauncher : public Device
{

public:
    RocketLauncher(ScreenObject &object, int level, int offset);
    ~RocketLauncher() override;
    void execute() override;
    int readPort(uint8_t port) override;

private:
    int readiness;
    int distance;
};

#endif
