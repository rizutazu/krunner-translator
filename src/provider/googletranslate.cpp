#include "googletranslate.h"
#include "shellprocess.h"

const QString GoogleTranslate::getProviderName() {
    return QStringLiteral("Google Translate");
}

bool GoogleTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return ShellProcess::googleTranslate(languages, text, result);
}
