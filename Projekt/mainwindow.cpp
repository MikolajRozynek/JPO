#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>

MainWindow::MainWindow(QObject *parent)
    : QObject(parent),
    m_networkManager(new QNetworkAccessManager(this)),
    m_currentRequestType(StationList) {

    // Domyślna wartość dla nazwy miasta - pusta
    m_cityName = "";

    // Domyślny status
    m_status = "Wprowadź nazwę miasta i naciśnij Enter";
    emit statusChanged();

    // Inicjalizacja ID wybranej stacji
    m_selectedStationId = 0;

    // Połączenie sygnału finished z QNetworkAccessManager do slota onNetworkReply
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
}

MainWindow::~MainWindow() {
    delete m_networkManager;
}

void MainWindow::handleAirQualityResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        m_airQualityStatus = "Nie można pobrać informacji o jakości powietrza";
        emit airQualityStatusChanged();
        return;
    }

    // Parsowanie odpowiedzi JSON
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject dataObject = doc.object();

    // Sprawdzamy, czy otrzymaliśmy poprawne dane
    if (dataObject.isEmpty()) {
        m_airQualityStatus = "Brak danych o jakości powietrza";
        emit airQualityStatusChanged();
        return;
    }

    // Pobieramy ogólny indeks jakości powietrza
    QJsonValue stIndexLevel = dataObject["stIndexLevel"];
    QString indexLevel;

    if (!stIndexLevel.isNull() && stIndexLevel.isObject()) {
        QJsonObject indexObj = stIndexLevel.toObject();
        indexLevel = indexObj["indexLevelName"].toString();
    } else {
        // Alternatywnie, możemy spróbować pobrać indeks PM10 jako przykład
        QJsonValue pm10IndexLevel = dataObject["pm10IndexLevel"];
        if (!pm10IndexLevel.isNull() && pm10IndexLevel.isObject()) {
            QJsonObject indexObj = pm10IndexLevel.toObject();
            indexLevel = indexObj["indexLevelName"].toString();
        }
    }

    if (!indexLevel.isEmpty()) {
        m_airQualityStatus = "Jakość powietrza: " + indexLevel;
    } else {
        m_airQualityStatus = "Brak informacji o jakości powietrza";
    }

    emit airQualityStatusChanged();
}

void MainWindow::fetchAirQualityStatus(int stationId) {
    // Debugowanie - sprawdzamy ID stacji
    qDebug() << "Pobieranie jakości powietrza dla stacji ID: " << stationId;

    // Resetujemy poprzedni status jakości powietrza
    m_airQualityStatus = "";
    emit airQualityStatusChanged();

    // Jeśli ID stacji jest nieprawidłowe, kończymy
    if (stationId <= 0) {
        m_airQualityStatus = "Nie można pobrać danych o jakości powietrza (brak ID stacji)";
        emit airQualityStatusChanged();
        return;
    }

    // Wysłanie żądania GET do API GIOŚ dla indeksu jakości powietrza
    QUrl url(QString("https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/%1").arg(stationId));
    QNetworkRequest request(url);

    // m_status = "Pobieranie indeksu jakości powietrza...";
    m_status = "Indeksu jakości powietrza pobrany";
    emit statusChanged();

    m_currentRequestType = AirQualityIndex;
    m_networkManager->get(request);
}

void MainWindow::setCityName(const QString &cityName) {
    // Ustawiamy nową nazwę miasta bez sprawdzania czy jest taka sama
    m_cityName = cityName;
    emit cityNameChanged();

    // Po zmianie miasta, zawsze pobieramy stacje, nawet jeśli nazwa nie zmieniła się
    fetchStations();
}

void MainWindow::fetchStations() {
    // Wysłanie żądania GET do API GIOŚ
    QUrl url("https://api.gios.gov.pl/pjp-api/rest/station/findAll");
    QNetworkRequest request(url);

    qDebug() << "Wyszukiwanie stacji dla miasta: " << m_cityName;

    m_status = "Ładowanie danych stacji...";
    emit statusChanged();

    m_currentRequestType = StationList;
    m_networkManager->get(request);
}

