#ifndef LIBRETRANSLATE_H
#define LIBRETRANSLATE_H

#include "abstracttranslateengine.h"

class LibreTranslate: public AbstractTranslateEngine {
public:
    const QString getProviderName() override;

    bool translate(const QPair<QString, QString> &languages, const QString &text, QString &result) override;

    // todo: implement libre translate
};



#endif //LIBRETRANSLATE_H
