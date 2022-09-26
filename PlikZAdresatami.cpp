#include "PlikZAdresatami.h"

string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat) {
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}

void PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat) {
    string liniaZDanymiAdresata = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true) {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (MetodyPomocnicze::czyPlikJestPusty(plikTekstowy) == true) {
            plikTekstowy << liniaZDanymiAdresata;
        } else {
            plikTekstowy << endl << liniaZDanymiAdresata ;
        }
        idOstatniegoAdresata++;
        cout << "Nowy adresat zostal dodany" << endl;
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    plikTekstowy.close();
    system("pause");
}

vector<Adresat> PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika) {
    Adresat adresat;
    vector<Adresat> adresaci;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;

    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);

    if (plikTekstowy.good() == true) {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami)) {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami)) {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        plikTekstowy.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;
    }

    if (daneOstaniegoAdresataWPliku != "") {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstaniegoAdresataWPliku);
    }
    return adresaci;
}

int PlikZAdresatami::pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami) {
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));

    return idUzytkownika;
}

Adresat PlikZAdresatami::pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami) {
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1, dlugoscLiniiDanychAdresata = daneAdresataOddzielonePionowymiKreskami.length();

    for (int pozycjaZnaku = 0; pozycjaZnaku < dlugoscLiniiDanychAdresata; pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch(numerPojedynczejDanejAdresata) {
            case 1:
                adresat.ustawId(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 2:
                adresat.ustawIdUzytkownika(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 3:
                adresat.ustawImie(pojedynczaDanaAdresata);
                break;
            case 4:
                adresat.ustawNazwisko(pojedynczaDanaAdresata);
                break;
            case 5:
                adresat.ustawNumerTelefonu(pojedynczaDanaAdresata);
                break;
            case 6:
                adresat.ustawEmail(pojedynczaDanaAdresata);
                break;
            case 7:
                adresat.ustawAdres(pojedynczaDanaAdresata);
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

int PlikZAdresatami::pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami) {
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}

int PlikZAdresatami::pobierzIdOstatniegoAdresata() {
    return idOstatniegoAdresata;
}

void PlikZAdresatami::usunAdresataZPliku(int idUsuwanegoAdresata) {
    string linia = "", idPobraneZLinii = "";
    int idPobraneZLiniiInt = 0;

    ifstream file;
    file.open("Adresaci.txt");

    ofstream temp;
    temp.open("Przejsciowy plik adresaci.txt");

    if (file.good()) {
        while (getline(file,linia)) {
            int dlugoscLinii = linia.length();

            for (int i = 0; i < dlugoscLinii; i++) {
                if (linia[i] != '|') {
                    idPobraneZLinii += linia[i];
                } else {
                    break;
                }
            }
            idPobraneZLiniiInt = MetodyPomocnicze::konwersjaStringNaInt(idPobraneZLinii);

            if (idPobraneZLiniiInt != idUsuwanegoAdresata) {
                temp << linia << endl;
            }
            idPobraneZLiniiInt = 0;
            idPobraneZLinii = "";
        }
        temp.close();
        file.close();

        remove("Adresaci.txt");
        rename("Przejsciowy plik adresaci.txt", "Adresaci.txt");
    } else {
        cout << "Usuwanie danych z pliku zakonczone niepowodzeniem!" << endl << endl;
    }
}

void PlikZAdresatami::zmienDaneAdresataWPliku(vector<string> daneDoEdycji, int idAdresataDoEdycji) {
    string stareDane = daneDoEdycji[0], noweDane = daneDoEdycji[1];
    int dlugoscStarychDanych = stareDane.length(), idPobraneZLiniiInt = 0;
    string linia = "", idPobraneZLinii = "";

    ifstream file;
    file.open("Adresaci.txt");
    ofstream temp;
    temp.open("Przejsciowy plik adresaci.txt");

    while (getline(file,linia)) {
        int dlugoscLinii = linia.length();

        for (int i = 0; i < dlugoscLinii; i++) {
            if (linia[i] != '|') {
                idPobraneZLinii += linia[i];
            } else {
                break;
            }
        }
        idPobraneZLiniiInt = MetodyPomocnicze::konwersjaStringNaInt(idPobraneZLinii);

        if (idPobraneZLiniiInt == idAdresataDoEdycji) {
            linia.replace(linia.find(stareDane), dlugoscStarychDanych, noweDane);
            temp << linia << endl;
        } else {
            temp << linia << endl;
        }
        idPobraneZLiniiInt = 0;
        idPobraneZLinii = "";
    }
    temp.close();
    file.close();

    remove("Adresaci.txt");
    rename("Przejsciowy plik adresaci.txt", "Adresaci.txt");
}
