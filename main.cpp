#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
/*Se crea el objeto matriz que tiene tres variables: la cantidad de filas, la cantidad de columnas y la matriz en si, la cual se
rige por un template el cual define el tipo de datos a almacenar en la matriz*/
template <typename element>
class matriz{

public:
    element**inicio;
    int filas;
    int columnas;
    matriz(){
        filas=0;
        columnas=0;
    }
    matriz(int n, int m){
        filas=n;
        columnas=m;
        inicio=new element*[filas];
        for(int i=0;i<filas;i++){
            *(inicio+i)=new element[columnas];
        }
    }
    void autorellenado(){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                *(*(inicio+i)+j)=i*columnas+j;
            }
        }
    }
    void ingresar(){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                cout<<"ingresa el elemento en la posicion "<<i<<" "<<j<<endl;
                cin>>*(*(inicio+i)+j);
            }
        }
    }
    void mostrar(){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                cout<<*(*(inicio+i)+j)<<"\t";
            }
            cout<<"\n";
        }
    }
/*La funcion orden se encarga de ordenar la matriz convirtiendola a un vector, para que el orden sea mas rapido y usando
elementos de stl, los cuales serian: vector, sort y reverse, siendo que se considera un booleano para definir si se ordena
de mayor a menor o menor a mayor, siendo que el ultimo es el que se encuentra por defecto*/
    void orden(bool inversa=false){
        vector<element> aux;
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                aux.push_back(*(*(inicio+i)+j));
            }
        }
        sort(aux.begin(),aux.end());
        if(inversa)
            reverse(aux.begin(),aux.end());
        for(int i=filas-1;i>=0;i--){
            for(int j=columnas-1;j>=0;j--){
                *(*(inicio+i)+j)=aux.back();
                aux.pop_back();
            }
        }
    }
/*se aplico la sobrecarga sobre multiples operadores para lograr operaciones tanto entre matrices como con variables numericas*/
    template <typename A>
    matriz operator+(const matriz<A>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            matriz aux(filas,columnas);
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    *(*(aux.inicio+i)+j)=*(*(inicio+i)+j)+*(*(matrizB.inicio+i)+j);
                }
            }
            return aux;
        }
    }
    template <typename A>
    matriz operator-(const matriz<A>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            matriz aux(filas,columnas);
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    *(*(aux.inicio+i)+j)=*(*(inicio+i)+j)-*(*(matrizB.inicio+i)+j);
                }
            }
            return aux;
        }
    }
    bool operator==(const matriz<int>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    if(*(*(inicio+i)+j)!=*(*(matrizB.inicio+i)+j)){
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
    bool operator==(const matriz<float>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    if(fabs(*(*(inicio+i)+j)-*(*(matrizB.inicio+i)+j))>0.000001){
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
    template <typename A>
    matriz operator<(const matriz<A>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            matriz aux(filas,columnas);
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    *(*(aux.inicio+i)+j)=((*(*(inicio+i)+j)-*(*(matrizB.inicio+i)+j))<-0.0000001)?*(*(inicio+i)+j):*(*(matrizB.inicio+i)+j);
                }
            }
            return aux;
        }
    }
    template <typename A>
    matriz operator>(const matriz<A>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            matriz aux(filas,columnas);
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    *(*(aux.inicio+i)+j)=((*(*(inicio+i)+j)-*(*(matrizB.inicio+i)+j))>0.00000001)?*(*(inicio+i)+j):*(*(matrizB.inicio+i)+j);
                }
            }
            return aux;
        }
    }
    template <typename A>
    matriz operator*(const matriz<A>& matrizB){
        if(columnas==matrizB.filas){
            matriz aux(filas,matrizB.columnas);
            for(int i=0;i<filas;i++){
                for(int j=0;j<matrizB.columnas;j++){
                    *(*(aux.inicio+i)+j)=0;
                    for(int k=0;k<columnas;k++){
                        *(*(aux.inicio+i)+j)+=*(*(inicio+i)+k)**(*(matrizB.inicio+k)+j);
                    }
                }
            }
            return aux;
        }
    }
    matriz operator*(element x){
        matriz aux(filas,columnas);
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                *(*(aux.inicio+i)+j)=*(*(inicio+i)+j)*x;
            }
        }
        return aux;
    }
    template <typename A>
    matriz operator/(const matriz<A>& matrizB){
        if(filas==matrizB.filas&&columnas==matrizB.columnas){
            matriz aux(filas,columnas);
            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    *(*(aux.inicio+i)+j)=(*(*(inicio+i)+j)+*(*(matrizB.inicio+i)+j))/2;
                }
            }
            return aux;
        }
    }
    void operator++(){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                ++*(*(inicio+i)+j);
            }
        }
    }
    void operator--(){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                --*(*(inicio+i)+j);
            }
        }
    }
    void operator+=(element x){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                *(*(inicio+i)+j)+=x;
            }
        }
    }
    void operator-=(element x){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                *(*(inicio+i)+j)-=x;
            }
        }
    }
    void operator*=(element x){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                *(*(inicio+i)+j)*=x;
            }
        }
    }
    template <typename A>
    void operator=(const matriz<A>&matrizB){
        for(int i=0;i<filas;i++){
            delete[]*(inicio+i);
        }
        delete[]inicio;
        matriz(matrizB.filas,matrizB.columnas);
        for(int i=0;i<matrizB.filas;i++){
            for(int j=0;j<matrizB.columnas;j++){
                *(*(inicio+i)+j)=*(*(matrizB.inicio+i)+j);
            }
        }
    }
    void operator^(int x){
        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                *(*(inicio+i)+j)=pow(*(*(inicio+i)+j),x);
            }
        }
    }
    ~matriz(){
        for(int i=0;i<filas;i++){
            delete[]*(inicio+i);
        }
        delete[]inicio;
    }
};
/*Los operadores sobrecargados y su tarea son:
    +   suma de matrices
    -   resta de matrices
    ==  comparacion de igualdad implementado tanto para enteros como para flotantes
    <   menor entre dos matrices
    >   mayor entre dos matrices
    *   multiplicacion de matrices
    *   multiplicacion de matriz con un escalar
    /   promedio entre dos matrices
    ++  aumenta en 1 a todos los elementos de la matriz
    --  disminuye en 1 a todos los elementos de la matriz
    +=  aumenta en n a todos los elementos de la matriz
    -=  disminuye en n a todos los elementos de la matriz
    *=  multiplica por n a todos los elementos de la matriz
    =   extrae todos los elemenos de la matriz derecha y se los otorga a la matriz izquierda
    ^   eleva a n a todos los elementos de la matriz
    */
