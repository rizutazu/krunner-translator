#include "googletranslate.h"
#include "translateshell.h"

const QString GoogleTranslate::getProviderName() {
    return QStringLiteral("Google");
}

bool GoogleTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return TranslateShell::translate(QStringLiteral("google"), languages, text, result);
}
