#include "deeplapi.h"
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
// reference: https://github.com/OwO-Network/DeepLX/blob/main/translate/translate.go

qint64 DeeplAPI::getRandomID() {
    qint64 id = QRandomGenerator(QDateTime::currentSecsSinceEpoch()).bounded(0, 99999) + 8300000;
    return id * 1000;
}

QString DeeplAPI::formatPostData(const QJsonObject &postData) {
    qint64 id = postData[QStringLiteral("id")].toInteger();
    QString jsonString = QString::fromUtf8(QJsonDocument(postData).toJson(QJsonDocument::Compact).data());
    if (id + 5 % 29 == 0 || id + 3 % 13 == 0) {
        jsonString = jsonString.replace(QStringLiteral("\"method\":\""), QStringLiteral("\"method\" : \""));
    } else {
        jsonString = jsonString.replace(QStringLiteral("\"method\":\""), QStringLiteral("\"method\": \""));
    }
    return jsonString;
}

qint64 DeeplAPI::generateTimestamp(const QString &text) {
    qint64 timestamp;
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    qint64 icount = (qint64)text.count(QStringLiteral("i"));
    if (icount != 0) {
        icount++;
        timestamp = time - time % icount + icount;
    } else {
        timestamp = time;
    }
    return timestamp;
}

