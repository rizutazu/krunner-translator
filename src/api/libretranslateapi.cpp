#include "libretranslateapi.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>

bool LibreTranslateAPI::translate(const QString &address, const QString &key, const QPair<QString, QString> &languages,
                                  const QString &text, QString &result) {

    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setUrl(QUrl(address + QStringLiteral("/translate")));

    QJsonObject postData = {
        {QStringLiteral("q"), text},
        {QStringLiteral("source"), languages.first.isEmpty() ? QStringLiteral("auto") : languages.first},
        {QStringLiteral("target"), languages.second},
        {QStringLiteral("api_key"), key}
    };

    QEventLoop loop;
    QEventLoop::connect(&mgr, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QNetworkReply *reply = mgr.post(request, QJsonDocument(postData).toJson());
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        const QJsonDocument responseContent = QJsonDocument::fromJson(reply->readAll());
        result = responseContent.object()[QStringLiteral("translatedText")].toString();
        if (result.isEmpty()) {
            return false;
        }
        return true;
    }

    const QJsonDocument responseContent = QJsonDocument::fromJson(reply->readAll());
    qDebug() << "Libre Translate statusCode"
        << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString() + QStringLiteral(",")
        << "error message:" << responseContent.object()[QStringLiteral("error")].toString();
    return false;
}
