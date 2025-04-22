#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QVariant>
#include <QMap>

class MainWindow : public QObject {
    Q_OBJECT
    // Właściwość do przechowywania listy stacji (udostępniana w QML)
    Q_PROPERTY(QVariantList stations READ stations NOTIFY stationsChanged)
    // Właściwość do przechowywania statusu (np. "Ładowanie danych...")
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    // Właściwość do przechowywania nazwy miasta
    Q_PROPERTY(QString cityName READ cityName WRITE setCityName NOTIFY cityNameChanged)
    // Właściwość do przechowywania danych pomiarowych
    Q_PROPERTY(QVariantList sensorData READ sensorData NOTIFY sensorDataChanged)
    // Właściwość do przechowywania historii pomiarów dla wybranego czujnika
    Q_PROPERTY(QVariantList sensorHistory READ sensorHistory NOTIFY sensorHistoryChanged)
    // Właściwość do przechowywania informacji o aktualnie wybranym czujniku
    Q_PROPERTY(QVariantMap selectedSensor READ selectedSensor NOTIFY selectedSensorChanged)

    //Właściwość do przechwytywania informacji o aktualnym stanie powietrza
    Q_PROPERTY(QString airQualityStatus READ airQualityStatus NOTIFY airQualityStatusChanged)

    // Dodaj to do sekcji Q_PROPERTY:
    Q_PROPERTY(int selectedStationId READ selectedStationId WRITE setSelectedStationId NOTIFY selectedStationIdChanged)

    // Dodaj to do sekcji public:
    int selectedStationId() const { return m_selectedStationId; }
    void setSelectedStationId(int id) {
        if (m_selectedStationId != id) {
            m_selectedStationId = id;
            emit selectedStationIdChanged();
        }
    }

public:
    explicit MainWindow(QObject *parent = nullptr);
    ~MainWindow();

    // Gettery dla właściwości
    QVariantList stations() const { return m_stations; }
    QString status() const { return m_status; }
    QString cityName() const { return m_cityName; }
    QVariantList sensorData() const { return m_sensorData; }
    QVariantList sensorHistory() const { return m_sensorHistory; }
    QVariantMap selectedSensor() const { return m_selectedSensor; }
    //stan powietrza
    QString airQualityStatus() const { return m_airQualityStatus; }

    // Setter dla miasta
    void setCityName(const QString &cityName);

public slots:
    // Funkcja do pobierania danych z API
    void fetchStations();
    // Funkcja do pobierania danych szczegółowych stacji
    void fetchStationDetails(int stationId);
    // Funkcja do pobierania danych z czujników
    void fetchSensorData(int stationId);
    // Funkcja do pobierania historii pomiarów dla wybranego czujnika
    Q_INVOKABLE void fetchSensorHistory(int sensorId, const QString &paramName, const QString &paramFormula);
    // Funkcja do zapisywania danych pomiarowych do pliku JSON
    Q_INVOKABLE void saveSensorDataToJson(const QString &cityName, int stationId);

    Q_INVOKABLE void fetchAirQualityForStation(int stationId);

signals:
    // Sygnały informujące o zmianie danych
    void stationsChanged();
    void statusChanged();
    void cityNameChanged();
    void sensorDataChanged();
    void sensorHistoryChanged();
    void selectedSensorChanged();

    void selectedStationIdChanged();
    //stan powietrza
    void airQualityStatusChanged();

private slots:
    // Slot do obsługi odpowiedzi z API
    void onNetworkReply(QNetworkReply *reply);
    // Metody do obsługi różnych typów odpowiedzi
    void handleStationDetailsReply(QNetworkReply *reply);
    void handleSensorDataReply(QNetworkReply *reply);
    void handleStationListReply(QNetworkReply *reply);
    void handleSensorHistoryReply(QNetworkReply *reply);
    void handleAirQualityResponse(QNetworkReply *reply);
    void fetchSensorDataForParam(int sensorId);
    void fetchAirQualityStatus(int stationId);

    // Nowa metoda do finalizacji i filtrowania danych z czujników
    void finalizeAndFilterSensorData();

private:
    QNetworkAccessManager *m_networkManager;
    QVariantList m_stations;     // Lista stacji w formacie QVariantList (dla QML)
    QString m_status;            // Status ładowania
    QString m_cityName;          // Nazwa miasta
    QVariantList m_sensorData;   // Dane pomiarowe
    QVariantList m_sensorHistory; // Historia pomiarów dla wybranego czujnika
    QVariantMap m_selectedSensor; // Informacje o wybranym czujniku

    int m_selectedStationId; // ID wybranej stacji

    // Nowe pola do obsługi asynchronicznego pobierania danych
    QMap<int, QVariant> m_tempSensorMap;  // Tymczasowa mapa do zbierania danych z czujników
    int m_pendingSensorRequests;          // Licznik oczekujących żądań


    QString m_airQualityStatus; //Stan powietrza

    // Enum do śledzenia typu zapytania
    enum RequestType {
        StationList,
        StationDetails,
        SensorData,
        SensorHistory,
        AirQualityIndex
    };

    RequestType m_currentRequestType;
};

#endif // MAINWINDOW_H
