#ifndef ADRESATMENEDZER_H
#define ADRESATMENEDZER_H

#include <iostream>
#include <vector>
#include "Adresat.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PlikZAdresatami.h"

class AdresatMenedzer {
    Adresat podajDaneNowegoAdresata(int idZalogowanegoUzytkownika, int idOstatniegoAdresata);
    PlikZAdresatami plikZAdresatami;
    string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);
public:
    AdresatMenedzer(string nazwaPlikuZAdresatami) : plikZAdresatami(nazwaPlikuZAdresatami) {};
    int dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika, int idOstatniegoAdresata);
    int wczytajAdresatowZalogowanegoUzytkownikaZPliku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika);
    void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci);
    void wyswietlDaneAdresata(Adresat adresat);
};

#endif
