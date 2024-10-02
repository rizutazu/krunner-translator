# KRunner Translator (Plasma 6)

KRunner Translator for Plasma 6.

This plugin is derived from [this project](https://github.com/naraesk/krunner-translator) , but it is NOT A DIRECT PORT to plasma 6, so you cannot expect their features will be same. E.g, configuration is not implemented, so you can only use free translate engines.

## Feature

- Translate text

Supported engine: `Google Translate`, `Bing Translate`, `Deepl Web Translate` 

- Play audio for the text

<img src="assets/image-20241001123726703.png" alt="image-20241001123726703" style="zoom:50%;" />

By clicking `Translation` results, their corresponding texts will be copied to clipboard.

By clicking `Play Audio` results, their corresponding audio will be played in the background.

## Usage

This plugin supports two input schemes:

1. `target_abbr text`
2. `source_abbr:target_abb text`

`target_abbr` / `source_abbr` means the abbreviation of source/target language respectively, and `text`means the text you want to translate.

You can find supported language abbreviation at [here](src/languagerepository.cpp).



Example:

- `ja hello` --> `こんにちは`

- `en:es hello` --> `Hola`



**Notice:**

- You cannot play audio of the *input text* (not *translation*) if you don't specify the source language, like picture shown above.
- Since Deepl translate does not support auto detect language, you must use the second input scheme to get its result if you want.
- Deepl translate result may be frequently unavailable due to its rate limit.

## Installation

1. Install [Translate Shell](https://github.com/soimort/translate-shell)
2. make sure `cmake` / `KDE6` / `Qt6` developing environment is prepared.
3. Run `./install.sh`

## Uninstall

- Run `./uninstall.sh`