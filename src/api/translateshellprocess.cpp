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

#include "translateshellprocess.h"
#include <QTextStream>

void TranslateShellProcess::playAudio(const QString &text) {
    QStringList arguments;
    arguments << QStringLiteral("-speak")
            //   << QStringLiteral("-no-translate")
              << text;
    QProcess process;
    process.start(QString::fromStdString("trans"), arguments);
    process.waitForFinished();
}


bool TranslateShellProcess::translate(const QString &engine, const QString &language, const QString &text, QString &result) {
    QStringList arguments;
    arguments << QStringLiteral(":") + language
              << text
              << QStringLiteral("--brief")
              << QStringLiteral("-e")
              << engine;

    QProcess process;
    process.start(QString::fromStdString("trans"), arguments);

    if (process.waitForStarted()) { // if command failed to start
        process.waitForFinished();
        if (process.exitStatus() == QProcess::NormalExit) { // exit status 0
            QTextStream txtStream(&process);
            result = txtStream.readLine();
            return true;
        }
        return false;
    }
    return false;
}

bool TranslateShellProcess::googleTranslate(const QString &language, const QString &text, QString &result) {
    return TranslateShellProcess::translate(QStringLiteral("google"), language, text, result);    
}

bool TranslateShellProcess::bingTranslate(const QString &language, const QString &text, QString &result) {
    return TranslateShellProcess::translate(QStringLiteral("bing"), language, text, result);
}
