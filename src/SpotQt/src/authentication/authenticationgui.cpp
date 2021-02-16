#include "authenticationgui.h"

#include <QApplication>

AuthenticationGui::AuthenticationGui(QObject *parent) :
    QObject(parent)
{}

void AuthenticationGui::openBrowser(const QString &url)
{
    engine.load(QStringLiteral("qrc:/WebBrowser.qml"));

    auto listObjects = engine.rootObjects();
    if (!listObjects.isEmpty())
        QMetaObject::invokeMethod(engine.rootObjects().at(0), "loadUrl", Q_ARG(QVariant, url));

    qDebug() << "URL" << url;
}
