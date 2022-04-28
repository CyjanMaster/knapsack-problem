//Patryk Jędrzejewski
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
chrono::steady_clock sc;

struct rzeczy
{
    int numer, wartosc, waga;
    float stosunek;
};

rzeczy p[100];
int iloscrzeczy;
int miejsce = 0;
int wartoscplecaka = 0;

string filename="knapsack.txt";

//sortowanie struktury po wartosci/wage
bool compare(rzeczy a, rzeczy b)
{
    return a.stosunek > b.stosunek;
}


//sortowanie struktury po numerze
bool wroc(rzeczy a, rzeczy b)
{
    return a.numer < b.numer;
}


void zachlanny()
{

    sort(p, p + iloscrzeczy, compare);
    int tempmiejsce = miejsce;
    wartoscplecaka=0;
    cout << endl;
    for (int i = 0; i < iloscrzeczy; i++)
    {
        cout << p[i].numer << " " << p[i].wartosc << " " << p[i].waga << " " << p[i].stosunek << endl;
    }

    cout << endl;

    cout<<"You should take items: ";
    for (int i = 0; i < iloscrzeczy; i++)
    {
        if (p[i].waga <= tempmiejsce)
        {
            wartoscplecaka = wartoscplecaka + p[i].wartosc;
            tempmiejsce = tempmiejsce - p[i].waga;
            cout << p[i].numer << " ";
        }
    }

    cout << endl << "Items in backpack are worth "<<wartoscplecaka << " and take "<< miejsce-tempmiejsce<<" space "<<endl;


    sort(p, p + iloscrzeczy, wroc);

}


void dynamiczny()
{
    float tab[100][100] = { 0 };

    for (int i = 0; i <= iloscrzeczy; i++)
    {
        for (int j = 0; j <= miejsce; j++)
        {
            if (i == 0 || j == 70)
            {
                tab[i][j] = 0;
            }
            else
            {
                if (p[i - 1].waga > j)
                {
                    tab[i][j] = tab[i - 1][j];
                }
                else
                {
                    int temp = tab[i - 1][j - p[i - 1].waga] + p[i - 1].wartosc;


                    if (tab[i - 1][j] > temp)
                    {
                        tab[i][j] = tab[i - 1][j];
                    }
                    else
                    {
                        tab[i][j] = temp;
                    }
                }

            }

            cout << tab[i][j] << "\t";
            wartoscplecaka = tab[i][j];
        }
        cout << endl;
    }
    int h = 0;
    int stop = 0;
    int i = iloscrzeczy;
    int j = miejsce;
    int tempsuma=0;
    cout<<"You should take items: ";
    while (i != 0)
    {
        if (tab[i][j] > tab[i - 1][j])
        {
            cout << i << " ";
            j = j - p[i - 1].waga;
            i--;
            tempsuma=tempsuma+p[i].waga;
        }
        else
        {
            i--;
        }
    }
    cout << endl << "Items in backpack are worth "<< wartoscplecaka << " and take "<< tempsuma<<" space"<<endl;
}


int ileliczb = pow(2, iloscrzeczy) - 1;
int fmaks = 0;
int wynik[32] = { 0 };

void decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];

    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    int tempsumawag = 0;
    for (int j = 0; j < i; j++)
    {
        if (binaryNum[j] == 1)
        {
            tempsumawag = tempsumawag + p[j].waga;
        }
    }
    int fx = 0;
    if (tempsumawag <= miejsce)
    {

        for (int j = 0; j < i; j++)
        {
            if (binaryNum[j] == 1)
            {
                fx = fx + p[j].wartosc;
            }
        }
    }

    if (fx > fmaks)
    {
        fmaks = fx;
        for (int j = 0; j < i; j++)
        {
            wynik[j] = binaryNum[j];
        }
    }

}

void bruteforce()
{
    int ileliczb = pow(2, iloscrzeczy) - 1;
    for (int i = 1; i <= ileliczb; i++)
    {
        decToBinary(i);
    }
    cout<<"You should take items: ";
    int tempsum=0;
    for (int j = 0; j < iloscrzeczy; j++)
    {
        if (wynik[j] == 1)
        {
            cout << p[j].numer << " ";
            tempsum=tempsum+p[j].waga;
        }
    }
    cout << endl << "Items in backpack are worth "<< fmaks << " and take "<< tempsum<<" space"<<endl;
}

