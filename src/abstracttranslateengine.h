
#ifndef ABSTRACTTRANSLATEENGINE_H
#define ABSTRACTTRANSLATEENGINE_H

#include <QString>

// AbstractTranslateEngine defines translator interface
class AbstractTranslateEngine {
public:
    AbstractTranslateEngine() {};

    virtual ~AbstractTranslateEngine() {};

    // get translate provider name, e.g., Google, Deepl
    virtual const QString getProviderName() = 0;

    // whether given languages are supported by this translate engine
    virtual bool supportLanguage(const QString &abbreviations) = 0;

    // translate given `text` to target language, put translation at `result`
    // abbreviations.first is source language abbr, abbreviations.second is target language abbr
    // return true if translate is ok, false if any error has occurred.
    virtual bool translate(const QPair<QString, QString> &abbreviations, const QString &text, QString &result) = 0;
};



#endif // ABSTRACTTRANSLATEENGINE_H