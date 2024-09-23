#ifndef BINGTRANSLATOR_H
#define BINGTRANSLATOR_H

#include "abstracttranslateengine.h"

class BingTranslate : public AbstractTranslateEngine {

public:
    void setAPIKey(const QString &key) override {Q_UNUSED(key)};
    const QString getProviderName() override;
    bool translate(const QString &language, const QString &text, QString &result) override;
};



#endif // BINGTRANSLATOR_H