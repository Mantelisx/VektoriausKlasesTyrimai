#include "Vector.h"
#include "CircleVector.h"
/*
bool compare_pavarde(const string &a, const string &b) {
    if (a.pavarde == b.pavarde) return a.vardas < b.vardas;
    return a.pavarde < b.pavarde;
}
*/


Vector<data> skirtstykStudentus(Vector<data>& studentai) {
    Vector<data> kieti, minksti;
    for (const auto& stud : studentai)
        if (stud.getRez() < 5)
            minksti.push_back(stud);
        else
            kieti.push_back(stud);
    studentai = kieti;
    return minksti;
}



void pirmastrategija(Vector<data> studentai, Vector<data>& kieti, Vector<data>& minksti) {

    for (const auto& stud : studentai)
        if (stud.getRez() < 5)
            minksti.push_back(stud);
        else
            kieti.push_back(stud);
    //std::find_if(begin(studentai), end(studentai), [](data a){return a.rez < 5})
}

bool Mazesnis(const data& a) {
    return a.getRez() < 5;
}
/*
void tobulinta(Vector<data>& studentai, Vector<data>& minksti) {

    for (const auto& stud : studentai)
        if (stud.getRez() < 5)
            minksti.push_back(stud);

    studentai.erase(std::remove_if(studentai.begin(), studentai.end(), Mazesnis), studentai.end());
}
*/
/*
Vector<data> antrastrategija(Vector<data>& studentai) {
    Vector<data> minksti;
    Vector<data>::size_type i = 0;
    // invariantas: vektoriaus `studentai` elementai [0, i) yra "kieti"
    while (i != studentai.size()) {
        if (studentai[i].rez < 5) {
            minksti.push_back(studentai[i]);
            studentai.erase(studentai.begin() + i); // iðtrinti i-àjá stud.
        }
        else
            ++i; // pereiti prie kito studento
    }
    return minksti; // gràþina studentus gavusius skolà
}
*/
/*
Vector<data> antrastrategija(Vector<data>& studentai) {
    Vector<data> minksti;
    Vector<data>::iterator it = studentai.begin();
    while (it != studentai.end()) {
        if (it->rez < 5) {
            minksti.push_back(*it); // dereference *it kad gauti elementà
            it = studentai.erase(it); // perduodame it, gauname it
        }
        else
            ++it; // pereiti prie kito studento
    }
    return minksti; // gràþina studentus gavusius skolà
}
*/
Vector<data> antrastrategija(Vector<data>& studentai) {
    Vector<data> minksti;
    Vector<data>::iterator it = studentai.end();  // pakeisti nuo pabaigos iki pradzios
    it--;
    std::sort(studentai.begin(), studentai.end(), [](data a, data b) {
        return a.getRez() < 5;

        });

    while (it != studentai.begin()) {
        if (it->getRez() < 5) {
            minksti.push_back(*it); // dereference *it kad gauti elementà
            studentai.pop_back();

        }

        //  else
        it--; // pereiti prie kito studento
    }
    return minksti; // gràþina studentus gavusius skolà
}


void generuotifailus(string& failopavadinimas, int kiek, int nd) {

    // cout << "Iveskite kiek norite studentu duomenu: " << endl;
    //int kiek;
    // int nd;
    // cin >> kiek;
    string failas;
    if (failopavadinimas == "") {
        failas = "failas" + std::to_string(kiek) + ".txt";
    }
    else failas = failopavadinimas;

    ofstream rf(failas);

    // const char* cstr = failas.data();
    // cout << "Iveskite kiek norite, kad studentai turetu nd pazymiu: " << endl;
    //  cin >> nd;

    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    int_distribution dist(1, 10);


    string ndskaicius = "ND";
    string vardas = "Vardas";
    string pavarde = "Pavarde";

    // failo sudarymas
    auto start = hrClock::now();    // pradedamas skaiciavimas

    rf << std::left << std::setw(15) << "Vardas" << std::right << std::setw(15) << "Pavarde";
    for (int i = 0; i < nd; i++) {
        rf << std::right << std::setw(15) << ndskaicius + std::to_string(i + 1);
    }
    rf << std::right << std::setw(15) << "Egz." << endl;

    for (int i = 0; i < kiek; i++) {
        rf << std::left << std::setw(15) << vardas + std::to_string(i + 1) << std::right << std::setw(15) << pavarde + std::to_string(i + 1);
        for (int j = 0; j < nd; j++) {
            rf << std::right << std::setw(15) << dist(mt);
        }
        rf << std::right << std::setw(15) << dist(mt); if (i + 1 != kiek) rf << endl;    // if sakinys, kad isvengti papildomo nuskaitymo kai pabaigoje failo endline ideda
    }

    auto end = hrClock::now();
    std::chrono::duration<double> diff = end - start; // Skirtumas (s)
    std::cout << "Failo sudarymas is " << kiek << " studentu uztruko: " << diff.count() << " s\n";


    // remove(cstr);
    failopavadinimas = failas;

    rf.close();
    cout << "failas uzdarytas" << endl;
}

