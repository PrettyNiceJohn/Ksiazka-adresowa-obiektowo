#ifndef PLIKZADRESATAMI_H
#define PLIKZADRESATAMI_H

#include <iostream>
#include <vector>
#include <fstream>

#include "Adresat.h"
#include "MetodyPomocnicze.h"
#include "PlikTekstowy.h"

using namespace std;

class PlikZAdresatami : public PlikTekstowy {
    string zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat);
    int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami);
    int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    int idOstatniegoAdresata;
    int idUsunietegoAdresata;
    int policzWszystkichAdresatow();

public:
    PlikZAdresatami(string nazwaPliku) : PlikTekstowy(nazwaPliku) {
        idOstatniegoAdresata = 0;
        idUsunietegoAdresata = 0;
    };

    void dopiszAdresataDoPliku(Adresat adresat);
    vector<Adresat> wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika);
    int pobierzIdOstatniegoAdresata();
    void usunAdresataZPliku(int idUsuwanegoAdresata);
    void zmienDaneAdresataWPliku(vector<string> daneDoEdycji, int idAdresataDoEdycji);
    int ustawIdOstatniegoAdresata();
    void ustawIdUsunietegoAdresata(int idUsuwanegoAdresata);
    int pobierzIdUsunietegoAdresata();
};

#endif
