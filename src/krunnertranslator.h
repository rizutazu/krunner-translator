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

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "languagerepository.h"
#include "abstracttranslateengine.h"
#include <KRunner/AbstractRunner>
#include <QList>
#include <QIcon>
#include <KRunner/Action>



class KRunnerTranslator : public KRunner::AbstractRunner
{
    Q_OBJECT

public:
    KRunnerTranslator(QObject *parent, const KPluginMetaData &metaData);
    ~KRunnerTranslator() override;
    void match(KRunner::RunnerContext &context) override;
    void run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &match) override;
    void reloadConfiguration() override;

private:
    static bool parseQuery(const QString &term, QString &text, QPair<QString, QString> &languages);

    // Translation match should have a provider name
    KRunner::QueryMatch generateTranslationMatch(const QString &provider, const QString &result, const QString &language);

    LanguageRepository languageRepository;

    QList<AbstractTranslateEngine*> engines;

    static KRunner::Action copyAction;
    static KRunner::Action playAction;
};

#endif
