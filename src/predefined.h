#ifndef PREDEFINEDLANGUAGES_H
#define PREDEFINEDLANGUAGES_H
#include "language.h"

// predefined languages

class Predefined {

public:
	// trans shell 0.9.7.1
    static Language Afrikaans;
    static Language Albanian;
    static Language Amharic;
    static Language Arabic;
    static Language Armenian;
    static Language Assamese;
    static Language Aymara;
    static Language Azerbaijani;
    static Language Bambara;
    static Language Bashkir;
    static Language Basque;
    static Language Belarusian;
    static Language Bengali;
    static Language Bhojpuri;
    static Language Bosnian;
    static Language Bulgarian;
    static Language Cantonese;
    static Language Catalan;
    static Language Cebuano;
    static Language Chichewa;

	// chinese variants
    static Language Chinese;
    static Language ChineseLiterary;
    static Language ChineseSimplified;
    static Language ChineseTraditional;

    static Language Chuvash;
    static Language Corsican;
    static Language Croatian;
    static Language Czech;
    static Language Danish;
    static Language Dari;
    static Language Dhivehi;
    static Language Dogri;
    static Language Dutch;
    static Language EasternMari;

	// english variants
    static Language English;
	static Language EnglishUS;
	static Language EnglishUK;

	static Language Esperanto;
    static Language Estonian;
    static Language Ewe;
    static Language Faroese;
    static Language Fijian;
    static Language Filipino;
    static Language Finnish;
    static Language French;
    static Language FrenchCanadian;
    static Language Frisian;
    static Language Galician;
    static Language Georgian;
    static Language German;
    static Language Greek;
    static Language Guarani;
    static Language Gujarati;
    static Language HaitianCreole;
    static Language Hausa;
    static Language Hawaiian;
    static Language Hebrew;
    static Language HillMari;
    static Language Hindi;
    static Language Hmong;
    static Language Hungarian;
    static Language Icelandic;
    static Language Igbo;
    static Language Ilocano;
    static Language Indonesian;
    static Language Inuinnaqtun;
    static Language Inuktitut;
    static Language InuktitutLatin;
    static Language Irish;
    static Language Italian;
    static Language Japanese;
    static Language Javanese;
    static Language Kannada;
    static Language Kazakh;
    static Language Khmer;
    static Language Kinyarwanda;
    static Language Klingon;
    static Language Konkani;
    static Language Korean;
    static Language Krio;
    static Language KurdishCentral;
    static Language KurdishNorthern;
    static Language Kyrgyz;
    static Language Lao;
    static Language Latin;
    static Language Latvian;
    static Language Lingala;
    static Language Lithuanian;
    static Language Luganda;
    static Language Luxembourgish;
    static Language Macedonian;
    static Language Maithili;
    static Language Malagasy;
    static Language Malay;
    static Language Malayalam;
    static Language Maltese;
    static Language Maori;
    static Language Marathi;
    static Language Meiteilon;
    static Language Mizo;
    static Language Mongolian;
    static Language MongolianTraditional;
    static Language Myanmar;
    static Language Nepali;

	// trans shell can handle both no and nb, deepl uses nb
    static Language Norwegian;
	static Language NorwegianNB;

    static Language Odia;
    static Language Oromo;
    static Language Papiamento;
    static Language Pashto;
    static Language Persian;
    static Language Polish;

	// portuguese variants
	static Language Portuguese;
    static Language PortugueseBrazilian;
    static Language PortugueseEuropean;