void veiksmaisufailu2(string test) {

    /*
    rf << std::left << std::setw(15) << "Vardas " << std::setw(15) << "Pavarde " << std::setw(15) << "Galutinis (Vid.) " << std::setw(15) << "Galutinis (Med.) " << endl;
    rf << "---------------------------------------------------------------- " << endl;
    */
    data temp;
    data nulinis;

    ifstream df(test);
    // ofstream rf("rez_"+test);
    ofstream fiveormore("rez_fiveormore_" + test);
    ofstream lessthanfive("rez_lessthanfive_" + test);

    int paz = 0;
    double vidurkis = 0;
    // Vector<data> sarasas;

    Vector<data> moreoreqfive;
    Vector<data> lessfive;

    Vector<data> studentas; // studentas vektorius strategijoms 1

    string sw;  // zodis
    int kiekyra = 0;  // kiek is viso  yra elementu


    string tempo;
    double egzas;



    while ((df.peek() != '\n') && (df >> sw)) {
        kiekyra++;
    }

    auto start = hrClock::now();    // pradedamas skaiciavimas
    while (!df.eof()) {

        //  cout << kiekyra;

          //nuskaitymas
        df >> tempo;
        temp.setVardas(tempo);
        df >> tempo;
        temp.setPavarde(tempo);
        //df >> tempo >> temp.pavarde;
        //cout << "vardas: " << temp.vardas << endl;
        for (int i = 0; i < kiekyra - 3; i++) {
            df >> paz;
            temp.getNd().push_back(paz);

            vidurkis += paz;
        }
        df >> egzas;
        temp.setEgzaminas(egzas);
        //df >> temp.egz;



        if (temp.getNd().size() != 0) vidurkis = vidurkis / (kiekyra - 3);
        else vidurkis = 0;

        temp.setRez(vidurkis * 0.4 + temp.getEgzaminas() * 0.6);
        vidurkis = 0;

        //mediana
        //sort(temp.getNd().begin(), temp.getNd().begin() + temp.getNd().size());
        sort(temp.getNd().begin(), temp.getNd().end());
        if (temp.getNd().size() % 2 == 1) {
            temp.setMediana(temp.getNd()[temp.getNd().size() / 2] * 0.4 + temp.getEgzaminas() * 0.6);
        }
        else {
            temp.setMediana(((temp.getNd()[temp.getNd().size() / 2] + temp.getNd()[(temp.getNd().size() / 2) - 1]) / 2.0) * 0.4 + temp.getEgzaminas() * 0.6);
        }

        moreoreqfive.push_back(temp);   //------------------------------------------ mano strategija ir 2 strategijai atitinka studentu pilna vektoriu.
        //studentas.push_back(temp);          // ----------------------------------- 1 strategija
        /*
        if (temp.rez >= 5) {
            moreoreqfive.push_back(temp);
        }
        else if (temp.rez < 5) {
            lessfive.push_back(temp);
        }
        */
        // cout << "suksirste i vektorius" << endl;

         //temp.nd.clear();
        temp = nulinis;
    }

    auto end = hrClock::now();
    std::chrono::duration<double> diff = end - start; // Skirtumas (s)
    std::cout << "Failo nuskaitymas is " << test << " uztruko: " << diff.count() << " s\n";

    df.close();





    //rikiavimas

   // std::sort(sarasas.begin(), sarasas.end(), compare_pavarde);
    //pagal pavarde
    /*
    std::sort(sarasas.begin(), sarasas.end(), [](data a, data b) {
        if (a.pavarde == b.pavarde) return a.vardas < b.vardas;
        return a.pavarde < b.pavarde;
        });
        */
        //pagal varda
        /*
        std::sort(sarasas.begin(), sarasas.end(), [](data a, data b) {
            if (a.vardas == b.vardas) return a.pavarde < b.pavarde;
            return a.vardas < b.vardas;
            });
            */
            //pagal pazymius
    /*
    std::sort(sarasas.begin(), sarasas.end(), [](data a, data b) {
        if (a.rez == b.rez) return a.pavarde < b.pavarde;
        return a.rez < b.rez;
        });
        */


        /*
         //-------------------------------------------------------- 1 strategija
         start = hrClock::now();    // pradedamas skaiciavimas
         std::sort(studentas.begin(), studentas.end(), [](data a, data b) {
             if (a.rez == b.rez) return a.pavarde < b.pavarde;
             return a.rez < b.rez;
             });

        */

        ///*
         // ---------------------------------------------- mano strategija ir 2 strategija
    start = hrClock::now();    // pradedamas skaiciavimas
    std::sort(moreoreqfive.begin(), moreoreqfive.end(), [](data a, data b) {
        if (a.getRez() == b.getRez()) return a.getPavarde() < b.getPavarde();
        return a.getRez() < b.getRez();
        });
    //*/





   /*
      std::sort(moreoreqfive.begin(), moreoreqfive.end(), [](data a, data b) {
          if (a.rez == b.rez) return a.pavarde < b.pavarde;
          return a.rez < b.rez;
          });
      //cout << "sort1" << endl;

      std::sort(lessfive.begin(), lessfive.end(), [](data a, data b) {
          if (a.rez == b.rez) return a.pavarde < b.pavarde;
          return a.rez < b.rez;
          });
     // cout << "sort2" << endl;
  */
    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    cout << test << " Irasu rusiavimas didejimo tvarka su sort uztruko: " << diff.count() << " s\n";


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 1 strategija
    /*

    start = hrClock::now();    // pradedamas skaiciavimas

    pirmastrategija(studentas, moreoreqfive, lessfive);

    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    std::cout << test << " Failo skirtsymas i minkstus ir kietus uztruko: " << diff.count() << " s\n";

    */
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 2 strategija
    /*

    start = hrClock::now();    // pradedamas skaiciavimas

    lessfive = antrastrategija(moreoreqfive);

    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    std::cout << test << " Failo skirtsymas i minkstus ir kietus uztruko: " << diff.count() << " s\n";

    */
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // mano strategija
    ///*

    start = hrClock::now();    // pradedamas skaiciavimas

    lessfive = skirtstykStudentus(moreoreqfive);
    //tobulinta(moreoreqfive, lessfive);

    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    std::cout << test << " Failo skirtsymas i minkstus ir kietus uztruko: " << diff.count() << " s\n";

    //*/
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //isvedimas
    /*
    for (const auto& el : sarasas) {
        rf << std::left << std::setw(15) << el.vardas << " " << std::setw(15) << el.pavarde;
        rf << std::setw(15) << std::fixed << std::setprecision(2) << el.rez << std::setw(15) << std::fixed << std::setprecision(2) << el.mediana << " " << endl;
    }
    */







    start = hrClock::now();    // pradedamas skaiciavimas

    // isvedimas >=5 galutinis pazymys
    fiveormore << std::left << std::setw(15) << "Vardas " << std::setw(15) << "Pavarde " << std::setw(15) << "Galutinis (Vid.) " << std::setw(15) << "Galutinis (Med.) " << endl;
    fiveormore << "---------------------------------------------------------------- " << endl;
    for (const auto& el : moreoreqfive) {
        if (el.getRez() >= 5) {
            fiveormore << std::left << std::setw(15) << el.getVardas() << " " << std::setw(15) << el.getPavarde();
            fiveormore << std::setw(15) << std::fixed << std::setprecision(2) << el.getRez() << std::setw(15) << std::fixed << std::setprecision(2) << el.getMediana() << " " << endl;
        }
    }

    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    cout << test << " Irasu studentu, kuriu galutinis balas >=5, irasymo i faila laikas: " << diff.count() << " s\n";

    fiveormore.close();
    moreoreqfive.clear();
    // cout << "daugiau arba lygu 5 iems" << endl;


    start = hrClock::now();    // pradedamas skaiciavimas

    // isvedimas <5 galutinis pazymys
    lessthanfive << std::left << std::setw(15) << "Vardas " << std::setw(15) << "Pavarde " << std::setw(15) << "Galutinis (Vid.) " << std::setw(15) << "Galutinis (Med.) " << endl;
    lessthanfive << "---------------------------------------------------------------- " << endl;
    for (const auto& el : lessfive) {
        if (el.getRez() < 5) {
            lessthanfive << std::left << std::setw(15) << el.getVardas() << " " << std::setw(15) << el.getPavarde();
            lessthanfive << std::setw(15) << std::fixed << std::setprecision(2) << el.getRez() << std::setw(15) << std::fixed << std::setprecision(2) << el.getMediana() << " " << endl;
        }
    }

    end = hrClock::now();
    diff = end - start; // Skirtumas (s)
    cout << test << " Irasu studentu, kuriu galutinis balas <5, irasymo i faila laikas: " << diff.count() << " s\n";

    lessthanfive.close();
    lessfive.clear();
    // cout << "maziau uz 5 is" << endl;


     //rf.close();
      //sarasas.clear();
    studentas.clear();

    // cout << "---------------------------------------------------------------- " << endl;
}

