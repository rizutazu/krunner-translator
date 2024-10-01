#ifndef DEEPLTRANSLATE_H
#define DEEPLTRANSLATE_H

#include "abstracttranslateengine.h"
#include <QList>
class DeeplTranslate : public AbstractTranslateEngine {

public:
    DeeplTranslate();
    void setAPIKey(const QString &key) override {Q_UNUSED(key)};
    const QString getProviderName() override;
    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;

private:
    bool supportLanguage(const QString &language);
    QList<QString> supportedLanguages;
};


#endif // DEEPLTRANSLATE_H