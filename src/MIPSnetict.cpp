/*
 * File:   main.cpp
 * Author: cristhian
 *
 * Created on May 1, 2016, 5:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>

using namespace std;

/*
 * Mae la función Interprete tiene varias funciones hijas.
 *  1- Decodificar: Toma el texto binario y lo pasa a string según el formato que es con la ayuda de las
 * funciones: tipoR,tipoI,tipoJ,idenReg.
 *  2- Interpretador: Toma las intrucciones acomodadas por el Decodificador para empezar a interpretarlas.
 *  3- asigReg: Toma los registros de string (registros en Mars Mips) y lo asigna a los de C++.
 * Lo que falta por hacer son las funciones bases como la suma,división y multiplicación.
 * Además de jugar con los punteros en memoria.
 */

// Se declaran los prototipos de funciones a utilizar.
void Interprete(void*,int,string*,int*,ifstream &,ifstream &);
void contar_lineas();
void Decodificar(string,int*);
void Registros(int*);
string* tipoR(string);
string* tipoI(string);
string* tipoJ(string);
string idenReg(string);
void interpretar(string*,int*);
int sumar(int,int,int);
int dividir(int,int,int,int*);
int multiplicar(int,int,int,int*);
int* asigReg(string, int*);
int convertir(string);
void salto(string*);
int XOR(int,int,int);
int comparar(int,int,int);


int main() {

    cout << "Iniciando Programa..." << endl;

    // declarando los registros.
    int regs[34] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int* ptrRegs = regs;
    int* hi = ptrRegs + 32;
    int* lo = ptrRegs + 33;

    cout << "EL puntero esta  en: " << ptrRegs << " con valor: " << *ptrRegs << endl;

    // solicitando memoria al sistema.
    int memoria = 1000;
    void* ptrHead = malloc(memoria);
    cout << ptrHead << endl;

    // Creando puntero a Stack.
    string R = "";
    string* ptrStack = &R;
    cout << ptrStack << endl;


    // Abriendo los archivos a interpretar.
    ifstream text("/home/tonylinux/Documentos/MIPS/congruencialMixtoBin");
    cout << text << endl;
    ifstream data("/home/tonylinux/Documentos/MIPS/congruencialMixtoDat");
    cout << data << endl;


    Interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data);


    return 0;
}


// Función para interpretar el código.
void Interprete(void* ptrHead,int memoria,string* ptrStack,int* ptrRegs,ifstream &text,ifstream &data){

    cout << "Interpretando..." << endl;
    contar_lineas();
    int lineas = 12;
    string ln;
    string op = "";
    for(int i = 0; i < lineas; i++){

        for(int j = 0; j < 1; j++){

            text >> ln;
            cout << "La linea " << i << " es: " << ln << endl;
            Decodificar(ln,ptrRegs);
        }

    }

}



void contar_lineas(){

    //Para contar las lineas
    char buffer[1000];
    ifstream examplefile ("/home/tonylinux/Documentos/MIPS/congruencialMixtoBin");
    if (! examplefile.is_open())
    {
        cout << "Error opening file\n";
        exit (1);
    }

    int lineas = 0;
    int palabras = 0;
    int caracteres = 0;
    while (! examplefile.eof() )
    {
        examplefile.getline (buffer, 1000);
        for (int Cont = 0; Cont <= 1000; Cont++)
        {
            if(buffer[Cont] != '\0')
            {
                caracteres++;
            }

            if ((buffer[Cont]==32)||(buffer[Cont]=='\0')) {

               palabras++;
            }

            if (buffer[Cont] == '\0')
            {
                break;
            }
        }

    lineas++;

    }

    cout << "El archivo tiene --> " << lineas -1 << " lineas." << endl;
    cout << "El archivo tiene --> " << palabras-1 << " palabras" << endl;
    cout << "El archivo tiene --> " << caracteres << " caracteres" << endl;
}


//Esta función verifica el OP para saber cual tipo de formato es la instrucción.
void Decodificar(string line, int*ptrRegs){

    string op = "";
    string r1 = "";
    string r2 = "";
    string rd = "";

    for(int i = 0; i < 6; i++){
        op += line[i];
    }

    if(op == "000000"){
        string* ptrR = tipoR(line);
        interpretar(ptrR,ptrRegs);
    }
    if(op != "000000"){
        if(op == "000010" || op == "000011"){
            string* ptrJ = tipoJ(line);
            interpretar(ptrJ,ptrRegs);

        } else{
            string* ptrI = tipoI(line);
            interpretar(ptrI,ptrRegs);
        }
    }
    op = "";

}


/*
 * Los siguientes tres métodos obtienen el formato de la intrucción, según corresponda.
 */

