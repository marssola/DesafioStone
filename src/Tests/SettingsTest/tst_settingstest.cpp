#include <QtTest>

// add necessary includes here
#include <settings/settings.h>
#include <settings/settingsdao.h>
#include <settings/itemsettings.h>

class SettingsTest : public QObject
{
    Q_OBJECT
    Settings m_settings;
    SettingsDao m_settingsDao;

    const QString m_clientID{QStringLiteral("f8023ea988e548df83fb42b5ce1e1a20")};
    const QString m_clientSecret{QStringLiteral("5cf01313067d4391a9a8643add01307a")};

public:
    SettingsTest() = default;
    ~SettingsTest() override = default;

private slots:
    void initTestCase();

    void loadSettings();
    void totalRegisters();
};

void SettingsTest::initTestCase()
{
    ItemSettings *clientID = new ItemSettings;
    clientID->setId(static_cast<int>(Settings::Type::ClientID));
    clientID->setField(QStringLiteral("ClientID"));
    clientID->setValue(m_clientID);

    ItemSettings *clientSecret = new ItemSettings;
    clientSecret->setId(static_cast<int>(Settings::Type::ClientSecret));
    clientSecret->setField(QStringLiteral("ClientSecret"));
    clientSecret->setValue(m_clientSecret);

    ItemSettings *userToken = new ItemSettings;
    userToken->setId(static_cast<int>(Settings::Type::UserToken));
    userToken->setField(QStringLiteral("UserToken"));
    userToken->setValue("");

    QMap<int, ItemSettings *> items{};
    items[static_cast<int>(Settings::Type::ClientID)] = clientID;
    items[static_cast<int>(Settings::Type::ClientSecret)] = clientSecret;
    items[static_cast<int>(Settings::Type::UserToken)] = userToken;
    m_settingsDao.update(items);
}

void SettingsTest::loadSettings()
{
    QVERIFY(m_settingsDao.loadAll(&m_settings));
}

void SettingsTest::totalRegisters()
{
    QVERIFY(m_settings.size() == 4);
}

QTEST_APPLESS_MAIN(SettingsTest)

#include "tst_settingstest.moc"
