/****************************************************************************/
//    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
//                                                                          //
//    This file is part of Black Chocobo.                                   //
//                                                                          //
//    Black Chocobo is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    Black Chocobo is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include <QtGui/QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"
#include <QSettings>


int main(int argc, char *argv[])
{

    QSettings setting(QSettings::NativeFormat,QSettings::UserScope,"blackchocobo","settings",0);
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);
    a.setApplicationName("Black Chocobo");
    QTranslator translator;
    QString lang = "lang/bchoco_";
    lang.append(setting.value("lang").toString());
    if (lang == "lang/bchoco_"){lang.append(QLocale::system().name().section('_', 0, 0));} //add system lang to end so we get a full item
    translator.load(lang);
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    return a.exec();
}
