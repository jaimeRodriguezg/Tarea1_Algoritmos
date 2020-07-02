#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

//muestra por pantalla el resultado esperado
void imprimir(vector< vector<int>>& matriz, int m, int n){
    cout << "[" << m << "]" << " X  [" << n << "]\n" << endl;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (j != 0){
                cout << "\t";
            }
            cout << matriz[i][j];
        }
        cout << endl;
    }
}

//resta matrices
void restarMatrices(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

//suma matrices
void sumarMatrices(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int dimension){
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


//Se realiza el algoritmo de Strassen
void strassen(vector<vector<int>>& M1, vector<vector<int>>& M2, vector<vector<int>>& M_resultante, int dimension){

    //Caso base de la recursion
    if (dimension == 1){
        M_resultante[0][0] = M1[0][0] * M2[0][0];
        return;
    }else{
        int dimension_2 = dimension / 2;
        vector<int> aux(dimension_2);
        vector<vector<int>> A(dimension_2, aux), B(dimension_2, aux), C(dimension_2, aux), D(dimension_2, aux),
                            E(dimension_2, aux), F(dimension_2, aux), G(dimension_2, aux), H(dimension_2, aux),
                            M_00(dimension_2, aux), M_01(dimension_2, aux), M_10(dimension_2, aux), M_11(dimension_2, aux),
                            p1(dimension_2, aux), p2(dimension_2, aux), p3(dimension_2, aux), p4(dimension_2, aux),
                            p5(dimension_2, aux), p6(dimension_2, aux), p7(dimension_2, aux),
                            aux1(dimension_2, aux), aux2(dimension_2, aux);

        //Se dividen las matrices en sub matrices
        for (int i = 0; i < dimension_2; i++){
            for (int j = 0; j < dimension_2; j++){
                A[i][j] = M1[i][j];
                B[i][j] = M1[i][j + dimension_2];
                C[i][j] = M1[i + dimension_2][j];
                D[i][j] = M1[i + dimension_2][j + dimension_2];

                E[i][j] = M2[i][j];
                F[i][j] = M2[i][j + dimension_2];
                G[i][j] = M2 [i + dimension_2] [j] ;
                H[i][j] = M2[i + dimension_2][j + dimension_2];
            }
        }

        // Se calcula p1 a p7
        restarMatrices(F, H, aux2, dimension_2);      // F - H
        strassen(A, aux2, p1, dimension_2);          // p1 = (A) * (F - H)

        sumarMatrices(A, B, aux1, dimension_2);      // A + B
        strassen(aux1, H, p2, dimension_2);          // p2 = (A+B) * (H)

        sumarMatrices(C, D, aux1, dimension_2);      // C + D
        strassen(aux1, E, p3, dimension_2);          // p3 = (C+D) * (E)

        restarMatrices(G, E, aux2, dimension_2);     // G - E
        strassen(D, aux2, p4, dimension_2);          // p4 = (D) * (G - E)
        
        sumarMatrices(A, D, aux1, dimension_2);      // A + D
        sumarMatrices(E, H, aux2, dimension_2);      // E + H
        strassen(aux1, aux2, p5, dimension_2);      // p5 = (A+D) * (E+H)
        
        restarMatrices(B, D, aux1, dimension_2);     // B - D
        sumarMatrices(G, H, aux2, dimension_2);      // G + H
        strassen(aux1, aux2, p6, dimension_2);       // p6 = (B-D) * (G+H)
       
        restarMatrices(A, C, aux1, dimension_2);     // A - C
        sumarMatrices(E, F, aux2, dimension_2);      // E + F
        strassen(aux1, aux2, p7, dimension_2);    // p7 = (C-A) * (E+F)
        
        // Calculando M_10, M_10, M_00 e M_11:
        sumarMatrices(p5, p4, aux1, dimension_2);       // p5 + p4
        restarMatrices(aux1, p2, aux2, dimension_2);       // (p5 +p4) - p2
        sumarMatrices(aux2, p6, M_00, dimension_2); // M_00 = (p5 + p4 - p2) + p6

        sumarMatrices(p1, p2, M_01, dimension_2);       // M_01 = p1 + p2

        sumarMatrices(p3, p4, M_10, dimension_2);       // M_10 = p3 + p4

        sumarMatrices(p1, p5, aux1, dimension_2);       // p1 + p5
        restarMatrices(aux1, p3, aux2, dimension_2);      // (p1 + p5 ) - p3
        restarMatrices(aux2, p7, M_11, dimension_2);  // M_11 = (p1 + p5 - p3) - p7

        // Se agrupan los resultados en una matriz
        for (int i = 0; i < dimension_2; i++){
            for (int j = 0; j < dimension_2; j++){
                M_resultante[i][j] = M_00[i][j];
                M_resultante[i][j + dimension_2] = M_01[i][j];
                M_resultante[i + dimension_2][j] = M_10[i][j];
                M_resultante[i + dimension_2][j + dimension_2] = M_11[i][j];
            }
        }
    }
}

//entrega la siguiente potencia de 2 para el algoritmo de strassen
int potenciaDeDos(int kn){
    int aux = ceil(log2(kn));
    return pow(2, aux);
}

// genera nuevas matrices rellenando con 0 en caso que sea necesario e ingresa la dimension en potencia de 2 y luego llama la funcion strassen
// para que aplique el algoritmo y muestra por consola a traves de la funcion imprimir el resultado de la multiplicacion de las matrices M1 y M2
void modificarMatrices(vector<vector<int>>& M1, vector<vector<int>>& M2, int kn, int n, int opcion){

     // max es kn
    int kn_ = potenciaDeDos(kn);
    vector<int> arreglo_de_ceros(kn_);
    vector<vector<int>> M1_(kn_, arreglo_de_ceros), M2_(kn_, arreglo_de_ceros), M_resultante(kn_, arreglo_de_ceros);
    if (opcion == 1) {
    
        for (int i = 0; i < kn; i++) {
            for (int j = 0; j < n; j++) {
                M1_[i][j] = M1[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < kn; j++) {
                M2_[i][j] = M2[i][j];
            }
        }
    }
    else {
    
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < kn; j++) {
                M1_[i][j] = M1[i][j];
            }
        }
        for (int i = 0; i < kn; i++) {
            for (int j = 0; j < n; j++) {
                M2_[i][j] = M2[i][j];
            }
        }
    }



    cout << "la matriz resultante es: " << endl;
    strassen(M1_, M2_, M_resultante, kn_);
    vector<int> m_final(kn);
    vector<vector<int>> M_final(kn, m_final);
    for (int i = 0; i < kn; i++){
        for (int j = 0; j < kn; j++){
            M_final[i][j] = M_resultante[i][j];
        }
    }

    imprimir(M_final, kn, kn);
}

bool comprobarOpcion(int opcion) {
    if (opcion == 1 || opcion == 2 || opcion == 3) {
        return true;
    }
    else {
        return false;
    }
}




int main(){

    bool algoritmos = true;

    while (algoritmos){
        int opcion;
        bool verificar;
        cout << "Elija el problema a resolver: \n" << endl;
        cout << "1. Problema 1 \n" << endl;
        cout << "2. Problema 2 \n" << endl;
        cout << "3. Salir \n" << endl;
        cin >> opcion;
        verificar = comprobarOpcion(opcion);
        if (verificar) {
            if (opcion == 1) {
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
                modificarMatrices(M1, M2, kn, n, opcion);
            }
            else if (opcion == 2) {
                int n, k, kn;
                vector<vector<int>> M1;
                vector<vector<int>> M2;
                cout << "Ingrese los valores de N y k respectivamente separados por un espacio" << endl;
                cin >> n >> k;
                kn = n * k;
                cout << "las dimensiones de la matriz son " << n << " X " << kn << endl;
                cout << "Ingrese los valores de cada fila separados por un espacio de la primera Matriz" << endl;
                //Primera Matriz
                for (int i = 0; i < n; i++) {
                    vector<int> fila(kn);
                    for (int j = 0; j < kn; j++) {
                        cin >> fila[j];
                    }
                    M1.push_back(fila);
                }
                cout << "las dimensiones de la matriz son " << kn << " X " << n << endl;
                cout << "Ingrese los valores de cada fila separados por un espacio de la segunda Matriz" << endl;
                //Segunda Matriz
                for (int i = 0; i < kn; i++) {
                    vector<int> fila(n);
                    for (int j = 0; j < n; j++) {
                        cin >> fila[j];
                    }
                    M2.push_back(fila);
                }
                modificarMatrices(M1, M2, kn, n, opcion);
            }
            else {
                algoritmos = false;
            }
        }
        else {
            cout << "Ingrese un numero dentro de las opciones.... \n" << endl;
        }
    }  
    return 0;
}