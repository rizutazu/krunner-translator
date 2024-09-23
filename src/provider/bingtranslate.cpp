#include "bingtranslate.h"
#include "translateshellprocess.h"

const QString BingTranslate::getProviderName() {
    return QStringLiteral("Bing Translate");
}

bool BingTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return TranslateShellProcess::bingTranslate(languages, text, result);
}
