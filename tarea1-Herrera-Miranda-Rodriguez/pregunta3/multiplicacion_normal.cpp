#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;


void multiplicarMatrices(vector<vector <int >>& M1, vector<vector <int >>& M2, int kn, int n) {

    vector<int> dimension (kn);
    vector<vector <int >> matrizResultante(kn, dimension);
    cout << "[" << kn << "]" << " X  [" << kn << "]\n" << endl;
    for (int i = 0; i < kn; i++) {
        for (int j = 0; j < kn; j++) {
            for (int k = 0; k < n; k++) {
                int producto = M1[i][k] * M2[k][j];
                matrizResultante[i][j] += producto;
            }
            cout << matrizResultante[i][j] << "  ";
        }
        cout << "\n";
    }
}

int main() {

    bool algoritmos = true;
    int n, k, kn;
    vector<vector<int>> M1;
    vector<vector<int>> M2;
    cout << "Ingrese los valores de N y k respectivamente separados por un espacio" << endl;
    cin >> n >> k;
    kn = n * k;
    cout << "las dimensiones de la matriz son " << kn << " X " << n << endl;
    cout << "Ingrese los valores de cada fila separados por un espacio de la primera Matriz" << endl;
    //Primera Matriz  
    for (int i = 0; i < kn; i++) {
        vector<int> fila(n);
        for (int j = 0; j < n; j++) {
            cin >> fila[j];
        }
        M1.push_back(fila);
    }
    cout << "las dimensiones de la matriz son " << n << " X " << kn << endl;
    cout << "Ingrese los valores de cada fila separados por un espacio de la segunda Matriz" << endl;
    //Segunda Matriz
    for (int i = 0; i < n; i++) {
        vector<int> fila(kn);
        for (int j = 0; j < kn; j++) {
            cin >> fila[j];
        }
        M2.push_back(fila);
    }
    multiplicarMatrices(M1, M2, kn, n);
    return 0;
}