/***************************************************************************
                          robcpu.h  -  description
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

#ifndef ROBCPU_H
#define ROBCPU_H

#include "cpu.h"
#include "screenobject.h"
#include <qfile.h>
#include <random>


/**CPU adapted for bot
  *@author Andreas Agorander
  */

class RobCpu : public CPU
{
public:
    RobCpu();
    RobCpu(Ram &ramdev, ScreenObject &object, int arg1, int arg2, int arg3,
           int arg4, int arg5, const std::mt19937 &randomness);
    ~RobCpu() override;
    void execute() override;
    int type() override;
    int specialValue() override;
    void sendmsg(char *msg) override;
    struct DebugContents debugContents() override;
    void execinstr() override;

private:
    std::mt19937 m_randomness;
    std::uniform_int_distribution<uint16_t> m_randDistribution;
};

#endif
