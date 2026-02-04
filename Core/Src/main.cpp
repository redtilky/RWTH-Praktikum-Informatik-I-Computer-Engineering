#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <exception>
#include <random>
#include "../Inc/Fahrausnahme.h"
#include "../Inc/Fahren.h"
#include "../Inc/Fahrrad.h"
#include "../Inc/Fahrzeug.h"
#include "../Inc/Farbe.h"
#include "../Inc/Kreuzung.h"
#include "../Inc/Losfahren.h"
#include "../Inc/Parken.h"
#include "../Inc/PKW.h"
#include "../Inc/SimuClient.h"
#include "../Inc/Simulationsobjekt.h"
#include "../Inc/Streckenende.h"
#include "../Inc/Tempolimit.h"
#include "../Inc/Verhalten.h"
#include "../Inc/vertagt_liste.h"
#include "../Inc/Weg.h"

using namespace std;
using namespace Farbe;

double dGlobaleZeit = 0.0;
double dZeittakt = 0.10;
double dEndZeit = 20.0;
double dEpsilone = 1e-6;

void vAufgabe5() {
    auto weg = make_unique<Weg>("Autobahn", 12.0);
    auto car1 = make_unique<PKW>("BMW", 20, 30);
    auto car2 = make_unique<PKW>("Audi", 25, 35);
    auto car3 = make_unique<PKW>("VW", 22, 32);

    weg->vAnnahme(std::move(car1), 1.5);
    weg->vAnnahme(std::move(car2));
    weg->vAnnahme(std::move(car3));

    Weg::vKopf();
    cout << *weg << endl;
    Fahrzeug::vKopf();


    for (double t = 0; t <= dEndZeit; t += dZeittakt) {
        std::cout << "Zeit: " << t << "s" << std::endl;
        dGlobaleZeit = t;
        weg->vSimulieren();
    }
}

void vAufgabe6() {
	Weg::vKopf();
    Weg weg1("Hin1", 500.0, Tempolimit::Innenorts);
    Weg weg2("Hin2", 500.0, Tempolimit::Autobahn);

    auto car1 = std::make_unique<PKW>("Car1", 120.0, 20, 300);
    auto car2 = std::make_unique<PKW>("Car2", 150.0, 15, 300);
    auto fah1 = std::make_unique<Fahrrad>("Fah1", 300);

    weg1.vAnnahme(move(car1), 3.0);
    weg1.vAnnahme(move(car2));
    weg2.vAnnahme(move(fah1));

    bInitialisiereGrafik(800, 500);
    int coords1[] = {700, 250, 100, 250};
    bZeichneStrasse(weg1.sGetName(), "hebele", 500, 2, coords1);
    int coords2[] = {300, 400, 500, 250};
    bZeichneStrasse(weg2.sGetName(), "hebeler", 500, 2, coords2);

    cout << weg1 << endl << weg2 << endl << endl;
    Fahrzeug::vKopf();

    while (dGlobaleZeit <= dEndZeit) {
        try {
            weg1.vSimulieren();
            weg2.vSimulieren();
        } catch (Fahrausnahme& ex) {
            ex.vBearbeiten();
        }

        vSleep(100);

        dGlobaleZeit += dZeittakt;
    }
}

