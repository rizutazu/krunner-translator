#ifndef GOOGLETRANSLATE_H
#define GOOGLETRANSLATE_H

#include "abstracttranslateengine.h"

class GoogleTranslate : public AbstractTranslateEngine {

public:
    void setAPIKey(const QString &key) override {Q_UNUSED(key)};
    const QString getProviderName() override;
    bool translate(const QString &language, const QString &text, QString &result) override;
};

#endif // GOOGLETRANSLATE_H