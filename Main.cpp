//#include "Circle.h"
#include "Vector.h"

#include "CircleVector.h"

using std::vector;

int main()
{
    //ofstream rf("rez.txt");
    // rf << "labas" << endl;
    //data s[2];
    setlocale(LC_ALL, "Lithuanian");
    int mok = 0;    // nustatomas mokiniu skaicius
    vector<data> sarasas;
    data laik;
    string abc;
    string dar;




    /*
    // vektoriu testavimas
    vector<int> b = {5};
    cout << b.empty() << endl;
    Vector<int> a;
    cout << a.empty() << endl;
    a.push_back(10);
    //a.clear();
    cout << a.empty() << endl;
    b.clear();
    cout << b.empty() << endl;
    */

    /*

    unsigned int perskirstymai1 = 0;
    unsigned int perskirstymai2 = 0;

    // Pradëti v1 uþpildymo laiko matavimà
    auto start = hrClock::now();    // pradedamas skaiciavimas

    unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;

    for (int i = 1; i <= sz; ++i) {
        if (v1.size() == v1.capacity()) {
            perskirstymai1++;
        }
        v1.push_back(i);
    }
    cout << "v1 capacity: " << v1.capacity() << endl;
    // Baigti v1 uþpildymo laiko matavimà
    auto end = hrClock::now();
    std::chrono::duration<double> diff = end - start; // Skirtumas (s)
    std::cout << "vector uzpildymas is " << sz << " elementu uztruko: " << diff.count() << " s\n";
    cout << "v1 perskirstimu skaicius: " << perskirstymai1 << endl;

    ///*
    // Pradëti v2 uþpildymo laiko matavimà
    start = hrClock::now();    // pradedamas skaiciavimas

    Vector<int> v2;

    for (int i = 1; i <= sz; ++i) {
        if (v2.size() == v2.capacity()) {
            perskirstymai2++;
        }
        v2.push_back(i);
    }
    cout << "v2 capacity: " << v2.capacity() << endl;
    // Baigti v2 uþpildymo laiko matavimà
    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    std::cout << "Vector uzpildymas is " << sz << " elementu uztruko: " << diff.count() << " s\n";
    cout << "v2 perskirstimu skaicius: " << perskirstymai2 << endl;




    Vector<int> v3;
    Vector<int> v4;
    // pushback funkcija (ideda elementa 10 i gala)
    v3.push_back(10); 
    v4.push_back(10);
    // tikrina ar jie lygus jei taip tai true, jei ne false (tikrinimo operatorius) (1)
    v3 == v4; 
    cout << (v3 == v4) << endl;
    // atspausdina 0 Vektor elemento reiksme  (10)
    cout << v3[0] << endl; 
    //tikrina ar Vektoriaus dydis 0 jei taip true, jei ne false (0)
    v3.empty();
    cout << v3.empty() << endl;
    // atspausdina Vektoriaus pirmo elemento reiksme (10)
    cout << *v3.begin() << endl;

    Vector<int> v5 = { 1,2,3,4,5 };
    vector<int> v7 = { 1,2,3,4,5 };
    Vector<int> v9(5,1);

    for (int i = 0; i < 5; i++) cout << v5[i] << endl;


    */

    //*/

    /*
    // testavimas
    data d1;
    cout << "getVardas: " << d1.getVardas() << endl;
    d1.changeVardas("labas");
    data d2 = d1;
    //d2.setVardas("labas2");
    //d1 = d2;
    cout << "getVardas labas: " << d1.getVardas() << endl;
    cout << "getVardas labas2: " << d2.getVardas() << endl;
    cout << "--------------------------------" << endl;
    d1.setRez(10.0);
    d2.setRez(5.0);
    data d3 = d1+d2;
    cout << "d1 + d2 " << d3.getRez() << endl;
    cout << "d1 + d2 " << (d1+d2).getRez() <<endl;
    cout << "d1 + d2 Mediana " << d3.getMediana() << endl;
    cout << "d1 > d2 " << (d1 > d2) << endl;
    cout << "d1 < d2 " << (d1 < d2) << endl;
    cout << "d1 >= d2 " << (d1 >= d2) << endl;
    cout << "d1 <= d2 " << (d1 <= d2) << endl;
    cout << "d1 == d2 " << (d1 == d2) << endl;

    */

    cout << "---------------------------------------------------------------- " << endl;

    cout << "Jei norite, kad duomenis skaitytu is failo – 1, jei paciam ivesti – 0" << endl;
    trycatch(abc);
    //cin >> abc;
   // while ((abc != "1") && (abc != "0")) {
   //     cout << "Ivedete blogai, veskite dar karta " << endl;
   //     cin >> abc;
   // }
    if (abc == "1") {
        veiksmaisufailu();
        //eil_po_eil("kursiokai.txt", "rez.txt", sarasas);
       // generuotifailus();
    }

    else {

        do {
            mok++;
            sarasas.reserve(mok);
            cout << "Ar norite kad " << mok << " -am(ai) mokiniui(-ei) pazymiai butu generuojami atsitiktinai? (bet koks simbolis) - taip, 0 - ne" << endl;
            cin >> abc;
            if (abc == "0") {
                ivestis(laik);
                sarasas.push_back(laik);
            }
            else {
                cout << "Kiek nd pazymiu turi mokinys? (max - " << C << " )" << endl;
                cin >> abc;
                while (!(isNumber(abc)) || (std::stoi(abc) > C || std::stoi(abc) < 0)) {
                    cout << "Ivedete blogai, veskite dar karta " << endl;
                    cin >> abc;
                }
                ivestis1(laik, std::stoi(abc));
                sarasas.push_back(laik);
            }
            cout << "Ar norite prideti dar viena mokini? (bet koks simbolis) - taip, 0 - ne" << endl;
            cin >> dar;
        } while (dar != "0");


        cout << "---------------------------------------------------------------- " << endl;
        cout << "Jei norite Vidurkio: rasykite – 1, jei norite Medianos rasykite – 0 " << endl;

        cin >> abc;

        while ((abc != "1") && (abc != "0")) {
            cout << "Ivedete blogai, veskite dar karta " << endl;
            cin >> abc;
        }


        if (abc == "1") {
            cout << std::left << std::setw(10) << "Vardas " << std::setw(10) << "Pavarde " << std::setw(10) << "Galutinis (Vid.) " << endl;
            cout << "---------------------------------------------------------------- " << endl;
            for (const auto& el : sarasas) {
                isved(el);
            }
        }

        else if (abc == "0") {
            cout << std::left << std::setw(10) << "Vardas " << std::setw(10) << "Pavarde " << std::setw(10) << "Galutinis (Med.) " << endl;
            cout << "---------------------------------------------------------------- " << endl;
            for (const auto& el : sarasas) {
                isvedmediana(el);
            }
        }
    }
    sarasas.clear();
    // df.close();     // uzdaromas duomenu failas
     //rf.close();     // uzdaromas rezultatu failas
    system("pause");
    return 0;
}
