#include <iostream>

//zeby mozna bylo uzywac stalych z biblioteki
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>
#include "CrackTimer.h"

using namespace std;

//do reguly simpsona wartosci te musza byc parzyste, im wieksze tym lepsza dokladnosc

static long double m = 0;
static long double s = 1;

//bedziemy uzywac reguly simpsona, zeby liczyc odpowiednie calki

long double normal_distribution(const long  double& s, const long double& m, const long double& lower_bound, const long double& upper_bound)
{
    long double mianownik = s * sqrt(2 * M_PI);
    long double sSquare = 2 * pow(s, 2);


    //delta simpsona, nasze n w delcie ustawilismy sobie na 4, n musi być liczbą parzystą, im większe n, tym większa dokladnosc
    //ale tracimy na szybkosci obliczen
    long double deltaX = (upper_bound - lower_bound) / 16384;
    long double x = lower_bound;
    long double sum = 0;

    //obliczamy wartosci poczatkowe i koncowe, bo one jako jedyne nie są mnożone przez 4 lub 2
    long double XminusM = -pow((x - m), 2);
    long double XminusMKonc = -pow((upper_bound - m), 2);

    sum += (1 / mianownik) * exp(XminusM / sSquare);
    sum += (1 / mianownik) * exp(XminusMKonc / sSquare);

    x += deltaX;

    int iteracja = 1;

    while (x <upper_bound)
    {
        long double XminusMPow = -pow((x - m), 2);
        if (iteracja % 2 == 0)
            sum += 2 * (1 / mianownik) * exp(XminusMPow / sSquare);
        else
            sum += 4 * (1 / mianownik) * exp(XminusMPow / sSquare);

        x += deltaX;
        iteracja++;
    }

    return (deltaX / 3) * sum;
}

int main()
{

    cout << "N(" << m << "," << s << ")" << "\n";

    while (true)
    {
        double a = 0, b = 0;
        string komenda;
        cin >> komenda;

        if (komenda == "Both")
        {
            cin >> m >> s;
            cout << "N(" << m << "," << s << ")" << "\n";
        }
        else if (komenda == "Mean")
        {
            cin >> m;
            cout << "N(" << m << "," << s << ")" << "\n";
        }
        else if (komenda == "Std")
        {
            cin >> s;
            cout << "N(" << m << "," << s << ")" << "\n";
        }

        //jako ze nie obliczamy z calki z nieskonczonosci roznych, to dodajmy lub odejmujemy jakas liczbe
        //nie da sie osiagnac idealnej precyzji, ale im blizej konca funkcji jestesmy, tym mniej na niej tracimy
        //mozna sobie pozmieniac te wartosci, albo pododawac np 10 i sprawdzic jak sie zmieni dokladnosc
        else if (komenda == "Over")
        {
            cin >> a >> b;
            CrackTimer timer;
            timer.StartTimer();
            cout << normal_distribution(s, m, a, b) << "\n";
            timer.EndTimer();
            cout << timer.ShowTime(CrackTimer::TimeUnit::MICROSECONDS) << "mcs \n";
        }
        else if (komenda == "Final")
        {
            cin >> a;
            cout << normal_distribution(s, m, a - 100, a) << "\n";
        }
        else if (komenda == "Initial")
        {
            cin >> a;
            cout << normal_distribution(s, m, a, a + 100) << "\n";
        }
        else if (komenda == "Outside")
        {
            cin >> a >> b;
            cout << normal_distribution(s, m, a - 100, a) + normal_distribution(s, m, b, b + 100) << "\n";
        }
        else
            break;
    }
}
