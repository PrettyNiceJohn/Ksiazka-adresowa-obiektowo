#include "AdresatMenedzer.h"

Adresat AdresatMenedzer::podajDaneNowegoAdresata() {
    Adresat adresat;

    if (pobierzIdUsunietegoAdresata() >= plikZAdresatami.pobierzIdOstatniegoAdresata()){
        adresat.ustawId(pobierzIdUsunietegoAdresata());
    } else {
        adresat.ustawId((plikZAdresatami.pobierzIdOstatniegoAdresata() + 1));
    }

    adresat.ustawIdUzytkownika(ID_ZALOGOWANEGO_UZYTKOWNIKA);

    cout << "Podaj imie: ";
    adresat.ustawImie(MetodyPomocnicze::wczytajLinie());
    adresat.ustawImie(MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.pobierzImie()));

    cout << "Podaj nazwisko: ";
    adresat.ustawNazwisko(MetodyPomocnicze::wczytajLinie());
    adresat.ustawNazwisko(MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.pobierzNazwisko()));

    cout << "Podaj numer telefonu: ";
    adresat.ustawNumerTelefonu(MetodyPomocnicze::wczytajLinie());

    cout << "Podaj email: ";
    adresat.ustawEmail(MetodyPomocnicze::wczytajLinie());

    cout << "Podaj adres: ";
    adresat.ustawAdres(MetodyPomocnicze::wczytajLinie());

    return adresat;
}

void AdresatMenedzer::dodajAdresata() {
    Adresat adresat;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;
    adresat = podajDaneNowegoAdresata();

    adresaci.push_back(adresat);
    plikZAdresatami.dopiszAdresataDoPliku(adresat);
}

void AdresatMenedzer::wyswietlWszystkichAdresatow() {
    system("cls");
    if (!adresaci.empty()) {
        cout << "             >>> ADRESACI <<<" << endl;
        cout << "-----------------------------------------------" << endl;

        for (vector<Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            wyswietlDaneAdresata(*itr);
        }
        cout << endl;
    } else {
        cout << endl << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void AdresatMenedzer::wyswietlDaneAdresata(Adresat adresat) {
    cout << endl << "Id:                 " << adresat.pobierzId() << endl;
    cout << "Imie:               " << adresat.pobierzImie() << endl;
    cout << "Nazwisko:           " << adresat.pobierzNazwisko() << endl;
    cout << "Numer telefonu:     " << adresat.pobierzNumerTelefonu() << endl;
    cout << "Email:              " << adresat.pobierzEmail() << endl;
    cout << "Adres:              " << adresat.pobierzAdres() << endl;
}

void AdresatMenedzer::wyszukajAdresatowPoImieniu() {
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> WYSZUKIWANIE ADRESATOW O IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        imiePoszukiwanegoAdresata = MetodyPomocnicze::wczytajLinie();
        imiePoszukiwanegoAdresata = MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (vector <Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzImie() == imiePoszukiwanegoAdresata) {
                wyswietlDaneAdresata(*itr);
                iloscAdresatow++;
            }
        }
        wyswietlIloscWyszukanychAdresatow(iloscAdresatow);
    } else {
        cout << endl << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void AdresatMenedzer::wyswietlIloscWyszukanychAdresatow(int iloscAdresatow) {
    if (iloscAdresatow == 0)
        cout << endl << "W ksiazce adresowej nie ma adresatow z tymi danymi." << endl;
    else
        cout << endl << "Ilosc adresatow w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
}

void AdresatMenedzer::wyszukajAdresatowPoNazwisku() {
    string nazwiskoPoszukiwanegoAdresata;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> WYSZUKIWANIE ADRESATOW O NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        nazwiskoPoszukiwanegoAdresata = MetodyPomocnicze::wczytajLinie();
        nazwiskoPoszukiwanegoAdresata = MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzNazwisko() == nazwiskoPoszukiwanegoAdresata) {
                wyswietlDaneAdresata(*itr);
                iloscAdresatow++;
            }
        }
        wyswietlIloscWyszukanychAdresatow(iloscAdresatow);
    } else {
        cout << endl << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    cout << endl;
    system("pause");
}

