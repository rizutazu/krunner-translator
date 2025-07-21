#ifndef PREDEFINEDLANGUAGES_H
#define PREDEFINEDLANGUAGES_H
#include "language.h"

// predefined languages

namespace Predefined {

    // trans shell 0.9.7.1
    extern Language Afrikaans;
    extern Language Albanian;
    extern Language Amharic;
    extern Language Arabic;
    extern Language Armenian;
    extern Language Assamese;
    extern Language Aymara;
    extern Language Azerbaijani;
    extern Language Bambara;
    extern Language Bashkir;
    extern Language Basque;
    extern Language Belarusian;
    extern Language Bengali;
    extern Language Bhojpuri;
    extern Language Bosnian;
    extern Language Bulgarian;
    extern Language Cantonese;
    extern Language Catalan;
    extern Language Cebuano;
    extern Language Chichewa;

    // chinese variants
    extern Language Chinese;
    extern Language ChineseLiterary;
    extern Language ChineseSimplified;
    extern Language ChineseTraditional;
    // hans/hant are used by deepl
    extern Language ChineseSimplifiedHANS;
    extern Language ChineseTraditionalHANT;

    extern Language Chuvash;
    extern Language Corsican;
    extern Language Croatian;
    extern Language Czech;
    extern Language Danish;
    extern Language Dari;
    extern Language Dhivehi;
    extern Language Dogri;
    extern Language Dutch;
    extern Language EasternMari;

    // english variants, seems like trans shell do not distinguish these variants
    extern Language English;
    extern Language EnglishUS;
    extern Language EnglishGB;

    extern Language Esperanto;
    extern Language Estonian;
    extern Language Ewe;
    extern Language Faroese;
    extern Language Fijian;
    extern Language Filipino;
    extern Language Finnish;
    extern Language French;
    extern Language FrenchCanadian;
    extern Language Frisian;
    extern Language Galician;
    extern Language Georgian;
    extern Language German;
    extern Language Greek;
    extern Language Guarani;
    extern Language Gujarati;
    extern Language HaitianCreole;
    extern Language Hausa;
    extern Language Hawaiian;
    extern Language Hebrew;
    extern Language HillMari;
    extern Language Hindi;
    extern Language Hmong;
    extern Language Hungarian;
    extern Language Icelandic;
    extern Language Igbo;
    extern Language Ilocano;
    extern Language Indonesian;
    extern Language Inuinnaqtun;
    extern Language Inuktitut;
    extern Language InuktitutLatin;
    extern Language Irish;
    extern Language Italian;
    extern Language Japanese;
    extern Language Javanese;
    extern Language Kannada;
    extern Language Kazakh;
    extern Language Khmer;
    extern Language Kinyarwanda;
    extern Language Klingon;
    extern Language Konkani;
    extern Language Korean;
    extern Language Krio;
    extern Language KurdishCentral;
    extern Language KurdishNorthern;
    extern Language Kyrgyz;
    extern Language Lao;
    extern Language Latin;
    extern Language Latvian;
    extern Language Lingala;
    extern Language Lithuanian;
    extern Language Luganda;
    extern Language Luxembourgish;
    extern Language Macedonian;
    extern Language Maithili;
    extern Language Malagasy;
    extern Language Malay;
    extern Language Malayalam;
    extern Language Maltese;
    extern Language Maori;
    extern Language Marathi;
    extern Language Meiteilon;
    extern Language Mizo;
    extern Language Mongolian;
    extern Language MongolianTraditional;
    extern Language Myanmar;
    extern Language Nepali;

    // trans shell can handle both no and nb, deepl uses nb
    extern Language Norwegian;
    extern Language NorwegianNB;

    extern Language Odia;
    extern Language Oromo;
    extern Language Papiamento;
    extern Language Pashto;
    extern Language Persian;
    extern Language Polish;

    // portuguese variants
    extern Language Portuguese;
    extern Language PortugueseBrazilian;
    extern Language PortugueseEuropean;

    extern Language Punjabi;
    extern Language Quechua;
    extern Language QuerétaroOtomi;
    extern Language Romanian;
    extern Language Russian;
    extern Language Samoan;
    extern Language Sanskrit;
    extern Language ScotsGaelic;
    extern Language Sepedi;
    extern Language SerbianCyrillic;
    extern Language SerbianLatin;
    extern Language Sesotho;
    extern Language Shona;
    extern Language Sindhi;
    extern Language Sinhala;
    extern Language Slovak;
    extern Language Slovenian;
    extern Language Somali;

    // spanish variants supported by deepl
    extern Language Spanish;
    extern Language SpanishLatinAmerican;

