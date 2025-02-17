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
#include "googletranslate.h"
#include "bingtranslate.h"
#include "deepltranslate.h"
#include "shellprocess.h"
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QThreadPool>
#include <QThread>

KRunner::Action KRunnerTranslator::copyAction = KRunner::Action(QStringLiteral("copy"), QStringLiteral("edit-copy"), QStringLiteral("Copy to clipboard"));
KRunner::Action KRunnerTranslator::playAction = KRunner::Action(QStringLiteral("play"), QStringLiteral("media-play"), QStringLiteral("Play audio"));

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
    QThread::sleep(std::chrono::nanoseconds(5 * 1000000));  // sleep for 0.5s to avoid incomplete input
    if (!context.isValid()) return;

    // qDebug() << "Parse ok, lang: " << languages.first << ":" << languages.second << " text: " << text << "\n";
    for (auto engine : engines) {
        QThreadPool::globalInstance()->start([&, engine](){ 
        // variable `engine` should not be reference capture, 
        // because `engine++;` at each loop end will change corresponding variable in running thread
            QString result;
            if (engine->translate(languages, text, result)) { // translate ok
                context.addMatch(generateTranslationMatch(engine->getProviderName(), result, languages.second)); // add translation result
            }  
        });
    }
    if (!languages.first.isEmpty()) {
        // when source language is provided, you can play source text as well
        auto match = generateTranslationMatch(QStringLiteral("Input text") , text, languages.first);
        // reduce relevance 
        match.setRelevance(0);  
        match.setSubtext(QString());
        match.setMatchCategory(QStringLiteral("Input text"));
        context.addMatch(match); 
        
    }
    QThreadPool::globalInstance()->waitForDone();
}

void KRunnerTranslator::run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &match) {
    Q_UNUSED(context);
    if (match.selectedAction().id() == QStringLiteral("copy")) {
        QApplication::clipboard()->setText(match.text());
    } else if (match.selectedAction().id() == QStringLiteral("play")) {
        ShellProcess::playAudio(match.text(), match.data().toString());
    }

    // User pressed Enter maybe
    QApplication::clipboard()->setText(match.text());
    
}

bool KRunnerTranslator::parseTerm(const QString &term, QString &text, QPair<QString, QString> &languages) {
    // format: "abbr-src:abbr-dest text-to-translate"
    // or "abbr-dest text-to-translate"
    // language.first == abbr-src, language.second == abbr-dest

    // first: find space at middle
    const qint64 indexSpace = term.indexOf(QStringLiteral(" "));
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
    const qint64 indexColon = abbrs.indexOf(QStringLiteral(":"));

    if (indexColon == -1) { // destination language only
        if (languageRepository.containsAbbreviation(abbrs)) {
            languages.first = QString();
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

KRunner::QueryMatch KRunnerTranslator::generateTranslationMatch(const QString &provider, const QString &result, const QString &language) {
    KRunner::QueryMatch translationMatch(this);

    translationMatch.setIcon(QIcon::fromTheme(QStringLiteral("applications-education-language")));
    translationMatch.setText(result);
    translationMatch.setSubtext(provider);
    translationMatch.setMatchCategory(QStringLiteral("Translation"));
    translationMatch.setData(language);
    translationMatch.setMultiLine(true);
    translationMatch.setRelevance(1);
    translationMatch.addAction(copyAction);
    translationMatch.addAction(playAction);
    
    return translationMatch;
}

void KRunnerTranslator::reloadConfiguration() {}

K_PLUGIN_CLASS_WITH_JSON(KRunnerTranslator, "krunnertranslator.json")

#include "krunnertranslator.moc"
