// Archivo de implementación de la clase Decodificar.
#include "decodificar.h"

/*
 * La función decodificar obtiene el opcode del código binario y en base a ello llama a la respectiva función
 * para su tipo de formato.
 */
string* Decodificar::decodificar(string line){
    
    //cout << "linea: " << line << endl;
    string op = "";
    string r1 = "";
    string r2 = "";
    string rd = "";
    
    for(int i = 0; i < 6; i++){
        op += line[i];
    }
    
    if(op == "000000"){
        string* ptrR = tipoR(line);
        return ptrR;
    }
    if(op != "000000"){
        
        if(op == "000010" || op == "000011"){
            string* ptrJ = tipoJ(line);
            return ptrJ;
        } 
        else{
            
            string* ptrI = tipoI(line);
            return ptrI;
        }
    }
    op = "";
}

/*Las siguientes funciones decodifican las instrucciones y las acomodan según al formato que pertenecen.
* Devuelven un puntero al array que contiene el formato.
 * Llaman a la función idenReg para saber decodificar los registros.
*/
string* Decodificar::tipoI(string linea){
    
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
    
    //cout << "El op es: " << op << " con r1: " << r1 << " con r2: " << r2 << " con inme: " << inme << endl;
    
    static string insI[4];
    insI[0] = op;
    insI[1] = r2;
    insI[2] = r1;
    insI[3] = inme;
    
    string* arrayI = insI;
    
    return arrayI;  
}

string* Decodificar::tipoR(string linea){
    
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
    if(fun == "101010"){
        fun = "slt";
    }
    if(fun == "100010"){
        fun = "sub";
    }
    
    //cout << "El op es: " << op << " con r1: " << r1 << " con r2: " << r2 << " con rd: " << rd << " y fun: " << fun
    //        << endl;
      
    static string insR[4];
    insR[0] = fun;
    insR[1] = rd;
    insR[2] = r1;
    insR[3] = r2;
    
    string* arrayR = insR;
    
    return arrayR;
}

string* Decodificar::tipoJ(string linea){
    
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
    
    //cout << "El op es: " << op << " con targ: " << targ << endl;
    
    static string insJ[4];
    insJ[0] = op;
    insJ[1] = targ;
    
    string* arrayJ = insJ;
    
    return arrayJ;
}

//Esta función decodifica los registros.
string Decodificar::idenReg(string reg){
    
    if(reg == "00000"){
        reg = "$zero";
    }
    if(reg == "00001"){
        reg = "$at";
    }
    if(reg == "00010"){
        reg = "$v0";
    }
    if(reg == "00100"){
        reg = "$a0";
    }
    if(reg == "01000"){
        reg = "$t0";
    }
    if(reg == "01001"){
        reg = "$t1";
    }
    if(reg == "01010"){
        reg = "$t2";
    }
    if(reg == "01011"){
        reg = "$t3";
    }
    if(reg == "01100"){
        reg = "$t4";
    }
    if(reg == "01101"){
        reg = "$t5";
    }
    if(reg == "01110"){
        reg = "$t6";
    }
    if(reg == "01111"){
        reg = "$t7";
    }
    if(reg == "10000"){
        reg = "$s0";
    }
    if(reg == "10001"){
        reg = "$s1";
    }
    if(reg == "10010"){
        reg = "$s2";
    }
    if(reg == "10011"){
        reg = "$s3";
    }
    if(reg == "10100"){
        reg = "$s4";
    }
    if(reg == "10101"){
        reg = "$s5";
    }
    if(reg == "10110"){
        reg = "$s6";
    }
    if(reg == "11000"){
        reg = "$t8";
    }
    if(reg == "11001"){
        reg = "$t9";
    }
    if(reg == "11111"){
        reg = "$ra";
    }
    
    return reg;
}