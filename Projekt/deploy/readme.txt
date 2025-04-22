# Stacje Pomiarowe GIOŚ

## Opis aplikacji
Aplikacja "Stacje Pomiarowe GIOŚ" to desktopowy program umożliwiający monitorowanie jakości powietrza na podstawie danych z sieci stacji pomiarowych Głównego Inspektoratu Ochrony Środowiska w Polsce. 

## Funkcjonalności
1. Wyszukiwanie stacji pomiarowych według nazwy miasta
2. Przeglądanie szczegółowych informacji o stacjach:
   - Nazwa i ID stacji
   - Współrzędne geograficzne
   - Adres
3. Wyświetlanie aktualnych pomiarów zanieczyszczeń powietrza:
   - PM10
   - PM2.5
   - Inne dostępne parametry
4. Wizualizacja danych historycznych za pomocą interaktywnych wykresów
5. Sprawdzanie indeksu jakości powietrza
6. Zapisywanie danych pomiarowych do plików JSON w celu późniejszej analizy

## Jak działa program
1. **Ekran główny**: 
   - Użytkownik wprowadza nazwę miasta w pole wyszukiwania
   - Po kliknięciu przycisku "Szukaj" aplikacja pobiera i wyświetla listę stacji pomiarowych w danym mieście
   
2. **Szczegóły stacji**:
   - Po kliknięciu na wybraną stację, aplikacja przechodzi do widoku szczegółów
   - Wyświetlane są informacje o stacji oraz lista dostępnych czujników z aktualnymi odczytami
   - Przy każdym czujniku dostępny jest przycisk "Wykres" umożliwiający przejście do analizy historycznej

3. **Wykres pomiarów**:
   - Dla wybranego parametru (np. PM10) wyświetlany jest wykres historycznych pomiarów
   - Widoczne są statystyki: wartość maksymalna, minimalna i średnia
   - Informacja o jakości powietrza
   - Możliwość zapisania danych do pliku JSON

## Komunikacja z API
Aplikacja komunikuje się z następującymi endpointami API GIOŚ:
- **Lista stacji**: `https://api.gios.gov.pl/pjp-api/rest/station/findAll`
- **Czujniki stacji**: `https://api.gios.gov.pl/pjp-api/rest/station/sensors/{stationId}`
- **Dane pomiarowe**: `https://api.gios.gov.pl/pjp-api/rest/data/getData/{sensorId}`
- **Indeks jakości powietrza**: `https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/{stationId}`

## Przepływ danych
1. Pobieranie listy wszystkich stacji z API
2. Filtrowanie stacji według nazwy miasta
3. Po wybraniu stacji - pobieranie listy czujników
4. Dla każdego czujnika - pobieranie aktualnych danych pomiarowych
5. Przy przeglądaniu danych historycznych - pobieranie historii pomiarów dla konkretnego czujnika
6. Pobieranie indeksu jakości powietrza dla stacji