    static Language Punjabi;
    static Language Quechua;
    static Language QuerétaroOtomi;
    static Language Romanian;
    static Language Russian;
    static Language Samoan;
    static Language Sanskrit;
    static Language ScotsGaelic;
    static Language Sepedi;
    static Language SerbianCyrillic;
    static Language SerbianLatin;
    static Language Sesotho;
    static Language Shona;
    static Language Sindhi;
    static Language Sinhala;
    static Language Slovak;
    static Language Slovenian;
    static Language Somali;
    static Language Spanish;
    static Language Sundanese;
    static Language Swahili;
    static Language Swedish;
    static Language Tahitian;
    static Language Tajik;
    static Language Tamil;
    static Language Tatar;
    static Language Telugu;
    static Language Thai;
    static Language Tibetan;
    static Language Tigrinya;
    static Language Tongan;
    static Language Tsonga;
    static Language Turkish;
    static Language Turkmen;
    static Language Twi;
    static Language Udmurt;
    static Language Ukrainian;
    static Language UpperSorbian;
    static Language Urdu;
    static Language Uyghur;
    static Language Uzbek;
    static Language Vietnamese;
    static Language Welsh;
    static Language Xhosa;
    static Language Yakut;
    static Language Yiddish;
    static Language Yoruba;
    static Language YucatecMaya;
    static Language Zulu;
	static void init();
};