void MainWindow::fetchStationDetails(int stationId) {
    // Wysłanie żądania GET do API GIOŚ dla szczegółów stacji
    QUrl url(QString("https://api.gios.gov.pl/pjp-api/rest/station/sensors/%1").arg(stationId));
    QNetworkRequest request(url);

    m_status = "Ładowanie szczegółów stacji...";
    emit statusChanged();

    m_currentRequestType = StationDetails;
    m_networkManager->get(request);
}

void MainWindow::fetchSensorData(int stationId) {
    // Najpierw pobieramy listę czujników dla danej stacji
    fetchStationDetails(stationId);
}

void MainWindow::fetchSensorHistory(int sensorId, const QString &paramName, const QString &paramFormula) {
    // Zapisujemy informacje o wybranym czujniku
    m_selectedSensor.clear();
    m_selectedSensor["id"] = sensorId;
    m_selectedSensor["param"] = paramName;
    m_selectedSensor["paramFormula"] = paramFormula;
    emit selectedSensorChanged();

    // Czyszczenie historii
    m_sensorHistory.clear();
    emit sensorHistoryChanged();

    // Wysłanie żądania GET do API GIOŚ dla historii danych z czujnika
    QUrl url(QString("https://api.gios.gov.pl/pjp-api/rest/data/getData/%1").arg(sensorId));
    QNetworkRequest request(url);

    m_status = QString("Ładowanie historii pomiarów dla: %1 (%2)...").arg(paramName).arg(paramFormula);
    emit statusChanged();

    m_currentRequestType = SensorHistory;
    m_networkManager->get(request);

    // Pobierz także jakość powietrza dla stacji jeśli mamy ID stacji
    if (m_selectedStationId > 0) {
        // Uruchamiamy po krótkim opóźnieniu, aby nie pomieszać żądań
        QTimer::singleShot(100, this, [this]() {
            fetchAirQualityStatus(m_selectedStationId);
        });
    }
}

void MainWindow::onNetworkReply(QNetworkReply *reply) {
    // Obsługujemy różne typy zapytań
    switch (m_currentRequestType) {
    case StationList:
        handleStationListReply(reply);
        break;
    case StationDetails:
        handleStationDetailsReply(reply);
        break;
    case SensorData:
        handleSensorDataReply(reply);
        break;
    case SensorHistory:
        handleSensorHistoryReply(reply);
        break;
    case AirQualityIndex: // Dodaj ten case
        handleAirQualityResponse(reply);
        break;
    }

    reply->deleteLater();
}

void MainWindow::handleStationListReply(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        m_status = "Błąd podczas pobierania danych: " + reply->errorString();
        emit statusChanged();
        return;
    }

    // Parsowanie odpowiedzi JSON
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonArray stationsArray = doc.array();

    // Czyszczenie poprzednich danych
    m_stations.clear();
    bool found = false;

    // Przeszukiwanie stacji w poszukiwaniu podanego miasta
    for (const QJsonValue &value : stationsArray) {
        QJsonObject station = value.toObject();
        QJsonObject city = station["city"].toObject();
        QString cityName = city["name"].toString();

        if (cityName.toLower() == m_cityName.toLower()) {
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
        m_status = "Nie znaleziono stacji w mieście: " + m_cityName;
    } else {
        m_status = "Znaleziono stacje w mieście: " + m_cityName;
    }

    emit stationsChanged();
    emit statusChanged();
}

void MainWindow::handleStationDetailsReply(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        m_status = "Błąd podczas pobierania szczegółów stacji: " + reply->errorString();
        emit statusChanged();
        return;
    }

    // Parsowanie odpowiedzi JSON
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonArray sensorsArray = doc.array();

    // Czyszczenie poprzednich danych
    m_sensorData.clear();
    m_pendingSensorRequests = sensorsArray.size();

    if (m_pendingSensorRequests == 0) {
        m_status = "Brak dostępnych czujników dla tej stacji";
        emit statusChanged();
        return;
    }

    // Przetwarzanie danych czujników
    for (const QJsonValue &value : sensorsArray) {
        QJsonObject sensor = value.toObject();
        int sensorId = sensor["id"].toInt();

        // Tworzymy tymczasowy obiekt z podstawowymi danymi czujnika
        QVariantMap sensorData;
        sensorData["id"] = sensorId;
        sensorData["param"] = sensor["param"].toObject()["paramName"].toString();
        sensorData["paramCode"] = sensor["param"].toObject()["paramCode"].toString();
        sensorData["paramFormula"] = sensor["param"].toObject()["paramFormula"].toString();

        // Zapisujemy dane w tymczasowej mapie, by później połączyć je z wartościami
        m_tempSensorMap.insert(sensorId, sensorData);

        // Pobieramy dane pomiarowe dla każdego czujnika
        fetchSensorDataForParam(sensorId);
    }

    m_status = "Ładowanie danych pomiarowych...";
    emit statusChanged();
}