void AdresatMenedzer::usunAdresata() {
    int idUsuwanegoAdresata = 0, brakZgodnosci = 0, dlugoscWektora = adresaci.size();
    string idStr = "";
    char wybor;

    system("cls");
    cout << "     >>> Usun adresata <<<" << endl << endl;

    if (dlugoscWektora == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
    } else {
        cout << "Podaj numer identyfikacyjny osoby, ktora chcesz usunac: ";

        idStr = MetodyPomocnicze::wczytajLinie();
        idUsuwanegoAdresata = MetodyPomocnicze::konwersjaStringNaInt(idStr);

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idUsuwanegoAdresata) {
                wyswietlDaneAdresata(*itr);
                cout << endl;
                cout << "Czy na pewno chcesz usunac dana osobe? [t/n] ";
                wybor = MetodyPomocnicze::wczytajZnak();

                if (wybor == 't') {
                    adresaci.erase(itr);

                    plikZAdresatami.usunAdresataZPliku(idUsuwanegoAdresata);

                    ustawIdUsunietegoAdresata(idUsuwanegoAdresata);

                    cout << endl << "Usuwanie danych zakonczone powodzeniem!" << endl << endl;
                    system("pause");
                    break;
                } else if (wybor == 'n') {
                    cout << endl << "Wstrzymano usuwanie danych!" << endl << endl;
                    system("pause");
                    break;
                } else {
                    cout << endl << "Musisz wpisac tak[t] lub nie[n]!" << endl << endl;
                    system("pause");
                }
            }  else {
                brakZgodnosci++;
            }
        }
        if (brakZgodnosci == dlugoscWektora) {
            cout << endl << "W ksiazce adresowej nie ma osoby o podanym numerze identyfikacyjnym!" << endl << endl;
            system("pause");
        } else if (adresaci.size() == 0) {
            cout << "Ksiazka adresowa jest teraz pusta!" << endl << endl;
            system("pause");
        }
    }
}

void AdresatMenedzer::edytujDaneAdresata() {
    string idString = "";
    int idAdresataDoEdycji, brakZgodnosci = 0, dlugoscWektora = adresaci.size();
    char wybor;

    system("cls");
    cout << "      >>> Edytuj dane adresata <<<" << endl << endl;

    if (dlugoscWektora == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
        system("pause");
    } else {
        cout << "Podaj numer identyfikacyjny osoby, ktorej chcesz edytowac dane: ";
        idString = MetodyPomocnicze::wczytajLinie();
        idAdresataDoEdycji = MetodyPomocnicze::konwersjaStringNaInt(idString);

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idAdresataDoEdycji) {
                wyswietlDaneAdresata(*itr);
                cout << endl;
                cout << "Czy chcesz edytowac dane podanej osoby? [t/n] ";
                wybor = MetodyPomocnicze::wczytajZnak();

                if (wybor == 't') {
                    wybierzDaneDoEdycji(idAdresataDoEdycji);
                    break;
                } else if (wybor == 'n') {
                    cout << endl << "Wstrzymano edycje danych!" << endl << endl;
                    system("pause");
                    break;
                } else {
                    cout << endl << "Musisz wpisac tak[t] lub nie[n]!" << endl << endl;
                    Sleep(1500);
                }
            }  else {
                brakZgodnosci++;
            }
        }
        if (brakZgodnosci == dlugoscWektora) {
            cout << endl << "W ksiazce adresowej nie ma osoby o podanym numerze identyfikacyjnym!" << endl << endl;
            system("pause");
        }
    }
}

