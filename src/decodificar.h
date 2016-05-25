/* 
 * File:   decodificar.h
 * Author: cristhian
 *
 * Created on May 21, 2016, 7:51 PM
 */

#ifndef DECODIFICAR_H
#define	DECODIFICAR_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

class Decodificar{
    
public:
    
    string* decodificar(string);
    string* tipoR(string);
    string* tipoI(string);
    string* tipoJ(string);
    string idenReg(string);

};


#endif	/* DECODIFICAR_H */

