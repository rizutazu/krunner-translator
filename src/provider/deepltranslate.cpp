#include "deepltranslate.h"
#include "deeplapi.h"
const QString DeeplTranslate::getProviderName() {
    return QStringLiteral("Deepl Translate");
}

bool DeeplTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    // deepl needs to specify source language
    if (languages.first.isEmpty()) {
        return false;
    }
    return DeeplAPI::webTranslate(languages, text, result);
    
}
