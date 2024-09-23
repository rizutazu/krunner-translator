
#ifndef ABSTRACTTRANSLATEENGINE_H
#define ABSTRACTTRANSLATEENGINE_H

#include <QString>
#include <QPair>

// AbstractTranslateEngine defines translator interface
class AbstractTranslateEngine {

public:
    AbstractTranslateEngine() {};
    virtual ~AbstractTranslateEngine() {};

    virtual void setAPIKey(const QString &key) = 0;
    // set up translate api key if needed

    virtual const QString getProviderName() = 0;
    // get translate provider name, e.g Google Translate, Deepl Translate

    virtual bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) = 0;
    // bool translate(): translate given `text` to target language, put translation at `result`
    // languages.first is translate source language, languages.second is translate target language
    // return true if translate is ok, false if any error has occurred.
};



#endif // ABSTRACTTRANSLATEENGINE_H