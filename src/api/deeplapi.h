#ifndef DEEPLAPI_H
#define DEEPLAPI_H

#include <QPair>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
class DeeplAPI {

public:
    static bool webTranslate(const QPair<QString, QString> &languages, const QString &text, QString &result);
private:
    static QJsonObject initJsonRPC(const QString &sourceLanguage, const QString &targetLanguage, const QString &text);
};

#endif // DEEPLAPI_H