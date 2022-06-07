//Kacper Jajuga, kierunek: informatyka, rok I, semestr II

#include <iostream>
#include <iomanip>
#include <ctime>

#define St 40   //stala - rozmiar tablicy z ocenami
#define Oc 11   //stala - rozmiar tablicy z iloscia konkretnych ocen

void zbieranieOcen(int tab[], int rozmiar);         //losowanie ocen do tablicy
void wyswietlanieTablicy(int tab[], int rozmiar);   //funkcja wyswietli wylosowana i posortowana tablice z ocenami
void sortowanieQuickSort(int tab[], int poczatekTab, int koniecTab);    //ta i nastepne 2 funkcje posortuja tablice
int dzielenieTablicy(int tab[], int poczatekTab, int koniecTab);
void zamienMiejscami(int &a, int &b);
double sredniaOcen(int tab[], int rozmiar); //pierwszy podpunkt zadania, srednia ocen
void ileOcen(int tab1[], int tab2[], int rozmiarTab1, int rozmiarTab2); //drugi punkt zadania, funkcja wyswietli ile studentow przyznalo kazda z ocen
int iloscNajwOcen(int tab[], int rozmiar);  //funkcja zwroci ile studentow przyznalo dana ocene najwieksza ilosc razy, przydatne do trzeciego i ostatniego punktu zadania
void ktoraOcena(int tab[], int rozmiar, int ilNajwOc);  //trzeci punkt zadania, funkcja wyswietli ocene lub oceny przyznane najwieksza ilosc razy
double medianaOcen(int tab[], int rozmiar); //czwarty punkt zadania, funkcja zwroci mediane
void tworzenieHistogramu(int tab[], int osX, int osY);  //piaty punkt zadania, funkcja wyswietli histogram

using namespace std;

int main()
{
    srand(time(NULL));
    int Oceny[St], IloscOcen[Oc];
    int najwiekszaOcena;    //zmienna przechowujaca ilosc studentow, ktorzy przyznali dana ocene najwieksza ilosc razu
    double mediana; //zmienna przechowujaca wartosc mediany
    zbieranieOcen(Oceny, St);
    cout << "Czterdziestu studentow poproszono o ocene jakosci jedzenia w stolowce w skali od 0 do 10." << endl;
    cout << "Tak prezentuja sie oceny: " << endl;
    wyswietlanieTablicy(Oceny, St);
    sortowanieQuickSort(Oceny, 0, St-1);
    cout << "Nacisnij ENTER, aby wyswietlic posortowana tablice..." << endl;
    cin.ignore();
    cout << "Przeanalizujmy oceny." << endl;
    cout << "Posortujmy wiec nasze oceny od najmniejszej do najwiekszej: " << endl;
    wyswietlanieTablicy(Oceny, St);
    cout << "Nacisnij ENTER, aby wyswietlic srednia ocen..." << endl;
    cin.ignore();
    cout << "Srednia przyznanych przez studentow ocen wynosi: " << sredniaOcen(Oceny, St) << endl;
    cout << "\nNacisnij ENTER, aby wyswietlic ilu studentow przyznalo pewna ocene..." << endl;
    cin.ignore();
    ileOcen(IloscOcen, Oceny, Oc, St);
    cout << endl;
    for (int i = 0; i < Oc; i++){
        cout << "Ocene " << i << " przyznalo " << IloscOcen[i] << " studentow." << endl;
    }
    cout << "\nNacisnij ENTER, aby wyswietlic ktora ocene/y studenci przyznali najwieksza ilosc razy..." << endl;
    cin.ignore();
    najwiekszaOcena = iloscNajwOcen(IloscOcen, Oc);
    ktoraOcena(IloscOcen, Oc, najwiekszaOcena);
    cout << "\n\nNacisnij ENTER, aby wyswietlic mediane ocen..." << endl;
    cin.ignore();
    mediana = medianaOcen(Oceny, St);
    cout << "Mediana wynosi: " << mediana << endl;
    cout << "\nNacisnij ENTER, aby wyswietlic histogram ocen..." << endl;
    cin.ignore();
    cout << "Mozemy teraz stworzyc histogram, ktory pokaze liczebnosc poszczegolnych grup." << endl;
    cout << "Wyglada on tak:\n" << endl;
    tworzenieHistogramu(IloscOcen, Oc, najwiekszaOcena);
    return 0;
}

void zbieranieOcen(int tab[], int rozmiar){
    for(int i = 0; i < rozmiar; i++){
        tab[i] = rand()%11;     //losowanie ocen do tablicy z zakresu <0, 11>
    }
}

void wyswietlanieTablicy(int tab[], int rozmiar){
    for(int i =0; i < rozmiar; i++){
        cout << setw(5) << tab[i];
        if (i%5 == 4){ //instrukcja, dzieki ktorej po 5 wyswietlonych ocenach przeskoczy do nowej linijki, dziêki czemu (w mojej ocenie) jest to czytelniejsze
            cout << endl;
        }
    }
}

