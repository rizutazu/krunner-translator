#ifndef DEEPLTRANSLATE_H
#define DEEPLTRANSLATE_H

#include "abstracttranslateengine.h"
#include "languagerepository.h"


class DeeplTranslate : public AbstractTranslateEngine {

public:
    explicit DeeplTranslate();
    ~DeeplTranslate() override;
    const QString &getProviderName() const override;
    bool translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) override;
    bool supportLanguage(const QString &abbreviation) override;

private:
    static QString provider;
    static LanguageRepository repo;

    class API;
    API *api;
};


#endif // DEEPLTRANSLATE_H