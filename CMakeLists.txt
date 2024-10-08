cmake_minimum_required(VERSION 3.16.0)
project(KRunnerTranslator)

set(KF6_MIN_VERSION 6)
find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Find the required Libaries
find_package (Qt6 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Core Widgets Network)
find_package (KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS Runner)

unset(QT_NO_CAST_FROM_ASCII)
unset(QT_NO_CAST_TO_ASCII)

set(krunner_translator_SRCS
        src/krunnertranslator.cpp src/krunnertranslator.h
        src/languagerepository.cpp src/languagerepository.h
        src/languages.cpp src/languages.h 
        src/supportedlanguages.h
        src/api/shellprocess.cpp src/api/shellprocess.h
        src/api/deeplapi.cpp src/api/deeplapi.h
        src/abstracttranslateengine.h
        src/provider/googletranslate.h src/provider/googletranslate.cpp
        src/provider/bingtranslate.h src/provider/bingtranslate.cpp
        src/provider/deepltranslate.h src/provider/deepltranslate.cpp
        )

include_directories (src src/api src/provider)

kcoreaddons_add_plugin(krunner_translator SOURCES ${krunner_translator_SRCS} INSTALL_NAMESPACE "kf6/krunner")

# Now make sure all files get to the right place
# add_library(krunner_translator MODULE ${krunner_translator_SRCS})
target_link_libraries(krunner_translator 
                        KF6::Runner 
                        Qt6::Core Qt6::Widgets Qt6::Network)

