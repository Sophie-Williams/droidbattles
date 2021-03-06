/***************************************************************************
                          device.h  -  description
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

#ifndef DEVICE_H
#define DEVICE_H

#include "screenobject.h"
#include "debugcontents.h"

/**Baseclass for all sub-bot-devices
  *@author Andreas Agorander
  */

class Device
{
    static const QStringList s_deviceNames;

public:
    static const QString deviceName(int index);
    static int deviceId(const QString &name);

    Device();
    virtual ~Device();
    Device(ScreenObject &object);
    void addInputPort(uint8_t port, uint16_t value);
    void setRelativeAngle(int);
    virtual void execute();
    virtual int readPort(uint8_t port);
    virtual int absorbHit(int str, int ifint);
    virtual void erase(QPainter *painter);
    virtual void draw(QPainter *painter);
    virtual int type();
    virtual int specialValue();
    virtual struct DebugContents debugContents();
    virtual void doSpecial(int, int = 0);

protected:
    void moveportstack(int port);

    int portstack[4][4];
    bool stacktaken[4][4];
    ScreenObject *ourbot;
    int relang;
    int ourlevel;
    bool intenabled;
    bool intenabled2;
};

#endif