void vAufgabe6a() {
    vertagt::VListe<int> liste;

    const int seed = 0;
    static std::mt19937 device(seed);
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < 15; ++i) {
    	liste.push_back(dist(device));
    }

    liste.vAktualisieren();

    std::cout << "Initialisierung: ";
	for (auto it = liste.begin(); it != liste.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

    for (auto it = liste.begin(); it != liste.end(); ++it) {
        if (*it > 5)
            liste.erase(it);
    }

    std::cout << "Nach der erase rufe (Noch keine Aktualisierung): ";
	for (auto it = liste.begin(); it != liste.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

    liste.vAktualisieren();

    std::cout << "Nach vAktualisieren(): ";
	for (auto it = liste.begin(); it != liste.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

    liste.push_front(1);
    liste.push_back(10);
    liste.vAktualisieren();

    std::cout << "Nach der push_front/push_back + Aktualisierung: ";
	for (auto it = liste.begin(); it != liste.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";
}

void vAufgabe6b() {
    Weg weg1("Hin1", 500.0, Tempolimit::Autobahn);
    Weg weg2("Hin2", 500.0, Tempolimit::Autobahn);

    auto car1 = std::make_unique<PKW>("Car1", 120.0, 20, 300);
    auto car2 = std::make_unique<PKW>("Car2", 150.0, 15, 300);
    auto fah1 = std::make_unique<Fahrrad>("Fah1", 300);

    weg1.vAnnahme(std::move(car1), 3.0);
    weg1.vAnnahme(std::move(car2));
    weg2.vAnnahme(std::move(fah1));
    weg1.vErsteInnitAkt();
    weg2.vErsteInnitAkt();

    bInitialisiereGrafik(800, 500);
    int coords1[] = {700, 250, 100, 250};
    bZeichneStrasse(weg1.sGetName(), "hebele", 500, 2, coords1);
    int coords2[] = {300, 400, 500, 250};
    bZeichneStrasse(weg2.sGetName(), "hebeler", 500, 2, coords2);

    Weg::vKopf();
    std::cout << weg1 << std::endl << weg2 << std::endl << std::endl;
    Fahrzeug::vKopf();

    while (dGlobaleZeit <= dEndZeit)
    {
    	vSetzeZeit(dGlobaleZeit);
        weg1.vSimulieren();
        weg2.vSimulieren();

        vSleep(100);
        dGlobaleZeit += dZeittakt;
    }

    Weg::vKopf();
    std::cout << weg1 << std::endl << weg2 << std::endl << std::endl;
}

void vAufgabe7() {
	auto Kr1 = std::make_shared<Kreuzung>("Kr1", 0.0);
	auto Kr2 = std::make_shared<Kreuzung>("Kr2", 1000.0);
	auto Kr3 = std::make_shared<Kreuzung>("Kr3", 0.0);
	auto Kr4 = std::make_shared<Kreuzung>("Kr4", 0.0);

	// Straße1: W12 / W21; 40km; 50 km/h (Innenorts)
	// Straße2: W23a / W32a; 115km; unlimited (Autobahn)
	// Straße3: W23b / W32b; 40km; 50 km/h (Innenorts)
	// Straße4: W24 / W42; 55km; 50 km/h (Innenorts)
	// Straße5: W34 / W43; 85km; unlimited (Autobahn)
	// Straße6: W44a / W44b; 130km; 100 km/h (Landstraße)

	Kreuzung::vVerbinde("W12", "W21", 40.0, Kr1, Kr2, Tempolimit::Innenorts);
	Kreuzung::vVerbinde("W23a", "W32a", 115.0, Kr2, Kr3, Tempolimit::Autobahn);
	Kreuzung::vVerbinde("W23b", "W32b", 40.0, Kr2, Kr3, Tempolimit::Innenorts);
	Kreuzung::vVerbinde("W24", "W42", 55.0, Kr2, Kr4, Tempolimit::Innenorts);
	Kreuzung::vVerbinde("W34", "W43", 85.0, Kr3, Kr4, Tempolimit::Autobahn);
	Kreuzung::vVerbinde("W44a", "W44b", 130.0, Kr4, Kr4, Tempolimit::Landstraße);

	bInitialisiereGrafik(1000, 650);
	bZeichneKreuzung(680, 40);  // Kr1
	bZeichneKreuzung(680, 300);  // Kr2
	bZeichneKreuzung(680, 570);  // Kr3
	bZeichneKreuzung(320, 300);  // Kr4

	// Straße1
	{
		int c[] = { 680, 40, 680, 300 };
		bZeichneStrasse("W12", "W21", 40, 2, c);
	}

	// Straße2
	{
		int c[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
		bZeichneStrasse("W23a", "W32a", 115, 6, c);
	}

	// Straße3
	{
		int c[] = { 680, 300, 680, 570 };
		bZeichneStrasse("W23b", "W32b", 40, 2, c);
	}

	// Straße4
	{
		int c[] = { 320, 300, 680, 300 };
		bZeichneStrasse("W42", "W24", 55, 2, c);
	}

	// Straße5
	{
		int c[] = { 320, 300, 320, 420, 350, 510, 500, 570, 680, 570 };
		bZeichneStrasse("W43", "W34", 85, 5, c);
	}

	// Straße6
	{
		int c[] = { 320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300 };
		bZeichneStrasse("W44a", "W44b", 130, 7, c);
	}

	auto car1 = std::make_unique<PKW>("Car1", 120.0, 8.0, 80.0);
	auto car2 = std::make_unique<PKW>("Car2", 150.0, 0.0, 60.0);
	auto fah1 = std::make_unique<Fahrrad>("Fah1", 25.0);

	Kr1->vAnnahme(std::move(car1), 3.0);
	Kr1->vAnnahme(std::move(car2), 0.0);
	Kr1->vAnnahme(std::move(fah1), 0.0);

	Fahrzeug::vKopf();

	while (dGlobaleZeit <= dEndZeit) {
		vSetzeZeit(dGlobaleZeit);

		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();

		vSleep(300);
		dGlobaleZeit += dZeittakt;
	}
}

int main() {
	vAufgabe7();
	return 0;
}
