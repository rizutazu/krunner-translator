#ifndef GOOGLETRANSLATE_H
#define GOOGLETRANSLATE_H

#include "abstracttranslateengine.h"

class GoogleTranslate : public AbstractTranslateEngine {

public:
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) override;
    bool supportLanguage(const QString &abbreviations) override;
};

#endif // GOOGLETRANSLATE_H