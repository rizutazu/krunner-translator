#ifndef DEEPLTRANSLATE_H
#define DEEPLTRANSLATE_H

#include "abstracttranslateengine.h"

class DeeplTranslate : public AbstractTranslateEngine {

public:
    void setAPIKey(const QString &key) override {Q_UNUSED(key)};
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;
};


#endif // DEEPLTRANSLATE_H