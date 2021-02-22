#include "authenticationgui.h"
#include <QDirIterator>
#include <QDebug>
#include <QDesktopServices>

AuthenticationGui::AuthenticationGui(QObject *parent) :
    QObject(parent),
    engine(nullptr)
{}

void AuthenticationGui::openBrowser(const QString &url)
{
#ifdef WIN32
    QDesktopServices::openUrl(QUrl(url));
#else
    engine = std::make_unique<QQmlApplicationEngine>();
    engine->load(QStringLiteral("qrc:/browser/WebBrowser.qml"));

    auto listObjects = engine->rootObjects();
    if (!listObjects.isEmpty())
        QMetaObject::invokeMethod(engine->rootObjects().at(0), "loadUrl", Q_ARG(QVariant, url));
#endif
}