void MainWindow::fetchSensorDataForParam(int sensorId) {
    // Wysłanie żądania GET do API GIOŚ dla danych z czujnika
    QUrl url(QString("https://api.gios.gov.pl/pjp-api/rest/data/getData/%1").arg(sensorId));
    QNetworkRequest request(url);

    m_currentRequestType = SensorData;
    m_networkManager->get(request);
}

void MainWindow::fetchAirQualityForStation(int stationId) {
    if (stationId > 0) {
        // Zapisz ID stacji
        m_selectedStationId = stationId;
        emit selectedStationIdChanged();

        // Pobierz jakość powietrza
        fetchAirQualityStatus(stationId);
    }
}

void MainWindow::handleSensorDataReply(QNetworkReply *reply) {
    // Zmniejszamy licznik oczekujących zapytań
    m_pendingSensorRequests--;

    if (reply->error() != QNetworkReply::NoError) {
        // Nawet w przypadku błędu sprawdzamy, czy to było ostatnie żądanie
        if (m_pendingSensorRequests == 0) {
            finalizeAndFilterSensorData();
        }
        return;
    }

    // Parsowanie odpowiedzi JSON
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject dataObject = doc.object();

    // Sprawdzamy czy mamy jakieś wartości
    QJsonArray values = dataObject["values"].toArray();
    if (values.isEmpty()) {
        // Jeśli to ostatnie żądanie, finalizujemy dane
        if (m_pendingSensorRequests == 0) {
            finalizeAndFilterSensorData();
        }
        return;
    }

    // Pobieramy identyfikator czujnika z adresu URL
    QString path = reply->request().url().path();
    int lastSlash = path.lastIndexOf('/');
    int sensorId = path.mid(lastSlash + 1).toInt();

    // Pobieramy dane z pierwszego elementu tablicy
    QJsonObject sensorReading = values[0].toObject();
    double value = sensorReading["value"].toDouble(-1); // Używamy -1 jako wartości dla NULL
    QString date = sensorReading["date"].toString();

    // Jeśli nie mamy wartości lub jest NULL, pomijamy ten czujnik
    if (value < 0 || date.isEmpty()) {
        // Jeśli to ostatnie żądanie, finalizujemy dane
        if (m_pendingSensorRequests == 0) {
            finalizeAndFilterSensorData();
        }
        return;
    }

    // Pobieramy wcześniej zapisane dane czujnika
    if (m_tempSensorMap.contains(sensorId)) {
        QVariantMap sensorData = m_tempSensorMap[sensorId].toMap();

        // Dodajemy dane pomiarowe
        sensorData["value"] = value;
        sensorData["date"] = date;
        sensorData["unit"] = dataObject["key"].toString();

        // Aktualizujemy dane w tymczasowej mapie
        m_tempSensorMap[sensorId] = sensorData;
    }

    // Jeśli to ostatnie żądanie, finalizujemy dane
    if (m_pendingSensorRequests == 0) {
        finalizeAndFilterSensorData();
    }
}

