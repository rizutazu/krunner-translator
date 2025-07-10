#ifndef LIBRETRANSLATE_H
#define LIBRETRANSLATE_H

#include "abstracttranslateengine.h"

class LibreTranslate: public AbstractTranslateEngine {
public:
    explicit LibreTranslate();
    ~LibreTranslate() override;
    const QString getProviderName() override;

    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;
    void setup(const QString &address, const QString &key);
    // todo: implement libre translate
private:
    QString address;
    QString key;

    class API;
    API *api;
};



#endif //LIBRETRANSLATE_H
