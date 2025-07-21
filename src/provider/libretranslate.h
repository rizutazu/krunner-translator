#ifndef LIBRETRANSLATE_H
#define LIBRETRANSLATE_H

#include "abstracttranslateengine.h"

class LibreTranslate: public AbstractTranslateEngine {
public:
    explicit LibreTranslate();
    ~LibreTranslate() override;
    const QString &getProviderName() const override;
    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;
    bool supportLanguage(const QString &abbreviations) override;

    void setup(const QString &address, const QString &key);

private:
    static QString provider;
    QString address;
    QString key;

    class API;
    API *api;
};



#endif //LIBRETRANSLATE_H