void MainWindow::handleSensorHistoryReply(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        m_status = "Błąd podczas pobierania historii pomiarów: " + reply->errorString();
        emit statusChanged();
        return;
    }

    // Parsowanie odpowiedzi JSON
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject dataObject = doc.object();

    // Pobieramy jednostkę miary
    QString unit = dataObject["key"].toString();

    // Pobieramy wszystkie wartości historyczne
    QJsonArray values = dataObject["values"].toArray();

    // Czyszczenie poprzednich danych
    m_sensorHistory.clear();

    // Przetwarzanie wartości historycznych - od najnowszych do najstarszych
    for (const QJsonValue &value : values) {
        QJsonObject reading = value.toObject();

        // Sprawdzamy czy wartość nie jest pusta (null)
        if (reading["value"].isNull()) {
            continue;
        }

        double readingValue = reading["value"].toDouble(-1);
        QString date = reading["date"].toString();

        // Jeśli mamy poprawną wartość i datę, dodajemy do historii
        if (readingValue >= 0 && !date.isEmpty()) {
            QVariantMap historyItem;
            historyItem["value"] = readingValue;
            historyItem["date"] = date;
            historyItem["unit"] = unit;

            m_sensorHistory.append(historyItem);
        }
    }

    // Aktualizacja statusu
    if (m_sensorHistory.isEmpty()) {
        m_status = "Brak danych historycznych dla wybranego czujnika";
    } else {
        m_status = QString("Załadowano %1 pomiarów historycznych").arg(m_sensorHistory.size());
    }

    // Pobranie jakości powietrza dla stacji (jeśli jeszcze nie pobrano)
    if (m_airQualityStatus.isEmpty() && m_selectedStationId > 0) {
        fetchAirQualityStatus(m_selectedStationId);
    }

    emit sensorHistoryChanged();
    emit statusChanged();
}

void MainWindow::finalizeAndFilterSensorData() {
    // Czyszczenie listy danych czujników
    m_sensorData.clear();

    // Przetwarzamy wszystkie zebrane dane
    bool dataFound = false;

    QMapIterator<int, QVariant> it(m_tempSensorMap);
    while (it.hasNext()) {
        it.next();
        QVariantMap sensorData = it.value().toMap();

        // Dodajemy tylko te czujniki, które mają wartość pomiarową i datę
        if (sensorData.contains("value") && sensorData.contains("date")) {
            m_sensorData.append(sensorData);
            dataFound = true;
        }
    }

    // Aktualizacja statusu
    if (dataFound) {
        m_status = "Załadowano dane pomiarowe";
    } else {
        m_status = "Brak dostępnych danych pomiarowych dla tej stacji";
    }

    // Czyścimy tymczasową mapę
    m_tempSensorMap.clear();

    // Informujemy o zmianach
    emit sensorDataChanged();
    emit statusChanged();
}

void MainWindow::saveSensorDataToJson(const QString &cityName, int stationId) {
    // Sprawdzamy, czy mamy dane historyczne do zapisania
    if (m_sensorHistory.isEmpty()) {
        m_status = "Brak danych do zapisania";
        emit statusChanged();
        return;
    }

    // Tworzymy główny obiekt JSON
    QJsonObject jsonData;

    // Dodajemy informacje o stacji i czujniku
    jsonData["city"] = cityName;
    jsonData["stationId"] = stationId;
    jsonData["paramName"] = m_selectedSensor["param"].toString();
    jsonData["paramFormula"] = m_selectedSensor["paramFormula"].toString();

    // Tworzymy tablicę dla pomiarów
    QJsonArray measurements;

    // Dodajemy każdy pomiar do tablicy
    for (const QVariant &measurement : m_sensorHistory) {
        QVariantMap measurementMap = measurement.toMap();

        QJsonObject measurementObj;
        measurementObj["date"] = measurementMap["date"].toString();
        measurementObj["value"] = measurementMap["value"].toDouble();
        measurementObj["unit"] = measurementMap["unit"].toString();

        measurements.append(measurementObj);
    }

    // Dodajemy tablicę pomiarów do głównego obiektu
    jsonData["measurements"] = measurements;

    // Tworzymy dokument JSON
    QJsonDocument document(jsonData);

    // Tworzymy katalog docelowy, jeśli nie istnieje
    QString saveDir = "C:/Users/User/AppData/Local/stacje_pomiarowe";
    QDir dir(saveDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Generujemy nazwę pliku w formacie: Miasto_DataZapisu_NumerStacji.json
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString saveDate = currentDateTime.toString("yyyyMMdd_HHmmss");
    QString fileName = QString("%1_%2_%3.json").arg(cityName).arg(saveDate).arg(stationId);

    // Pełna ścieżka do pliku
    QString filePath = saveDir + "/" + fileName;

    // Otwieramy plik do zapisu
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        m_status = "Błąd podczas zapisywania pliku: " + file.errorString();
        emit statusChanged();
        return;
    }

    // Zapisujemy dane do pliku
    file.write(document.toJson(QJsonDocument::Indented)); // Indented dla czytelności
    file.close();

    // Aktualizujemy status
    m_status = "Dane zapisane do pliku: " + fileName;
    emit statusChanged();
}