#define AddTranslateShellSupportedLanguage(repo) \
	repo.addLanguage(Predefined::Afrikaans); repo.addLanguage(Predefined::Albanian);\
	repo.addLanguage(Predefined::Amharic); repo.addLanguage(Predefined::Arabic);\
	repo.addLanguage(Predefined::Armenian); repo.addLanguage(Predefined::Assamese);\
	repo.addLanguage(Predefined::Aymara); repo.addLanguage(Predefined::Azerbaijani);\
	repo.addLanguage(Predefined::Bambara); repo.addLanguage(Predefined::Bashkir);\
	repo.addLanguage(Predefined::Basque); repo.addLanguage(Predefined::Belarusian);\
	repo.addLanguage(Predefined::Bengali); repo.addLanguage(Predefined::Bhojpuri);\
	repo.addLanguage(Predefined::Bosnian); repo.addLanguage(Predefined::Bulgarian);\
	repo.addLanguage(Predefined::Cantonese); repo.addLanguage(Predefined::Catalan);\
	repo.addLanguage(Predefined::Cebuano); repo.addLanguage(Predefined::Chichewa);\
	repo.addLanguage(Predefined::Chinese); repo.addLanguage(Predefined::ChineseLiterary);\
	repo.addLanguage(Predefined::ChineseSimplified); repo.addLanguage(Predefined::ChineseTraditional);\
	repo.addLanguage(Predefined::Chuvash); repo.addLanguage(Predefined::Corsican);\
	repo.addLanguage(Predefined::Croatian); repo.addLanguage(Predefined::Czech);\
	repo.addLanguage(Predefined::Danish); repo.addLanguage(Predefined::Dari);\
	repo.addLanguage(Predefined::Dhivehi); repo.addLanguage(Predefined::Dogri);\
	repo.addLanguage(Predefined::Dutch); repo.addLanguage(Predefined::EasternMari);\
	repo.addLanguage(Predefined::English); repo.addLanguage(Predefined::Esperanto);\
	repo.addLanguage(Predefined::EnglishUS); repo.addLanguage(Predefined::EnglishUK);\
	repo.addLanguage(Predefined::Estonian); repo.addLanguage(Predefined::Ewe);\
	repo.addLanguage(Predefined::Faroese); repo.addLanguage(Predefined::Fijian);\
	repo.addLanguage(Predefined::Filipino); repo.addLanguage(Predefined::Finnish);\
	repo.addLanguage(Predefined::French); repo.addLanguage(Predefined::FrenchCanadian);\
	repo.addLanguage(Predefined::Frisian); repo.addLanguage(Predefined::Galician);\
	repo.addLanguage(Predefined::Georgian); repo.addLanguage(Predefined::German);\
	repo.addLanguage(Predefined::Greek); repo.addLanguage(Predefined::Guarani);\
	repo.addLanguage(Predefined::Gujarati); repo.addLanguage(Predefined::HaitianCreole);\
	repo.addLanguage(Predefined::Hausa); repo.addLanguage(Predefined::Hawaiian);\
	repo.addLanguage(Predefined::Hebrew); repo.addLanguage(Predefined::HillMari);\
	repo.addLanguage(Predefined::Hindi); repo.addLanguage(Predefined::Hmong);\
	repo.addLanguage(Predefined::Hungarian); repo.addLanguage(Predefined::Icelandic);\
	repo.addLanguage(Predefined::Igbo); repo.addLanguage(Predefined::Ilocano);\
	repo.addLanguage(Predefined::Indonesian); repo.addLanguage(Predefined::Inuinnaqtun);\
	repo.addLanguage(Predefined::Inuktitut); repo.addLanguage(Predefined::InuktitutLatin);\
	repo.addLanguage(Predefined::Irish); repo.addLanguage(Predefined::Italian);\
	repo.addLanguage(Predefined::Japanese); repo.addLanguage(Predefined::Javanese);\
	repo.addLanguage(Predefined::Kannada); repo.addLanguage(Predefined::Kazakh);\
	repo.addLanguage(Predefined::Khmer); repo.addLanguage(Predefined::Kinyarwanda);\
	repo.addLanguage(Predefined::Klingon); repo.addLanguage(Predefined::Konkani);\
	repo.addLanguage(Predefined::Korean); repo.addLanguage(Predefined::Krio);\
	repo.addLanguage(Predefined::KurdishCentral); repo.addLanguage(Predefined::KurdishNorthern);\
	repo.addLanguage(Predefined::Kyrgyz); repo.addLanguage(Predefined::Lao);\
	repo.addLanguage(Predefined::Latin); repo.addLanguage(Predefined::Latvian);\
	repo.addLanguage(Predefined::Lingala); repo.addLanguage(Predefined::Lithuanian);\
	repo.addLanguage(Predefined::Luganda); repo.addLanguage(Predefined::Luxembourgish);\
	repo.addLanguage(Predefined::Macedonian); repo.addLanguage(Predefined::Maithili);\
	repo.addLanguage(Predefined::Malagasy); repo.addLanguage(Predefined::Malay);\
	repo.addLanguage(Predefined::Malayalam); repo.addLanguage(Predefined::Maltese);\
	repo.addLanguage(Predefined::Maori); repo.addLanguage(Predefined::Marathi);\
	repo.addLanguage(Predefined::Meiteilon); repo.addLanguage(Predefined::Mizo);\
	repo.addLanguage(Predefined::Mongolian); repo.addLanguage(Predefined::MongolianTraditional);\
	repo.addLanguage(Predefined::Myanmar); repo.addLanguage(Predefined::Nepali);\
	repo.addLanguage(Predefined::Norwegian); repo.addLanguage(Predefined::Odia);\
	repo.addLanguage(Predefined::NorwegianNB);\
	repo.addLanguage(Predefined::Oromo); repo.addLanguage(Predefined::Papiamento);\
	repo.addLanguage(Predefined::Pashto); repo.addLanguage(Predefined::Persian);\
	repo.addLanguage(Predefined::Portuguese);\
	repo.addLanguage(Predefined::Polish); repo.addLanguage(Predefined::PortugueseBrazilian);\
	repo.addLanguage(Predefined::PortugueseEuropean); repo.addLanguage(Predefined::Punjabi);\
	repo.addLanguage(Predefined::Quechua); repo.addLanguage(Predefined::QuerétaroOtomi);\
	repo.addLanguage(Predefined::Romanian); repo.addLanguage(Predefined::Russian);\
	repo.addLanguage(Predefined::Samoan); repo.addLanguage(Predefined::Sanskrit);\
	repo.addLanguage(Predefined::ScotsGaelic); repo.addLanguage(Predefined::Sepedi);\
	repo.addLanguage(Predefined::SerbianCyrillic); repo.addLanguage(Predefined::SerbianLatin);\
	repo.addLanguage(Predefined::Sesotho); repo.addLanguage(Predefined::Shona);\
	repo.addLanguage(Predefined::Sindhi); repo.addLanguage(Predefined::Sinhala);\
	repo.addLanguage(Predefined::Slovak); repo.addLanguage(Predefined::Slovenian);\
	repo.addLanguage(Predefined::Somali); repo.addLanguage(Predefined::Spanish);\
	repo.addLanguage(Predefined::Sundanese); repo.addLanguage(Predefined::Swahili);\
	repo.addLanguage(Predefined::Swedish); repo.addLanguage(Predefined::Tahitian);\
	repo.addLanguage(Predefined::Tajik); repo.addLanguage(Predefined::Tamil);\
	repo.addLanguage(Predefined::Tatar); repo.addLanguage(Predefined::Telugu);\
	repo.addLanguage(Predefined::Thai); repo.addLanguage(Predefined::Tibetan);\
	repo.addLanguage(Predefined::Tigrinya); repo.addLanguage(Predefined::Tongan);\
	repo.addLanguage(Predefined::Tsonga); repo.addLanguage(Predefined::Turkish);\
	repo.addLanguage(Predefined::Turkmen); repo.addLanguage(Predefined::Twi);\
	repo.addLanguage(Predefined::Udmurt); repo.addLanguage(Predefined::Ukrainian);\
	repo.addLanguage(Predefined::UpperSorbian); repo.addLanguage(Predefined::Urdu);\
	repo.addLanguage(Predefined::Uyghur); repo.addLanguage(Predefined::Uzbek);\
	repo.addLanguage(Predefined::Vietnamese); repo.addLanguage(Predefined::Welsh);\
	repo.addLanguage(Predefined::Xhosa); repo.addLanguage(Predefined::Yakut);\
	repo.addLanguage(Predefined::Yiddish); repo.addLanguage(Predefined::Yoruba);\
	repo.addLanguage(Predefined::YucatecMaya); repo.addLanguage(Predefined::Zulu);

