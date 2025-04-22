import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: "Stacje Pomiarowe GIOŚ"
    color: "#f5f5f5" // Light background for the application

    // Właściwość do przechowywania aktualnego ekranu
    property int currentScreen: 0 // 0 - lista stacji, 1 - szczegóły stacji, 2 - historia pomiarów

    // Właściwości do przechowywania zakresu dat
    property date startDate: new Date()
    property date endDate: new Date()

    // Nasłuchiwanie zmiany ekranu, aby zresetować wykres
    onCurrentScreenChanged: {
        if (currentScreen === 2) {
            // Resetujemy wykres przy wejściu na ekran wykresu
            resetChart();
        }
    }

    // Funkcja do resetowania wykresu
    function resetChart() {
        if (dataCanvas) {
            dataCanvas.dataPoints = [];
            dataCanvas.minValue = 0;
            dataCanvas.maxValue = 100;
            dataCanvas.requestPaint();

            if (gridCanvas) {
                gridCanvas.requestPaint();
            }

            // Reset filtrowanych dat
            chartScreen.filteredDates = [];
            chartScreen.filteredData = [];

            // Reset statystyk
            chartScreen.lowestValue = null;
            chartScreen.lowestDate = null;
            chartScreen.highestValue = null;
            chartScreen.highestDate = null;
            chartScreen.averageValue = null;
            chartScreen.unit = "";

            // Usuwamy etykiety punktów
            clearPointLabels();
        }
    }

    // Funkcja do czyszczenia etykiet punktów
    function clearPointLabels() {
        var children = pointLabelsContainer ? pointLabelsContainer.children : [];
        for (var i = children.length - 1; i >= 0; i--) {
            children[i].destroy();
        }
    }

    // Nagłówek
    Rectangle {
        id: header
        width: parent.width
        height: 60
        color: "#4CAF50"

        Text {
            id: headerText
            anchors.centerIn: parent
            text: {
                if (currentScreen === 0) return "Stacje Pomiarowe GIOŚ";
                else if (currentScreen === 1) return "Szczegóły Stacji";
                else return "Wykres Pomiarów: " + mainWindow.selectedSensor.param + " (" + mainWindow.selectedSensor.paramFormula + ")";
            }
            color: "white"
            font.pixelSize: 20
            font.bold: true
        }

        // Przycisk powrotu
        Rectangle {
            visible: currentScreen > 0
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            width: 40
            height: 40
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: "←"
                font.pixelSize: 24
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // Powrót do poprzedniego ekranu
                    if (currentScreen === 2) currentScreen = 1;
                    else if (currentScreen === 1) currentScreen = 0;
                }
            }
        }
    }

    // Główna zawartość
    StackLayout {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: currentScreen

        // Ekran listy stacji
        Item {
            id: stationsScreen

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                // Pole wyszukiwania
                Rectangle {
                    width: parent.width
                    height: 50
                    color: "#f5f5f5"
                    border.color: "#ddd"
                    radius: 5

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 10

                        Text {
                            text: "Miasto:"
                            font.pixelSize: 16
                            Layout.alignment: Qt.AlignVCenter
                        }

                        TextField {
                            id: cityInput
                            Layout.fillWidth: true
                            placeholderText: "Wprowadź nazwę miasta..."
                            font.pixelSize: 16

                            onAccepted: {
                                mainWindow.cityName = text;
                                mainWindow.fetchStations(); // Dodajemy jawne wywołanie
                            }
                        }

                        Button {
                            text: "Szukaj"
                            onClicked: {
                                mainWindow.cityName = cityInput.text;
                                mainWindow.fetchStations(); // Dodajemy jawne wywołanie fetchStations()
                            }
                        }
                    }
                }

                // Tekst informacyjny
                Text {
                    id: statusText
                    text: mainWindow.status
                    font.pixelSize: 16
                    color: "#333"
                }

                // Lista stacji
                ListView {
                    id: stationList
                    width: parent.width
                    height: parent.height - statusText.height - 70 // odejmujemy wysokość pola wyszukiwania
                    spacing: 10
                    clip: true

                    model: mainWindow.stations

                    delegate: Rectangle {
                        width: parent.width
                        height: 120
                        color: "#daeaf6" // Zmieniony kolor tła kafelka na jasnobłękitny
                        radius: 5
                        border.color: "#a4c6e3" // Ciemniejszy odcień obramowania

                        Column {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 5

                            Text { text: "<b>Nazwa:</b> " + modelData.stationName; font.pixelSize: 14 }
                            Text { text: "<b>ID:</b> " + modelData.stationId; font.pixelSize: 14 }
                            Text { text: "<b>Współrzędne:</b> " + modelData.lat + ", " + modelData.lon; font.pixelSize: 14 }
                            Text { text: "<b>Adres:</b> " + (modelData.address ? modelData.address : "Brak danych"); font.pixelSize: 14 }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                // Debugowanie - sprawdzamy ID stacji
                                console.log("Wybrana stacja ID: " + modelData.stationId);

                                // Pobieramy dane szczegółowe dla wybranej stacji
                                mainWindow.fetchStationDetails(modelData.stationId);

                                // Zapisujemy ID wybranej stacji
                                mainWindow.selectedStationId = modelData.stationId;

                                // Zapisujemy dane wybranej stacji
                                selectedStationInfo.stationId = modelData.stationId;
                                selectedStationInfo.stationName = modelData.stationName;
                                selectedStationInfo.address = modelData.address ? modelData.address : "Brak danych";
                                selectedStationInfo.coordinates = modelData.lat + ", " + modelData.lon;

                                // Przechodzimy do ekranu szczegółów
                                currentScreen = 1;
                            }
                        }
                    }
                }
            }
        }

        // Ekran szczegółów stacji
        Item {
            id: detailsScreen

            // Obiekt do przechowywania informacji o wybranej stacji
            QtObject {
                id: selectedStationInfo
                property int stationId: 0
                property string stationName: ""
                property string address: ""
                property string coordinates: ""
            }

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 15

                // Informacje o stacji
                Rectangle {
                    width: parent.width
                    height: 150
                    color: "#daeaf6" // Taki sam kolor jak kafelki na pierwszym ekranie
                    radius: 5
                    border.color: "#a4c6e3"

                    Column {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 8

                        Text {
                            text: "<b>Stacja:</b> " + selectedStationInfo.stationName
                            font.pixelSize: 18
                            font.bold: true
                        }
                        Text { text: "<b>ID stacji:</b> " + selectedStationInfo.stationId; font.pixelSize: 14 }
                        Text { text: "<b>Adres:</b> " + selectedStationInfo.address; font.pixelSize: 14 }
                        Text { text: "<b>Współrzędne:</b> " + selectedStationInfo.coordinates; font.pixelSize: 14 }
                    }
                }

                // Tekst informacyjny i status
                Item {
                    width: parent.width
                    height: 30

                    Text {
                        anchors.left: parent.left
                        text: "Dane pomiarowe"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        anchors.right: parent.right
                        text: mainWindow.status
                        font.pixelSize: 14
                        color: "#555"
                    }
                }

                // Informacja gdy brak danych
                Text {
                    visible: mainWindow.sensorData.length === 0
                    text: "Brak dostępnych danych pomiarowych dla tej stacji"
                    font.pixelSize: 14
                    color: "#555"
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }

                // Lista danych pomiarowych
                ListView {
                    id: sensorDataList
                    width: parent.width
                    height: parent.height - 250
                    spacing: 10
                    clip: true
                    visible: mainWindow.sensorData.length > 0

                    model: mainWindow.sensorData

                    delegate: Rectangle {
                        width: parent.width
                        height: 100
                        color: "#e6f2ff" // Nieco jaśniejszy odcień dla danych pomiarowych
                        radius: 5
                        border.color: "#a4c6e3"

                        Column {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 5

                            Text {
                                text: "<b>Parametr:</b> " + modelData.param + " (" + modelData.paramFormula + ")"
                                font.pixelSize: 16
                            }
                            Text {
                                text: "<b>Ostatni pomiar:</b> " + modelData.value + " µg/m3 " + modelData.unit
                                font.pixelSize: 14
                            }
                            Text {
                                text: "<b>Data pomiaru:</b> " + modelData.date
                                font.pixelSize: 14
                            }
                        }

                        // Przycisk "Wykres"
                        Rectangle {
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 10
                            width: 100
                            height: 30
                            color: "#4CAF50"
                            radius: 4

                            Text {
                                anchors.centerIn: parent
                                text: "Wykres"
                                color: "white"
                                font.pixelSize: 14
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    // Resetowanie wykresu przed pobraniem nowych danych
                                    resetChart();

                                    // Pobieramy historię pomiarów dla wybranego czujnika
                                    mainWindow.fetchSensorHistory(modelData.id, modelData.param, modelData.paramFormula);

                                    // Przechodzimy do ekranu wykresu
                                    currentScreen = 2;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Ekran wykresu pomiarów - własna implementacja bez QtCharts
        Item {
            id: chartScreen

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                // Informacja o zakresie dat (tylko wyświetlanie)
                Text {
                    id: chartInfoText
                    width: parent.width
                    text: {
                        if (mainWindow.sensorHistory.length > 0 && chartScreen.filteredData && chartScreen.filteredData.length > 0) {
                            // Znajdujemy najwcześniejszą i najpóźniejszą datę w przefiltrowanych danych
                            var earliestDate = new Date(chartScreen.filteredData[0].date);
                            var latestDate = new Date(chartScreen.filteredData[0].date);

                            for (var i = 1; i < chartScreen.filteredData.length; i++) {
                                var currentDate = new Date(chartScreen.filteredData[i].date);
                                if (currentDate < earliestDate) {
                                    earliestDate = currentDate;
                                }
                                if (currentDate > latestDate) {
                                    latestDate = currentDate;
                                }
                            }

                            // Formatujemy daty jako YYYY-MM-DD
                            var earliestStr = earliestDate.toISOString().split('T')[0];
                            var latestStr = latestDate.toISOString().split('T')[0];

                            return "Wyświetlanie " + chartScreen.filteredData.length + " pomiarów z okresu " +
                                  earliestStr + " - " + latestStr;
                        } else {
                            return "";
                        }
                    }
                    font.pixelSize: 14
                    color: "#333"
                    horizontalAlignment: Text.AlignHCenter
                }

                // Panel z informacjami o odczytach (statystyki)
                Rectangle {
                    visible: mainWindow.sensorHistory.length > 0
                    width: parent.width
                    height: 80 // Zwiększam wysokość, aby zmieścić dodatkowe informacje
                    color: "#f5f5f5"
                    border.color: "#ddd"
                    radius: 5

                    Row {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 20

                        // Maksymalny odczyt
                        Column {
                            spacing: 2
                            width: (parent.width - 40) / 3  // Równy podział na 3 kolumny
                            height: parent.height

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: "Maksymalny odczyt:"
                                font.pixelSize: 14
                                font.bold: true
                                color: "#e53935" // Czerwony
                            }

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: {
                                    if (chartScreen.highestValue !== null) {
                                        return chartScreen.highestValue.toFixed(1) + " µg/m3 " + chartScreen.unit;
                                    }
                                    return "---";
                                }
                                font.pixelSize: 18
                                color: "#e53935" // Czerwony
                            }

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: {
                                    if (chartScreen.highestDate !== null) {
                                        var date = new Date(chartScreen.highestDate);
                                        return date.toLocaleDateString() + " " +
                                               date.toLocaleTimeString(Qt.locale(), "HH:mm");
                                    }
                                    return "";
                                }
                                font.pixelSize: 12
                                color: "#e53935" // Czerwony
                            }
                        }

                        // Minimalny odczyt
                        Column {
                            spacing: 2
                            width: (parent.width - 40) / 3  // Równy podział na 3 kolumny
                            height: parent.height

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: "Minimalny odczyt:"
                                font.pixelSize: 14
                                font.bold: true
                                color: "#4CAF50" // Zielony
                            }

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: {
                                    if (chartScreen.lowestValue !== null) {
                                        return chartScreen.lowestValue.toFixed(1) + " µg/m3 " + chartScreen.unit;
                                    }
                                    return "---";
                                }
                                font.pixelSize: 18
                                color: "#4CAF50" // Zielony
                            }

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: {
                                    if (chartScreen.lowestDate !== null) {
                                        var date = new Date(chartScreen.lowestDate);
                                        return date.toLocaleDateString() + " " +
                                               date.toLocaleTimeString(Qt.locale(), "HH:mm");
                                    }
                                    return "";
                                }
                                font.pixelSize: 12
                                color: "#4CAF50" // Zielony
                            }
                        }

                        // Średni odczyt
                        Column {
                            spacing: 2
                            width: (parent.width - 40) / 3  // Równy podział na 3 kolumny
                            height: parent.height

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: "Wartość średnia:"
                                font.pixelSize: 14
                                font.bold: true
                                color: "#3949ab" // Niebieski
                            }

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: {
                                    if (chartScreen.averageValue !== null) {
                                        return chartScreen.averageValue.toFixed(1) + " µg/m3 " + chartScreen.unit;
                                    }
                                    return "---";
                                }
                                font.pixelSize: 18
                                color: "#3949ab" // Niebieski
                            }

                            Text {
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                text: "(z całego okresu)"
                                font.pixelSize: 12
                                color: "#3949ab" // Niebieski
                            }
                        }
                    }
                }

                // Status
                Column {
                    id: statusContainer
                    width: parent.width
                    spacing: 5

                    Text {
                        id: chartStatusText
                        text: mainWindow.status
                        font.pixelSize: 14
                        color: "#555"
                        width: parent.width
                        // visible: text !== ""
                    }

                    Text {
                        id: airQualityText
                        text: mainWindow.airQualityStatus
                        font.pixelSize: 14
                        font.bold: true
                        color: {
                            // Color based on air quality status
                            var status = mainWindow.airQualityStatus.toLowerCase();
                            if (status.includes("bardzo dobry")) return "#57b108"; // Ciemny Zielony
                            if (status.includes("dobry")) return "#b0dd10"; // Zielony
                            if (status.includes("umiarkowany")) return "#ffd911"; // Żółty
                            if (status.includes("dostateczny")) return "#e58100"; // Pomarańczowy
                            if (status.includes("zły")) return "#e50000"; // Czerwony
                            if (status.includes("bardzo zły")) return "#990000"; // Ciemny Czerwony
                            return "#555"; // Default gray
                        }
                        width: parent.width
                        // visible: text !== ""
                    }
                }

                // Informacja gdy brak danych historycznych
                Text {
                    visible: mainWindow.sensorHistory.length === 0
                    text: "Brak dostępnych danych historycznych dla tego czujnika"
                    font.pixelSize: 14
                    color: "#555"
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }

                // Własna implementacja wykresu
                Rectangle {
                    id: chartContainer
                    visible: mainWindow.sensorHistory.length > 0
                    width: parent.width
                    height: parent.height - chartInfoText.height - chartStatusText.height - statusContainer.height - 160 //zmienione ze 100
                    color: "white"
                    border.color: "#ddd"
                    border.width: 1
                    radius: 5

                    // Tytuł PM10 przeniesiony na górę wykresu
                    Text {
                        id: chartTitle
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: {
                            if (mainWindow.sensorHistory.length > 0) {
                                // Jeśli mamy dane, pokazujemy typ pomiaru (PM10)
                                return mainWindow.selectedSensor.paramFormula;
                            }
                            return "";
                        }
                        font.pixelSize: 16
                        font.bold: true
                        color: "#333"
                    }

                    // Obszar wykresu
                    Item {
                        id: chartArea
                        anchors.fill: parent
                        anchors.margins: 50 // Zwiększony margines dla etykiet osi

                        // Siatka wykresu
                        Canvas {
                            id: gridCanvas
                            anchors.fill: parent

                            onPaint: {
                                var ctx = getContext("2d");
                                ctx.clearRect(0, 0, width, height); // Czyszczenie canvasu
                                ctx.strokeStyle = "#eee";
                                ctx.lineWidth = 1;

                                // Poziome linie siatki
                                var stepY = height / 5;
                                for (var i = 0; i <= 5; i++) {
                                    var y = i * stepY;
                                    ctx.beginPath();
                                    ctx.moveTo(0, y);
                                    ctx.lineTo(width, y);
                                    ctx.stroke();
                                }

                                // Pionowe linie siatki
                                var stepX = width / 6;
                                for (var j = 0; j <= 6; j++) {
                                    var x = j * stepX;
                                    ctx.beginPath();
                                    ctx.moveTo(x, 0);
                                    ctx.lineTo(x, height);
                                    ctx.stroke();
                                }
                            }
                        }

                        // Dane wykresu
                        Canvas {
                            id: dataCanvas
                            anchors.fill: parent

                            property var dataPoints: []
                            property real minValue: 0
                            property real maxValue: 100

                            onPaint: {
                                var ctx = getContext("2d");
                                ctx.clearRect(0, 0, width, height); // Czyszczenie canvasu

                                if (dataPoints.length < 2) return;

                                // Rysowanie linii
                                ctx.strokeStyle = "#4CAF50";
                                ctx.lineWidth = 2;
                                ctx.lineJoin = "round";

                                ctx.beginPath();
                                for (var i = 0; i < dataPoints.length; i++) {
                                    var point = dataPoints[i];
                                    var x = point.x * width;
                                    var y = height - ((point.y - minValue) / (maxValue - minValue)) * height;

                                    if (i === 0) {
                                        ctx.moveTo(x, y);
                                    } else {
                                        ctx.lineTo(x, y);
                                    }
                                }
                                ctx.stroke();

                                // Rysowanie punktów
                                ctx.fillStyle = "#4CAF50";
                                for (var j = 0; j < dataPoints.length; j++) {
                                    var dp = dataPoints[j];
                                    var dpX = dp.x * width;
                                    var dpY = height - ((dp.y - minValue) / (maxValue - minValue)) * height;

                                    ctx.beginPath();
                                    ctx.arc(dpX, dpY, 5, 0, 2 * Math.PI); // Zwiększony rozmiar punktu
                                    ctx.fill();
                                }

                                // Po narysowaniu wykresu tworzymy etykiety
                                // Qt.callLater(createDateLabels);
                            }
                        }

                        // Kontener dla etykiet punktów
                        Item {
                            id: pointLabelsContainer
                            anchors.fill: parent
                            // Tu będą dynamicznie tworzone etykiety
                        }
                    }

                    // Etykiety osi Y (wartości)
                    Column {
                        anchors.right: chartArea.left
                        anchors.rightMargin: 5
                        anchors.verticalCenter: chartArea.verticalCenter
                        height: chartArea.height
                        spacing: (chartArea.height - 60) / 4

                        Text {
                            text: dataCanvas.maxValue.toFixed(1)
                            font.pixelSize: 10
                            anchors.right: parent.right
                            width: 40
                            horizontalAlignment: Text.AlignRight
                        }
                        Text {
                            text: (dataCanvas.minValue + (dataCanvas.maxValue - dataCanvas.minValue) * 0.75).toFixed(1)
                            font.pixelSize: 10
                            anchors.right: parent.right
                            width: 40
                            horizontalAlignment: Text.AlignRight
                        }
                        Text {
                            text: (dataCanvas.minValue + (dataCanvas.maxValue - dataCanvas.minValue) * 0.5).toFixed(1)
                            font.pixelSize: 10
                            anchors.right: parent.right
                            width: 40
                            horizontalAlignment: Text.AlignRight
                        }
                        Text {
                            text: (dataCanvas.minValue + (dataCanvas.maxValue - dataCanvas.minValue) * 0.25).toFixed(1)
                            font.pixelSize: 10
                            anchors.right: parent.right
                            width: 40
                            horizontalAlignment: Text.AlignRight
                        }
                        Text {
                            text: dataCanvas.minValue.toFixed(1)
                            font.pixelSize: 10
                            anchors.right: parent.right
                            width: 40
                            horizontalAlignment: Text.AlignRight
                        }
                    }

                    // Tytuł osi X
                    Text {
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 5
                        anchors.horizontalCenter: chartArea.horizontalCenter
                        text: "Data pomiaru"
                        font.pixelSize: 12
                    }
                }
                // Przycisk do zapisywania danych do pliku JSON
                Rectangle {
                    id: saveButton
                    visible: mainWindow.sensorHistory.length > 0
                    width: 200
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    // anchors.top: chartContainer.bottom
                    // anchors.topMargin: 10
                    color: "#4CAF50"
                    radius: 5

                    Text {
                        anchors.centerIn: parent
                        text: "Zapisz dane do JSON"
                        color: "white"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    // Efekt naciśnięcia przycisku
                    Rectangle {
                        id: buttonOverlay
                        anchors.fill: parent
                        color: "white"
                        opacity: 0
                        radius: parent.radius
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.color = "#45a049"
                        onExited: parent.color = "#4CAF50"
                        onPressed: buttonOverlay.opacity = 0.3
                        onReleased: buttonOverlay.opacity = 0
                        onClicked: {
                            // Wywołujemy funkcję zapisującą dane
                            var cityName = mainWindow.cityName.trim();
                            if (cityName === "") {
                                cityName = "NieznaneCity"; // Domyślna nazwa, jeśli miasto nie jest określone
                            }
                            var stationId = selectedStationInfo.stationId;
                            mainWindow.saveSensorDataToJson(cityName, stationId);
                        }
                    }
                }
            }

            // Pomocnicze właściwości
            property var filteredDates: []
            property var filteredData: []

            // Właściwości dla statystyk
            property var lowestValue: null
            property var lowestDate: null
            property var highestValue: null
            property var highestDate: null
            property var averageValue: null
            property string unit: ""

            // Funkcja do tworzenia etykiet z datami pod punktami
            function createDateLabels() {
                // Usuwamy poprzednie etykiety
                clearPointLabels();

                // Jeśli nie mamy danych, kończymy
                if (!filteredData || filteredData.length === 0) return;

                // Ograniczamy liczbę etykiet dla czytelności
                var maxLabels = Math.min(filteredData.length, 20);
                var skipFactor = Math.ceil(filteredData.length / maxLabels);

                for (var i = 0; i < filteredData.length; i += skipFactor) {
                    var dataPoint = filteredData[i];
                    var xPos = (i / (filteredData.length - 1 || 1)) * chartArea.width;
                    var yPos = chartArea.height - ((dataPoint.value - dataCanvas.minValue) /
                            (dataCanvas.maxValue - dataCanvas.minValue)) * chartArea.height;

                    var date = new Date(dataPoint.date);

                    // Format daty DD-MM
                    var dateStr = String(date.getDate()).padStart(2, '0') + "-" +
                                 String(date.getMonth() + 1).padStart(2, '0');

                    // Format czasu HH:MM
                    var timeStr = String(date.getHours()).padStart(2, '0') + ":" +
                                 String(date.getMinutes()).padStart(2, '0');

                    // Tworzenie elementu Column z etykietą
                    var labelElement = Qt.createQmlObject(
                        'import QtQuick 2.15; ' +
                        'Column { ' +
                        '   width: 40; ' +
                        '   spacing: 1; ' +
                        '   anchors.top: parent.top; ' +
                        '   anchors.horizontalCenter: parent.left; ' +
                        '   anchors.horizontalCenterOffset: ' + xPos + '; ' +
                        '   anchors.topMargin: ' + (yPos + 10) + '; ' +
                        '   Text { ' +
                        '     text: "' + dataPoint.value.toFixed(1) + '"; ' +
                        '     font.pixelSize: 9; ' +
                        '     color: "#4CAF50"; ' +
                        '     horizontalAlignment: Text.AlignHCenter; ' +
                        '     width: parent.width; ' +
                        '   } ' +
                        '   Text { ' +
                        '     text: "' + dateStr + '"; ' +
                        '     font.pixelSize: 8; ' +
                        '     horizontalAlignment: Text.AlignHCenter; ' +
                        '     width: parent.width; ' +
                        '   } ' +
                        '   Text { ' +
                        '     text: "' + timeStr + '"; ' +
                        '     font.pixelSize: 8; ' +
                        '     horizontalAlignment: Text.AlignHCenter; ' +
                        '     width: parent.width; ' +
                        '   } ' +
                        '} ',
                        pointLabelsContainer,
                        "dynamicLabel"
                    );
                }
            }

            // Funkcja do aktualizacji wykresu w oparciu o wybrany zakres dat
            function updateChart() {
                if (mainWindow.sensorHistory.length === 0) return;

                // Czyszczenie poprzednich danych
                dataCanvas.dataPoints = [];
                filteredDates = [];
                filteredData = [];

                // Usuwamy etykiety
                clearPointLabels();

                // Filtrujemy dane według zakresu dat
                var rawFilteredData = [];
                var minY = Number.MAX_VALUE;
                var maxY = Number.MIN_VALUE;
                var dates = [];

                // Zmienne dla statystyk
                var lowestValue = Number.MAX_VALUE;
                var lowestDate = null;
                var highestValue = Number.MIN_VALUE;
                var highestDate = null;
                var sum = 0;
                var count = 0;
                var unit = "";

                for (var i = 0; i < mainWindow.sensorHistory.length; i++) {
                    var record = mainWindow.sensorHistory[i];
                    var recordDate = new Date(record.date);

                    if (recordDate >= startDate && recordDate <= endDate) {
                        // Zapisujemy jednostkę miary
                        if (unit === "" && record.unit) {
                            unit = record.unit;
                        }

                        rawFilteredData.push({
                            date: recordDate,
                            value: record.value
                        });

                        dates.push(record.date);

                        // Aktualizujemy min/max dla osi Y
                        minY = Math.min(minY, record.value);
                        maxY = Math.max(maxY, record.value);

                        // Aktualizujemy statystyki
                        sum += record.value;
                        count++;

                        // Najniższa wartość
                        if (record.value < lowestValue) {
                            lowestValue = record.value;
                            lowestDate = recordDate;
                        }

                        // Najwyższa wartość
                        if (record.value > highestValue) {
                            highestValue = record.value;
                            highestDate = recordDate;
                        }
                    }
                }

                // Sortujemy dane po dacie (od najstarszych do najnowszych)
                rawFilteredData.sort(function(a, b) {
                    return a.date - b.date;
                });

                // Zapisujemy przefiltrowane daty i dane
                filteredData = rawFilteredData;
                filteredDates = dates.sort(function(a, b) {
                    return new Date(a) - new Date(b);
                });

                // Dodajemy margines 10% do min/max
                var yRange = maxY - minY;
                if (yRange === 0) yRange = maxY * 0.2 || 10; // Zapobiegamy dzieleniu przez zero

                var yMargin = yRange * 0.1;
                minY = Math.max(0, minY - yMargin);
                maxY = maxY + yMargin;

                // Aktualizujemy dane dla canvas
                var dataPoints = [];
                for (var j = 0; j < filteredData.length; j++) {
                    var position = j / (filteredData.length - 1 || 1);
                    dataPoints.push({
                        x: position,
                        y: filteredData[j].value
                    });
                }

                dataCanvas.dataPoints = dataPoints;
                dataCanvas.minValue = minY;
                dataCanvas.maxValue = maxY;
                dataCanvas.requestPaint();
                gridCanvas.requestPaint();

                // Aktualizacja statystyk
                if (count > 0) {
                    chartScreen.lowestValue = lowestValue;
                    chartScreen.lowestDate = lowestDate;
                    chartScreen.highestValue = highestValue;
                    chartScreen.highestDate = highestDate;
                    chartScreen.averageValue = sum / count;
                    chartScreen.unit = unit;
                } else {
                    chartScreen.lowestValue = null;
                    chartScreen.lowestDate = null;
                    chartScreen.highestValue = null;
                    chartScreen.highestDate = null;
                    chartScreen.averageValue = null;
                    chartScreen.unit = "";
                }
            }

            // Inicjalizacja wykresu po załadowaniu ekranu
            Component.onCompleted: {
                // Łączymy zmianę w mainWindow.sensorHistory z aktualizacją wykresu
                mainWindow.sensorHistoryChanged.connect(function() {
                    if (mainWindow.sensorHistory.length > 0) {
                        // Ustawiamy domyślne daty - ostatni tydzień
                        var lastDate = new Date(mainWindow.sensorHistory[0].date);
                        var weekBefore = new Date(lastDate);
                        weekBefore.setDate(lastDate.getDate() - 7);

                        startDate = weekBefore;
                        endDate = lastDate;

                        // Aktualizujemy wykres z nowymi danymi
                        updateChart();
                    }
                });
            }

        }
    }

    // Po załadowaniu okna wywołujemy pobieranie danych
    Component.onCompleted: {
        mainWindow.fetchStations();
    }
}