    extern Language Sundanese;
    extern Language Swahili;
    extern Language Swedish;
    extern Language Tahitian;
    extern Language Tajik;
    extern Language Tamil;
    extern Language Tatar;
    extern Language Telugu;
    extern Language Thai;
    extern Language Tibetan;
    extern Language Tigrinya;
    extern Language Tongan;
    extern Language Tsonga;
    extern Language Turkish;
    extern Language Turkmen;
    extern Language Twi;
    extern Language Udmurt;
    extern Language Ukrainian;
    extern Language UpperSorbian;
    extern Language Urdu;
    extern Language Uyghur;
    extern Language Uzbek;
    extern Language Vietnamese;
    extern Language Welsh;
    extern Language Xhosa;
    extern Language Yakut;
    extern Language Yiddish;
    extern Language Yoruba;
    extern Language YucatecMaya;
    extern Language Zulu;

    extern void init();
};


#define AddTranslateShellSupportedLanguage(repo) \
    do { \
        using namespace Predefined;\
        Predefined::init();\
        repo.addLanguage(Afrikaans); repo.addLanguage(Albanian);\
        repo.addLanguage(Amharic); repo.addLanguage(Arabic);\
        repo.addLanguage(Armenian); repo.addLanguage(Assamese);\
        repo.addLanguage(Aymara); repo.addLanguage(Azerbaijani);\
        repo.addLanguage(Bambara); repo.addLanguage(Bashkir);\
        repo.addLanguage(Basque); repo.addLanguage(Belarusian);\
        repo.addLanguage(Bengali); repo.addLanguage(Bhojpuri);\
        repo.addLanguage(Bosnian); repo.addLanguage(Bulgarian);\
        repo.addLanguage(Cantonese); repo.addLanguage(Catalan);\
        repo.addLanguage(Cebuano); repo.addLanguage(Chichewa);\
        repo.addLanguage(Chinese); repo.addLanguage(ChineseLiterary);\
        repo.addLanguage(ChineseSimplified); repo.addLanguage(ChineseTraditional);\
        repo.addLanguage(Chuvash); repo.addLanguage(Corsican);\
        repo.addLanguage(Croatian); repo.addLanguage(Czech);\
        repo.addLanguage(Danish); repo.addLanguage(Dari);\
        repo.addLanguage(Dhivehi); repo.addLanguage(Dogri);\
        repo.addLanguage(Dutch); repo.addLanguage(EasternMari);\
        repo.addLanguage(English); repo.addLanguage(Esperanto);\
        repo.addLanguage(Estonian); repo.addLanguage(Ewe);\
        repo.addLanguage(Faroese); repo.addLanguage(Fijian);\
        repo.addLanguage(Filipino); repo.addLanguage(Finnish);\
        repo.addLanguage(French); repo.addLanguage(FrenchCanadian);\
        repo.addLanguage(Frisian); repo.addLanguage(Galician);\
        repo.addLanguage(Georgian); repo.addLanguage(German);\
        repo.addLanguage(Greek); repo.addLanguage(Guarani);\
        repo.addLanguage(Gujarati); repo.addLanguage(HaitianCreole);\
        repo.addLanguage(Hausa); repo.addLanguage(Hawaiian);\
        repo.addLanguage(Hebrew); repo.addLanguage(HillMari);\
        repo.addLanguage(Hindi); repo.addLanguage(Hmong);\
        repo.addLanguage(Hungarian); repo.addLanguage(Icelandic);\
        repo.addLanguage(Igbo); repo.addLanguage(Ilocano);\
        repo.addLanguage(Indonesian); repo.addLanguage(Inuinnaqtun);\
        repo.addLanguage(Inuktitut); repo.addLanguage(InuktitutLatin);\
        repo.addLanguage(Irish); repo.addLanguage(Italian);\
        repo.addLanguage(Japanese); repo.addLanguage(Javanese);\
        repo.addLanguage(Kannada); repo.addLanguage(Kazakh);\
        repo.addLanguage(Khmer); repo.addLanguage(Kinyarwanda);\
        repo.addLanguage(Klingon); repo.addLanguage(Konkani);\
        repo.addLanguage(Korean); repo.addLanguage(Krio);\
        repo.addLanguage(KurdishCentral); repo.addLanguage(KurdishNorthern);\
        repo.addLanguage(Kyrgyz); repo.addLanguage(Lao);\
        repo.addLanguage(Latin); repo.addLanguage(Latvian);\
        repo.addLanguage(Lingala); repo.addLanguage(Lithuanian);\
        repo.addLanguage(Luganda); repo.addLanguage(Luxembourgish);\
        repo.addLanguage(Macedonian); repo.addLanguage(Maithili);\
        repo.addLanguage(Malagasy); repo.addLanguage(Malay);\
        repo.addLanguage(Malayalam); repo.addLanguage(Maltese);\
        repo.addLanguage(Maori); repo.addLanguage(Marathi);\
        repo.addLanguage(Meiteilon); repo.addLanguage(Mizo);\
        repo.addLanguage(Mongolian); repo.addLanguage(MongolianTraditional);\
        repo.addLanguage(Myanmar); repo.addLanguage(Nepali);\
        repo.addLanguage(Norwegian); repo.addLanguage(Odia);\
        repo.addLanguage(NorwegianNB);\
        repo.addLanguage(Oromo); repo.addLanguage(Papiamento);\
        repo.addLanguage(Pashto); repo.addLanguage(Persian);\
        repo.addLanguage(Portuguese);\
        repo.addLanguage(Polish); repo.addLanguage(PortugueseBrazilian);\
        repo.addLanguage(PortugueseEuropean); repo.addLanguage(Punjabi);\
        repo.addLanguage(Quechua); repo.addLanguage(QuerétaroOtomi);\
        repo.addLanguage(Romanian); repo.addLanguage(Russian);\
        repo.addLanguage(Samoan); repo.addLanguage(Sanskrit);\
        repo.addLanguage(ScotsGaelic); repo.addLanguage(Sepedi);\
        repo.addLanguage(SerbianCyrillic); repo.addLanguage(SerbianLatin);\
        repo.addLanguage(Sesotho); repo.addLanguage(Shona);\
        repo.addLanguage(Sindhi); repo.addLanguage(Sinhala);\
        repo.addLanguage(Slovak); repo.addLanguage(Slovenian);\
        repo.addLanguage(Somali); repo.addLanguage(Spanish);\
        repo.addLanguage(Sundanese); repo.addLanguage(Swahili);\
        repo.addLanguage(Swedish); repo.addLanguage(Tahitian);\
        repo.addLanguage(Tajik); repo.addLanguage(Tamil);\
        repo.addLanguage(Tatar); repo.addLanguage(Telugu);\
        repo.addLanguage(Thai); repo.addLanguage(Tibetan);\
        repo.addLanguage(Tigrinya); repo.addLanguage(Tongan);\
        repo.addLanguage(Tsonga); repo.addLanguage(Turkish);\
        repo.addLanguage(Turkmen); repo.addLanguage(Twi);\
        repo.addLanguage(Udmurt); repo.addLanguage(Ukrainian);\
        repo.addLanguage(UpperSorbian); repo.addLanguage(Urdu);\
        repo.addLanguage(Uyghur); repo.addLanguage(Uzbek);\
        repo.addLanguage(Vietnamese); repo.addLanguage(Welsh);\
        repo.addLanguage(Xhosa); repo.addLanguage(Yakut);\
        repo.addLanguage(Yiddish); repo.addLanguage(Yoruba);\
        repo.addLanguage(YucatecMaya); repo.addLanguage(Zulu);\
    } while (0)


