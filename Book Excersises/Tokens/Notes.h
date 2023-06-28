#pragma once
#include <iostream>

void notes()
{
    //znaki polskie dzia³aj¹
    //system("chcp 1250");
    //cout << "Œema";

    //dokonuje bezpiecznej inicjalizacji
    double x{ 0 };

    //zwraca b³¹d, konwersja jest zawê¿aj¹ca, u¿ycie znaku "=" nie sprawdza, czy konwersja jest zawê¿aj¹ca
    //char charr{ x }; 

    //znaki polskie dzia³aj¹
    system("chcp 1250");
    std::cout << "Œema";

    //dokonuje bezpiecznej inicjalizacji
    double x{ 0 };

    //zwraca b³¹d, konwersja jest zawê¿aj¹ca, u¿ycie znaku "=" nie sprawdza, czy konwersja jest zawê¿aj¹ca
    //char charr{ x };

    //sta³a, ale jej wartoœæ musi byæ znana podczas kompilacji, czyli nie mo¿na jej wartoœci obliczyæ za pomoc¹ zmiennych niewiadomych (np. w funckji)
    //constexpr double pi=3.14+n, gdzie n jest niewiadome, jest niedozwolone
    constexpr double pi = 3.14;

    //sta³a, jej wartoœæ nie musi byæ znana podczas kompilacji, jej wartoœæ mo¿na obliczyæ za pomoc¹ zmiennych niewiadomych (np. w funkcji)
    const double PI = 3.14;

    //zwraca b³¹d, konwersja jest zawê¿aj¹ca, klamry jak zawsze chroni¹ przed tak¹ konwersj¹
    //int i{ pi / 2 };
    //git, nie zawê¿amy konwersji, nie zostanie obliczona dok³adna wartoœæ, zostanie skonwertowana na si³ê do typu int
    int i(pi / 2);


    //to jest mo¿liwe XD
    switch (1)
    {
    case 1: case 2: case 3:
        std::cout << "sieeema";
        break;
    case 'n': case 'o':
        std::cout << "lolololo";
        break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    }

    //OBS£UGA B£ÊDÓW
    //errors
    /*
    runtime_error - zwraca b³¹d czasu pracy
    out_of_range - oznacza, ¿e podana wartoœæ jest spoza zakresu
    exception- klasa bazowa dla wszystkich errorów, dziedzicz¹ z niej, mo¿emy tworzyæ w³aœne b³êdy tworz¹c klasy dziedzicz¹ce z niej
    try
    {
      //kod w którym mo¿e pojawiæ siê b³¹d
    }
    catch(runtime_error)
    {
    //obs³uga runtime_error
    }
    catch(exception &e)
    {
       cerr<<e.what(); // wyœwietla nam komunikat b³êdu, o ile go przekazaliœmy
       ten blok catch bêdzie dzia³a³ dla ka¿dego rzuconego wyj¹tku, który dziedziczy z klasy exception, pozwalaj¹c nam na obs³ugê wszystkich powi¹zanych z tym b³êdów
    }
    catch(...)
    {
      //obs³uga wszystkich b³êdów
      //najczêœciej u¿ywamy tego, ¿eby opisaæ b³¹d, który nie jest przewidziany
    }

    //bloki catch wykonuj¹ siê w odpowiedniej kolejnoœci, czyli jak rzucimy runtime_error, a pierwszy bêdzie blok catch exception &e, a potem runtime_error
    // to ten nasz runtime_error zostanie obs³u¿ony jak zwyk³y exception, dlatego warto jednak najpierw obs³ugiwaæ dok³adnie znane b³êdy, a póŸniej te bardziej ogólne
    */

    //extern oznacza, ¿e deklaracja nie jest definicj¹ zmiennej
    extern int a;

}


//obliczenie funkcji zostanie wykonane podczas kompilacji, mo¿e to przyœpieszyæ nasz program, ale trzeba tego u¿ywaæ z rozwag¹ mimo wszystko
constexpr int func(int& a)
{
    const int b = 10;
    int c = 5;
    return a;
    //constexpr int b = a; b³¹d, a nie jest wyra¿eniem sta³ym
    constexpr int c = b; // git b jest sta³e
    return a++;//wynik dalej jest znany
    return a + c;
    return c;
    //funkcje constexpr musz¹ byæ bardzo proste w budowie, trzeba pamiêtaæ, ¿e ich wynik musi byæ znany ju¿ podczas kompilacji
    // podczas kompilacji kompilator sprawdzi sobie ile wynosi a, dlatego bêdzie zna³ od razu wynik funkcji
    //w funkcji constexpr od c++14 mo¿na u¿ywaæ w œrodku ju¿ nawet pêtli !

}


//funkcja ta zwraca referencjê do jakiegoœ obiektu int
const int& default_number()
{
    static const int num(20);// obiekt num, przy wielu wywo³ywaniach utworzy siê tylko raz i zapisze w pamiêci, jeœli nasza funkcja bêdzie
    //wykorzystywana wiele razy, num nie bêdzie za ka¿dym razem tworzone na nowo, jako ¿e jest to zmienna statyczna, zwracamy do niej referencjê, któr¹
    //sobie przypiszemy potem jakiemuœ obiektowi
    return num;
}

//using std::cout
//using std::cin
//takie coœ jest mo¿liwe, w miarê koniecznoœci unikaæ u¿ywania using namespace "nazwa przestrzeni"


/*
enum enumerator{a,b,c,d,e,f,g,h...}// ten enumerator jest mniej restrykcyjny ni¿ ten klasowy
//trzeba uwa¿aæ na takie enumeratory, gdy¿ czasami taki enumerator mo¿e prowadziæ do niebezpiecznych konwerski, a co wa¿niejsze
// jego nazwy mog¹ kolidowaæ z innymi nazwami w danym zakresie


enum class enumerator{a,b,c,d,e,f,g,h...}// enumerator klasowy, bardziej restrykcyjny ni¿ zwyk³y, ale bezpieczniejszy
//czêsto zapobiega niebezpiecznym konwersjom
//¿eby u¿yæ go nale¿y u¿yæ nastêpuj¹cej sk³adni: nazwa_enumeratora::nazwa_zmiennej
//konwersje na typ int wymagaj¹ rzutowania

//mo¿na przeci¹¿aæ operatory dla enumeratorów np. enumerator operator+(enumerator& e)

*/