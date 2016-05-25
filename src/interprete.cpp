//Archivo de implementación de la clase Interprete.
#include "interprete.h"
#include "decodificar.h"
#include <unistd.h>
using namespace std;

//Variables globales para ciertas condiciones
bool flag = false;
int parada = 0;
int asig = 0;
int cant = 0;
int ranNumsArray[5];

//Se define la función interprete.
/*
 * Toma varios parámetros, entre los más importantes están:
 * El .text para interpretar el código.
 * El puntero a los registros.
 * El método a usar y la cantidad de líneas.
 * Esta función se encarga de interpretar los saltos (j, jal, jr y tags) del código máquina.
 * Además llama a otras dos funciones para interpretar el resto del código.
 */
void Interprete::interprete(void* ptrHead, int memoria, string* ptrStack, int* ptrRegs , ifstream &text, ifstream &data, int*ranNums,int lineas,int metodo){
    
    cout << "Interpretando..." << endl;

    string ln;
    string op = "";
    string pasado;
    
    flag = false;
    parada = 0;
    asig = 0;
    cant = 0;
    
    Decodificar deco; //Se instancia un objeto de la clase Decodificar.
    
    int cantNumRan;
    cout << "Ingrese la candidad de numeros aleatorios por generar." << endl;
    cout << "Cantidad: ";
    cin >> cantNumRan;
    
    while(parada < cantNumRan){ //loop para cantidad de aleatorios.
            for(int i = 0; i < lineas; i++){ // loop para líneas del código.

                for(int j = 0; j < 1; j++){ //loop para abrir línea por línea.

                    text >> ln;
                    //cout << ln << endl;
                    string* jum = deco.decodificar(ln); //Llama a la función decoficar para facilitar la interpretación.

                    if(metodo == 1){ // Verifica cada método para interpretar sus respectivos saltos.
                        
                        if(*jum == "jal" || *jum == "j" || *jum == "jr"){
                        //cout << "VA PARA MODULO" << endl;
                        if(*(jum +1) == "00000000000000000000010111"){
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum +1) == "00000000000000000000100100"){
                            //cout << "VA PARA NUMERO" << endl;
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum + 2) == "$ra"){
                            //cout << "DE VUELTA AL MAIN!" << endl;
                            text.seekg(0,ios::beg);
                            if(pasado == "00000000000000000000100100"){
                                for(int k = 0; k < 8; k++){
                                        text >> ln; 
                                }
                            }
                            if(pasado == "00000000000000000000010111"){
                                for(int k = 0; k < 7; k++){
                                        text >> ln; 
                                }
                            }
                        }
                        if(*(jum + 1) == "00000000000000000000000100"){
                            //cout << "SALTO AL BUCLE" << endl;
                            int dir = convertir(*(jum + 1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }    


                    } else{

                        interpretar(jum,ptrRegs,ranNums,metodo,cantNumRan); //Llama a la función interpretar para que 
                      }                                       // interprete el resto del código.
                    }
                    if(metodo == 2){
                        
                        if(*jum == "jal" || *jum == "j" || *jum == "jr"){
                        //cout << "VA PARA MODULO" << endl;
                        if(*(jum +1) == "00000000000000000000010111"){
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum +1) == "00000000000000000000010001"){
                            //cout << "VA PARA NUMERO" << endl;
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum + 2) == "$ra"){
                            //cout << "DE VUELTA AL MAIN!" << endl;
                            text.seekg(0,ios::beg);
                            if(pasado == "00000000000000000000010001"){
                                for(int k = 0; k < 9; k++){
                                        text >> ln; 
                                }
                            }
                            if(pasado == "00000000000000000000010111"){
                                for(int k = 0; k < 10; k++){
                                        text >> ln; 
                                }
                            }
                        }
                        if(*(jum + 1) == "00000000000000000000000110"){
                            //cout << "SALTO AL BUCLE" << endl;
                            int dir = convertir(*(jum + 1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }    


                    } else{

                        interpretar(jum,ptrRegs,ranNums,metodo,cantNumRan);
                      }
                    }
                    if(metodo == 3){
                        
                        if(*jum == "jal" || *jum == "j" || *jum == "jr"){
                        //cout << "VA PARA MODULO" << endl;
                        if(*(jum +1) == "00000000000000000000010001"){
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum +1) == "00000000000000000000010111"){
                            //cout << "VA PARA NUMERO" << endl;
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum + 2) == "$ra"){
                            //cout << "DE VUELTA AL MAIN!" << endl;
                            text.seekg(0,ios::beg);
                            if(pasado == "00000000000000000000010001"){
                                for(int k = 0; k < 9; k++){
                                        text >> ln; 
                                }
                            }
                            if(pasado == "00000000000000000000010111"){
                                for(int k = 0; k < 10; k++){
                                        text >> ln; 
                                }
                            }
                        }
                        if(*(jum + 1) == "00000000000000000000000110"){
                            //cout << "SALTO AL BUCLE" << endl;
                            int dir = convertir(*(jum + 1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }    


                    } else{

                        interpretar(jum,ptrRegs,ranNums,metodo,cantNumRan);
                      }
                    }
                    if(metodo == 4){
                        
                        if(*jum == "jal" || *jum == "j" || *jum == "jr"){
                        //cout << "VA PARA MODULO" << endl;
                        if(*(jum +1) == "00000000000000000000010010"){
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum +1) == "00000000000000000000011110"){
                            //cout << "VA PARA NUMERO" << endl;
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum + 2) == "$ra"){
                            //cout << "DE VUELTA AL MAIN!" << endl;
                            text.seekg(0,ios::beg);
                            if(pasado == "00000000000000000000010010"){
                                for(int k = 0; k < 10; k++){
                                        text >> ln; 
                                }
                            }
                            if(pasado == "00000000000000000000011110"){
                                for(int k = 0; k < 11; k++){
                                        text >> ln; 
                                }
                            }
                        }
                        if(*(jum + 1) == "00000000000000000000000111"){
                            //cout << "SALTO AL BUCLE" << endl;
                            int dir = convertir(*(jum + 1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }    


                    } else{

                        interpretar(jum,ptrRegs,ranNums,metodo,cantNumRan);
                      }
                    }
                    if(metodo == 5){
                        
                        if(*jum == "jal" || *jum == "j" || *jum == "jr"){
                        //cout << "VA PARA MODULO" << endl;
                        if(*(jum +1) == "00000000000000000000010000"){
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum +1) == "00000000000000000000010101"){
                            //cout << "VA PARA NUMERO" << endl;
                            pasado = *(jum + 1);
                            int dir = convertir(*(jum+1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }
                        if(*(jum + 2) == "$ra"){
                            //cout << "DE VUELTA AL MAIN!" << endl;
                            text.seekg(0,ios::beg);
                            if(pasado == "00000000000000000000010000"){
                                for(int k = 0; k < 8; k++){
                                        text >> ln; 
                                }
                            }
                            if(pasado == "00000000000000000000010101"){
                                for(int k = 0; k < 9; k++){
                                        text >> ln; 
                                }
                            }
                        }
                        if(*(jum + 1) == "00000000000000000000000101"){
                            //cout << "SALTO AL BUCLE" << endl;
                            int dir = convertir(*(jum + 1));
                            text.seekg(0,ios::beg);
                            for(int k = 0; k < dir; k++){
                                text >> ln;
                            }
                        }    


                    } else{

                        interpretar(jum,ptrRegs,ranNums,metodo,cantNumRan);
                      }
                    }
                    if(metodo == 6){
                        
                        if(*jum == "jal" || *jum == "j" || *jum == "jr"){

                            if(*(jum +1) == "00000000000000000000001011"){
                                //cout << "cuadradosMed" << endl;
                                pasado = *(jum + 1);
                                int dir = convertir(*(jum+1));
                                text.seekg(0,ios::beg);
                                for(int k = 0; k < dir; k++){
                                    text >> ln;
                                }
                            }
                            if(*(jum +1) == "00000000000000000000001111"){
                                //cout << "cuentaDig" << endl;
                                pasado = *(jum + 1);
                                int dir = convertir(*(jum+1));
                                text.seekg(0,ios::beg);
                                for(int k = 0; k < dir; k++){
                                    text >> ln;
                                }
                            }
                            if(*(jum +1) == "00000000000000000000011011"){
                                //cout << "extremosSig" << endl;
                                pasado = *(jum + 1);
                                int dir = convertir(*(jum+1));
                                text.seekg(0,ios::beg);
                                for(int k = 0; k < dir; k++){
                                    text >> ln;
                                }
                            }
                            if(*(jum +1) == "00000000000000000000100010"){
                                //cout << "extremosNoSig" << endl;
                                pasado = *(jum + 1);
                                int dir = convertir(*(jum+1));
                                text.seekg(0,ios::beg);
                                for(int k = 0; k < dir; k++){
                                    text >> ln;
                                }
                            }

                        } else{
                            
                            //cout << *(ptrRegs + 11) << endl;
                            interpretar(jum,ptrRegs,ranNums,metodo,cantNumRan);
                            
                            if(*jum == "beq"){
                                //cout << *(ptrRegs + 11) << endl;
                                if(*(ptrRegs + 11) == 0){
                            
                                    if(*(jum + 3) == "0000000000000100"){
                                        //cout << "cuadradosMedAux1.2" << endl;
                                        text.seekg(0,ios::beg);
                                        for(int k = 0; k < 21; k++){
                                            text >> ln; 
                                        }
                                    }
                                }   
                                if(*(ptrRegs + 13) <= 1){
                                    
                                    if(*(jum + 3) == "0000000000000101"){

                                        if(*(jum + 1) == "$t5"){
                                            //cout << "extremosNoSig" << endl;
                                            text.seekg(0,ios::beg);
                                            for(int k = 0; k < 34; k++){
                                                text >> ln; 
                                            }
                                        }
                                                
                                    }
                                }
                                if(*(ptrRegs + 12) <= 1){
                                    
                                    if(*(jum + 3) == "0000000000000101"){
                                        
                                        if(*(jum + 1) == "$t4"){
                                            //cout << "cuadradosMedAux2.1" << endl;
                                            text.seekg(0,ios::beg);
                                            for(int k = 0; k < 41; k++){
                                                text >> ln; 
                                            }
                                        }    
                                    }    
                                }
                            }
                          }
                        } // modo 6
                    
                } 
            }
    }    
}

/*Esta función asigna el registro según la indicación del código decodificado.
 * Toma como parámetros el código decodificado y el puntero a los registros para su respectiva asignación.
 */
int* Interprete::asigReg(string registro , int* ptrRegs){
    
    int* reg = ptrRegs;
    
    if(registro == "$zero"){
        return reg;
    }
    if(registro == "$at"){
        reg += 1;
        return reg;
    }
    if(registro == "$v0"){
        reg += 2;
        return reg;
    }
    if(registro == "$a0"){
        reg += 4;
        return reg;
    }
    if(registro == "$t0"){
        reg += 8;
        return reg;
    }
    if(registro == "$t1"){
        reg += 9;
        return reg;
    }
    if(registro == "$t2"){
        reg += 10;
        return reg;
    }
    if(registro == "$t3"){
        reg += 11;
        return reg;
    }
    if(registro == "$t4"){
        reg += 12;
        return reg;
    }
    if(registro == "$t5"){
        reg += 13;
        return reg;
    }
    if(registro == "$t6"){
        reg += 14;
        return reg;
    }
    if(registro == "$t7"){
        reg += 15;
        return reg;
    }
    if(registro == "$t8"){
        reg += 24;
        return reg;
    }
    if(registro == "$t9"){
        reg += 25;
        return reg;
    }
    if(registro == "$s0"){
        reg += 16;
        return reg;
    }
    if(registro == "$s1"){
        reg += 17;
        return reg;
    }
    if(registro == "$s2"){
        reg  += 18;
        return reg;
    }
    if(registro == "$s3"){
        reg += 19;
        return reg;
    }
    if(registro == "$s4"){
        reg += 20;
        return reg;
    }
    if(registro == "$s5"){
        reg += 21;
        return reg;
    }
    if(registro == "$s6"){
        reg += 22;
        return reg;
    }
    if(registro == "$ra"){
        reg += 31;
        return reg;
    }
    else {
        
        int inmediato = convertir(registro); // si no es un resgistro, es un inmediato (número).
        reg = &inmediato;                   // Por lo que llama a convertir para saber su valor en decimal.
        return reg;
    }
    
}

/*
 * La función interprete interpreta el resto del código, asignado los valores a los registros según lo indica 
 * el código decodificado.
 * Utiliza como parámetros principales la instrucción decodificada, el puntero a los registros y el tipo de método.
 */
void Interprete::interpretar(string* instruccion, int* ptrRegs, int* ranNums,int m,int cantidad){
    
    //int n;
    //cin >> n;
    
    string op = *instruccion;
    string rb = *(instruccion + 1);
    string r1 = *(instruccion + 2);
    string r2 = *(instruccion + 3);
    
    if(op == "addiu" || op == "addi" || op == "add" || op == "addu"){ // Verifica cada instrucción para saber 
        if(rb == "$t8"){                                  // que operación tiene que realizar.
            
        }
        else{
        int* x = asigReg(rb,ptrRegs); // se asignan los registros indicados por el código máquina.
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = sumar(*x,*a,*b,ptrRegs,m); // se llama a la función operación segpun corresponda.
        }
     
    }
    if(op == "sub"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = restar(*x,*a,*b,ptrRegs);
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
        //cout << "X: " << *x << endl;
         ptrRegs[0] = 0;
    } 
    if(op == "mflo"){
        int* x = asigReg(rb,ptrRegs);
        *x = *(ptrRegs + 33);
         ptrRegs[0] = 0;
    }
    if(op == "slti" || op == "slt"){
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        *x = comparar(*x,*a,*b);
    }
    if(op == "beq"){
        
        int* x = asigReg(rb,ptrRegs);
        int* a = asigReg(r1,ptrRegs);
        int* b = asigReg(r2,ptrRegs);
        //cout << "POR COMPARAR: " << *x << " y " << *a << endl; 
        
    }
    if(op == "syscall"){
        
        if(*(ptrRegs + 2) == 1){
            ranNums = ptrRegs + 4;
            
            if(m == 1){
                *ranNums = binDec(*ranNums);
            }
            parada += 1;
            cout << "SYSCALL" << parada << ": " << *ranNums<< endl;
            semaforo(ranNums,cantidad);
        }
    }   
}

// Las siguientes funciones son simples operaciones, devuelven un valor, el cual será asignado a un registro
// en la función Interpretar atraves de asigReg.
int Interprete::sumar(int x, int a, int b, int* ptrRegs,int m){
    
    //cout << x << " = " << a << " + " << b << endl;
    if(flag == false && m == 1){
        flag = true;
        //x = *(ptrRegs + 8);
        return x;
    } 
    if(flag == false && m == 2){
        asig += 1;
        //cout << "valor x: " << x << endl;
        if(asig == 4){
            flag = true;
            return x;
        }
        return x;
        
    }
    if(flag == false && m == 3){
        asig += 1;
        if(asig == 2){
            flag = true;
            return x;
        }
        return x;
    }
    
    
    else{
        x = a + b;
        //cout << "suma: " << x << endl;
        return x;
    }
    
}

int Interprete::restar(int x, int a, int b, int* ptrRegs){
    
    //cout << x << " = " << a << " - " << b << endl;
    x = a - b;
    //cout << "Resta: " << x << endl;
    return x;
}

int Interprete::multiplicar(int x, int a, int b, int* ptrRegs){
    
    //cout << x << " = " << a << " * " << b << endl;
    x = a*b;
    *(ptrRegs + 33) = x;
    //cout << "valor multi: " << x << endl;
    return x;   
}

int Interprete::dividir(int x, int a, int b, int* ptrRegs){
    
    //cout << x << " = " << a << " / " << b << endl;
    x = a/b;
    *(ptrRegs + 32) = a%b;
    *(ptrRegs + 33) = a/b;
    //cout << "valor divi: " << x << endl;
    return x;
}

int Interprete::XOR(int x, int a, int b){
    
    x = (a + b) % 2;
    int y = a/10;
    int z = y*10 + x;
    
    return z;
}

int Interprete::convertir(string inme){
    
    int dec = 0;
    string inmediato = "";
    char* ptr;
    
    for(int i = 0; i < inme.length(); i++){
        
        if(inme[i] != '0'){
            
            for(int j = i; j < inme.length(); j++){
                inmediato += inme[j];
            }
            break;
        }
    }
    
    dec = std::strtol(inmediato.c_str(),&ptr,2);
    
    return dec;  
}

int Interprete::comparar(int x, int a, int b){
    
    //cout << "POR COMPARAR: " << x << " " << a << " " << b << endl;
    
    if(a < b){
        x = 1;
        
        return x;
    }
    else{
        x = 0;
        
        return x;
    } 
}

int Interprete::binDec(int num){
    
    int dec = 0, rem,base = 1;
    
    while (num > 0){
        
        rem = num % 10;
        dec = dec + rem * base;
        base = base * 2;
        num = num / 10;
    }
    
    return dec;
}

//Función para contar las líneas del código binario.
int Interprete::contarLineas(ifstream &text){
    
    char buffer[1000];
    //ifstream examplefile ("/home/cristhian/MARSMips/MCB");
    
    if (! text.is_open())
    {
        cout << "Error opening file\n";
        exit (1);
    }
    
    int lineas = 0;
    int palabras = 0;
    int caracteres = 0;
    
    while (! text.eof() )
    {
        text.getline (buffer, 1000);
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
    
    /*cout << "El archivo tiene --> " << lineas -1 << " lineas." << endl;
    cout << "El archivo tiene --> " << palabras-1 << " palabras" << endl;
    cout << "El archivo tiene --> " << caracteres << " caracteres" << endl;*/
    
    int lines = lineas - 1;
    
    return lines;
}


void Interprete::semaforo(int* ranNums, int cantidad){
    
    //cout << "Valor cant: " << cant << endl;
    if(cant != 0){
        
        ranNumsArray[cant] = *ranNums;
        cant += 1;
    }
    
    if(cant >= cantidad){
        cout << "Array lleno" << endl;
        //SE LLAMA AL ÁRBOL ACÁ...
        //sleep(2);
        for(int i = 0; i < cantidad; i++){
            cout << ranNumsArray[i] << " ";
        }
        cant = 0;
    } 
    else{
        
        if(cant == 0){
            ranNumsArray[cantidad];
            cant += 1;
            ranNumsArray[0] = *ranNums;
        }
    }
}