#include "mainwindow.h"

#include <QJsonDocument>

#include <QJsonArray>

#include <QJsonObject>


MainWindow::MainWindow(QObject *parent) : QObject(parent), m_networkManager(new QNetworkAccessManager(this)) {

    // Połączenie sygnału finished z naszym slotem

    connect(m_networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);

    m_status = "Ładowanie danych...";

    emit statusChanged();

}


MainWindow::~MainWindow() {

    delete m_networkManager;

}


void MainWindow::fetchStations() {

    // Wysłanie żądania GET do API GIOŚ

    QUrl url("https://api.gios.gov.pl/pjp-api/rest/station/findAll");

    QNetworkRequest request(url);

    m_networkManager->get(request);

}


void MainWindow::onNetworkReply(QNetworkReply *reply) {

    if (reply->error() != QNetworkReply::NoError) {

        m_status = "Błąd podczas pobierania danych: " + reply->errorString();

        emit statusChanged();

        reply->deleteLater();

        return;

    }


    // Parsowanie odpowiedzi JSON

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    QJsonArray stationsArray = doc.array();


    // Czyszczenie poprzednich danych

    m_stations.clear();

    bool found = false;


    // Przeszukiwanie stacji w poszukiwaniu Piły

    for (const QJsonValue &value : stationsArray) {

        QJsonObject station = value.toObject();

        QJsonObject city = station["city"].toObject();

        QString cityName = city["name"].toString();


        if (cityName == "Poznań") {

            found = true;

            QVariantMap stationData;

            stationData["stationId"] = station["id"].toInt();

            stationData["stationName"] = station["stationName"].toString();

            stationData["lat"] = station["gegrLat"].toString();

            stationData["lon"] = station["gegrLon"].toString();

            stationData["address"] = station["addressStreet"].toString();

            m_stations.append(stationData);

        }

    }


    // Aktualizacja statusu

    if (!found) {

        m_status = "Nie znaleziono stacji w Pile.";

    } else {

        m_status = "Znaleziono stacje w Pile:";

    }


    emit stationsChanged();

    emit statusChanged();


    reply->deleteLater();

}

