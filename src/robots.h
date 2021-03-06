/***************************************************************************
                          robots.h  -  description
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

#ifndef ROBOTS_H
#define ROBOTS_H

#include "screenobject.h"
#include <QDataStream>
#include <QString>
#include <QWidget>
#include "textmodebattlearea.h"
#include "ram.h"
#include "device.h"
#include <QFile>
#include "commonsymbols.h"
#include "robcpu.h"
#include "engine.h"
#include "steering.h"
#include "plasma.h"
#include "armor.h"
#include "scanner.h"
#include "fuel.h"
#include "turret.h"
#include <QBitmap>
#include <QMessageBox>
#include "timedev.h"
#include "shield.h"
#include "repair.h"
#include <QString>
#include "communication.h"
#include "minelayer.h"
#include "beamer.h"
#include "rocketlauncher.h"
#include "chafflauncher.h"

#include "confstruct.h"
#include "radarmissilelauncher.h"
#include "scandetect.h"
#include "chiller.h"
#include "cloaker.h"

#include "debugcontents.h"
/**The bot that is programmed...
  *@author Andreas Agorander
  */

class Robots : public ScreenObject
{

    Q_OBJECT

public:
    Robots(const QString &name, TextmodeBattleArea &object, int mnum, ConfStruct, int tm,
           bool er = true, bool ui = true);
    ~Robots() override;
    int execute() override;
    void eraseObject(QPainter *painter) override;
    void drawObject(QPainter *painter, int opt) override;
    int readDevicePort(uint8_t port) override;
    void writeDevicePort(uint8_t port, uint16_t value) override;
    int objectHit(int type, int strength) override;
    void objectScanned(int intensity, int dir) override;
    void addScreenObject(int X, int Y, int dir, int type, int arg1 = 0, int arg2 = 0,
                         void *arg3 = 0) override;
    int writetoBattleArea(int bot, int dev, int choice, int arg1, int arg2) override;
    int writeToDevice(int dev, int action, int value) override;
    ObjectType type() override;
    int collisionType() override;
    int collisionStrength() override;
    int size() override;
    void writeRadio(int) override;
    QString getDebugMessage1() override;
    QString getDebugMessage2() override;
    void setDebugVariable1(int) override;
    void setDebugVariable2(int) override;
    void showError(const QString &, const QString &);
    int memorySize() override;
    void addInterrupt(int) override;
    struct DebugContents debugContents() override;
    int cpuCount();
    // the caller has to delete the returned pointer
    QVector<DebugContents> *allDebugContents();
    int returnRadar() override;
    void setRadar(int x) override;
    void dumpRam() override;

    int cost() const;

private:
    int RAMamount;
    Ram *ramdevice;
    int radarsignature;
    Device *devicelist[32];
    int8_t hitabsorborder[32];
    TextmodeBattleArea *ourarea;
    bool gfxin;
    QMessageBox *rulebreak;
    int ourradiodev;
    bool showerror;
    int currentradar;
    int piccols;
    int picrows;
    int currentrow;
    int rowchangeval;
    int degreesperpic;
    int m_cost;
};

#endif
