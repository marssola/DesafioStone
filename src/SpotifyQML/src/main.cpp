#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if ((obj == nullptr) && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QIcon::setThemeSearchPaths({":/icons"});
    QIcon::setThemeName(QStringLiteral("material-round"));

    engine.addImportPath(QStringLiteral("../SpotQt-plugin"));
    engine.addImportPath(QStringLiteral("%1/plugins").arg(ROOT_PATH));
    engine.load(url);

    return QGuiApplication::exec();
}
