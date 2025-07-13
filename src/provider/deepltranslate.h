#ifndef DEEPLTRANSLATE_H
#define DEEPLTRANSLATE_H

#include "abstracttranslateengine.h"
#include "languagerepository.h"


class DeeplTranslate : public AbstractTranslateEngine {

public:
    explicit DeeplTranslate();
    ~DeeplTranslate() override;
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) override;
    bool supportLanguage(const QString &abbreviation) override;

private:
    LanguageRepository repo;

    class API;
    API *api;
};


#endif // DEEPLTRANSLATE_H