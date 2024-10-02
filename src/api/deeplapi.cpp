#include "deeplapi.h"
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
// reference: https://github.com/OwO-Network/DeepLX/blob/main/translate/translate.go
//    && https://github.com/guobao2333/DeepLX-Serverless/blob/main/translate.js
bool DeeplAPI::webTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result) {

    QJsonObject postData = DeeplAPI::initJsonRPC(languages.first.toUpper(), languages.second.toUpper(), text);
    qint64 id = postData[QStringLiteral("id")].toInteger();

    QString jsonString = QString::fromUtf8(QJsonDocument(postData).toJson(QJsonDocument::Compact).data());

    if (id + 5 % 29 == 0 || id + 3 % 13 == 0) {
        jsonString = jsonString.replace(QStringLiteral("\"method\":\""), QStringLiteral("\"method\" : \""));
    } else {
        jsonString = jsonString.replace(QStringLiteral("\"method\":\""), QStringLiteral("\"method\": \""));
    }
    QByteArray requestContent = jsonString.toUtf8();

    QNetworkRequest request;
    request.setUrl(QUrl(QStringLiteral("https://www2.deepl.com/jsonrpc")));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("x-app-os-name", "iOS");
    request.setRawHeader("x-app-os-version", "16.3.0");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.9");
    // request.setRawHeader("Accept-Encoding", "deflate, br");
    request.setRawHeader("x-app-device", "iPhone13,2");
    request.setRawHeader("User-Agent", "DeepL-iOS/2.9.1 iOS 16.3.0 (iPhone13,2)");
    request.setRawHeader("x-app-build", "510265");
    request.setRawHeader("x-app-version", "2.9.1");
    request.setRawHeader("Connection", "keep-alive");


    QNetworkAccessManager mgr;
    QEventLoop loop;
    QObject::connect(&mgr, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QNetworkReply *reply = mgr.post(request, requestContent);
    loop.exec();
    reply->deleteLater();


    if (reply->error() == QNetworkReply::NoError) {
        // for (auto header : reply->rawHeaderList()) {
        //     qDebug() << "Header: " << header.toStdString() << ": " << reply->rawHeader(header).toStdString();
        // }
        QJsonDocument responseContent = QJsonDocument::fromJson(reply->readAll());
        // qDebug() << "Deepl: server reply: " << QString::fromUtf8(responseContent.toJson(QJsonDocument::Compact).data());
        QString translation = responseContent.object()[QStringLiteral("result")]
            .toObject()[QStringLiteral("texts")]
            .toArray()[0]
            .toObject()[QStringLiteral("text")]
            .toString();
        if (translation.isEmpty()) {
            return false;
        } else {
            result = translation;
            return true;
        }
    } else {
        qint64 statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Krunner Translator: Deepl error";
        if (statusCode == 429) {
            qDebug() << "Status code: " << statusCode << "Too many requests. Please try again later";
        } else {
            qDebug() << "Status code: " << statusCode;
        }
        return false;
    }
    
}

QJsonObject DeeplAPI::initJsonRPC(const QString &sourceLanguage, const QString &targetLanguage, const QString &text) {

    QJsonObject postData, params, lang, txt;
    QJsonArray txtArray;

    txt = {
        {QStringLiteral("text"), text},
        {QStringLiteral("requestAlternatives"), 0}
    };
    txtArray.push_back(txt);

    lang = {
        {QStringLiteral("source_lang_user_selected"), sourceLanguage},
        {QStringLiteral("target_lang"), targetLanguage}
    };
    
    qint64 timestamp;
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    qint64 icount = (qint64)text.count(QStringLiteral("i"));
    if (icount != 0) {
        icount++;
        timestamp = time - time % icount + icount;
    } else {
        timestamp = time;
    }

    params = {
        {QStringLiteral("texts"), txtArray},
        {QStringLiteral("splitting"), QStringLiteral("newlines")},
        {QStringLiteral("lang"), lang},
        {QStringLiteral("timestamp"), timestamp},

    };

    qint64 id = QRandomGenerator(QDateTime::currentSecsSinceEpoch()).bounded(0, 99999) + 8300000;
    id *= 1000;
    
    postData = {
        {QStringLiteral("jsonrpc"), QStringLiteral("2.0")},
        {QStringLiteral("method"), QStringLiteral("LMT_handle_texts")},
        {QStringLiteral("id"), id},
        {QStringLiteral("params"), params}
    };

    return postData;
}
