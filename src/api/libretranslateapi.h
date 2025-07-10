#ifndef LIBRETRANSLATEAPI_H
#define LIBRETRANSLATEAPI_H

#include <QNetworkAccessManager>

class LibreTranslateAPI {
public:
    bool translate(const QString &address, const QString &key, const QPair<QString, QString> &languages,
        const QString &text, QString &result);
private:
    QNetworkAccessManager mgr;
};



#endif //LIBRETRANSLATEAPI_H
