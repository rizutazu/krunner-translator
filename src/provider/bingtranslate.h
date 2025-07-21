#ifndef BINGTRANSLATOR_H
#define BINGTRANSLATOR_H

#include "abstracttranslateengine.h"

class BingTranslate : public AbstractTranslateEngine {

public:
    const QString &getProviderName() const override;
    bool translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) override;
    bool supportLanguage(const QString &abbreviations) override;

private:
    static QString provider;
};



#endif // BINGTRANSLATOR_H