void sortowanieQuickSort(int tab[], int poczatekTab, int koniecTab){
    int p;
    if (poczatekTab >= koniecTab){
        return;
    }
        p = dzielenieTablicy(tab, poczatekTab, koniecTab);
        sortowanieQuickSort(tab, poczatekTab, p-1);
        sortowanieQuickSort(tab, p+1, koniecTab);
}

int dzielenieTablicy(int tab[], int poczatekTab, int koniecTab){
    int pivot = tab[koniecTab]; //ustawienie pivota na ostatnia liczbe w tabeli, pivot rownie dobrze moze byc losowa liczba

    int ileLiczbMniejszychLubRownych = 0;
    for (int i = poczatekTab; i < koniecTab; i++){  //sprawdzanie ile liczb w tabli jest mniejszych lub rownych od pivot
        if (tab[i] <= pivot){
            ileLiczbMniejszychLubRownych++;
        }
    }

    int miejscePivot;
    miejscePivot = poczatekTab + ileLiczbMniejszychLubRownych;  //ustalenie poprawnego miejsca pivot
    zamienMiejscami(tab[miejscePivot], tab[koniecTab]); //ustawienie pivot na poprawnym miejscu

    int i = poczatekTab, j = koniecTab;
    while (i < miejscePivot && j > miejscePivot){
        while (tab[i] <= pivot){
            i++;
        }
        while (tab[j] > pivot){
            j--;
        }
        if (i < miejscePivot && j > miejscePivot){
            zamienMiejscami(tab[i++], tab[j--]);
        }
    }

    return miejscePivot;
}

void zamienMiejscami(int &a, int &b){   //zamiana miejscami liczb podanych do funkcji, nie chcialem uzywac funkcji swap
    int pomocnicza = a;
    a = b;
    b = pomocnicza;
}

double sredniaOcen(int tab[], int rozmiar){
    double suma = 0;
    for (int i = 0; i < rozmiar; i++){
        suma += tab[i];
    }
    return suma/rozmiar;
}

void ileOcen(int tab1[], int tab2[], int rozmiarTab1, int rozmiarTab2){
    for (int i = 0; i < rozmiarTab1; i++){
        tab1[i] = 0; //zerowanie tablicy, inaczej zostana wyswietlone bledne liczby
    }

    for (int i = 0; i < rozmiarTab1; i++){
        for (int j = 0; j < rozmiarTab2; j++){
            if(tab2[j] == i){   //jezeli ocena jest rowna i...
                tab1[i]++;      //...to dodaj jednego ucznia do tablicy pod tym samym indeksem
            }
        }
    }
}

int iloscNajwOcen(int tab[], int rozmiar){
    int wartosc = tab[0];   //przypisanie pierwszej wartosci w tabeli jako najwiekszej ilosci ocen, zeby mozna bylo pozniej do niej porownywac
    for (int i = 1; i < rozmiar; i++){
        if (tab[i] > wartosc){
            wartosc = tab[i];
        }
    }
    return wartosc;
}

void ktoraOcena(int tab[], int rozmiar, int ilNajwOc){
    cout << "Najwieksza ilosc razy studenci przyznali ocene: ";
    for (int i = 0; i < rozmiar; i++){
        if(tab[i] == ilNajwOc){ //jesli wartosc komorki jest rowna najwiekszej ilosci ocen, to...
            cout << i << " ";   //...wyswietl ktora to ocena
        }
    }
}

double medianaOcen(int tab[], int rozmiar){
    if(rozmiar%2 == 0){ //tutaj nie musialem dawac if...else, jednak stwierdzilem, ze dzieki temu program bedzie bardziej uniwersalny
        double suma, srednia;
        suma = tab[(rozmiar/2)-1] + tab[rozmiar/2]; //w tym przypadku jest to suma 20 i 21 elementu tablicy
        srednia = suma/2;
        return srednia;
    }
    else
        return tab[rozmiar/2]; //w naszym programie mamy parzysta ilosc elementow tablicy, mimo wszystko napisalem ten fragment gdyby ktos chcial znalezc mediane w tablicy o nieparzystych elementach
}

void tworzenieHistogramu(int tab[], int osX, int osY){
    for (int i = osY; i > 0; i--){
        cout << setw(2) << i;   //wyswietlanie ilosci osob
        for (int j = 0; j < osX; j++){
            if(tab[j] >= i){    //jesli ilosc ocen jest wieksza lub rowna ilosci osob, ktore ja przyznaly, to...
                cout << setw(5) << "*"; //...wyswietl gwiazdke...
            }
            else{
                cout << setw(5) << " "; //... w przeciwnym wypadku wyswietl puste pole
            }
        }
        cout << endl;
    }
    cout <<"  "; //dzieki temu estetyczniej bedzie wygladal wykres
    for (int i = 0; i < osX; i++){

        cout << setw(5) << i;   //wyswietlanie konkretnych ocen
    }
}
