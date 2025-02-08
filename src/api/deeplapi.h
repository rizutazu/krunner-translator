#ifndef DEEPLAPI_H
#define DEEPLAPI_H

#include <QJsonObject>
#include <QtNetwork/QNetworkReply>
class DeeplAPI {

public:
    bool webTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result);
private:
    QNetworkAccessManager mgr;
    static qint64 getRandomID();
    static QString formatPostData(const QJsonObject &postData);
    static qint64 generateTimestamp(const QString &text);
    QNetworkReply *makeRequest(const QJsonObject &postData, const QString &method);
    QNetworkReply *splitText(const QString &text);
    // static QJsonObject initJsonRPC(const QString &sourceLanguage, const QString &targetLanguage, const QString &text);

};

#endif // DEEPLAPI_H