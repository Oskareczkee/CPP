#pragma once
#include <iostream>

void notes()
{
    //znaki polskie dzia�aj�
    //system("chcp 1250");
    //cout << "�ema";

    //dokonuje bezpiecznej inicjalizacji
    double x{ 0 };

    //zwraca b��d, konwersja jest zaw�aj�ca, u�ycie znaku "=" nie sprawdza, czy konwersja jest zaw�aj�ca
    //char charr{ x }; 

    //znaki polskie dzia�aj�
    system("chcp 1250");
    std::cout << "�ema";

    //dokonuje bezpiecznej inicjalizacji
    double x{ 0 };

    //zwraca b��d, konwersja jest zaw�aj�ca, u�ycie znaku "=" nie sprawdza, czy konwersja jest zaw�aj�ca
    //char charr{ x };

    //sta�a, ale jej warto�� musi by� znana podczas kompilacji, czyli nie mo�na jej warto�ci obliczy� za pomoc� zmiennych niewiadomych (np. w funckji)
    //constexpr double pi=3.14+n, gdzie n jest niewiadome, jest niedozwolone
    constexpr double pi = 3.14;

    //sta�a, jej warto�� nie musi by� znana podczas kompilacji, jej warto�� mo�na obliczy� za pomoc� zmiennych niewiadomych (np. w funkcji)
    const double PI = 3.14;

    //zwraca b��d, konwersja jest zaw�aj�ca, klamry jak zawsze chroni� przed tak� konwersj�
    //int i{ pi / 2 };
    //git, nie zaw�amy konwersji, nie zostanie obliczona dok�adna warto��, zostanie skonwertowana na si�� do typu int
    int i(pi / 2);


    //to jest mo�liwe XD
    switch (1)
    {
    case 1: case 2: case 3:
        std::cout << "sieeema";
        break;
    case 'n': case 'o':
        std::cout << "lolololo";
        break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    }

    //OBS�UGA B��D�W
    //errors
    /*
    runtime_error - zwraca b��d czasu pracy
    out_of_range - oznacza, �e podana warto�� jest spoza zakresu
    exception- klasa bazowa dla wszystkich error�w, dziedzicz� z niej, mo�emy tworzy� w�a�ne b��dy tworz�c klasy dziedzicz�ce z niej
    try
    {
      //kod w kt�rym mo�e pojawi� si� b��d
    }
    catch(runtime_error)
    {
    //obs�uga runtime_error
    }
    catch(exception &e)
    {
       cerr<<e.what(); // wy�wietla nam komunikat b��du, o ile go przekazali�my
       ten blok catch b�dzie dzia�a� dla ka�dego rzuconego wyj�tku, kt�ry dziedziczy z klasy exception, pozwalaj�c nam na obs�ug� wszystkich powi�zanych z tym b��d�w
    }
    catch(...)
    {
      //obs�uga wszystkich b��d�w
      //najcz�ciej u�ywamy tego, �eby opisa� b��d, kt�ry nie jest przewidziany
    }

    //bloki catch wykonuj� si� w odpowiedniej kolejno�ci, czyli jak rzucimy runtime_error, a pierwszy b�dzie blok catch exception &e, a potem runtime_error
    // to ten nasz runtime_error zostanie obs�u�ony jak zwyk�y exception, dlatego warto jednak najpierw obs�ugiwa� dok�adnie znane b��dy, a p�niej te bardziej og�lne
    */

    //extern oznacza, �e deklaracja nie jest definicj� zmiennej
    extern int a;

}


//obliczenie funkcji zostanie wykonane podczas kompilacji, mo�e to przy�pieszy� nasz program, ale trzeba tego u�ywa� z rozwag� mimo wszystko
constexpr int func(int& a)
{
    const int b = 10;
    int c = 5;
    return a;
    //constexpr int b = a; b��d, a nie jest wyra�eniem sta�ym
    constexpr int c = b; // git b jest sta�e
    return a++;//wynik dalej jest znany
    return a + c;
    return c;
    //funkcje constexpr musz� by� bardzo proste w budowie, trzeba pami�ta�, �e ich wynik musi by� znany ju� podczas kompilacji
    // podczas kompilacji kompilator sprawdzi sobie ile wynosi a, dlatego b�dzie zna� od razu wynik funkcji
    //w funkcji constexpr od c++14 mo�na u�ywa� w �rodku ju� nawet p�tli !

}


//funkcja ta zwraca referencj� do jakiego� obiektu int
const int& default_number()
{
    static const int num(20);// obiekt num, przy wielu wywo�ywaniach utworzy si� tylko raz i zapisze w pami�ci, je�li nasza funkcja b�dzie
    //wykorzystywana wiele razy, num nie b�dzie za ka�dym razem tworzone na nowo, jako �e jest to zmienna statyczna, zwracamy do niej referencj�, kt�r�
    //sobie przypiszemy potem jakiemu� obiektowi
    return num;
}

//using std::cout
//using std::cin
//takie co� jest mo�liwe, w miar� konieczno�ci unika� u�ywania using namespace "nazwa przestrzeni"


/*
enum enumerator{a,b,c,d,e,f,g,h...}// ten enumerator jest mniej restrykcyjny ni� ten klasowy
//trzeba uwa�a� na takie enumeratory, gdy� czasami taki enumerator mo�e prowadzi� do niebezpiecznych konwerski, a co wa�niejsze
// jego nazwy mog� kolidowa� z innymi nazwami w danym zakresie


enum class enumerator{a,b,c,d,e,f,g,h...}// enumerator klasowy, bardziej restrykcyjny ni� zwyk�y, ale bezpieczniejszy
//cz�sto zapobiega niebezpiecznym konwersjom
//�eby u�y� go nale�y u�y� nast�puj�cej sk�adni: nazwa_enumeratora::nazwa_zmiennej
//konwersje na typ int wymagaj� rzutowania

//mo�na przeci��a� operatory dla enumerator�w np. enumerator operator+(enumerator& e)

*/