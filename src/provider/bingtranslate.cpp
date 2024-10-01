#include "bingtranslate.h"
#include "shellprocess.h"

const QString BingTranslate::getProviderName() {
    return QStringLiteral("Bing Translate");
}

bool BingTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return ShellProcess::bingTranslate(languages, text, result);
}
