cmake_minimum_required(VERSION 3.16.0)
project(RunnerTranslator)

set(KF6_MIN_VERSION 6)
find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Find the required Libaries
find_package (Qt6 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core)
find_package (KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS Service Runner TextWidgets)



set(krunner_translator_SRCS
        src/translator.cpp src/translator.h
        src/translateShellProcess.cpp src/translateShellProcess.h
        src/LanguageRepository.cpp src/LanguageRepository.h
        src/languages.cpp src/languages.h src/SupportedLanguages.h)

kcoreaddons_add_plugin(krunner_translator SOURCES ${krunner_translator_SRCS} INSTALL_NAMESPACE "kf6/krunner")

# Now make sure all files get to the right place
# add_library(krunner_translator MODULE ${krunner_translator_SRCS})
target_link_libraries(krunner_translator KF6::Runner Qt6::Widgets
                      KF6::Service)


# install(TARGETS krunner_translator DESTINATION ${PLUGIN_INSTALL_DIR}/krunner)
# install(TARGETS kcm_krunner_translator DESTINATION ${PLUGIN_INSTALL_DIR})
# install(FILES src/config/plasma-runner-translator_config.desktop DESTINATION ${SERVICES_INSTALL_DIR})
