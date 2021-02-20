TEMPLATE = subdirs

authenticationTest.subdir       = AuthenticationTest
settingsTest.subdir             = SettingsTest

authenticationTest.depends      = settingsTest

SUBDIRS += \
    PlaylistTest \
    authenticationTest \
    settingsTest
