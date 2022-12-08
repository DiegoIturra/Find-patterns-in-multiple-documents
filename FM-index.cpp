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

void doc_locate(const string& T , const string& p){

}


int main(int argc, char** argv) {
    if (argc !=  2) {
        cout << "Uso: " << argv[0] << " <archivo entrada>" << endl;
        return 1;
    }

    cout << argv[1] << endl;

    // Una versión compacta del suffix array, implementada en la biblioteca
    // SDSL. En este caso, utiliza un wavelet tree tipo wt_int<> como
    // building-block
    // Otros posibles building blocks son: wt_huff<>, wt_int<rrr_vector<> >, entre
    // otras combinaciones
    cout << "Construyendo el FM-index ..." << endl;
    csa_wt<wt_huff<>> fm_index;
    construct(fm_index, argv[1], 1);
      
    
    cout << "Tamaño del FM-index " << size_in_mega_bytes(fm_index) << " MB." << endl;

    string patron;
    cout << "Ingrese un patrón a buscar: ";
    cin >> patron;

    // Tamaño del patrón
    size_t m  = patron.size();

    // Buscando las ocurrencias del patrón
    size_t occs = sdsl::count(fm_index, patron.begin(), patron.end());

    cout << "# de ocurrencias: " << occs << endl;
    if (occs > 0) {
        cout << "Las ocurrencias comienzan en las siguientes posiciones: " << endl;
        //auto locations = locate(fm_index, query.begin(), query.begin()+m)
        auto posiciones = sdsl::locate(fm_index, patron.begin(), patron.end());
        sort(posiciones.begin(), posiciones.end());
      
        for (size_t i = 0; i < occs; ++i) {
	       cout << posiciones[i] << endl;
        }
    }
    return 0;
}
