#include "skaiciavimai.h"
// #include <string>
// #include <vector>
// #include <iostream>
// #include <sstream>

using namespace std;

void MokiniuIsvedimas(vector<mokinys> & M, vector<mokinys> & N, int vidurkioTipas){
    ofstream fout;
    try{
        fout.open("../Pazangieji.txt", std::ios::out);
        if(!fout.is_open())  throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
        fout << left << setw(17) << "Vardas";
        fout << left << setw(17) << "Pavarde";
        if(vidurkioTipas == 1){
            fout << "Galutinis (Vid.)" << "\n";
            for(const auto &p : M){
                fout << left << setw(17) << p.vard(); 
                fout << left << setw(17) << p.pavard();
                fout << fixed << setprecision(2) << p.vid() <<"\n"; 
            }
        }
        else if(vidurkioTipas == 2){
            fout << "Galutinis (Med.)" << "\n";
            for(const auto &p : M){
                fout << left << setw(17) << p.vard(); 
                fout << left << setw(17) << p.pavard();
                fout << fixed << setprecision(2) << p.med() <<"\n"; 
            }
        }
        fout.close();
    }catch(const ios_base::failure& e){
        cerr << "KLAIDA: " << e.what() << "\n";
        cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << "\n";
        return;
    }

    try{
        fout.open("../Nepazangieji.txt", std::ios::out);
        if(!fout.is_open())  throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
        fout << left << setw(17) << "Vardas";
        fout << left << setw(17) << "Pavarde";
        if(vidurkioTipas == 1){
            fout << "Galutinis (Vid.)" << "\n";
            for(const auto &n : N){
                fout << left << setw(17) << n.vard(); 
                fout << left << setw(17) << n.pavard(); 
                fout << fixed << setprecision(2) << n.vid() <<"\n"; 
            }
        }
        else if(vidurkioTipas == 2){ 
            fout << "Galutinis (Med.)" << "\n";
            for(const auto &n : N){
                fout << left << setw(17) << n.vard(); 
                fout << left << setw(17) << n.pavard(); 
                fout << fixed << setprecision(2) << n.med() <<"\n"; 
            }
        }
        fout.close();
    }catch(const ios_base::failure& e){
        cerr << "KLAIDA: " << e.what() << "\n";
        cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << "\n";
        return;
    }
}

//Funkcija generuoja skirtingu dydziu failus 
void FailuGeneravimas(string failoPavadinimas, int pasirinkimas){
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 10);

    auto start = std::chrono::high_resolution_clock::now();
    ofstream fw(failoPavadinimas);
    stringstream buferis;
    const int BUFFER_SIZE = 1000;

    buferis << left << setw(17) << "Vardas";
    buferis << left << setw(17) << "Pavarde";
    buferis << left << setw(5) << "ND1" << left << setw(5) << "ND2" << left << setw(5) << "ND3" << left << setw(5) << "ND4" << left << setw(5) << "ND5";
    buferis << left << setw(5) << "ND6" << left << setw(5) << "ND7" << left << setw(5) << "ND8" << left << setw(5) << "ND9";
    buferis << "Egz.";
    buferis << "\n";
    for(int i=0; i<pasirinkimas; i++){
        if(buferis.str().size() > BUFFER_SIZE){
            fw << buferis.rdbuf();
            buferis.str("");
            buferis.clear();
        }
        buferis << left << setw(17) << "Vardas" + to_string(i + 1);
        buferis << left << setw(17) << "Pavarde" + to_string(i + 1);
        for(int j = 0; j < 10; j++){
            buferis << left << setw(5) << dist(mt);
        }
        buferis << "\n"; 
    }
    fw << buferis.rdbuf();
    fw.close();
    auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
    std::chrono::duration<double> diff = end-start; // Skirtumas (s)
    std::cout << "Elementų užpildymas užtruko: "<< diff.count() << " s\n";
}


bool SudaroTikRaides(string & str) {
    for (int i=0; i<str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

//Funkcija, kuri leidzia perskaityti varda ir pavarde ir kartu patikrina ar vardas ir pavarde yra zodziai sudaryti is raidziu
void mokinys::VarduSkaitymas(istringstream & iss, mokinys& M, int indeksas, bool & err){
    iss >> M.vardas >> M.pavarde;
    if(!SudaroTikRaides(M.vardas) || !SudaroTikRaides(M.pavarde)){
        cout<<"Varda ir pavarde gali sudaryti tik raides!\n";
        err=1;   
    } else {
        err=0;
    }
}
//Funkcija skirta generuoti atsitiktinius pazymius
void mokinys::GeneruotiPazymius(mokinys & M, int indeksas){
    for(int i=0; i<M.tarpiniaiRezultatai.size(); i++){
       M.tarpiniaiRezultatai[i] = (double)rand()/RAND_MAX * 10;
    }
}
//Funkcija skirta atsitikitiniu vardu ir pavardziu generavimui sudarytu is atsitiktiniu raidziu
void mokinys::VarduPavardziuGeneravimas(mokinys & M, int indeksas){
    char v;
    int vardoIlgis = 0, pavardesIlgis = 0; 
    vardoIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    pavardesIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    for(int i=0; i<vardoIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        M.vardas.push_back(v);
    }
    for(int i=0; i<pavardesIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        M.pavarde.push_back(v);
    }
}