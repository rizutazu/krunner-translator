#ifndef GOOGLETRANSLATE_H
#define GOOGLETRANSLATE_H

#include "abstracttranslateengine.h"

class GoogleTranslate : public AbstractTranslateEngine {

public:
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;
};

#endif // GOOGLETRANSLATE_H