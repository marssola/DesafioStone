#include "authenticationservice.h"
#include "authenticationconsts.h"

#include <QCoreApplication>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

AuthenticationService::AuthenticationService(QObject *parent) :
    QObject(parent),
    m_authenticated(false),
    m_clientId((QStringLiteral(""))),
    m_clientSecret(QStringLiteral("")),
    m_authorizationCode(QStringLiteral("")),
    m_userToken(QStringLiteral("")),
    m_authBrowser(nullptr),
    m_tcpServer(nullptr)
{}

AuthenticationService::~AuthenticationService()
{
    endAuthenticationService();
}

bool AuthenticationService::needAuthentication()
{
    m_authenticated = (QDateTime::currentDateTime() < m_tokenExpires) && !m_userToken.isEmpty();
    if (m_authenticated)
        emit authenticated();
    return !m_authenticated;
}

void AuthenticationService::startAuthenticationService()
{
    m_tcpServer = std::make_unique<QTcpServer>();

    connect(m_tcpServer.get(), &QTcpServer::newConnection, this, &AuthenticationService::parseHttpRequest);
    if (!m_tcpServer->listen(QHostAddress::Any, TcpHttpConst::tcpServerPort)) {
        qCritical() << "Error trying start server" << m_tcpServer->errorString();
        return;
    }

    m_authBrowser = std::make_unique<AuthenticationGui>();
    m_authBrowser->moveToThread(&m_threadAuthBrowser);
    connect(&m_threadAuthBrowser, &QThread::started, this, [&]() { m_authBrowser->openBrowser(getSpotifyAuthUrl()); });
    m_threadAuthBrowser.start();
}

void AuthenticationService::endAuthenticationService()
{
    if (m_tcpServer != nullptr)
        m_tcpServer->close();
    m_tcpServer.reset(nullptr);
}

void AuthenticationService::getSpotifyToken()
{
    if (m_authorizationCode.isEmpty()) {
        qCritical() << "Error: Authorization Code is not defined";
        return;
    }

    qDebug() << "Get Spotify Token";

    QNetworkAccessManager networkManager;
    QNetworkRequest request(QStringLiteral("https://accounts.spotify.com/api/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QStringLiteral("%1:%2").arg(m_clientId, m_clientSecret).toUtf8().toBase64());

    const QString data(QStringLiteral("grant_type=authorization_code&code=%1&redirect_uri=%2").arg(m_authorizationCode, TcpHttpConst::redirectUrl));

    QEventLoop eventLoop;
    connect(&networkManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    auto *reply = networkManager.post(request, data.toUtf8());
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError)
        qCritical() << "Error trying request" << reply->error() << reply->errorString();

    try {
        QJsonParseError parseError{};
        auto json = QJsonDocument::fromJson(reply->readAll(), &parseError);
        if (parseError.error != QJsonParseError::NoError)
            qCritical() << "Error trying to parse JSON" << parseError.errorString();

        const auto &obj = json.object();
        const auto fieldAccessToken(QStringLiteral("access_token"));
        const auto fieldExpiresIn(QStringLiteral("expires_in"));

        if (obj.contains(fieldAccessToken) && obj.contains(fieldExpiresIn)) {
            setUserToken(obj.value(fieldAccessToken).toString());;
            setTokenExpires(QDateTime::currentDateTime().addSecs(obj.value(fieldExpiresIn).toInt()));

            m_authenticated = true;
            emit authenticationChanged();
            emit authenticated();
            return;
        }
    }  catch (...) {
        qCritical() << "Error trying read message";
    }

    emit authenticationFailed();
}

void AuthenticationService::parseHttpRequest()
{
    emit newConnection();

    auto *socket = m_tcpServer->nextPendingConnection();
    if (socket == nullptr) {
        qCritical() << "Server error: Invalid pending connection";
        emit httpParsed();
        return;
    }

    socket->waitForReadyRead();
    auto response = QString(socket->readAll());

    if (!response.contains(TcpHttpConst::paramCode)) {
        socket->write(QStringLiteral("HTTP/1.1 400 Bad Request\r\n\r\nBad Request").toUtf8());
        socket->waitForBytesWritten();
        emit authenticationFailed();
        socket->flush();
        socket->close();

        emit httpParsed();
        return;
    }

    // Parse http request
    constexpr auto posRight = 6;
    auto strLeft = response.left(response.indexOf(TcpHttpConst::headerHttp));

    // Send response Ok && close socket
    socket->write(QStringLiteral("HTTP/1.1 200 OK\r\n\r\nOk").toUtf8());
    socket->flush();
    socket->waitForBytesWritten();
    socket->close();
    emit httpParsed();

    m_authBrowser.reset(nullptr);
    m_threadAuthBrowser.quit();

    setAuthorizationCode(strLeft.right(strLeft.length() - strLeft.indexOf(TcpHttpConst::paramCode) - posRight).trimmed());
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

QDateTime AuthenticationService::getTokenExpires() const
{
    return m_tokenExpires;
}

void AuthenticationService::setTokenExpires(const QDateTime &tokenExpires)
{
    if (m_tokenExpires == tokenExpires)
        return;

    m_tokenExpires = tokenExpires;
    emit tokenExpiresChanged();
}

QString AuthenticationService::getUserToken() const
{
    return m_userToken;
}

void AuthenticationService::setUserToken(const QString &userToken)
{
    if (m_userToken == userToken)
        return;

    m_userToken = userToken;
    emit userTokenChanged();
}

QString AuthenticationService::getAuthorizationCode() const
{
    return m_authorizationCode;
}

void AuthenticationService::setAuthorizationCode(const QString &authorizationCode)
{
    if (m_authorizationCode == authorizationCode)
        return;

    m_authorizationCode = authorizationCode;
    emit authorizationCodeChanged();
}

QString AuthenticationService::getClientSecret() const
{
    return m_clientSecret;
}

void AuthenticationService::setClientSecret(const QString &clientSecret)
{
    if (m_clientSecret == clientSecret)
        return;

    m_clientSecret = clientSecret;
    emit clientSecretChanged();
}

QString AuthenticationService::getClientId() const
{
    return m_clientId;
}

void AuthenticationService::setClientId(const QString &clientId)
{
    if (m_clientId == clientId)
        return;

    m_clientId = clientId;
    emit clientIdChanged();
}
