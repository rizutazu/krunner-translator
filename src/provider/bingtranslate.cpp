#include "bingtranslate.h"
#include "translateshell.h"

const QString BingTranslate::getProviderName() {
    return QStringLiteral("Bing");
}

bool BingTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return TranslateShell::translate(QStringLiteral("bing"), languages, text, result);
}
