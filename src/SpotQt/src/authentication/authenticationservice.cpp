#include "authenticationservice.h"
#include "authenticationconsts.h"

#include <QDebug>
#include <QUrl>

AuthenticationService::AuthenticationService(QObject *parent) :
    QObject(parent),
    m_authenticated(false),
    m_clientId((QStringLiteral(""))),
    m_clientSecret(QStringLiteral("")),
    m_authBrowser(nullptr),
    m_networkAccessManager(nullptr),
    m_tcpServer(nullptr)
{}

AuthenticationService::~AuthenticationService()
{
    endAuthenticationService();
}

bool AuthenticationService::needToAuthenticate() const
{
    return !m_authenticated;
}

void AuthenticationService::startAuthenticationService()
{
    m_networkAccessManager = std::make_unique<QNetworkAccessManager>();
    m_tcpServer = std::make_unique<QTcpServer>();

    connect(m_tcpServer.get(), &QTcpServer::newConnection, this, &AuthenticationService::parseHttpRequest);
    if (!m_tcpServer->listen(QHostAddress::Any, TcpHttpConst::tcpServerPort)) {
        qCritical() << "Error trying start server";
        return;
    }

//    m_authBrowser = std::make_unique<AuthenticationGui>();
//    m_authBrowser->moveToThread(&m_threadAuthBrowser);
//    connect(&m_threadAuthBrowser, &QThread::started, this, [&]() { m_authBrowser->openBrowser(getSpotifyAuthUrl()); });
//    m_threadAuthBrowser.start();
}

void AuthenticationService::endAuthenticationService()
{
    if (m_tcpServer != nullptr)
        m_tcpServer->close();
    m_networkAccessManager.reset(nullptr);
    m_tcpServer.reset(nullptr);
}

void AuthenticationService::parseHttpRequest()
{
    auto *socket = m_tcpServer->nextPendingConnection();
    socket->waitForReadyRead();
    auto response = QString(socket->readAll());

    if (!response.contains(TcpHttpConst::paramCode)) {
        socket->write(QStringLiteral("HTTP/1.1 400 Bad Request\r\n\r\nBad Request").toUtf8());
        socket->waitForBytesWritten();
        emit authenticationFailed();
        socket->flush();
        socket->close();
        return;
    }

    // Parse http request
    constexpr auto posRight = 6;
    auto strLeft = response.left(response.indexOf(TcpHttpConst::headerHttp));
    auto authenticationCode = strLeft.right(strLeft.length() - strLeft.indexOf(TcpHttpConst::paramCode) - posRight);

    // Send response Ok && close socket
    socket->write(QStringLiteral("HTTP/1.1 200 OK\r\n\r\nOk").toUtf8());
    socket->flush();
    socket->waitForBytesWritten();
    socket->close();

    m_authBrowser.reset(nullptr);
    m_threadAuthBrowser.quit();
}

QString AuthenticationService::getSpotifyAuthUrl()
{
    const QStringList scopes {
        "playlist-read-collaborative",
        "playlist-read-private",
        "playlist-modify-private",
        "playlist-modify-public",
        "user-follow-read",
        "user-follow-modify",
        "user-library-modify",
        "user-library-read",
        "user-modify-playback-state",
        "user-read-currently-playing",
        "user-read-playback-state",
        "user-read-private",
        "user-read-recently-played",
        "streaming",
        "user-read-email",
        "user-top-read"
    };

    return QStringLiteral("https://accounts.spotify.com/authorize?client_id=%1&response_type=code&redirect_uri=%2&scope=%3")
            .arg(m_clientId, TcpHttpConst::redirectUrl, scopes.join(QStringLiteral("%20")));
}

QString AuthenticationService::getClientSecret() const
{
    return m_clientSecret;
}

void AuthenticationService::setClientSecret(const QString &clientSecret)
{
    m_clientSecret = clientSecret;
}

QString AuthenticationService::getClientId() const
{
    return m_clientId;
}

void AuthenticationService::setClientId(const QString &clientId)
{
    m_clientId = clientId;
}