#define AddDeeplSupportedLanguage(repo) \
	repo.addLanguage(Predefined::Arabic); repo.addLanguage(Predefined::Bulgarian);\
	repo.addLanguage(Predefined::Czech); repo.addLanguage(Predefined::Danish);\
	repo.addLanguage(Predefined::German); repo.addLanguage(Predefined::Greek);\
	repo.addLanguage(Predefined::English); repo.addLanguage(Predefined::Spanish);\
	repo.addLanguage(Predefined::Estonian); repo.addLanguage(Predefined::Finnish);\
	repo.addLanguage(Predefined::French); repo.addLanguage(Predefined::Hebrew);\
	repo.addLanguage(Predefined::Hungarian); repo.addLanguage(Predefined::Indonesian);\
	repo.addLanguage(Predefined::Italian); repo.addLanguage(Predefined::Japanese);\
	repo.addLanguage(Predefined::Korean); repo.addLanguage(Predefined::Lithuanian);\
	repo.addLanguage(Predefined::Latvian); repo.addLanguage(Predefined::NorwegianNB);\
	repo.addLanguage(Predefined::Dutch); repo.addLanguage(Predefined::Polish);\
	repo.addLanguage(Predefined::Portuguese); repo.addLanguage(Predefined::Romanian);\
	repo.addLanguage(Predefined::Russian); repo.addLanguage(Predefined::Slovak);\
	repo.addLanguage(Predefined::Slovenian); repo.addLanguage(Predefined::Swedish);\
	repo.addLanguage(Predefined::Thai); repo.addLanguage(Predefined::Turkish);\
	repo.addLanguage(Predefined::Ukrainian); repo.addLanguage(Predefined::Vietnamese);\
	repo.addLanguage(Predefined::Chinese);



#endif //PREDEFINEDLANGUAGES_H
