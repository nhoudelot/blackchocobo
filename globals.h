/****************************************************************************/
//    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
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

#ifndef GLOBALS_H
#define GLOBALS_H
    #ifndef FF7SAVE_H
        #include "FF7SAVE.h"
    #endif
#include <QCoreApplication>
#include <QTextCodec>
#include "FF7Text.h"
#include "FF7StaticData.h"

int ff7__checksum(void * qw );
void fix_pc_bytemask(FF7*ff7 ,int,bool);
void fix_psx_header(FF7*ff7,int);
void fix_vmc_header(FF7*ff7);
QString avatar_style(int);
int stat_gain(int who,int stat, int stat_amount, int next_lvl);
#endif // GLOBALS_H