void AdresatMenedzer::wybierzDaneDoEdycji(int idAdresataDoEdycji) {
    char wybor;
    string imie, nazwisko, numerTelefonu, email, adres;
    vector<string> daneDoEdycji;

    system ("cls");
    cout << "  >>> Edytuj dana adresata <<<" << endl << endl;
    cout << "Wybierz dane do edycji: " << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu" << endl;
    cout << endl << "Twoj wybor: ";
    wybor = MetodyPomocnicze::wczytajZnak();
    cout << endl;

    switch (wybor) {
    case '1':
        system("cls");
        cout << "  > Imie <" << endl << endl;

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idAdresataDoEdycji) {
                cout << "Stare: " << itr -> Adresat::pobierzImie() << endl;
                cout << "Nowe: ";
                imie = MetodyPomocnicze::wczytajLinie();
                imie = MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);

                daneDoEdycji.push_back(itr -> Adresat::pobierzImie());
                daneDoEdycji.push_back(imie);

                itr -> Adresat::ustawImie(imie);
            }
        }
        plikZAdresatami.zmienDaneAdresataWPliku(daneDoEdycji, idAdresataDoEdycji);
        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '2':
        system("cls");
        cout << "  > Nazwisko <" << endl << endl;

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idAdresataDoEdycji) {
                cout << "Stare: " << itr -> Adresat::pobierzNazwisko() << endl;
                cout << "Nowe: ";
                nazwisko = MetodyPomocnicze::wczytajLinie();
                nazwisko = MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);

                daneDoEdycji.push_back(itr -> Adresat::pobierzNazwisko());
                daneDoEdycji.push_back(nazwisko);

                itr -> Adresat::ustawNazwisko(nazwisko);
            }
        }
        plikZAdresatami.zmienDaneAdresataWPliku(daneDoEdycji, idAdresataDoEdycji);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '3':
        system("cls");
        cout << "  > Numer telefonu <" << endl << endl;

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idAdresataDoEdycji) {
                cout << "Stary: " << itr -> Adresat::pobierzNumerTelefonu() << endl;
                cout << "Nowy: ";
                numerTelefonu = MetodyPomocnicze::wczytajLinie();

                daneDoEdycji.push_back(itr -> Adresat::pobierzNumerTelefonu());
                daneDoEdycji.push_back(numerTelefonu);

                itr -> Adresat::ustawNumerTelefonu(numerTelefonu);
            }
        }
        plikZAdresatami.zmienDaneAdresataWPliku(daneDoEdycji, idAdresataDoEdycji);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '4':
        system("cls");
        cout << "  > Email <" << endl << endl;

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idAdresataDoEdycji) {
                cout << "Stary: " << itr -> Adresat::pobierzEmail() << endl;
                cout << "Nowy: ";
                email = MetodyPomocnicze::wczytajLinie();

                daneDoEdycji.push_back(itr -> Adresat::pobierzEmail());
                daneDoEdycji.push_back(email);

                itr -> Adresat::ustawEmail(email);
            }
        }
        plikZAdresatami.zmienDaneAdresataWPliku(daneDoEdycji, idAdresataDoEdycji);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '5':
        system("cls");
        cout << "  > Adres <" << endl << endl;

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr -> Adresat::pobierzId() == idAdresataDoEdycji) {
                cout << "Stary: " << itr -> Adresat::pobierzAdres() << endl;
                cout << "Nowy: ";
                adres = MetodyPomocnicze::wczytajLinie();

                daneDoEdycji.push_back(itr -> Adresat::pobierzAdres());
                daneDoEdycji.push_back(adres);

                itr -> Adresat::ustawAdres(adres);
            }
        }
        plikZAdresatami.zmienDaneAdresataWPliku(daneDoEdycji, idAdresataDoEdycji);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '6':
        break;
    default:
        cout << "Musisz wybrac cyfre od 1 do 6!" << endl;
        Sleep(1500);
        break;
    }
}

int AdresatMenedzer::pobierzIdUsunietegoAdresata(){
    return idUsunietegoAdresata;
}

void AdresatMenedzer::ustawIdUsunietegoAdresata(int idUsuwanegoAdresata){
    idUsunietegoAdresata = idUsuwanegoAdresata;
}
