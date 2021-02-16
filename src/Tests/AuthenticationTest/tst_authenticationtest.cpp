#include <QtTest>
#include <QCoreApplication>
#include <QTcpSocket>

#include <authentication/authenticationservice.h>
#include <authentication/authenticationconsts.h>

// add necessary includes here

class AuthenticationTest : public QObject
{
    Q_OBJECT
    bool m_needAuthenticate{false};
    AuthenticationService m_authService;

public:
    AuthenticationTest();
    ~AuthenticationTest() override = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testNeedAuthenticate();
    void testParseResponseHttp();
};

AuthenticationTest::AuthenticationTest()
{
    connect(&m_authService, &AuthenticationService::authenticationFailed, this, []() { qCritical() << "Authentication failed"; });
}

void AuthenticationTest::initTestCase()
{
    m_authService.setClientId(QStringLiteral("f8023ea988e548df83fb42b5ce1e1a20"));
    m_authService.setClientSecret(QStringLiteral("5cf01313067d4391a9a8643add01307a"));
}

void AuthenticationTest::cleanupTestCase()
{
    m_authService.endAuthenticationService();
}

void AuthenticationTest::testNeedAuthenticate()
{
    m_needAuthenticate = m_authService.needToAuthenticate();
//    if (m_needAuthenticate)
//        m_authService.startAuthenticationService();
    QVERIFY(m_needAuthenticate == true);
}

void AuthenticationTest::testParseResponseHttp()
{
    constexpr auto waitTime = 3000;

    QTcpSocket socket;
    socket.connectToHost(QHostAddress(QStringLiteral("127.0.0.1")), TcpHttpConst::tcpServerPort);
    if (socket.waitForConnected(waitTime)) {
        const QString data(QStringLiteral("GET /?code=AQBwG7BRKApsdF5BMCnAU2UaQLCEg725Gfk4elQFRN4V51o8o4xsxFcaZXkis5kFfvmjL1GbxPmT-ZMYlFv0_XrlCnL8uRNGwu2L1-pPFx3BnaHwxEr8AIYfUK01lt9a4IUWtqQsjv62_vcCjrD47uRN7Y0AWU4avFl0orJ0IOpQxCHsIx-y-LRk5QLVA5tksH0KMFGmWRJQ4DBvh7n1h5WZUZWxWDdGsjwq6nnuZzDdRVdakWuoqA7Zd4taSDV7hoDi2HQxywdx0dIEJOhiKILyd879k0AZD9KSdUgQnPG6l27ljN2Y6uDK5woWKsO4OiF7noxEPngTVFw7U2227LguZOjwbtxeX0SBXOkqGJuwPi-hgpbV5JZ0cchxovPQaSmk8z1zunRRFAf8tLxf1OyRNOZ9al1Vgw6-PNmLrCQjmxXHYzUr7VR4rSNJOvW-CmxtNza3GmJ2Z4E5DnxD9Kd2Hp2PVI5JS-5HtVzdOj5Kahw6mbu6341zYfe-xvI4bGcwxaR8OpkFPZ8-OjG-MHPWnFBqpaNo6GKW4vk-6_EKZuk2IDJsFpUV8v-gLdaIAwffcv-whxCj6H5e9ITWIShcKmmYZSqcW44fGV2b6IKNKeo8sEbrHA HTTP/1.1\r\nHost: localhost:9876\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) QtWebEngine/5.15.2 Chrome/83.0.4103.122 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\n\r\n"));
        socket.write(data.toUtf8());
        socket.waitForBytesWritten(waitTime);

        socket.waitForReadyRead(waitTime);
        const auto response = socket.readAll();
        socket.close();

        if (response.contains("Bad Request")) {
            QVERIFY2(false, "Server: Bad Request");
            return;
        }

        QVERIFY(true);
        return;
    }

    QVERIFY2(false, "Server: Not connected");
}


QTEST_MAIN(AuthenticationTest)

#include "tst_authenticationtest.moc"