string* tipoR(string linea){

    cout << "Instruccion tipo R" << endl;
    string op = "";
    string r1 = "";
    string r2 = "";
    string rd = "";
    string fun = "";

    for(int i = 0; i < 6; i++){
        op += linea[i];
    }

    for(int j = 6; j < 6 + 5; j++){
        r1 += linea[j];
    }
    r1 = idenReg(r1);

    for(int k = 11; k < 16; k++){
        r2 += linea[k];
    }
    r2 = idenReg(r2);

    for(int m = 16; m < 21; m++){
        rd += linea[m];
    }
    rd = idenReg(rd);

    for(int n = 26; n < 32; n++){
        fun += linea[n];
    }

    if(fun == "100110"){
        fun = "xor";
    }
    if(fun == "011010"){
        fun = "div";
    }
    if(fun == "010000"){
        fun = "mfhi";
    }
    if(fun == "010010"){
        fun = "mflo";
    }
    if(fun == "011000"){
        fun = "mult";
    }
    if(fun == "100000"){
        fun = "add";
    }
    if(fun == "001100"){
        fun = "syscall";
    }
    if(fun == "001000"){
        fun = "jr";
    }
    if(fun == "100001"){
        fun = "addu";
    }

    cout << "El op es: " << op << " con r1: " << r1 << " con r2: " << r2 << " con rd: " << rd << " y fun: " << fun
            << endl;

    // Esto ayuda a obtener las instrucciones a utilizar en orden.
    static string insR[4];
    insR[0] = fun;
    insR[1] = rd;
    insR[2] = r1;
    insR[3] = r2;
    string* arrayR = insR;

    return arrayR;

}

string* tipoI(string linea){

    cout << "Instruccion tipo I" << endl;
    string op = "";
    string r1 = "";
    string r2 = "";
    string inme = "";

    for(int i = 0; i < 6; i++){
        op += linea[i];
    }

    if(op == "001001"){
        op = "addiu";
    }
    if(op == "001000"){
        op = "addi";
    }
    if(op == "001010"){
        op = "slti";
    }
    if(op == "000100"){
        op = "beq";
    }
    if(op == "001000"){
        op = "addi";
    }

    for(int j = 6; j < 11; j++){
        r1 += linea[j];
    }
    r1 = idenReg(r1);
    for(int k = 11; k < 16; k++){
        r2 += linea[k];
    }
    r2 = idenReg(r2);
    for(int m = 16; m < 32; m++){
        inme += linea[m];
    }

    cout << "El op es: " << op << " con r1: " << r1 << " con r2: " << r2 << " con inme: " << inme << endl;

    // Esto ayuda a obtener las instrucciones a utilizar en orden.
    static string insI[4];
    insI[0] = op;
    insI[1] = r2;
    insI[2] = r1;
    insI[3] = inme;
    string* arrayI = insI;

    return arrayI;

}

string* tipoJ(string linea){

    cout << "Instruccion tipo J" << endl;
    string op = "";
    string targ = "";

    for(int i = 0; i < 6; i++){
        op += linea[i];
    }

    if(op == "000011"){
        op = "jal";
    }
    if(op == "000010"){
        op = "j";
    }

    for(int j = 6; j < 32; j++){
        targ += linea[j];
    }

    cout << "El op es: " << op << " con targ: " << targ << endl;

    // Esto ayuda a obtener las instrucciones a utilizar en orden.
    static string insJ[4];
    insJ[0] = op;
    insJ[1] = targ;
    string* arrayJ = insJ;

    return arrayJ;

}

// Esta función identifica el registro utilizado en Mars Mips.
string idenReg(string r1){

    if(r1 == "00000"){
        r1 = "$zero";
    }
    if(r1 == "00001"){
        r1 = "$at";
    }
    if(r1 == "00010"){
        r1 = "$v0";
    }
    if(r1 == "00100"){
        r1 = "$a0";
    }
    if(r1 == "01000"){
        r1 = "$t0";
    }
    if(r1 == "01001"){
        r1 = "$t1";
    }
    if(r1 == "01010"){
        r1 = "$t2";
    }
    if(r1 == "01011"){
        r1 = "$t3";
    }
    if(r1 == "01100"){
        r1 = "$t4";
    }
    if(r1 == "01101"){
        r1 = "$t5";
    }
    if(r1 == "01110"){
        r1 = "$t6";
    }
    if(r1 == "01111"){
        r1 = "$t7";
    }
    if(r1 == "10000"){
        r1 = "$s0";
    }
    if(r1 == "10001"){
        r1 = "$s1";
    }
    if(r1 == "10010"){
        r1 = "$s2";
    }
    if(r1 == "10011"){
        r1 = "$s3";
    }
    if(r1 == "10100"){
        r1 = "$s4";
    }
    if(r1 == "10101"){
        r1 = "$s5";
    }
    if(r1 == "10110"){
        r1 = "$s6";
    }
    if(r1 == "11000"){
        r1 = "$t8";
    }
    if(r1 == "11001"){
        r1 = "$t9";
    }
    if(r1 == "11111"){
        r1 = "$ra";
    }


    return r1;
}

