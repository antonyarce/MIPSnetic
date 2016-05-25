/* 
 * File:   main.cpp
 * Author: cristhian
 *
 * Created on May 21, 2016, 7:12 PM
 */

#include <cstdlib>
#include "decodificar.h"
#include "interprete.h"
#include <ctime>

using namespace std;

/*
 *Función principal para la ejecución del programa. 
 */
int main(int argc, char** argv) {

    cout << "Iniciando Programa..." << endl;
    
    Interprete inter;
    ifstream tet("/home/cristhian/MARSMips/MCB");
    ifstream tet2("/home/cristhian/MARSMips/MCM");
    ifstream tet3("/home/cristhian/MARSMips/MCA");
    ifstream tet4("/home/cristhian/MARSMips/MCP");
    ifstream tet5("/home/cristhian/MARSMips/MCX");
    ifstream tet6("/home/cristhian/MARSMips/MCMD");
    ifstream data("/home/cristhian/MARSMips/code2");
    int lineas1 = inter.contarLineas(tet);
    int lineas2 = inter.contarLineas(tet2);
    int lineas3 = inter.contarLineas(tet3);
    int lineas4 = inter.contarLineas(tet4);
    int lineas5 = inter.contarLineas(tet5);
    int lineas6 = inter.contarLineas(tet6);
    
    int metodo;
    cout << "¡Bienvenido seleccione un metodo de generacion de numeros aleatorios!" << endl;
    cout << endl;
    cout << "1 - Metodo Congruecial Binario." << endl;
    cout << "2 - Metodo Congruencial Mixto." << endl;
    cout << "3 - Metodo Congruencial Aditivo." << endl;
    cout << "4 - Metodo Congruencial Polinomial." << endl;
    cout << "5 - Metodo Congruencial Multiplicativo." << endl;
    cout << "6 - Metodo Cuadrados Medios." << endl;
    cout << endl;
    cout << "Presione (0) para finalizar el programa." << endl;
    cout << endl;
    cout << "Metodo: ";
    cin >> metodo;
    
    int regs[34] = {0,0,0,0,0,0,0,0,time(0),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,pow(10,9),0,0,0,0,0,0,0,0,0};
    int* ptrRegs = regs;
    int* hi = ptrRegs + 32;
    int* lo = ptrRegs + 33;
    int* ptrRanNum;
  
    int memoria = 1000;
    void* ptrHead = malloc(memoria);
    
    string R = "";
    string* ptrStack = &R;
    
    while(metodo != 0){
        
        
        if(metodo == 1){
            
            ifstream text("/home/cristhian/MARSMips/MCB");
            inter.interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data,ptrRanNum,lineas1,metodo);
        }
        if(metodo == 2){
            ifstream text("/home/cristhian/MARSMips/MCM");
            int regs1[34] = {0,0,0,0,0,0,0,0,time(0),pow(7,5),0,pow(2,31) - 1,0,0,0,0,0,0,0,0,0,0,0,0,pow(10,9),0,0,0,0,0,0,0,0,0};
            int* ptrRegs = regs1;
            inter.interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data,ptrRanNum,lineas2,metodo);
        }
        if(metodo == 3){
            ifstream text("/home/cristhian/MARSMips/MCA");
            int regs2[34] = {0,0,0,0,0,0,0,0,time(0),0,time(0) + 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int* ptrRegs = regs2;
            inter.interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data,ptrRanNum,lineas3,metodo);
        }
        if(metodo == 4){
            ifstream text("/home/cristhian/MARSMips/MCP");
            int regs3[34] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int* ptrRegs = regs3;
            inter.interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data,ptrRanNum,lineas4,metodo);
        }
        if(metodo == 5){
            ifstream text("/home/cristhian/MARSMips/MCX");
            int regs4[34] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int* ptrRegs = regs4;
            inter.interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data,ptrRanNum,lineas5,metodo);
        }
        if(metodo == 6){
            ifstream text("/home/cristhian/MARSMips/MCMD");
            int regs5[34] = {0,0,0,0,0,0,0,0,44544,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int* ptrRegs = regs5;
            inter.interprete(ptrHead,memoria,ptrStack,ptrRegs,text,data,ptrRanNum,lineas6,metodo);
        }
        cout << endl;
        cout << "Metodo: ";
        cin >> metodo;
    }
    
    cout << "¡Fin del programa!" << endl;
    
    return 0;
}

