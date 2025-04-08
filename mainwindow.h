#ifndef MAINWINDOW_H

#define MAINWINDOW_H


#include <QObject>

#include <QNetworkAccessManager>

#include <QNetworkReply>

#include <QList>

#include <QVariant>


class MainWindow : public QObject {

    Q_OBJECT

    // Właściwość do przechowywania listy stacji (udostępniana w QML)

    Q_PROPERTY(QVariantList stations READ stations NOTIFY stationsChanged)

    // Właściwość do przechowywania statusu (np. "Ładowanie danych...")

    Q_PROPERTY(QString status READ status NOTIFY statusChanged)


public:

    explicit MainWindow(QObject *parent = nullptr);

    ~MainWindow();


    // Gettery dla właściwości

    QVariantList stations() const { return m_stations; }

    QString status() const { return m_status; }


public slots:

    // Funkcja do pobierania danych z API

    void fetchStations();


signals:

    // Sygnały informujące o zmianie danych

    void stationsChanged();

    void statusChanged();


private slots:

    // Slot do obsługi odpowiedzi z API

    void onNetworkReply(QNetworkReply *reply);


private:

    QNetworkAccessManager *m_networkManager;

    QVariantList m_stations; // Lista stacji w formacie QVariantList (dla QML)

    QString m_status;        // Status ładowania

};


#endif // MAINWINDOW_H
