/* 
 * File:   interprete.h
 * Author: cristhian
 *
 * Created on May 21, 2016, 7:12 PM
 */

#ifndef INTERPRETE_H
#define	INTERPRETE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <math.h>

using namespace std;

class Interprete{
    
public:
    
    void interprete(void*,int,string*,int*,ifstream &,ifstream &,int*,int,int);
    int contarLineas(ifstream &);
    void interpretar(string*,int*,int*,int,int);
    int sumar(int,int,int,int*,int);
    int restar(int,int,int,int*);
    void semaforo(int*,int);
    int dividir(int,int,int,int*);
    int multiplicar(int,int,int,int*);
    int* asigReg(string, int*);
    int convertir(string);
    int XOR(int,int,int);
    int comparar(int,int,int);
    int binDec(int n);
    
};



#endif	/* INTERPRETE_H */

