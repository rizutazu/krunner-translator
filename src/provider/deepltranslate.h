#ifndef DEEPLTRANSLATE_H
#define DEEPLTRANSLATE_H

#include "abstracttranslateengine.h"
#include <QList>

#include "deeplapi.h"

class DeeplTranslate : public AbstractTranslateEngine {

public:
    DeeplTranslate();
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;

private:
    bool supportLanguage(const QString &language);
    DeeplAPI api;
    QList<QString> supportedLanguages;
};


#endif // DEEPLTRANSLATE_H