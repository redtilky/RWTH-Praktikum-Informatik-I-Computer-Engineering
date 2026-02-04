# RWTH Praktikum Informatik I – Fahrzeug-Simulation (Computer Engineering)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![OOP](https://img.shields.io/badge/OOP-Polymorphie%20%7C%20Vererbung%20%7C%20RAII-success)
![Pattern](https://img.shields.io/badge/Design%20Patterns-Strategy%20%7C%20Exceptions-orange)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)
![Status](https://img.shields.io/badge/Status-Work%20in%20Progress-yellow)

**Kurzbeschreibung:**  
Dieses Projekt implementiert eine objektorientierte **Verkehrs-/Fahrzeug-Simulation** in **C++**. Fahrzeuge bewegen sich auf **Wegen**, werden an **Kreuzungen** weitergeleitet und können abhängig vom **Verhalten** (z. B. *Fahren*, *Parken*) unterschiedliche Aktionen ausführen. Ereignisse wie *Streckenende* und *Losfahren* werden über eigene **Ausnahmeklassen** modelliert und verarbeitet.

---

## Inhalte / Features

### ✅ Objektmodell
- `Simulationsobjekt`  
  Abstrakte Basisklasse (Name, ID, Zeitstempel; globale Simulationszeit).
- `Fahrzeug`  
  Basisklasse mit gemeinsamen Zuständen (Strecke, Zeit, Verhalten).
- Spezialisierungen:
  - `PKW` (Verbrauch, Tankvolumen, Tankinhalt)
  - `Fahrrad` (Ermüdungsmodell → sinkende effektive Geschwindigkeit)
- `Weg`  
  Streckenabschnitt mit **Länge**, **Tempolimit**, Rückweg und optionaler Zielkreuzung; verwaltet Fahrzeuge.
- `Kreuzung`  
  Knotenpunkt; verwaltet ausgehende Wege; optional **Tankstelle**.

### ✅ Bewegungsmodell (Strategy Pattern)
- `Verhalten` als abstrakte Schnittstelle
- `Fahren` berechnet die fahrbare Strecke im Zeitintervall
- `Parken` blockiert bis zu einer Startzeit und löst danach ein *Losfahren*-Ereignis aus

### ✅ Ereignisse / Exceptions
- `Fahrausnahme` (abstrakt) kapselt Kontext: **Fahrzeug + Weg**
- `Streckenende`: Wegende erreicht → Abgabe/Übergabe an Kreuzung und Wahl eines neuen Weges
- `Losfahren`: Ereignis beim Start nach Parkphase

### ✅ Sichere Container-Modifikation
- `vertagt::VListe` + `VAktion`-Mechanismus  
  Ermöglicht Einfügen/Löschen während Iteration (verzögerte Ausführung).

### ✅ Visualisierung (SimuClient)
- Einbindung über `SimuClient` / `SimuClientSocket`  
  (z. B. `bZeichnePKW`, `bZeichneFahrrad`) für eine grafische Darstellung der Simulation.

---

## Projektstruktur

```text
Core/
  Inc/                 Header
  Src/                 Implementierungen
Debug/                 Build-Artefakte (sollten i. d. R. nicht versioniert werden)
SimuServer.jar         Server/Visualisierung (projektspezifisch)
