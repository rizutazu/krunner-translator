/******************************************************************************
 *  Copyright (C) 2013 – 2020 by David Baum <david.baum@naraesk.eu>           *
 *                                                                            *
 *  This library is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU Lesser General Public License as published  *
 *  by the Free Software Foundation; either version 2 of the License or (at   *
 *  your option) any later version.                                           *
 *                                                                            *
 *  This library is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 *  Library General Public License for more details.                          *
 *                                                                            *
 *  You should have received a copy of the GNU Lesser General Public License  *
 *  along with this library; see the file COPYING.LIB.                        *
 *  If not, see <http://www.gnu.org/licenses/>.                               *
 *****************************************************************************/

#ifndef SHELLPROCESS_H
#define SHELLPROCESS_H

#include <QProcess>
#include <QString>
#include "languagerepository.h"

class TranslateShell {

public:
    static void playAudio(const QString &text, const QString &abbreviation);
    static bool translate(const QString &engine, const QPair<QString, QString> &abbreviations, const QString &text, QString &result);
    static bool supportLanguage(const QString &abbreviation);
private:
    // the actual init function
    static void init();

    // Dear runtime pls call my init()
    static inline struct Constructor {
        Constructor() {
            init();
        }
    } _constructor;

    static LanguageRepository repo;
};

#endif //SHELLPROCESS_H
