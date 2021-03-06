/***************************************************************************
                          communication.h  -  description
                             -------------------
    begin                : Sun Jul 16 2000
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "device.h"
#include "screenobject.h"

/**
	* This device enables communication between bots in the same team
  *@author Andreas Agorander
  */

class Communication : public Device
{

public:
    Communication(ScreenObject &object);
    ~Communication() override;
    int readPort(uint8_t port) override;
    void execute() override;
    void doSpecial(int x, int y) override;

private:
    int msglist[32];
    int nummsg;
    int receiver;
};

#endif
