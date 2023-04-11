#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

string text(string fuente);
int* arch_bin(char cad[]);
int fun_01(int bloq[], int seed);
void metod_1(int cad_bin[], int seed, int lon, string salida);
void metod_2(int cad_bin[], int seed, int lon, string salida);

int main()
{
    string fuente, salida;
    cout<<"Nombre de archivo fuente: ";
    cin>>fuente;
    cout<<"Nombre de archivo de salida (extension .dat): ";
    cin>>salida;

    int len_text = size(text(fuente));
    char cad[len_text];
    for (int i = 0; i <= len_text;i++){
        cad[i] = text(fuente)[i];
    }

    int *p;
    int cad_bin[len_text*8];
    p = arch_bin(cad);
    for (int i = 0; i < 8*len_text; i++){
        cad_bin[i] = *(p+i);
    }


    int seed, met;
    cout<<"\nIngresa la semilla de codificacion: ";
    cin>>seed;
    cout<<"Ingresa el metodo de codificacion 1 o 2: ";
    cin>>met;

    if (met == 1){
        metod_1(cad_bin,seed,8*len_text,salida);
    }
    else if (met == 2) {
        metod_2(cad_bin,seed,8*len_text,salida);
    }
    else {
        cout<<"Entrada invalida!"<<endl;
        exit(1);
    }


    return 0;
}

string text(string fuente){

    ifstream file;
    file.open("C:/Users/sergi/OneDrive/Escritorio/Practica_3d/punto11/"+fuente,ios::in); //Aqui va la ubicacion del archivo de texto
    string text;

    if(file.fail()){
        cout<<"\nNo se pudo leer el archivo. Directorio: ../punto11/"<<endl;
        exit(1);
    }
    while (!file.eof()) {
        getline(file,text);
    }
    file.close();

    return text;
}

int* arch_bin(char cad[]){

    int len_cad = strlen(cad);
    int cad_num[len_cad];
    static int cad_bin[100000];

    for (int i = 0; i < len_cad; i++){
        for (int v = 0; v <= 255; v++){
            if (cad[i] == v){
                cad_num[i] = v;
                break;
            }
        }
    }

    int aux = 0;
    for (int i = 0; i < len_cad; i++){
        int dec = cad_num[i];
        int bin[8];

        for (int v = 7; v >= 0; v--){
            bin[v] = dec%2;
            dec /= 2;
        }

        for (int c = 0; c < 8; c++){
            cad_bin[aux] = bin[c];
            aux++;
        }
    }

    return cad_bin;
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

void metod_1(int cad_bin[], int seed, int lon, string salida){

    int aux = 0, it;
    int cod_bin[lon];
    for (int i = 0; i < lon; i += seed){
        int bloq[seed], bloq_an[seed], bloq_c[seed];
        for (int v = 0; v < seed; v++){
            bloq_an[v] = bloq[v];
            bloq[v] = cad_bin[aux];
            bloq_c[v] = bloq[v];
            aux++;
        }

        if (i < seed){
            it = 0;
            for (int v = 0; v < seed; v++){
                if (bloq[v] == 0){
                    cod_bin[it] = 1;
                    it++;
                }
                else {
                    cod_bin[it] = 0;
                    it++;
                }
            }
        }
        else {
            if (fun_01(bloq_an,seed) == 0){
                for (int v = 1; v < seed; v += 2){
                    if (bloq_c[v] == 0){
                        bloq_c[v] = 1;
                    }
                    else {
                        bloq_c[v] = 0;
                    }
                }
                for (int v = 0; v < seed; v++){
                    cod_bin[it] = bloq_c[v];
                    it++;
                }
            }
            else if (fun_01(bloq_an,seed) == 1) {
                for (int v = 2; v < seed; v += 3){
                    if (bloq_c[v] == 0){
                        bloq_c[v] = 1;
                    }
                    else {
                        bloq_c[v] = 0;
                    }
                }
                for (int v = 0; v < seed; v++){
                    cod_bin[it] = bloq_c[v];
                    it++;
                }
            }
            else {
                for (int v = 0; v < seed; v++){
                    if (bloq_c[v] == 0){
                        bloq_c[v] = 1;
                    }
                    else {
                        bloq_c[v] = 0;
                    }
                }
                for (int v = 0; v < seed; v++){
                    cod_bin[it] = bloq_c[v];
                    it++;
                }
            }
        }
    }
    ofstream file;
    file.open("C:/Users/sergi/OneDrive/Escritorio/Practica_3d/punto11/"+salida,ios::binary); //Aqui va la ubicacion del archivo de texto
    if(file.fail()){
        cout<<"No se pudo crear el archivo. Directorio: ../Codificacion_char/"<<endl;
        exit(1);
    }

    for (int i = 0; i < lon; i++){
        file.write((char *)(&cod_bin[i]), sizeof (int));
    }
    file.close();
    cout<<"\nEl archivo codificado en metodo 1 ha sido creado correctamente! \n Directorio: ../Codificacion_char/"+salida+"\n"<<endl;
}

void metod_2(int cad_bin[], int seed, int lon, string salida){
    int aux = 0,it = 0;
    int cod_bin[lon];
    for (int i = 0; i < lon; i += seed){
        int bloq[seed], bloq_c[seed];
        for (int v = 0; v < seed; v++){
            bloq[v] = cad_bin[aux];
            aux++;
        }
        bloq_c[0] = bloq[seed-1];
        for (int v = 1; v < seed; v++){
            bloq_c[v] = bloq[v-1];
        }
        for (int v = 0; v < seed; v++){
            cod_bin[it] = bloq_c[v];
            it++;
        }
    }
    ofstream file;
    file.open("C:/Users/sergi/OneDrive/Escritorio/Practica_3d/punto11/"+salida,ios::binary); //Aqui va la ubicacion del archivo de texto
    if(file.fail()){
        cout<<"No se pudo crear el archivo. Directorio: ../punto11/"<<endl;
        exit(1);
    }

    for (int i = 0; i < lon; i++){
        file.write((char *)(&cod_bin[i]), sizeof (int));
    }
    file.close();
    cout<<"\nEl archivo codificado en metodo 2 ha sido creado correctamente! \nDirectorio: ../punto11/"+salida+"\n"<<endl;
}
