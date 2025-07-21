#include "deepltranslate.h"
#include "deeplapi.h"
#include "predefined.h"

// it sounds quite weird...
class DeeplTranslate::API : public DeeplAPI {};

QString DeeplTranslate::provider = QStringLiteral("Deepl");
LanguageRepository DeeplTranslate::repo;

DeeplTranslate::DeeplTranslate() {
    api = new API();
    AddDeeplSupportedLanguage(repo);
}

DeeplTranslate::~DeeplTranslate() {
    delete api;
}

const QString &DeeplTranslate::getProviderName() const {
    return provider;
}

bool DeeplTranslate::supportLanguage(const QString &abbreviation) {
    return repo.containsAbbreviation(abbreviation);
}

bool DeeplTranslate::translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) {
    // deepl needs to specify source language
    if (abbreviations.first.isEmpty()) {
        return false;
    }
    return api->webTranslate(abbreviations, text, result);
}
