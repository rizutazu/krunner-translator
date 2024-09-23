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

#include "krunnertranslator.h"
#include <QApplication>
#include <QClipboard>
// #include <QAction>
// #include <KConfigCore/KConfig>
// #include <QThread>
#include <QIcon>
#include <QDebug>
#include "googletranslate.h"
#include "bingtranslate.h"
#include "translateshellprocess.h"

KRunnerTranslator::KRunnerTranslator(QObject *parent, const KPluginMetaData &metaData)
        : KRunner::AbstractRunner(parent, metaData) {
    languageRepository.initialize();
    // init language repo

    engines.append(new GoogleTranslate());
    engines.append(new BingTranslate());
    // init engines
    
}
KRunnerTranslator::~KRunnerTranslator() {
    for (auto engine : engines) {
        delete engine;
    }
}

void KRunnerTranslator::match(KRunner::RunnerContext &context) {
    
    const QString term = context.query();
    QString text;
    QString language;

    // std::cerr << "New query: " << term.toStdString() << std::endl;

    if (!parseTerm(term, text, language)) return;
    if (!context.isValid()) return;

    // std::cerr << "parse ok, lan: " << language.toStdString() << " text: " << text.toStdString() << std::endl;

    for (auto engine : engines) {
        QString result;
        if (engine->translate(language, text, result)) { // translate ok
            context.addMatch(generateTranslationMatch(engine->getProviderName(), result)); // add translation result
            if (engine->getProviderName() == QStringLiteral("Google Translate")) { // for google translate: add play audio
                context.addMatch(generatePlayAudioMatch(result));
                context.addMatch(generatePlayAudioMatch(text));
            }
        }
    }
}

void KRunnerTranslator::run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &match) {
    Q_UNUSED(context);
    QString category = match.matchCategory();
    if (category == QStringLiteral("Translation")) {
        QApplication::clipboard()->setText(match.text());
    } else if (category == QStringLiteral("Play Audio")) {
        TranslateShellProcess::playAudio(match.text());
    } else {
        qDebug() << "Unknown query match category: " << category.toStdString() << "\n";
    }
    
}

bool KRunnerTranslator::parseTerm(const QString &term, QString &text, QString &language) {
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

KRunner::QueryMatch KRunnerTranslator::generateTranslationMatch(const QString &provider, const QString &result) {
    KRunner::QueryMatch translationMatch(this);

    translationMatch.setIcon(QIcon::fromTheme(QStringLiteral("applications-education-language")));
    translationMatch.setText(result);
    translationMatch.setSubtext(QStringLiteral("From ").append(provider));
    translationMatch.setMatchCategory(QStringLiteral("Translation"));
    translationMatch.setRelevance(1); 
    
    return translationMatch;
}

KRunner::QueryMatch KRunnerTranslator::generatePlayAudioMatch(const QString &text) {
    KRunner::QueryMatch playAudioMatch(this);

    playAudioMatch.setIcon(QIcon::fromTheme(QStringLiteral("media-play")));
    playAudioMatch.setText(text);
    playAudioMatch.setSubtext(QStringLiteral("Play audio of this text"));
    playAudioMatch.setMatchCategory(QStringLiteral("Play Audio"));
    playAudioMatch.setRelevance(1);

    return playAudioMatch;
}


void KRunnerTranslator::reloadConfiguration() {}

K_PLUGIN_CLASS_WITH_JSON(KRunnerTranslator, "translator.json")

#include "krunnertranslator.moc"
