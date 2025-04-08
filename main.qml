import QtQuick 2.15

import QtQuick.Controls 2.15


ApplicationWindow {

    id: root

    visible: true

    width: 400

    height: 500

    title: "Stacje Pomiarowe"


    // Nagłówek

    Rectangle {

        id: header

        width: parent.width

        height: 50

        color: "#4CAF50"


        Text {

            anchors.centerIn: parent

            text: "Stacje Pomiarowe w Pile"

            color: "white"

            font.pixelSize: 20

            font.bold: true

        }

    }


    // Główna zawartość

    Column {

        anchors.top: header.bottom

        anchors.left: parent.left

        anchors.right: parent.right

        anchors.bottom: parent.bottom

        anchors.margins: 10

        spacing: 10


        // Tekst informacyjny

        Text {

            id: statusText

            text: mainWindow.status // Pobieramy status z MainWindow

            font.pixelSize: 16

            color: "#333"

        }


        // Lista stacji

        ListView {

            id: stationList

            width: parent.width

            height: parent.height - statusText.height - 20

            spacing: 10

            clip: true


            model: mainWindow.stations // Pobieramy listę stacji z MainWindow


            delegate: Rectangle {

                width: parent.width

                height: 120

                color: "#f0f0f0"

                radius: 5


                Column {

                    anchors.fill: parent

                    anchors.margins: 10

                    spacing: 5


                    Text { text: "<b>Nazwa:</b> " + modelData.stationName; font.pixelSize: 14 }

                    Text { text: "<b>ID:</b> " + modelData.stationId; font.pixelSize: 14 }

                    Text { text: "<b>Współrzędne:</b> " + modelData.lat + ", " + modelData.lon; font.pixelSize: 14 }

                    Text { text: "<b>Adres:</b> " + (modelData.address ? modelData.address : "Brak danych"); font.pixelSize: 14 }

                }

            }

        }

    }


    // Po załadowaniu okna wywołujemy pobieranie danych

    Component.onCompleted: {

        mainWindow.fetchStations();

    }

}