bool czyliczba(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}


int main(int argc, const char* argv[])
{
    int wyjscie = 0;
    int wyjscie2 = 0;

    ifstream plecak;
    plecak.open(filename);

    int c = 0;
    string e;
    srand(static_cast<unsigned int>(time(nullptr)));
    int x = 0;
    string xd;

    cout << "To choose an option, type equivalent number" << endl << "Input from file (specified in 'filename' variable) - 1" << endl << "Input from keyboard - 2" << endl << "Exit- 3" << endl;
    while (c != 1)
    {
        cin >> xd;
        if (czyliczba(xd))
        {
            x = stoi(xd);
            if ((x > 0) && (x <= 3))
            {
                c = 1;
            }
            else
                cout << "Entered value is invalid" << endl;
        }
        else
        {
            cout << "Entered value is invalid" << endl;
        }
    }

    if (x == 1)
    {
        plecak >> iloscrzeczy >> miejsce;
        int i = 0;
        int a,b;
        while (!plecak.eof())
        {
            plecak >> a >> b;

            p[i].waga=a;
            p[i].wartosc=b;
            p[i].stosunek = (float)(p[i].wartosc) / (float)(p[i].waga);
            p[i].numer = i + 1;
            i++;
        }
        plecak.close();
    }
    if (x == 2)
    {

        cout << "Enter number of items and capacity of backpack" << endl;

        string an;
        string bn;

        cin >> an;
        cin >> bn;

        if (czyliczba(an) && czyliczba(bn))
        {   int am, bm;
            am = stoi(an);
            bm = stoi(bn);
            iloscrzeczy=am;
            miejsce=bm;
        }
        else
        {
                cout << "Entered values are not numbers" << endl;
                return 0;
        }
        cout << "Weight of item, value of item" << endl;
        for(int i=0; i<iloscrzeczy; i++)
        {
            cout<<"Enter "<<iloscrzeczy-i<<" more pairs of numbers"<<endl;
            string ah;
            string bh;

            cin >> ah;
            cin >> bh;

            if (czyliczba(ah) && czyliczba(bh))
            {
                int ae, be;
                ae = stoi(ah);
                be = stoi(bh);
                    p[i].waga=ae;
                    p[i].wartosc=be;
                    p[i].stosunek=(float)(p[i].wartosc)/(float)(p[i].waga);
                    p[i].numer=i+1;
            }

            else
            {
                cout << "Entered values are not numbers, enter once more" << endl;
                i--;
            }
        }
    }
    if (x == 3)
    {
        return 0;
    }


    cout << "Backpack contain: " << endl;

    cout << "Number of an item / value / weight / value-weight ratio " << endl;
    for (int i = 0; i < iloscrzeczy; i++)
    {
        cout << p[i].numer << " " << p[i].wartosc << " " << p[i].waga << " " << p[i].stosunek << endl;
    }

    while (wyjscie2 == 0)
    {
        cout << endl;
        cout << "To choose an option, type equivalent number" << endl << "Dynamic algorithm - 1" << endl << "Greedy algorithm sorting value-weight ratio - 2" << endl;
        cout << "Brute force - 3" << endl << "Exit - 4" << endl;
        int h = 0;
        int f=0;
        string fe;
        while (h != 1)
        {
            cin >> fe;
            if (czyliczba(fe))
            {
                f = stoi(fe);
                if ((f > 0) && (f <= 4))
                {
                    h = 1;
                }
                else
                    cout << "Entered value is invalid" << endl;
            }
            else
            {
                cout << "Entered value is invalid" << endl;
            }
        }
        cout << endl;

        if (f == 1)
        {
                auto start = sc.now();
                dynamiczny();
                auto end = sc.now();

                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Knapsack problem using dynamic programming solved in " << time_span.count() << " microseconds." << endl;
        }
        if (f == 2)
        {

                auto start = sc.now();
                zachlanny();
                auto end = sc.now();

                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Knapsack problem using greedy algorithm solved in" << time_span.count() << " microseconds." << endl;


        }
       if (f == 3)
        {
                auto start = sc.now();
                bruteforce();
                auto end = sc.now();

                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Knapsack problem using brute force solved in " << time_span.count() << " microseconds." << endl;

        }

        if (f == 4)
        {
            wyjscie2 = 1;
        }
    }
}
