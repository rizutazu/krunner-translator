#include "googletranslate.h"
#include "translateshell.h"

const QString GoogleTranslate::getProviderName() {
    return QStringLiteral("Google");
}

bool GoogleTranslate::translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) {
    return TranslateShell::translate(QStringLiteral("google"), abbreviations, text, result);
}

bool GoogleTranslate::supportLanguage(const QString &abbreviations) {
    return TranslateShell::supportLanguage(abbreviations);
}
