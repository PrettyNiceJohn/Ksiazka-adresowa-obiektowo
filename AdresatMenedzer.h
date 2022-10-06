#ifndef ADRESATMENEDZER_H
#define ADRESATMENEDZER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>

#include "Adresat.h"
#include "PlikZAdresatami.h"

class AdresatMenedzer {
    const int ID_ZALOGOWANEGO_UZYTKOWNIKA;
    vector<Adresat> adresaci;
    Adresat podajDaneNowegoAdresata();
    string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);
    PlikZAdresatami plikZAdresatami;
    void wyswietlDaneAdresata(Adresat adresat);
    void wyswietlIloscWyszukanychAdresatow(int iloscAdresatow);
    void wybierzDaneDoEdycji(int idAdresataDoEdycji);

public:
    AdresatMenedzer(string nazwaPlikuZAdresatami, int idZalogowanegoUzytkownika)
        : ID_ZALOGOWANEGO_UZYTKOWNIKA(idZalogowanegoUzytkownika), plikZAdresatami(nazwaPlikuZAdresatami) {
        adresaci = plikZAdresatami.wczytajAdresatowZalogowanegoUzytkownikaZPliku(ID_ZALOGOWANEGO_UZYTKOWNIKA);
    };
    void dodajAdresata();
    void wyswietlWszystkichAdresatow();
    void wyszukajAdresatowPoImieniu();
    void wyszukajAdresatowPoNazwisku();
    void usunAdresata();
    void edytujDaneAdresata();
};

#endif
