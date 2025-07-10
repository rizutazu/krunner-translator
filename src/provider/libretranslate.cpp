//
// Created by nashi on 7/10/25.
//

#include "libretranslate.h"

const QString LibreTranslate::getProviderName() {
    return QStringLiteral("Libre Translate");
}

bool LibreTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    return false;
}
