#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

struct Wegpunkt {
    std::string name;
    double x;
    double y;
};

const double PI = 3.14159265358979323846;

double abstand(const Wegpunkt& a, const Wegpunkt& b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double strecke = std::sqrt(dx * dx + dy * dy);
    return strecke;
}

double gesamtLaenge(const std::vector<Wegpunkt>& route){
    double summe = 0;
    for(std::size_t i = 1; i < route.size(); i++){
        summe = summe + abstand(route[i - 1], route[i]);
    }
    return summe;
}

double flugzeitMinuten(double laengeNM, double geschwindigkeitKt){
    double zeit;
    zeit = ((laengeNM / geschwindigkeitKt)*60);
    return zeit;
}

double leseZahl (const std::string& frage){
    while (true){
        std::cout<<frage;
        double wert;
        std::cin>>wert;
        if (std::cin){
            return wert;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<"Ungueltige Eingabe, bitte eine Zahl angeben."<<std::endl;
    }
}

bool speichereRoute(const std::vector<Wegpunkt>& route, const std::string& dateiname){
    std::ofstream datei(dateiname);
    if(!datei){
        std::cout<<"Datei nicht angelegt."<<std::endl;
        return false;
    }
    for(const Wegpunkt& w : route){
        datei << w.name << " " << w.x << " " << w.y << "\n";
    }
    return true;
}

bool leseRoute(std::vector<Wegpunkt>& route, const std::string& dateiname){
    std::ifstream datei(dateiname);
    if(!datei){
        std::cout<<"Datei nicht gefunden."<<std::endl;
        return false;
    }
    std::vector<Wegpunkt> geladen;
    Wegpunkt w;
    while(datei >> w.name >> w.x >> w.y){
        geladen.push_back(w);
    }
    if (!datei.eof()){
        std::cout<<"Datei fehlerhaft, bitte Format ueberpruefen."<<std::endl;
        return false;
    }
    if(!geladen.empty()){
        route = geladen;
        return true;
    }
    std::cout<<"Datei ist leer, Lesen abgebrochen."<<std::endl;
    return false;
}

double kursGrad(const Wegpunkt& von, const Wegpunkt& nach){
    double bogenmass;
    double dx = nach.x - von.x;
    double dy = nach.y - von.y;
    bogenmass = std::atan2(dx, dy);
    double gradmass = bogenmass * 180 / PI;
    if (gradmass < 0){
        gradmass = gradmass + 360;
    }
    return gradmass;
}

double bodengeschwindigkeit(double luftKt, double kurs, double windVonGrad, double windKt){
    double windVonBogen = windVonGrad / 180 * PI;
    double kursBogen = kurs / 180 * PI;
    double bodengeschw = luftKt - windKt * std::cos(windVonBogen - kursBogen);
    return bodengeschw;
}

int main()
{
    Wegpunkt start;
    start.name = "START";
    start.x = 0;
    start.y = 0;
    
    std::vector<Wegpunkt> route;
    route.push_back(start);
    
    double geschwindigkeit = 220.0;
    double windVonGrad = 0;
    double windKt = 0;
    
    int auswahl = 0;
    while (auswahl != 7) {
        std::cout << "\n--- Streckenrechner ---" << std::endl;
        std::cout << "1: Wegpunkt hinzufuegen" << std::endl;
        std::cout << "2: Wegpunkte anzeigen" << std::endl;
        std::cout << "3: Geschwindigkeit aendern" << std::endl;
        std::cout << "4: Route speichern" << std::endl;
        std::cout << "5: Route laden" << std::endl;
        std::cout << "6: Wind aendern" << std::endl;
        std::cout << "7: Programm beenden" << std::endl;
        std::cout << "Auswahl: ";
        std::cin >> auswahl;
        
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            auswahl = 0;
        }
        
        switch (auswahl) {
            case 1:{
                Wegpunkt neu;
                
                std::cout<<"Gib einen Namen an: ";
                std::cin>>neu.name;
                neu.x = leseZahl("Gib die x-Koordinate in NM an: ");
                neu.y = leseZahl("Gib die y-Koordinate in NM an: ");
                
                route.push_back(neu);
                
                std::cout<<"Wegpunkt "<<neu.name<<" hinzugefuegt."<<std::endl;
                
                break;
            }
            case 2:
                for(const Wegpunkt& w : route){
                    std::cout << w.name << ": "<<w.x<<" "<<w.y<< std::endl;
                }
                if (route.size() > 1){
                    double gesamtzeit = 0;
                    bool flugMoeglich = true;
                    for(std::size_t i = 1; i < route.size(); i++){
                        std::cout<<route[i - 1].name<<" -> "<<route[i].name<<": "<< abstand(route[i - 1], route[i])<<" NM, "<<kursGrad(route[i - 1], route[i])<<" Grad"<<std::endl;
                        double teilgeschwindigkeit = bodengeschwindigkeit(geschwindigkeit, kursGrad(route[i - 1], route[i]), windVonGrad, windKt);
                        if (teilgeschwindigkeit > 0){
                            double teilZeit = flugzeitMinuten(abstand(route[i - 1], route[i]), teilgeschwindigkeit);
                            std::cout<<"Die Flugzeit fuer das Teilstueck bei "<<teilgeschwindigkeit<<" kt betraegt "<<teilZeit<<" Minuten."<<std::endl;
                            gesamtzeit = gesamtzeit + teilZeit;
                        } else {
                            flugMoeglich = false;
                            std::cout<<"Flug nicht moeglich: Wind zu stark."<<std::endl;
                        }
                    }
                    double laenge = gesamtLaenge(route);
                    std::cout<<"Die Route ist "<<laenge<<" NM lang."<<std::endl;
                    if (flugMoeglich){
                       std::cout<<"Flugzeit bei "<<geschwindigkeit<<" kt: "<<gesamtzeit<<" Minuten"<<std::endl;
                    } else {
                        std::cout<<"Die Route ist bei diesem Wind nicht fliegbar."<<std::endl;
                    }
                }
                break;
            case 3:{
                double geschwindigkeitNeu;
                
                while (true){
                    geschwindigkeitNeu = leseZahl("Neue Geschwindigkeit eingeben: ");
                    if (geschwindigkeitNeu <= 0){
                        std::cout<<"Ungueltige Eingabe, bitte eine positive Zahl angeben."<<std::endl;
                    } else {
                        geschwindigkeit = geschwindigkeitNeu;
                        std::cout<<"Geschwindigkeit erfolgreich geaendert."<<std::endl;
                        break;
                    }
                }
                
                break;
            }
            case 4:
                if (speichereRoute(route, "route.txt")){
                    std::cout<<"Route erfolgreich gespeichert."<<std::endl;
                }
                break;
            case 5:
                if(leseRoute(route, "route.txt")){
                    std::cout<<"Route erfolgreich geladen."<<std::endl;
                }
                break;
            case 6:{
                while(true){
                    windKt = leseZahl("Gib die Windgeschwindigkeit an: ");
                    if (windKt >= 0){
                        std::cout<<"Windgeschwindigkeit erfolgreich geaendert."<<std::endl;
                        break;
                    }
                    std::cout<<"Bitte einen Wert groesser gleich 0 angeben."<<std::endl;}
                while(true){
                    windVonGrad = leseZahl("Gib die Richtung des Windes in Grad an: ");
                    if (windVonGrad >= 0 && windVonGrad <=360){
                        std::cout<<"Wind Richtung erfolgreich geaendert."<<std::endl;
                        break;
                    }
                    std::cout<<"Bitte eine Wert zwischen 0 und 360 eingeben."<<std::endl;
                }
                break;
            }
            case 7:
                std::cout << "Programm beendet." << std::endl;
                break;
            default:
                std::cout << "Ungueltige Auswahl." << std::endl;
        }
    }
}
