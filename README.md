# Streckenrechner

## Überblick
Dieses Programm dient der Berechnung von Distanz und Flugzeit unter Berücksichtigung von Flugzeug- und Windgeschwindigkeit zwischen Wegpunkten. Diese können zuvor vom Nutzer selber eingegeben und gespeichert bzw. aus dem Speicher gelesen werden.

## Rechenmodell
Das Programm nimmt x für Osten und y Norden als Koordinaten in NM an um auf einer geraden Strecke den Abstand zu berechnen. Die tatsächliche Geschwindigkeit ermittelt sich aus Fluggeschwindigkeit, sowie der Windgeschwindigkeit entlang des Kurses. Daraus ermittelt sich die Flugzeit.

## Menü und Funktionen
Das interaktive Menü öffnet sich bei starten des Programms und ermöglicht dem Nutzer die Wahl zwischen sieben Punkten mittels Eingabe der korrespondierenden Zahl. Punkt eins ist das Hinzufügen von Wegpunkten über drei Abfragen zu Name, sowie x und y Koordinate, bevor er in einem Vektor gespeichert wird. Punkt zwei zeigt alle Wegpunkte in Reihe an und ermittelt Abstand und Flugzeit zwischen den einzelnen Punkten, sowie für die gesamte Strecke. Über die Punkte vier und fünf können die Wegpunkte in einer separaten Datei gespeichert, bzw. aus dieser gelesen werden. Punkte drei und sechs ermöglichen die Eingabe neuer Werte für die Geschwindigkeit und den Wind und Punkt sieben beendet das Programm.

## Dateiformat
Die externe Datei ‚route.txt‘ speichert Wegpunkte zeilenweise, wobei die Werte durch Leerzeichen getrennt sind. In Reihenfolge ist es ‚Name‘, ‚x-Koordinate‘ und ‚y-Koordinate‘.

## Bekannte Grenzen
Grenzen sind unter anderem, dass Wegpunkte keine Namen mit Leerzeichen haben dürfen, da alles nach dem Leerzeichen als versuchte Eingabe der x-Koordinate gilt und somit falsch ist und verworfen wird. Weiterhin ist z.B. die Prüfung der Datei vor Einlese der Daten nicht perfekt, da im Fall, dass dem letztem Wegpunkt die y-Koordinate fehlt die Einlese problemlos laufen würde, dieser Wegpunkt allerdings im Weiterrechnen zu Definitionslücken führen würde.

## Ausführen
Im Terminal: main.cpp und route.txt in einen Ordner legen. Weitere Befehle im Terminal ausführen. g++ -std=c++20 main.cpp -o streckenrechner ./streckenrechner

Alternativ main.cpp und route.txt Replit oder OnlineGDB einfügen und 'Run' drücken.

## Beispielausgabe

--- Streckenrechner ---
1: Wegpunkt hinzufuegen
2: Wegpunkte anzeigen
3: Geschwindigkeit aendern
4: Route speichern
5: Route laden
6: Wind aendern
7: Programm beenden
Auswahl: 2
START: 0 0
ALPHA: 30 40
BRAVO: 30 100
START -> ALPHA: 50 NM, 36.8699 Grad
Die Flugzeit fuer das Teilstueck bei 220 kt betraegt 13.6364 Minuten.
ALPHA -> BRAVO: 60 NM, 0 Grad
Die Flugzeit fuer das Teilstueck bei 220 kt betraegt 16.3636 Minuten.
Die Route ist 110 NM lang.
Flugzeit bei 220 kt: 30 Minuten