void veiksmaisufailu() {

    auto st = hrClock::now();
    auto end = hrClock::now();
    std::chrono::duration<double> difff; // Skirtumas (s)

    string failiukas = "test";
    int student, ndarb;
    cout << "Ar norite generuoti failus? bet koks simbolis – taip, 0 – ne" << endl;
    cin >> failiukas;
    while (failiukas != "0") {
        cout << "Failo pavadinimas: " << endl;
        cin >> failiukas;
        cout << "Studentu skaicius: " << endl;
        cin >> student;
        cout << "Namu darbu skaicius: " << endl;
        cin >> ndarb;
        generuotifailus(failiukas, student, ndarb);

        cout << "Testi generavima? bet koks simbolis – taip, 0 – ne" << endl;
        cin >> failiukas;
    }

    cout << "Ar norite apdoroti failus? bet koks simbolis – taip, 0 – ne" << endl;
    cin >> failiukas;
    if (failiukas != "0") {
        ifstream myfile;
        cout << "Iveskite failo pavadinima: (negali buti 0)" << endl;
        system("dir"); // linux vietoj dir - ls
        cin >> failiukas;
        do {

            myfile.open(failiukas);
            if (myfile) {
                cout << "failas " << failiukas << " yra" << endl;
                cout << "---------------------------------------------------------------- " << endl;
                st = hrClock::now();
                veiksmaisufailu2(failiukas);
                end = hrClock::now();
                difff = end - st; // Skirtumas (s)
                cout << endl;
                cout << failiukas << " Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
                cout << "---------------------------------------------------------------- " << endl;
            }
            else {
                cout << "failas " << failiukas << " nerastas." << endl;;
            }
            myfile.close();
            cout << "Ar norite testi? 1 – taip, 0 – ne " << endl;
            cin >> failiukas;
            if (failiukas == "1") {
                cout << "Iveskite failo pavadinima: (negali buti 0)" << endl;
                cin >> failiukas;
            }
        } while (failiukas != "0");

    }
    // string tikrinti;
    // string test = "testas.txt";

    // veiksmaisufailu2("failas100000.txt");

    // do{ 
    //     cout << "rasykite bet koki simbolá, jei norite generuoti faila arba 0, jei nenorite testi." << endl;
    //     cin >> tikrinti; 
    //     if (tikrinti != "0") {
            // auto st = hrClock::now();
           //  auto end = hrClock::now();
           //  std::chrono::duration<double> difff = end - st; // Skirtumas (s)
           //  generuotifailus(test);
          //   auto st = hrClock::now();
            // cout << test << endl;
           //  veiksmaisufailu2(test);

     //generuotifailus(test, 10, 7);
    // veiksmaisufailu2(test);
     /*
             auto st = hrClock::now();
             veiksmaisufailu2("failas1000.txt");
             auto end = hrClock::now();
             std::chrono::duration<double> difff = end - st; // Skirtumas (s)
             cout << endl;
             cout << "failas1000.txt" <<" Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
             cout << "---------------------------------------------------------------- " << endl;
             system("pause");

             st = hrClock::now();
             veiksmaisufailu2("failas10000.txt");
             end = hrClock::now();
             difff = end - st; // Skirtumas (s)
             cout << endl;
             cout << "failas10000.txt" << " Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
             cout << "---------------------------------------------------------------- " << endl;
             system("pause");
     */ /*
             st = hrClock::now();
             veiksmaisufailu2("failas100000.txt");
             end = hrClock::now();
             difff = end - st; // Skirtumas (s)
             cout << endl;
             cout << "failas100000.txt" << " Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
             cout << "---------------------------------------------------------------- " << endl;
             system("pause");
     */ /*
             st = hrClock::now();
             veiksmaisufailu2("failas1000000.txt");
             end = hrClock::now();
             difff = end - st; // Skirtumas (s)
             cout << endl;
             cout << "failas1000000.txt" << " Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
             cout << "---------------------------------------------------------------- " << endl;
             system("pause");

             st = hrClock::now();
             veiksmaisufailu2("failas10000000.txt");
             end = hrClock::now();
             difff = end - st; // Skirtumas (s)
             cout << endl;
             cout << "failas10000000.txt" << " Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
             cout << "---------------------------------------------------------------- " << endl;
             system("pause");
     */
     //  auto end = hrClock::now();
    //   std::chrono::duration<double> difff = end - st; // Skirtumas (s)
     //  cout << endl;
     // cout << test <<" Irasu, visas programos sugaiðtas laikas: " << difff.count() << " s\n\n";
     //  cout << "---------------------------------------------------------------- " << endl;

//    }
// } while (tikrinti != "0");





}


