/***************************************************************************
                          beamer.h  -  description
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

#ifndef BEAMER_H
#define BEAMER_H

#include "device.h"
#include "screenobject.h"
/**
	* Device that fires beams
  *@author Andreas Agorander
  */

class Beamer : public Device
{

public:
    Beamer(ScreenObject &, int arg1);
    ~Beamer() override;
    void execute() override;
    int readPort(uint8_t port) override;

private:
    int length;
};

#endif
