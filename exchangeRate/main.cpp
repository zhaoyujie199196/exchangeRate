#include "mainwindow.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "exrmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    EXRManager manager;
    manager.init();
    QQuickView view;
    view.engine()->rootContext()->setContextProperty("EXRManager", &manager);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/Main.qml"));
    view.show();

    // manager.exec("2019-01-01", "2019-01-11", 3030);

    return a.exec();
}
