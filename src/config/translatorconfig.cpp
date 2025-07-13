#include "translatorconfig.h"
#include "configentry.h"
#include <KPluginFactory>
#include <KSharedConfig>
#include <KConfigGroup>

K_PLUGIN_CLASS(TranslatorConfig)

TranslatorConfig::TranslatorConfig(QObject *parent) : KCModule(parent) {
    ui = new Ui::TranslatorConfigUI();
    ui->setupUi(KCModule::widget());

    connect(ui->googleCheckBox, &QCheckBox::checkStateChanged, this, &TranslatorConfig::markAsChanged);
    connect(ui->bingCheckBox,&QCheckBox::checkStateChanged, this, &TranslatorConfig::markAsChanged);
    connect(ui->deeplCheckBox, &QCheckBox::checkStateChanged, this, &TranslatorConfig::markAsChanged);
    connect(ui->libreCheckBox, &QCheckBox::checkStateChanged, this, &TranslatorConfig::markAsChanged);
    connect(ui->libreAddr, &QLineEdit::textChanged, this, &TranslatorConfig::markAsChanged);
    connect(ui->libreKey, &QLineEdit::textChanged, this, &TranslatorConfig::markAsChanged);

    // only show up address and key config when the box is checked
    connect(ui->libreCheckBox, &QCheckBox::checkStateChanged, this, [&](){
        ui->libreFrame->setEnabled(ui->libreCheckBox->isChecked());
    });

    connect(ui->tabs, &QTabWidget::currentChanged, this, [&]() {
        KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("krunnerrc"));
        KConfigGroup group = config->group(QStringLiteral("Runners")).group(QStringLiteral(KRUNNER_PLUGIN_NAME));
        group.writeEntry(CONFIG_CURRENT_INDEX, ui->tabs->currentIndex());
        group.sync();
    });

}


void TranslatorConfig::save() {
    KCModule::save();

    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("krunnerrc"));
    KConfigGroup group = config->group(QStringLiteral("Runners")).group(QStringLiteral(KRUNNER_PLUGIN_NAME));

    group.writeEntry(CONFIG_GOOGLE, ui->googleCheckBox->isChecked());
    group.writeEntry(CONFIG_BING, ui->bingCheckBox->isChecked());
    group.writeEntry(CONFIG_DEEPL, ui->deeplCheckBox->isChecked());
    group.writeEntry(CONFIG_LIBRE, ui->libreCheckBox->isChecked());

    group.writeEntry(CONFIG_LIBRE_ADDR, ui->libreAddr->text());
    group.writeEntry(CONFIG_LIBRE_KEY, ui->libreKey->text());

    group.sync();
}

void TranslatorConfig::load() {
    KCModule::load();


    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("krunnerrc"));
    const KConfigGroup group = config->group(QStringLiteral("Runners")).group(QStringLiteral(KRUNNER_PLUGIN_NAME));

    ui->googleCheckBox->setChecked(group.readEntry(CONFIG_GOOGLE, true));
    ui->bingCheckBox->setChecked(group.readEntry(CONFIG_BING, true));
    ui->deeplCheckBox->setChecked(group.readEntry(CONFIG_DEEPL, true));
    ui->libreCheckBox->setChecked(group.readEntry(CONFIG_LIBRE, false));
    ui->libreAddr->setText(group.readEntry(CONFIG_LIBRE_ADDR, ""));
    ui->libreKey->setText(group.readEntry(CONFIG_LIBRE_KEY, ""));

    ui->libreFrame->setEnabled(ui->libreCheckBox->isChecked());

    ui->tabs->setCurrentIndex(group.readEntry(CONFIG_CURRENT_INDEX, 0));
}

void TranslatorConfig::defaults() {
    KCModule::defaults();

    ui->googleCheckBox->setChecked(true);
    ui->bingCheckBox->setChecked(true);
    ui->deeplCheckBox->setChecked(true);
    ui->libreCheckBox->setChecked(false);
    ui->libreAddr->setText(QString());
    ui->libreKey->setText(QString());
    setNeedsSave(true);
}



#include "translatorconfig.moc"

#include "moc_translatorconfig.cpp"

