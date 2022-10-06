#ifndef METODYPOMOCNICZE_H
#define METODYPOMOCNICZE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class MetodyPomocnicze {
public:
    static string konwerjsaIntNaString(int liczba);
    static string wczytajLinie();
    static char wczytajZnak();
    static string pobierzLiczbe(string tekst, int pozycjaZnaku);
    static int konwersjaStringNaInt(string liczba);
};

#endif
