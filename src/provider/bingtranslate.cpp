#include "bingtranslate.h"
#include "translateshellprocess.h"

const QString BingTranslate::getProviderName() {
    return QStringLiteral("Bing Translate");
}

bool BingTranslate::translate(const QString &language, const QString &text, QString &result) {
    return TranslateShellProcess::bingTranslate(language, text, result);
}