#define AddDeeplSupportedLanguage(repo) \
    do { \
        using namespace Predefined;\
        Predefined::init();\
        repo.addLanguage(Arabic); repo.addLanguage(Bulgarian);\
        repo.addLanguage(Czech); repo.addLanguage(Danish);\
        repo.addLanguage(German); repo.addLanguage(Greek);\
        repo.addLanguage(English); repo.addLanguage(Spanish);\
        repo.addLanguage(EnglishUS); repo.addLanguage(EnglishGB);\
        repo.addLanguage(SpanishLatinAmerican);\
        repo.addLanguage(Estonian); repo.addLanguage(Finnish);\
        repo.addLanguage(French); repo.addLanguage(Hebrew);\
        repo.addLanguage(Hungarian); repo.addLanguage(Indonesian);\
        repo.addLanguage(Italian); repo.addLanguage(Japanese);\
        repo.addLanguage(Korean); repo.addLanguage(Lithuanian);\
        repo.addLanguage(Latvian); repo.addLanguage(NorwegianNB);\
        repo.addLanguage(Dutch); repo.addLanguage(Polish);\
        repo.addLanguage(Portuguese); repo.addLanguage(Romanian);\
        repo.addLanguage(PortugueseBrazilian); repo.addLanguage(PortugueseEuropean);\
        repo.addLanguage(Russian); repo.addLanguage(Slovak);\
        repo.addLanguage(Slovenian); repo.addLanguage(Swedish);\
        repo.addLanguage(Thai); repo.addLanguage(Turkish);\
        repo.addLanguage(Ukrainian); repo.addLanguage(Vietnamese);\
        repo.addLanguage(Chinese);\
        repo.addLanguage(ChineseSimplifiedHANS); repo.addLanguage(ChineseTraditionalHANT);\
    } while (0)




#endif //PREDEFINEDLANGUAGES_H
