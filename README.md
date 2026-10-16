# Streckenrechner

## Überblick
Dieses Programm dient der Berechnung von Distanz und Flugzeit unter Berücksichtigung von Flugzeug- und Windgeschwindigkeit zwischen Wegpunkten. Diese können zuvor vom Nutzer selber eingegeben und gespeichert bzw. aus dem Speicher gelesen werden.

## Rechenmodell
Das Programm nimmt x für Osten und y Norden als Koordinaten in NM an, um auf einer geraden Strecke den Abstand, sowie den Kurs in Grad, bei Norden mit 0° beginnend und im Uhrzeigersinn zu 360° steigend, zu berechnen. Die Bodengeschwindigkeit ermittelt sich aus Fluggeschwindigkeit, sowie der Windgeschwindigkeit entlang des Kurses. Die Gradzahl des Windes gibt dessen Herkunft an (90° = aus Osten). Daraus ermittelt sich die Flugzeit. Erdkrümmung und Abdrift durch den Wind werden nicht berücksichtigt.

## Menü und Funktionen
Das interaktive Menü öffnet sich bei Start des Programms und ermöglicht dem Nutzer die Wahl zwischen sieben Punkten, mittels Eingabe der korrespondierenden Zahl. Punkt eins ist das Hinzufügen von Wegpunkten über drei Abfragen zu Name, sowie x und y Koordinate, bevor er in einem Vektor gespeichert wird. Punkt zwei zeigt alle Wegpunkte in Reihe, inklusive des vorprogrammierten Punktes ‚START’ bei (0,0) an und ermittelt Abstand, Kurs in Grad und Flugzeit zwischen den einzelnen Punkten, sowie Abstand und Flugzeit für die gesamte Strecke. Über die Punkte vier und fünf können die Wegpunkte in einer separaten Datei gespeichert, bzw. aus dieser gelesen werden. Beim Laden wird  die gesamte Route, inklusive des Punktes ‚START‘ ersetzt. Punkte drei und sechs ermöglichen die Eingabe neuer Werte für die Geschwindigkeit und den Wind und Punkt sieben beendet das Programm.

## Dateiformat
Die externe Datei ‚route.txt‘ speichert Wegpunkte zeilenweise, wobei die Werte durch Leerzeichen getrennt sind. In Reihenfolge ist es ‚Name‘, ‚x-Koordinate‘ und ‚y-Koordinate‘.
Bsp.:
```
START 0 0
ALPHA 30 40
```

## Bekannte Grenzen
- Wegpunkte dürfen keine Namen mit Leerzeichen haben, da alles nach dem Leerzeichen als versuchte Eingabe der x-Koordinate gilt und somit falsch ist und verworfen wird. Folgend führt eine Namenseingabe wie ‚ALPHA 30‘ dazu, dass 30 stillschweigend als x-Koordinate übernommen wird, ohne eine entsprechende Meldung auszugeben.
- Die Prüfung der Datei bei der Einlese der Daten ist nicht perfekt, da im Fall, dass dem letztem Wegpunkt die y-Koordinate fehlt, die Einlese diesen Wegpunkt im Ganzen trotz Ausgabe ‚Route erfolgreich geladen‘ verwirft.
-  Wind und Geschwindigkeit werden nicht als Werte in der Datei gespeichert und können so beim Laden nicht mit aufgerufen werden.

## Ausführen
Im Terminal: main.cpp in einen Ordner legen. Ordner öffnen. Weitere Befehle im Terminal ausführen.
```
g++ -std=c++20 main.cpp -o streckenrechner
./streckenrechner
```

Alternativ main.cpp und route.txt Replit oder OnlineGDB einfügen und 'Run' drücken.

## Beispielausgabe
```
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
```
