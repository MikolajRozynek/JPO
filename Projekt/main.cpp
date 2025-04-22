#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    try {
        // Usuwamy przestarzałe ustawienie, które jest teraz domyślnie włączone
        // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);

        // Utworzenie instancji MainWindow
        MainWindow mainWindow;

        QQmlApplicationEngine engine;

        // Udostępnienie MainWindow w QML jako "mainWindow"
        engine.rootContext()->setContextProperty("mainWindow", &mainWindow);

        // Ustawienie ścieżki do pliku QML
        const QUrl url(QStringLiteral("qrc:/main.qml"));

        // Zabezpieczenie przed błędami podczas ładowania QML
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
                             if (!obj && url == objUrl) {
                                 qDebug() << "Błąd podczas ładowania QML!";
                                 QCoreApplication::exit(-1);
                             } else if (obj && url == objUrl) {
                                 qDebug() << "QML załadowany pomyślnie.";
                             }
                         }, Qt::QueuedConnection);

        // Próba załadowania pliku QML
        engine.load(url);

        // Jeśli nie zostały utworzone żadne obiekty QML, zwróć błąd
        if (engine.rootObjects().isEmpty()) {
            qDebug() << "Nie udało się załadować QML!";
            return -1;
        }

        return app.exec();
    } catch (const std::exception& e) {
        qDebug() << "Złapano wyjątek:" << e.what();
        return -1;
    } catch (...) {
        qDebug() << "Złapano nieznany wyjątek!";
        return -1;
    }
}