// Esta función interpreta las instrucciones acomodadas.
void interpretar(string* inst,int* ptrRegs){

    string op = *inst;
    string rb = *(inst + 1);
    string r1 = *(inst + 2);
    string r2 = *(inst + 3);

    //cout << "INSTRUCCION: " << op << " ," << rb << " ," << r1 << " ," << r2 << endl;
    //cout << "DIRECCIONES: " << x << "  " << a << "  " << b << endl;
    if(op == "addiu" || op == "addi" || op == "add"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = sumar(*x,*a,*b);

        cout << "finalmente: "<< endl;
        for(int i = 0; i < 32; i++){
            cout << ptrRegs[i] << endl;
        }
    }
    if(op == "div"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = dividir(*x,*a,*b,ptrRegs);
    }
    if(op == "mult"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = multiplicar(*x,*a,*b,ptrRegs);
    }
    if(op == "xor"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = XOR(*x,*a,*b);
    }
    if(op == "mfhi"){
        int* x = asigReg(rb,ptrRegs);
        *x = *(ptrRegs + 32);
         ptrRegs[0] = 0;

    }
    if(op == "mflo"){
        int* x = asigReg(rb,ptrRegs);
        *x = *(ptrRegs + 33);
         ptrRegs[0] = 0;

    }
    if(op == "slti"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = comparar(*x,*a,*b);
        cout << "EN X PASA: "<< *x << endl;
    }
    if(op == "beq"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        cout << "VALORES: " << *x << " " << *a << endl;
        if(*x == *a){

        }
    }


}


// Esta función realizará las sumas del programa.
int sumar(int x,int a,int p){

    cout << "Los valores son: " << x << " " << a << " " << p <<endl;
    x = a + p;
    cout << "La suma es: " << x << endl;

    return x;
}

// Esta función toma el registro utilizado en Mars Mips y lo pasa al de C++.
int* asigReg(string r, int* ptrRegs){


    int* reg = ptrRegs;
    if(r == "$zero"){
        return reg;
    }
    if(r == "$at"){
        reg += 1;
        return reg;
    }
    if(r == "$v0"){
        reg += 2;
        return reg;
    }
    if(r == "$a0"){
        reg += 4;
        return reg;
    }
    if(r == "$t0"){
        reg += 8;
        return reg;
    }
    if(r == "$t1"){
        reg += 9;
        return reg;
    }
    if(r == "$t2"){
        reg += 10;
        return reg;
    }
    if(r == "$t3"){
        reg += 11;
        return reg;
    }
    if(r == "$t4"){
        reg += 12;
        return reg;
    }
    if(r == "$t5"){
        reg += 13;
        return reg;
    }
    if(r == "$t6"){
        reg += 14;
        return reg;
    }
    if(r == "$t7"){
        reg += 15;
        return reg;
    }
    if(r == "$t8"){
        reg += 24;
        return reg;
    }
    if(r == "$t9"){
        reg += 25;
        return reg;
    }
    if(r == "$s0"){
        reg += 16;
        return reg;
    }
    if(r == "$s1"){
        reg += 17;
        return reg;
    }
    if(r == "$s2"){
        reg  += 18;
        return reg;
    }
    if(r == "$s3"){
        reg += 19;
        return reg;
    }
    if(r == "$s4"){
        reg += 20;
        return reg;
    }
    if(r == "$s5"){
        reg += 21;
        return reg;
    }
    if(r == "$s6"){
        reg += 22;
        return reg;
    }
    if(r == "$ra"){
        reg += 31;
        return reg;
    }
    else {
        int inmediato = convertir(r);
        reg = &inmediato;
        return reg;
    }

    cout << "ASIGNANDO" << endl;
}


int convertir(string inme){

    cout << "ESTO ES STRING: " << inme << endl;
    int bin = 0;
    string inmediato = "";
    char* ptr;
    for(int i = 0; i < inme.length(); i++){

        if(inme[i] != '0'){

            for(int j = i; j < inme.length(); j++){
                inmediato += inme[j];
            }
            cout << "INME: " << inmediato << endl;
            break;
        }
    }

    bin = std::strtol(inmediato.c_str(),&ptr,2);

    cout << "ESTO ES BINARION: " << bin << endl;

    return bin;
}


void salto(string* inst){

    string dir = *(inst + 3);
    char* ptrdir;
    int ls = std::strtol(dir.c_str(),&ptrdir,2);
    cout << "SALTO A: " << ls << endl;
}

int dividir(int x, int a ,int b,int* ptrRegs){

    x = a/b;
    *(ptrRegs + 32) = a%b;
    *(ptrRegs + 33) = a/b;

    return x;
}

int multiplicar(int x, int a ,int b,int* ptrRegs){

    x = a*b;
    *(ptrRegs + 33) = x;


    return x;
}

int XOR(int x,int a,int b)
{
    x += (a + b) % 2;
    cout << "ESTO ES EL XOR: " << x << endl;
    return x;
}

int comparar(int x,int a,int b){

    if(a < b){
        x = 1;
    }
    else{
        x = 0;
    }

    return x;
}
