#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Controller con;

    con.run();

    return app.exec();
}
