#include "UzytkownikMenedzer.h"

void UzytkownikMenedzer::rejestracjaUzytkownika() {
    Uzytkownik uzytkownik = podajDaneNowegoUzytkownika();

    uzytkownicy.push_back(uzytkownik);
    plikZUzytkownikami.dopiszUzytkownikaDoPliku(uzytkownik);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;
    system("pause");
}

Uzytkownik UzytkownikMenedzer::podajDaneNowegoUzytkownika() {
    Uzytkownik uzytkownik;
    string login;
    string haslo;

    uzytkownik.ustawId(pobierzIdNowegoUzytkownika());

    do {
        cout << "Podaj login: ";
        cin >> login;
        uzytkownik.ustawLogin(login);
    } while (czyIstniejeLogin(uzytkownik.pobierzLogin()) == true);

    cout << "Podaj haslo: ";
    cin >> haslo;

    uzytkownik.ustawHaslo(haslo);

    return uzytkownik;
}

void UzytkownikMenedzer::ustawIdZalogowanegoUzytkownika(int noweId) {
    idZalogowanegoUzytkownika = noweId;
}

int UzytkownikMenedzer::pobierzIdNowegoUzytkownika() {
    if (uzytkownicy.empty() == true)
        return 1;
    else
        return uzytkownicy.back().pobierzId() + 1;
}

bool UzytkownikMenedzer::czyIstniejeLogin(string login) {
    int dlugoscWektoraUzytkownicy = uzytkownicy.size();

    for (int i = 0; i < dlugoscWektoraUzytkownicy; i++) {
        if (uzytkownicy[i].pobierzLogin() == login) {
            cout << endl << "Istnieje uzytkownik o takim loginie." << endl;
            return true;
        }
    }
    return false;
}

void UzytkownikMenedzer::logowanieUzytkownika() {
    Uzytkownik uzytkownik;
    string login = "", haslo = "";
    int dlugoscWektoraUzytkownicy = uzytkownicy.size();

    cout << endl << "Podaj login: ";
    login = MetodyPomocnicze::wczytajLinie();

    for (int i = 0; i < dlugoscWektoraUzytkownicy; i++) {
        if (uzytkownicy[i].pobierzLogin() == login) {
            for (int iloscProb = 3; iloscProb > 0; iloscProb--) {
                cout << "Podaj haslo. Pozostalo prob: " << iloscProb << ": ";
                haslo = MetodyPomocnicze::wczytajLinie();

                if (uzytkownicy[i].pobierzHaslo() == haslo) {
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    ustawIdZalogowanegoUzytkownika(uzytkownicy[i].pobierzId());
                    return;
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo." << endl;
            system("pause");
            return;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl << endl;
    system("pause");
    return;
}

void UzytkownikMenedzer::zmianaHaslaZalogowanegoUzytkownika() {
    string noweHaslo = "";
    cout << "Podaj nowe haslo: ";
    noweHaslo = MetodyPomocnicze::wczytajLinie();
    int dlugoscWektoraUzytkownicy = uzytkownicy.size();

    for (int i = 0; i < dlugoscWektoraUzytkownicy; i++) {
        if (uzytkownicy[i].pobierzId() == idZalogowanegoUzytkownika) {
            uzytkownicy[i].ustawHaslo(noweHaslo);
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
        }
    }
    plikZUzytkownikami.zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);
}

void UzytkownikMenedzer::wylogowanieUzytkownika() {
    idZalogowanegoUzytkownika = 0;
}

int UzytkownikMenedzer::pobierzIdZalogowanegoUzytkownika() {
    return idZalogowanegoUzytkownika;
}

bool UzytkownikMenedzer::czyUzytkownikJestZalogowany() {
    if (idZalogowanegoUzytkownika > 0) {
        return true;
    } else {
        return false;
    }
}
