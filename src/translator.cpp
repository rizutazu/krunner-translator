/******************************************************************************
 *  Copyright (C) 2013 – 2018 by David Baum <david.baum@naraesk.eu>           *
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

#include "translator.h"

// #include <src/translateShellProcess.h>
// #include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
// #include <QAction>
// #include <KConfigCore/KConfig>
// #include <QThread>
#include <QIcon>
#include <iostream>

Translator::Translator(QObject *parent, const KPluginMetaData &metaData)
        : KRunner::AbstractRunner(parent, metaData) {
    languageRepository.initialize();
    // QThread::setPriority(QThread::HighestPriority);
}

bool Translator::parseTerm(const QString &term, QString &text, QString &language) {
    // format: "abbr text-to-translate"

    // first: find space
    const int index = term.indexOf(QStringLiteral(" "));
    if (index == -1) return false;

    // then, at space right is text-to-translate
    text = term.mid(index + 1);

    // at space left is abbr
    language = term.first(index);
    if (languageRepository.containsAbbreviation(language)) {
        return true;
    } else {
        return false;
    }
}

void Translator::match(KRunner::RunnerContext &context) {
    
    const QString term = context.query();
    QString text;
    QString language;

    std::cerr << "New query: " << term.toStdString() << std::endl;

    if (!parseTerm(term, text, language)) return;
    if (!context.isValid()) return;

    std::cerr << "pase ok, lan: " << language.toStdString() << " text: " << text.toStdString() << std::endl;

    QString result = translateShellProcess.translate(language, text);

    std::cerr << "get result: " << result.toStdString() << std::endl;

    KRunner::QueryMatch match(this);
    // match.setType(KRunner::QueryMatch::ExactMatch);
    match.setIcon(QIcon::fromTheme(QStringLiteral("applications-education-language")));
    match.setText(result);
    match.setSubtext(QStringLiteral("Google Translate"));
    match.setRelevance(1); 
    
    // match.setSelectedAction(actions.first());
    context.addMatch(match);
}

void Translator::run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &match) {
    QApplication::clipboard()->setText(match.text());
}

// QList<QAction *> Translator::actionsForMatch(const Plasma::QueryMatch &match) {
//     if (match.data().toString() == QStringLiteral("audio")) {
//         return actions;
//     }
//     return {actions.first()};
// }

void Translator::reloadConfiguration() {

}

K_PLUGIN_CLASS_WITH_JSON(Translator, "translator.json")

#include "translator.moc"
