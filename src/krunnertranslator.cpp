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
// #include <QList>
// #include <QtConcurrent>
#include <QThreadPool>
#include <KRunner/Action>
#include "googletranslate.h"
#include "bingtranslate.h"
#include "deepltranslate.h"
#include "shellprocess.h"

KRunnerTranslator::KRunnerTranslator(QObject *parent, const KPluginMetaData &metaData)
        : KRunner::AbstractRunner(parent, metaData) {
    languageRepository.initialize();
    // init language repo

    engines.append(new GoogleTranslate());
    engines.append(new BingTranslate());
    engines.append(new DeeplTranslate());
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
    QPair<QString, QString> languages;

    // qDebug() << "New query: " << term.toStdString() << "\n";

    if (!parseTerm(term, text, languages)) return;
    if (!context.isValid()) return;

    // qDebug() << "Parse ok, lang: " << languages.first << ":" << languages.second << " text: " << text << "\n";
    for (auto engine : engines) {
        QThreadPool::globalInstance()->start([&, engine](){ 
        // variable `engine` should not be reference capture, 
        // because `engine++;` at each loop end will change corresponding variable in running thread
            QString result;
            if (engine->translate(languages, text, result)) { // translate ok
                context.addMatch(generateTranslationMatch(engine->getProviderName(), result)); // add translation result
                if (engine->getProviderName() == QStringLiteral("Google Translate")) { // for google translate only: add play audio
                    context.addMatch(generatePlayAudioMatch(result, languages.second)); 
                    // play audio for target text
                    if (languages.first != QStringLiteral("")) {
                        context.addMatch(generatePlayAudioMatch(text, languages.first)); 
                        // when source language is provided, you can play source text as well
                    }
                }
            }  
        });
    }
    QThreadPool::globalInstance()->waitForDone();
}

void KRunnerTranslator::run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &match) {
    Q_UNUSED(context);
    QString category = match.matchCategory();
    if (category == QStringLiteral("Translation")) {
        QApplication::clipboard()->setText(match.text());
    } else if (category == QStringLiteral("Play Audio")) {
        ShellProcess::playAudio(match.text(), match.data().toString());
    } else {
        qDebug() << "Unknown query match category: " << category.toStdString() << "\n";
    }
    
}

bool KRunnerTranslator::parseTerm(const QString &term, QString &text, QPair<QString, QString> &languages) {
    // format: "abbr-src:abbr-dest text-to-translate"
    // or "abbr-dest text-to-translate"
    // language.first == abbr-src, language.second == abbr-dest

    // first: find space at middle
    const int indexSpace = term.indexOf(QStringLiteral(" "));
    if (indexSpace == -1) return false;

    // then, at space right is text-to-translate
    // remove whitespace
    text = term.mid(indexSpace + 1).simplified();

    // no text to translate: return
    if (text.isEmpty()) {
        return false;
    }

    // at space left is abbrs
    const QString abbrs = term.first(indexSpace);
    const int indexColon = abbrs.indexOf(QStringLiteral(":"));

    if (indexColon == -1) { // destination language only
        if (languageRepository.containsAbbreviation(abbrs)) {
            languages.first = QStringLiteral("");
            languages.second = abbrs;
            return true;
        } else {
            return false;
        }
    } else {    // src:dest pair
        QString first = abbrs.first(indexColon);
        QString second = abbrs.mid(indexColon + 1);
        if (languageRepository.containsAbbreviation(first)
                && languageRepository.containsAbbreviation(second)) {
            languages.first = first;
            languages.second = second;
            return true;
        } else {
            return false;
        }
    }
}

KRunner::QueryMatch KRunnerTranslator::generateTranslationMatch(const QString &provider, const QString &result) {
    KRunner::QueryMatch translationMatch(this);

    translationMatch.setIcon(QIcon::fromTheme(QStringLiteral("applications-education-language")));
    translationMatch.setText(result);
    translationMatch.setSubtext(provider);
    translationMatch.setMatchCategory(QStringLiteral("Translation"));
    translationMatch.setMultiLine(true);
    translationMatch.setRelevance(1);
    
    return translationMatch;
}

KRunner::QueryMatch KRunnerTranslator::generatePlayAudioMatch(const QString &text, const QString &language) {
    KRunner::QueryMatch playAudioMatch(this);

    playAudioMatch.setIcon(QIcon::fromTheme(QStringLiteral("media-play")));
    playAudioMatch.setText(text);
    playAudioMatch.setSubtext(language + QStringLiteral(" text"));
    playAudioMatch.setMatchCategory(QStringLiteral("Play Audio"));
    playAudioMatch.setData(language);
    // playAudioMatch.setMultiLine(true);
    playAudioMatch.setRelevance(1);

    return playAudioMatch;
}

void KRunnerTranslator::reloadConfiguration() {}

K_PLUGIN_CLASS_WITH_JSON(KRunnerTranslator, "krunnertranslator.json")

#include "krunnertranslator.moc"
