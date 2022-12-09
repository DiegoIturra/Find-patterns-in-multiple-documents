// Construcción del FM index de un texto
//
// Prerrequisitos: Tener la biblioteca SDSL instalada
//
// Compilación: g++ -O3 -o fmi FM-index.cpp -lsdsl -ldivsufsort -ldivsufsort64 -std=c++11

#include <sdsl/suffix_arrays.hpp>
#include <string>
#include <iostream>
#include <algorithm>

using namespace sdsl;
using namespace std;

// Cada estructura de datos y algoritmo deben proveer de la funcionalidad doc locate(T, p), 
// la cual retorna los documentos que contienen al menos una ocurrencia del patr ́on p.
//  Los documentos ser ́an representado por medio de su concatenaci ́on T

class FM_index {

    private:
        csa_wt<wt_huff<>> fm_index;
        string T;
        vector<int> docSeparation;

    public:
        FM_index(vector<string>& fileNames) {
            // Construir el texto T
            for (string& fileName : fileNames) {
                ifstream file("textos/"+fileName);
                string line;
                while (getline(file, line)) {
                    T += line;
                }
                T += '$';
                docSeparation.push_back(T.size());
            }
            T.pop_back();
            cout << T << endl;

            // Construir el FM index
            construct(fm_index, T, 1);
        };

        // Retorna las posiciones donde comienza el patrón p
        vector<int> locate(string& p) {
            vector<int> posiciones;
            auto locations = sdsl::locate(fm_index, p.begin(), p.end());
            for (auto& location : locations) {
                posiciones.push_back(location);
            }
            return posiciones;
        };

        // Retorna el número de ocurrencias del patrón p
        size_t count(string& p) {

            cout << "Patrón: " << p << endl;
            size_t occs = sdsl::count(fm_index, p.begin(), p.end());
            cout << "Ocurrencias: " << occs << endl;
            return occs;
        };

        // Retorna el tamaño del FM index en megabytes
        size_t size() {
            return sdsl::size_in_mega_bytes(fm_index);
        };

        // Retorna los documentos que tienen al menos una ocurrencia del patrón p
        vector<int> doc_locate(string& p) {
            vector<int> docs;
            auto posiciones = locate(p);
            for (auto& pos : posiciones) {
                int docNum = 1;
                for (int& index : docSeparation) {
                    if (pos < index) {
                        docs.push_back(docNum);
                        break;
                    }
                    docNum++;
                }
            }
            return docs;
        };

};


int main(int argc, char** argv) {
    if (argc <  2) {
        cout << "Uso: " << argv[0] << " <archivo entrada 1> <archivo entrada 2> ... <archivo entrada n>" << endl;
        return 1;
    }

    vector<string> fileNames;

    for (int i = 1; i < argc; ++i) {
        fileNames.push_back(argv[i]);
    }

    // Una versión compacta del suffix array, implementada en la biblioteca
    // SDSL. En este caso, utiliza un wavelet tree tipo wt_int<> como
    // building-block
    // Otros posibles building blocks son: wt_huff<>, wt_int<rrr_vector<> >, entre
    // otras combinaciones
    cout << "Construyendo el FM-index ..." << endl;
    FM_index fm_index(fileNames);

    
    cout << "Tamaño del FM-index " << fm_index.size() << " MB." << endl;

    string patron;
    cout << "Ingrese un patrón a buscar: ";
    cin >> patron;

    // Tamaño del patrón
    size_t m  = patron.size();


    // Buscando las ocurrencias del patrón
    size_t occs = fm_index.count(patron);

    
    if (occs > 0) {
        cout << "Las ocurrencias comienzan en las siguientes posiciones: " << endl;
        //auto locations = locate(fm_index, query.begin(), query.begin()+m)
        auto posiciones = fm_index.locate(patron);
        sort(posiciones.begin(), posiciones.end());
      
        for (size_t i = 0; i < occs; ++i) {
	       cout << posiciones[i] << endl;
        }
        
    }
    return 0;
}
