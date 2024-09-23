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

#ifndef TRANSLATESHELLPROCESS_H
#define TRANSLATESHELLPROCESS_H

#include <QProcess>
#include <QString>

class TranslateShellProcess {

public:
    // QString translate(const QString &language, const QString &text);
    static bool googleTranslate(const QString &language, const QString &text, QString &result);
    static bool bingTranslate(const QString &language, const QString &text, QString &result);
    static void playAudio(const QString &text);
private:
    static bool translate(const QString &engine, const QString &language, const QString &text, QString &result);
};

#endif //TRANSLATESHELLPROCESS_H
