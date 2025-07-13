#include "bingtranslate.h"
#include "translateshell.h"

const QString BingTranslate::getProviderName() {
    return QStringLiteral("Bing");
}

bool BingTranslate::translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) {
    return TranslateShell::translate(QStringLiteral("bing"), abbreviations, text, result);
}

bool BingTranslate::supportLanguage(const QString &abbreviations) {
    return TranslateShell::supportLanguage(abbreviations);
}
