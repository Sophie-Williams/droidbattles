/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Apr  1 17:40:01 CEST 2000
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

#include <qapplication.h>
#include <qfont.h>

//If you want another look, change this include
#include "battlearea.h"
#include "droidbattles.h"
#include "textmodebattlearea.h"
#include "textmodefilemanip.h"
#include <QCommandLineParser>
#include <QDebug>
#include <QMessageBox>
#include <QStyleFactory>

void startbattle(int argc, char *argv[])
{
    std::array<QString, 8> bots;
    int numbots = 0;
    int battletype = 0;
    bool teamfight = false;
    std::array<int, 8> teams = { 1 };
    int numfights = 1;

    int xsize = 32768;
    int ysize = 32768;
    int maxrounds = 6000;

    int curarg = 3;
    int tteam = 1;
    while (curarg < argc) {
        if (strcmp(argv[curarg], "-bot") == 0) {
            if (argc < curarg + 2) {
                qWarning() << " ERROR: -bot without following bot specification";
                return;
            }
            if (numbots >= 8) {
                qWarning() << " ERROR: To many -bot specifications";
                return;
            }
            bots[numbots] = argv[curarg + 1];
            QFile f(bots[numbots]);
            if (!f.exists()) {
                qWarning() << " ERROR: Botfile " << bots[numbots] << " not found";
                return;
            }
            curarg += 2;
            teams[numbots] = tteam;
            numbots++;
        } else if (strcmp(argv[curarg], "-normal") == 0) {
            battletype = 0;
            curarg++;
        } else if (strcmp(argv[curarg], "-survival") == 0) {
            battletype = 1;
            curarg++;
        } else if (strcmp(argv[curarg], "-deathmatch") == 0) {
            battletype = 2;
            curarg++;
        } else if (strcmp(argv[curarg], "-team") == 0) {
            teamfight = true;
            if (argc < curarg + 2) {
                qWarning() << " ERROR: -team without following team specification";
                return;
            }
            int temp = atoi(argv[curarg + 1]);
            if (temp < 1 || temp > 4) {
                qWarning() << " ERROR: -team followed by invalid specification";
                return;
            }
            tteam = temp;
            curarg += 2;
        } else if (strcmp(argv[curarg], "-xsize") == 0) {
            if (argc < curarg + 2) {
                qWarning() << " ERROR: -xsize without following size specification";
                return;
            }
            int temp = atoi(argv[curarg + 1]);
            if (temp < 8192 || temp > 65535) {
                qWarning() << " ERROR: -xsize followed by invalid specification";
                return;
            }
            xsize = temp;
            curarg += 2;
        } else if (strcmp(argv[curarg], "-ysize") == 0) {
            if (argc < curarg + 2) {
                qWarning() << " ERROR: -ysize without following team specification";
                return;
            }
            int temp = atoi(argv[curarg + 1]);
            if (temp < 8192 || temp > 65535) {
                qWarning() << " ERROR: -ysize followed by invalid specification";
                return;
            }
            ysize = temp;
            curarg += 2;
        } else if (strcmp(argv[curarg], "-numfights") == 0) {
            if (argc < curarg + 2) {
                qWarning() << " ERROR: -numfights without following specification";
                return;
            }
            int temp = atoi(argv[curarg + 1]);
            if (temp < 1) {
                qWarning() << " ERROR: -numfights followed by invalid specification";
                return;
            }
            numfights = temp;
            curarg += 2;
        } else if (strcmp(argv[curarg], "-maxrounds") == 0) {
            if (argc < curarg + 2) {
                qWarning() << " ERROR: -maxrounds without following specification";
                return;
            }
            int temp = atoi(argv[curarg + 1]);
            if (temp < 100) {
                qWarning() << " ERROR: -maxrounds followed by invalid specification";
                return;
            }
            maxrounds = temp;
            curarg += 2;
        }
    }
    if (numbots > 1) {
        BattleConfig battleConfig;
        battleConfig.names = bots;
        battleConfig.numFights = numfights;
        battleConfig.maxRounds = maxrounds;
        battleConfig.xSize = xsize;
        battleConfig.ySize = ysize;
        battleConfig.isTeams = teamfight;
        battleConfig.teams = teams;
        battleConfig.fastMode = false;
        battleConfig.mode = battletype;
        battleConfig.random_seed = BattleConfig::seedingDevice();
        TextmodeBattleArea *area = new TextmodeBattleArea(battleConfig);
        while (true) {
            if (area->execround() == 3) {
                break;
            }
        }
    } else {
        qWarning() << " ERROR: Not enough bots specified";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication *app;

    bool useGUI = true;
    if (argc > 1) {
        if (strcmp(argv[1], "-textmode") == 0) {
            useGUI = false;
        }
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

    if (useGUI) {
        QGuiApplication *guiApp = new QApplication(argc, argv);
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        app = guiApp;
        QFont font(QGuiApplication::font());
        font.setPixelSize(12);
        QGuiApplication::setFont(font);
    } else {
        app = new QCoreApplication(argc, argv);
    }
    QCoreApplication::setApplicationName("droidbattles");
    QCoreApplication::setOrganizationName("martin");

    QCommandLineParser parser;
    QCommandLineOption botOption("bot",
                                 "Pass a path to a .bot file to use",
                                 "path");
    QCommandLineOption ticksOption("rounds",
                                   "Max rounds per battle (~50 rounds per second by default)",
                                   "number");
    QCommandLineOption battlesOption("num-battles",
                                     "Number of battles to run",
                                     "number");
    QCommandLineOption ticklessOption("tickless",
                                     "Run without delay between ticks");
    QCommandLineOption headlessOption("headless",
                                     "Run without UI");
    QCommandLineOption tickIntervalOption("tick-interval",
                                     "Interval between each tick",
                                          "milliseconds");
    QCommandLineOption seedOption("seed",
                                     "Randomness seed to ues",
                                          "number");

    parser.addHelpOption();
    parser.addOption(botOption);
    parser.addOption(ticksOption);
    parser.addOption(battlesOption);
    parser.addOption(ticklessOption);
    parser.addOption(headlessOption);
    parser.addOption(tickIntervalOption);
    parser.addOption(seedOption);

    parser.process(*app);

    QStringList bots = parser.values(botOption);

    if (!bots.isEmpty()) {
        BattleConfig battleConf;

        if (bots.count() >= int(battleConf.names.size())) {
            QMessageBox::critical(nullptr, "Invalid options", QString("Too many bots passed (passed %1 bots, max bots %1)").arg(bots.count()).arg(battleConf.names.size()));
            return 1;
        }
        if (bots.count() < 2) {
            QMessageBox::critical(nullptr, "Invalid options", "Not enough bots passed");
            return 1;
        }

        for (int i = 0; i < bots.count(); i++) {
            battleConf.names[i] = bots[i];
        }

        int maxRounds = parser.value(ticksOption).toInt();
        if (maxRounds > 100) {
            battleConf.maxRounds = maxRounds;
        }
        int numFights = parser.value(battlesOption).toInt();
        if (numFights > 1) {
            battleConf.numFights = numFights;
        }
        if (parser.isSet(ticklessOption)) {
            battleConf.fastMode = true;
        }
        battleConf.random_seed =  parser.value(seedOption).toUInt();
        if (!battleConf.random_seed) {
            battleConf.random_seed = BattleConfig::seedingDevice();
        }

        BattleArea *battleArea = new BattleArea(battleConf);
        QObject::connect(battleArea, &BattleArea::destroyed, app, &QCoreApplication::quit);
        QObject::connect(battleArea, &BattleArea::closed, app, &QCoreApplication::quit);
        battleArea->show();

        return app->exec();
    }

    if (useGUI) {
        DroidBattles *droidbattles = new DroidBattles();

        droidbattles->show();
        return QCoreApplication::exec();
    }
    if (strcmp(argv[2], "-assemble") == 0) {
        if (argc >= 4) {
            TextModeFileManip::assemble(argv[3]);
        }
    } else if (strcmp(argv[2], "-check") == 0) {
        if (argc >= 4) {
            TextModeFileManip::checkConfig(argv[3]);
        }
    } else if (strcmp(argv[2], "-loadconfig") == 0) {
        if (argc >= 4) {
            TextModeFileManip::loadConfig(argv[3]);
        }
    } else if (strcmp(argv[2], "-battle") == 0) {
        startbattle(argc, argv);
    }
}
