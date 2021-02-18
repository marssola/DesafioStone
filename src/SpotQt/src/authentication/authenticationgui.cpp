#include "authenticationgui.h"

AuthenticationGui::AuthenticationGui(QObject *parent) :
    QObject(parent),
    engine(nullptr)
{}

void AuthenticationGui::openBrowser(const QString &url)
{
    engine = std::make_unique<QQmlApplicationEngine>();
    engine->load(QStringLiteral("qrc:/WebBrowser.qml"));

    auto listObjects = engine->rootObjects();
    if (!listObjects.isEmpty())
        QMetaObject::invokeMethod(engine->rootObjects().at(0), "loadUrl", Q_ARG(QVariant, url));
}
