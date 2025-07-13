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
#include "libretranslate.h"
#include "configentry.h"
#include "translateshell.h"
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QThreadPool>
#include <QThread>
#include <KConfigGroup>

KRunner::Action KRunnerTranslator::copyAction = KRunner::Action(QStringLiteral("copy"), QStringLiteral("edit-copy"), QStringLiteral("Copy to clipboard"));
KRunner::Action KRunnerTranslator::playAction = KRunner::Action(QStringLiteral("play"), QStringLiteral("media-play"), QStringLiteral("Play audio"));

KRunnerTranslator::KRunnerTranslator(QObject *parent, const KPluginMetaData &metaData)
        : AbstractRunner(parent, metaData) {
}

KRunnerTranslator::~KRunnerTranslator() {
    for (auto engine : engines) {
        delete engine;
    }
}

void KRunnerTranslator::match(KRunner::RunnerContext &context) {
    
    const QString query = context.query();
    QString text;
    QPair<QString, QString> abbreviations;

    // qDebug() << "New query: " << term.toStdString() << "\n";
    if (!parseQuery(query, text, abbreviations)) return;
    QThread::sleep(std::chrono::nanoseconds(5 * 1000000));  // sleep for 0.5s to avoid incomplete input
    if (!context.isValid()) return;

    // qDebug() << "Parse ok, lang: " << abbreviations.first << ":" << abbreviations.second << " text: " << text << "\n";
    for (auto engine : engines) {
        // variable `engine` should not be reference capture,
        // because `engine++;` at each loop end will change corresponding variable in running thread
        QThreadPool::globalInstance()->start([&, engine](){
            if (!abbreviations.first.isEmpty() && !engine->supportLanguage(abbreviations.first)) {
                return;
            }

            if (!engine->supportLanguage(abbreviations.second)) {
                return;
            }
            QString result;
            if (engine->translate(abbreviations, text, result)) { // translate ok
                context.addMatch(generateTranslationMatch(engine->getProviderName(), result, abbreviations.second)); // add translation result
            }  
        });
    }
    if (!abbreviations.first.isEmpty()) {
        // when source language is provided, you can play source text as well
        auto match = generateTranslationMatch(QStringLiteral("Input text") , text, abbreviations.first);
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
        TranslateShell::playAudio(match.text(), match.data().toString());
    }

    // User pressed Enter maybe
    QApplication::clipboard()->setText(match.text());
    
}

bool KRunnerTranslator::parseQuery(const QString &term, QString &text, QPair<QString, QString> &languages) {
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
        languages.first = QString();
        languages.second = abbrs.toLower();
        return true;
    } else {    // src:dest pair
        languages.first = abbrs.first(indexColon).toLower();
        languages.second = abbrs.mid(indexColon + 1).toLower();
        return true;
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

void KRunnerTranslator::reloadConfiguration() {

    for (auto engine: engines) {
        delete engine;
    }
    engines.clear();

    KConfigGroup group = config();
    if (group.readEntry(CONFIG_GOOGLE, true)) {
        engines.append(new GoogleTranslate());
    }
    if (group.readEntry(CONFIG_BING, true)) {
        engines.append(new BingTranslate());
    }
    if (group.readEntry(CONFIG_DEEPL, true)) {
        engines.append(new DeeplTranslate());
    }
    if (group.readEntry(CONFIG_LIBRE, false)) {
        auto *t = new LibreTranslate();
        t->setup(group.readEntry(CONFIG_LIBRE_ADDR, QString()),
            group.readEntry(CONFIG_LIBRE_KEY, QString()));
        engines.append(t);
    }
}

K_PLUGIN_CLASS_WITH_JSON(KRunnerTranslator, "krunnertranslator.json")

#include "krunnertranslator.moc"
