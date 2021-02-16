#include <QtTest>
#include <QSignalSpy>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QTimer>

#include <authentication/authenticationservice.h>
#include <authentication/authenticationconsts.h>

// add necessary includes here

class AuthenticationTest : public QObject
{
    Q_OBJECT
    bool m_needAuthenticate {false};
    AuthenticationService m_authService;
    QTcpSocket m_client;
    const QString m_code {QStringLiteral("AQBwG7BRKApsdF5BMCnAU2UaQLCEg725Gfk4elQFRN4V51o8o4xsxFcaZXkis5kFfvmjL1GbxPmT-ZMYlFv0_XrlCnL8uRNGwu2L1-pPFx3BnaHwxEr8AIYfUK01lt9a4IUWtqQsjv62_vcCjrD47uRN7Y0AWU4avFl0orJ0IOpQxCHsIx-y-LRk5QLVA5tksH0KMFGmWRJQ4DBvh7n1h5WZUZWxWDdGsjwq6nnuZzDdRVdakWuoqA7Zd4taSDV7hoDi2HQxywdx0dIEJOhiKILyd879k0AZD9KSdUgQnPG6l27ljN2Y6uDK5woWKsO4OiF7noxEPngTVFw7U2227LguZOjwbtxeX0SBXOkqGJuwPi-hgpbV5JZ0cchxovPQaSmk8z1zunRRFAf8tLxf1OyRNOZ9al1Vgw6-PNmLrCQjmxXHYzUr7VR4rSNJOvW-CmxtNza3GmJ2Z4E5DnxD9Kd2Hp2PVI5JS-5HtVzdOj5Kahw6mbu6341zYfe-xvI4bGcwxaR8OpkFPZ8-OjG-MHPWnFBqpaNo6GKW4vk-6_EKZuk2IDJsFpUV8v-gLdaIAwffcv-whxCj6H5e9ITWIShcKmmYZSqcW44fGV2b6IKNKeo8sEbrHA")};

    const int m_waitTime {5000};

public:
    AuthenticationTest() = default;
    ~AuthenticationTest() override = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testServerStarted();
    void testSendData();
    void testReceiveData();
    void testCode();
};

void AuthenticationTest::initTestCase()
{
    m_authService.setClientId(QStringLiteral("f8023ea988e548df83fb42b5ce1e1a20"));
    m_authService.setClientSecret(QStringLiteral("5cf01313067d4391a9a8643add01307a"));

    m_authService.startAuthenticationService();
}

void AuthenticationTest::cleanupTestCase()
{
    m_authService.endAuthenticationService();
}

void AuthenticationTest::testServerStarted()
{
    m_client.connectToHost(QStringLiteral("localhost"), TcpHttpConst::tcpServerPort);
    m_client.waitForConnected(m_waitTime);
    QVERIFY(m_client.state() == QAbstractSocket::ConnectedState);
}

void AuthenticationTest::testSendData()
{
    const QString data(QStringLiteral("GET /?code=%1 HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) QtWebEngine/5.15.2 Chrome/83.0.4103.122 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\n\r\n").arg(m_code));
    m_client.write(data.toUtf8());
    QVERIFY(m_client.waitForBytesWritten(m_waitTime) > 0);
}

void AuthenticationTest::testReceiveData()
{
    QSignalSpy spynewConnection(&m_authService, &AuthenticationService::newConnection);
    QSignalSpy spyParseHttp(&m_authService, &AuthenticationService::httpParsed);
    QSignalSpy spyCode(&m_authService, &AuthenticationService::authorizationCodeChanged);

    spynewConnection.wait(m_waitTime);
    QCOMPARE(spynewConnection.count(), 1);

    spyParseHttp.wait(m_waitTime);
    QCOMPARE(spyParseHttp.count(), 1);

    spyCode.wait(m_waitTime);
    QCOMPARE(spyCode.count(), 1);

    QVERIFY(m_client.readAll().contains("200 OK"));
}

void AuthenticationTest::testCode()
{
    QCOMPARE(m_authService.getAuthorizationCode(), m_code);
}


QTEST_MAIN(AuthenticationTest)
#include "tst_authenticationtest.moc"
