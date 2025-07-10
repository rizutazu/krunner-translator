#ifndef TRANSLATORCONFIG_H
#define TRANSLATORCONFIG_H

#include "ui_translatorconfig.h"
#include <KCModule>


class TranslatorConfig: public KCModule {
    Q_OBJECT
public:
    explicit TranslatorConfig(QObject *parent);
    ~TranslatorConfig() override = default;

public Q_SLOTS:
    void save() override;
    void load() override;
    void defaults() override;
private:
    Ui::TranslatorConfigUI *ui;
};



#endif //TRANSLATORCONFIG_H
