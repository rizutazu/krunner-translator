#ifndef DEEPLAPI_H
#define DEEPLAPI_H

#include <QJsonObject>
#include <QtNetwork/QNetworkReply>
class DeeplAPI {
public:
    bool webTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result);
private:
    static qint64 getRandomID();
    static QString formatPostData(const QJsonObject &postData);
    static qint64 generateTimestamp(const QString &text);
    QNetworkReply *makeRequest(const QJsonObject &postData, const QString &method);
    QNetworkReply *splitText(const QString &text);
    QNetworkAccessManager mgr;
};

#endif // DEEPLAPI_H