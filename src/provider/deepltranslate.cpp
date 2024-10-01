#include "deepltranslate.h"
#include "deeplapi.h"
DeeplTranslate::DeeplTranslate() {
    supportedLanguages = {QStringLiteral("ar"), QStringLiteral("bg"), QStringLiteral("cs"), 
        QStringLiteral("da"), QStringLiteral("de"), QStringLiteral("el"), QStringLiteral("en"), 
        QStringLiteral("es"), QStringLiteral("et"), QStringLiteral("fi"), QStringLiteral("fr"), 
        QStringLiteral("hu"), QStringLiteral("id"), QStringLiteral("it"), QStringLiteral("ja"), 
        QStringLiteral("ko"), QStringLiteral("lt"), QStringLiteral("lv"), QStringLiteral("nb"), 
        QStringLiteral("nl"), QStringLiteral("pl"), QStringLiteral("pt"), QStringLiteral("ro"), 
        QStringLiteral("ru"), QStringLiteral("sk"), QStringLiteral("sl"), QStringLiteral("sv"), 
        QStringLiteral("tr"), QStringLiteral("uk"), QStringLiteral("zh")};
}

const QString DeeplTranslate::getProviderName() {
    return QStringLiteral("Deepl Translate");
}

bool DeeplTranslate::supportLanguage(const QString &language) {
    return supportedLanguages.contains(language);
}

bool DeeplTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    // deepl needs to specify source language
    if (languages.first.isEmpty()) {
        return false;
    }
    // for Norwegian: no -> nb
    QPair<QString, QString> lang;
    lang.first = languages.first == QStringLiteral("no") ? QStringLiteral("nb") : languages.first;
    lang.second = languages.second == QStringLiteral("no") ? QStringLiteral("nb") : languages.second;
    if (supportLanguage(lang.first) && supportLanguage(lang.second)) {
        return DeeplAPI::webTranslate(lang, text, result);
    } else {
        return false;
    }
    
    
}
