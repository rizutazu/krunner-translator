#include "libretranslate.h"
#include "libretranslateapi.h"

class LibreTranslate::API : public LibreTranslateAPI {

};

LibreTranslate::LibreTranslate() {
    api = new API();
}

LibreTranslate::~LibreTranslate() {
    delete api;
}

const QString LibreTranslate::getProviderName() {
    return QStringLiteral("Libre Translate");
}

bool LibreTranslate::translate(const QPair<QString, QString> &languages, const QString &text, QString &result) {
    if (address.isEmpty()) {
        return false;
    }
    return api->translate(address, key, languages, text, result);
}

void LibreTranslate::setup(const QString &address, const QString &key) {
    this->address = address;
    this->key = key;
}