int main(){
    matriz <float>A(4,4);
    matriz <float>B(4,4);
    A.autorellenado();
    B.autorellenado();
    cout<<"\n\nMatriz A:\n";
    A.mostrar();
    cout<<"\n\nMatriz B:\n";
    B.mostrar();
    cout<<"\n\nMatriz A+B:\n";
    (A+B).mostrar();
    cout<<"\n\nMatriz A-B:\n";
    (A-B).mostrar();
    cout<<"\n\nMatriz A*B:\n";
    (A*B).mostrar();
    cout<<"\n\nMatriz A*5:\n";
    (A*5).mostrar();
    cout<<"\n\nA==B?:\n";
    if(A==B){
        cout<<"A y B son iguales\n";
    }else{
        cout<<"A y B son diferentes\n";
    }
    cout<<"\n\nMatriz A++:\n";
    ++A;
    A.mostrar();
    cout<<"\n\nA==B?:\n";
    if(A==B){
        cout<<"A y B son iguales\n";
    }else{
        cout<<"A y B son diferentes\n";
    }
    cout<<"\n\nMatriz A+=6:\n";
    A+=6;
    A.mostrar();
    cout<<"\n\nMatriz B--:\n";
    --B;
    B.mostrar();
    cout<<"\n\nMatriz de los numeros mayores:\n";
    (A>B).mostrar();
    cout<<"\n\nMatriz de los numeros menores:\n";
    (A<B).mostrar();
    cout<<"\n\nMatriz A ordenada de mayor a menor:\n";
    A.orden(true);
    A.mostrar();
    cout<<"\n\nMatriz A ordenada de menor a mayor:\n";
    A.orden();
    A.mostrar();
    cout<<"\n\nMatriz A despues de ser igualada a B:\n";
    A=B;
    A.mostrar();
    return 0;
}
