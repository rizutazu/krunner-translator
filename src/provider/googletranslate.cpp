#include "googletranslate.h"
#include "translateshellprocess.h"

const QString GoogleTranslate::getProviderName() {
    return QStringLiteral("Google Translate");
}

bool GoogleTranslate::translate(const QString &language, const QString &text, QString &result) {
    return TranslateShellProcess::googleTranslate(language, text, result);
}