bool isNumber(const string& s) {

    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

void ivestis(data& temp) {
    int n = 0;
    int k = 1;
    double vidurkis = 0;
    string s1;

    string tempo;

    temp.getNd().clear();
    cout << "Iveskite varda: "; cin >> tempo; temp.setVardas(tempo);
    cout << "Iveskite pavarde: "; cin >> tempo; temp.setPavarde(tempo);
    cout << "Rasykite 0, jei pazymiai baigiasi (max nd pazymiu yra " << C << " )" << endl;

    temp.getNd().reserve(1);
    while (k && (n < C)) {    //

        cout << "Iveskite " << n + 1 << " - a pazymi: ";
        // cin >> temp.nd[n];
        cin >> s1;
        //s1 = std::to_string(temp.nd[n]);// pavercia i stringa
        if (isNumber(s1) && !(std::stoi(s1) > 10 || std::stoi(s1) < 0)) {
            // temp.nd[n] = std::stoi(s1);     // konvertuoja string i int tipa
            if (std::stoi(s1) == 0) {
                k = 0;
            }
            else {
                temp.getNd().push_back(std::stoi(s1));
                vidurkis += temp.getNd().back();
            }
        }
        else {
            //temp.nd[n] = 10;
            temp.getNd().push_back(10);
            vidurkis += temp.getNd().back();
            cout << "galimai ivedete ne numeri arba netinkama pazymi todel " << n + 1 << " mokiniui(-ei) jis buvo pakeistas i 10" << endl;
        }


        if (k != 0) {
            n++;
            temp.getNd().reserve(n + 1);
        }
    }


    if (temp.getNd().size() != 0) {
        vidurkis = vidurkis / n;
    }
    else vidurkis = 0;



    cout << "Iveskite egzamino ivertinima: "; //cin >> temp.egz;
    cin >> s1;
    if (isNumber(s1) && !(std::stoi(s1) > 10 || std::stoi(s1) < 0)) {
        temp.setEgzaminas(std::stoi(s1));
    }
    else {
        temp.setEgzaminas(10);
        cout << "galimai ivedete ne numeri arba netinkama egzamino pazymi todel " << n + 1 << " mokiniui(-ei) jis buvo pakeistas i 10" << endl;
    }
    temp.setRez(vidurkis * 0.4 + temp.getEgzaminas() * 0.6);

    // medianos skaiciavimas
    if (temp.getNd().size() == 0) {
        temp.setMediana(temp.getEgzaminas() * 0.6);
    }
    else {
        sort(temp.getNd().begin(), temp.getNd().begin() + n);
        //temp.nd.size() vietoj n
        if (temp.getNd().size() % 2 == 1) {
            temp.setMediana(temp.getNd()[temp.getNd().size() / 2] * 0.4 + temp.getEgzaminas() * 0.6);
        }
        else {
            temp.setMediana(((temp.getNd()[temp.getNd().size() / 2] + temp.getNd()[(temp.getNd().size() / 2) - 1]) / 2.0) * 0.4 + temp.getEgzaminas() * 0.6);
        }
    }

    //return temp;
}

void ivestis1(data& temp, int kiek) {
    string tempo;
    // int n=0;
    double vidurkis = 0;
    srand((unsigned)time(0));
    if (kiek > 0) {
        temp.getNd().reserve(kiek);
    }

    cout << "Iveskite varda: "; cin >> tempo; temp.setVardas(tempo);
    cout << "Iveskite pavarde: "; cin >> tempo; temp.setPavarde(tempo);
    cout << "pazymiai: " << endl;
    for (int i = 0; i < kiek; i++) {    //C
        temp.getNd()[i] = (rand() % 10) + 1; // pazymiai nuo 1 iki 10
        cout << temp.getNd()[i] << " ";
        vidurkis += temp.getNd()[i];
        // n++;

    }

    if (kiek != 0) {
        vidurkis = vidurkis / kiek;
    }
    else vidurkis = 0;

    temp.setEgzaminas((rand() % 10) + 1);
    cout << endl;
    cout << "Egzaminas: " << temp.getEgzaminas() << endl;

    temp.setRez(vidurkis * 0.4 + temp.getEgzaminas() * 0.6);

    // medianos skaiciavimas
    if (kiek > 0) {
        sort(temp.getNd().begin(), temp.getNd().begin() + kiek);
        if (kiek % 2 == 1) {
            temp.setMediana(temp.getNd()[kiek / 2] * 0.4 + temp.getEgzaminas() * 0.6);
        }
        else {
            temp.setMediana(((temp.getNd()[kiek / 2] + temp.getNd()[(kiek / 2) - 1]) / 2.0) * 0.4 + temp.getEgzaminas() * 0.6);
        }
    }
    else temp.setMediana(temp.getEgzaminas() * 0.6);
}

void ivestisfailas(data& temp) {
    cout << "labas" << endl;
}

void isved(const data& temp) {
    cout << std::left << std::setw(10) << temp.getVardas() << " " << std::setw(10) << temp.getPavarde();
    cout << std::setw(10) << std::fixed << std::setprecision(2) << temp.getRez() << " " << endl;
}

void isvedmediana(const data& temp) {
    cout << std::left << std::setw(10) << temp.getVardas() << " " << std::setw(10) << temp.getPavarde();
    cout << std::setw(10) << std::fixed << std::setprecision(2) << temp.getMediana() << " " << endl;
}

void isvedfailas(const data& temp) {
    cout << std::left << std::setw(10) << temp.getVardas() << " " << std::setw(10) << temp.getPavarde();
    cout << std::setw(10) << std::fixed << std::setprecision(2) << temp.getRez() << std::setw(10) << std::fixed << std::setprecision(2) << temp.getMediana() << " " << endl;
}

void trycatch(string& a) {
    cin >> a;
    do {
        try {
            if (cin.fail()) {
                throw std::runtime_error("Irasete netinkamai\n");
            }
        }
        catch (const std::runtime_error& e) {
            std::wcout << e.what();
            std::wcin.clear();
            std::wcin.ignore(256, '\n');
            cout << "Iveskite is naujo: " << endl;
            cin >> a;
        }
    } while (std::cin.fail() == true);
}


bool operator>(const data& a, const data& b) {
    return a.rez > b.rez;
}

bool operator<(const data& a, const data& b) {
    return a.rez < b.rez;
}

bool operator>=(const data& a, const data& b) {
    return a.rez >= b.rez;
}

bool operator<=(const data& a, const data& b) {
    return a.rez <= b.rez;
}

bool operator==(const data& a, const data& b) {
    return a.rez == b.rez;
}
