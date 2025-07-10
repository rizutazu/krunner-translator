#ifndef DEEPLTRANSLATE_H
#define DEEPLTRANSLATE_H

#include "abstracttranslateengine.h"
#include <QList>


class DeeplTranslate : public AbstractTranslateEngine {

public:
    DeeplTranslate();
    ~DeeplTranslate() override;
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;

private:
    bool supportLanguage(const QString &language);
    QList<QString> supportedLanguages;
    class API;
    API *api;
};


#endif // DEEPLTRANSLATE_H