#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int size_file(string fuente);
int fun_01(int bloq[], int seed);
void arch_txt(int deco_bin[], int lon, string salida);
void metod_1(int cod_bin[], int seed, int lon, string salida);
void metod_2(int cod_bin[], int seed, int lon, string salida);


int main()
{

    string fuente, salida;
    cout<<"\nIngresa el nombre del archivo a decodificar: ";
    cin>>fuente;
    cout<<"Ingresa el nombre del archivo de salida: ";
    cin>>salida;

    int seed, met;
    cout<<"\nIngresa la semilla de codificacion: ";
    cin>>seed;
    cout<<"Ingresa el metodo de codificacion 1 o 2: ";
    cin>>met;

    ifstream file ("C:/Users/sergi/OneDrive/Escritorio/Practica_3d/punto12/"+fuente, ios::binary); //Aqui va la ubicacion del archivo de texto
    if(file.fail()){
        cout<<">>ERROR<< No se pudo leer el archivo en: ../punto12/"<<endl;
        exit(1);
    }

    int lon = size_file(fuente);
    int cod_bin[lon];

    for (int i = 0; i < lon; i++){
        file.read((char *)(&cod_bin[i]),sizeof(int));
    }
    file.close();

    if (met == 1){
        metod_1(cod_bin,seed,lon,salida);
    }
    else if (met == 2) {
        metod_2(cod_bin,seed,lon,salida);
    }
    else {
        cout<<"Entrada invalida!"<<endl;
        exit(1);
    }


    return 0;
}

int size_file(string fuente){
    ifstream file ("C:/Users/sergi/OneDrive/Escritorio/Practica_3d/punto12/"+fuente, ios::binary);//Aqui va la ubicacion del archivo de texto
    string cont;
    getline(file,cont);
    int lon = size (cont);
    return lon/4;
}

int fun_01(int bloq[], int seed){
    int s0 = 0, s1 = 0;
    for (int i = 0; i < seed; i++){
        if (bloq[i] == 0){
            s0++;
        }
        else {
            s1++;
        }
    }

    if (s1 > s0){
        return 1;
    }
    else if (s0 > s1) {
        return 0;
    }
    else {
        return 2;
    }
}


void arch_txt(int deco_bin[], int lon, string salida){
    int aux=0,it=0;
    char text[lon/8];

    ofstream file;
    file.open("C:/Users/sergi/OneDrive/Escritorio/Practica_3d/punto12/"+salida,ios::out); //Aqui va la ubicacion del archivo de texto
    if(file.fail()){
        cout<<">>ERROR<< No se pudo crear el archivo. Extension .txt"<<endl;
        exit(1);
    }

    for (int i = 0; i < lon; i += 8){
        int num_dec = 0;
        for (int v = 0; v < 8; v++){
            num_dec = num_dec*2+deco_bin[aux];
            aux++;
        }
        text[it] = num_dec;
        file<<text[it];
        it++;
    }
    file.close();
    cout<<"\nEl archivo decodificado ha sido creado correctamente!\n Directorio: ../punto12/"+salida+"\n"<<endl;
}

void metod_1(int cod_bin[], int seed, int lon, string salida){

    int bloq[seed], bloq_an[seed];
    int aux=0, it=0;
    int deco_bin[lon];

    for (int i = 0; i < lon; i += seed){
        for (int v = 0; v < seed; v++){
            bloq_an[v] = bloq[v];
            bloq[v] = cod_bin[aux];
            aux++;
        }
        if (it < seed){
            for (int v = 0; v < seed; v++){
                if (bloq[v] == 0){
                    bloq[v] = 1;
                }
                else {
                    bloq[v] = 0;
                }
                deco_bin[it] = bloq[v];
                it++;
            }
        }
        else {
            if (fun_01(bloq_an,seed) == 0){
                for (int v = 1; v < seed; v += 2){
                    if (bloq[v] == 0){
                        bloq[v] = 1;
                    }
                    else {
                        bloq[v] = 0;
                    }
                }
                for (int v = 0; v < seed; v++){
                    deco_bin[it] = bloq[v];
                    it++;
                }
            }
            else if (fun_01(bloq_an,seed) == 1) {
                for (int v = 2; v < seed; v += 3){
                    if (bloq[v] == 0){
                        bloq[v] = 1;
                    }
                    else {
                        bloq[v] = 0;
                    }
                }
                for (int v = 0; v < seed; v++){
                    deco_bin[it] = bloq[v];
                    it++;
                }
            }
            else {
                for (int v = 0; v < seed; v++){
                    if (bloq[v] == 0){
                        bloq[v] = 1;
                    }
                    else {
                        bloq[v] = 0;
                    }
                    deco_bin[it] = bloq[v];
                    it++;
                }
            }
        }
    }
    arch_txt(deco_bin,lon,salida);
}


void metod_2(int cod_bin[], int seed, int lon, string salida){
    int aux = 0,it = 0;
    int deco_bin[lon];
    for (int i = 0; i < lon; i += seed){
        int bloq[seed], bloq_c[seed];
        for (int v = 0; v < seed; v++){
            bloq[v] = cod_bin[aux];
            aux++;
        }
        bloq_c[seed-1] = bloq[0];
        for (int v = 0; v < seed-1; v++){
            bloq_c[v] = bloq[v+1];
        }
        for (int v = 0; v < seed; v++){
            deco_bin[it] = bloq_c[v];
            it++;
        }
    }
    arch_txt(deco_bin,lon,salida);
}

