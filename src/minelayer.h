/***************************************************************************
                          minelayer.h  -  description
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

#ifndef MINELAYER_H
#define MINELAYER_H

#include "device.h"

/**
	* Device that lays the mines
  *@author Andreas Agorander
  */

class MineLayer : public Device
{

public:
    MineLayer(ScreenObject &, int);
    ~MineLayer() override;
    int readPort(uint8_t port) override;
    void execute() override;

private:
    int minesleft;
};

#endif
