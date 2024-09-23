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

void TranslateShellProcess::playAudio(const QString &text, const QString &language) {
    QStringList arguments;
    arguments << language + QStringLiteral(":") 
              << QStringLiteral("-speak")
            //   << QStringLiteral("-no-translate")
              << text;
    QProcess process;
    process.setProgram(QStringLiteral("trans"));
    process.setArguments(arguments);
    process.startDetached(nullptr);
    process.setStandardOutputFile(QProcess::nullDevice());
}


bool TranslateShellProcess::translate(const QString &engine, const QPair<QString, QString> &languages, const QString &text, QString &result) {
    QStringList arguments;
    arguments << languages.first + QStringLiteral(":") + languages.second
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


bool TranslateShellProcess::googleTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return TranslateShellProcess::translate(QStringLiteral("google"), languages, text, result);    
}

bool TranslateShellProcess::bingTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return TranslateShellProcess::translate(QStringLiteral("bing"), languages, text, result);
}