// make a request, do not delete later
QNetworkReply *DeeplAPI::makeRequest(const QJsonObject &postData, const QString &method) {

    QNetworkRequest request;
    request.setUrl(QUrl(QStringLiteral("https://www2.deepl.com/jsonrpc?client=chrome-extension,1.28.0&method=%1").arg(method)));
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.9,zh-CN;q=0.8,zh-TW;q=0.7,zh-HK;q=0.6,zh;q=0.5");
    request.setRawHeader("Authorization", "None");
    request.setRawHeader("Cache-Control", "no-cache");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("DNT", "1");
    request.setRawHeader("Origin", "chrome-extension://cofdbpoegempjloogbagkncekinflcnj");
    request.setRawHeader("Priority", "u=1, i");
    request.setRawHeader("Referer", "https://www.deepl.com/");
    request.setRawHeader("Sec-Fetch-Dest", "empty");
    request.setRawHeader("Sec-Fetch-Mode", "cors");
    request.setRawHeader("Sec-Fetch-Site", "none");
    request.setRawHeader("Sec-GPC", "1");
    request.setRawHeader("User-Agent", "DeepLBrowserExtension/1.28.0 Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36");

    // qDebug() << "make request url: " << request.url();
    // qDebug() << "headers: " << request.headers();
    // qDebug() << "post data: " << postData;

    QEventLoop loop;
    QObject::connect(&mgr, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QNetworkReply *reply = mgr.post(request, formatPostData(postData).toUtf8());
    loop.exec();
    return reply;
}


QNetworkReply *DeeplAPI::splitText(const QString &text) {

    QJsonObject postData = {
        {QStringLiteral("jsonrpc"), QStringLiteral("2.0")},
        {QStringLiteral("method"), QStringLiteral("LMT_split_text")},
        {QStringLiteral("id"), getRandomID()},
        {QStringLiteral("params"), QJsonObject {
            {QStringLiteral("commonJobParams"), QJsonObject {
                {QStringLiteral("mode"), QStringLiteral("translate")},
            }},
            {QStringLiteral("lang"), QJsonObject {
                {QStringLiteral("lang_user_selected"), QStringLiteral("auto")},
            }},
            {QStringLiteral("texts"), QJsonArray {text}},
            {QStringLiteral("textType"), QStringLiteral("plaintext")},
            {QStringLiteral("timestamp"), 0}
        }}
    };

    return makeRequest(postData, QStringLiteral("LMT_split_text"));
}


bool DeeplAPI::webTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    QNetworkReply *splitReply = splitText(text);
    if (splitReply->error() == QNetworkReply::NoError) {

        // qDebug() << "split response ok";

        QJsonDocument responseContent = QJsonDocument::fromJson(splitReply->readAll());

        // qDebug() << "response: " << responseContent;

        QJsonArray chunks = responseContent
            .object()[QStringLiteral("result")]
            .toObject()[QStringLiteral("texts")]
            .toArray()[0]
            .toObject()[QStringLiteral("chunks")]
            .toArray();

        QJsonArray jobs;

        // qDebug() << "chunks size" << chunks.size();

        for (int i = 0; i < chunks.size(); i++) {
            auto sentence = chunks[i]
                .toObject()[QStringLiteral("sentences")]
                .toArray()[0]
                .toObject();
            QString contextBefore, contextAfter;
            if (i > 0) {
                contextBefore = chunks[i - 1]
                    .toObject()[QStringLiteral("sentences")]
                    .toArray()[0]
                    .toObject()[QStringLiteral("text")]
                    .toString();
            }
            if (i < chunks.size() - 1) {
                contextAfter = chunks[i + 1]
                    .toObject()[QStringLiteral("sentences")]
                    .toArray()[0]
                    .toObject()[QStringLiteral("text")]
                    .toString();
            }
            jobs.append(QJsonObject {
                {QStringLiteral("kind"), QStringLiteral("default")},
                {QStringLiteral("preferred_num_beams"), 4},
                {QStringLiteral("raw_en_context_before"), QJsonArray {contextBefore}},
                {QStringLiteral("raw_en_context_after"), QJsonArray {contextAfter}},
                {QStringLiteral("sentences"), QJsonArray { QJsonObject {
                    {QStringLiteral("prefix"), sentence[QStringLiteral("prefix")].toString()},
                    {QStringLiteral("text"), sentence[QStringLiteral("text")].toString()},
                    {QStringLiteral("id"), i + 1}
                }}}
            });
        }

        QJsonObject postData = {
            {QStringLiteral("jsonrpc"), QStringLiteral("2.0")},
            {QStringLiteral("method"), QStringLiteral("LMT_handle_jobs")},
            {QStringLiteral("id"), getRandomID()},
            {QStringLiteral("params"), QJsonObject {
                {QStringLiteral("commonJobParams"), QJsonObject {
                    {QStringLiteral("mode"), QStringLiteral("translate")},
                    // {QStringLiteral("regionalVariant"), QString()},
                }},
                {QStringLiteral("lang"), QJsonObject {
                    {QStringLiteral("source_lang_computed"), languages.first.toUpper()},
                    {QStringLiteral("target_lang"), languages.second.toUpper()},
                }},
                {QStringLiteral("jobs"), jobs},
                {QStringLiteral("priority"), 1},
                {QStringLiteral("timestamp"), generateTimestamp(text)},
            }}
        };

        QNetworkReply *translateReply = makeRequest(postData, QStringLiteral("LMT_handle_jobs"));

        if (translateReply->error() == QNetworkReply::NoError) {

            auto partTranslations = QJsonDocument::fromJson(translateReply->readAll())
                .object()[QStringLiteral("result")]
                .toObject()[QStringLiteral("translations")]
                .toArray();

            // qDebug() << "translate reply" << partTranslations;

            for (auto partTranslation : partTranslations) {
                result += partTranslation
                    .toObject()[QStringLiteral("beams")]
                    .toArray()[0]
                    .toObject()[QStringLiteral("sentences")]
                    .toArray()[0]
                    .toObject()[QStringLiteral("text")]
                    .toString();
                result += QStringLiteral(" ");
            }
            result = result.simplified();

            translateReply->deleteLater();
            splitReply->deleteLater();

            if (result.isEmpty()) {
                return false;
            } else {
                return true;
            }
        } else {
            // qint64 statusCode = translateReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            // qDebug() << "Deepl handle jobs" << statusCode;
            translateReply->deleteLater();
            splitReply->deleteLater();
            return false;
        }
    } else {
        // qint64 statusCode = splitReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        // qDebug() << "Deepl split text" << statusCode;
        splitReply->deleteLater();
        return false;
    }
}