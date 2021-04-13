/*
 * funciones matematicas.h
 *
 *  Created on: 12 abr. 2021
 *      Author: Asus
 */

#ifndef FUNCIONES_MATEMATICAS_H_
#define FUNCIONES_MATEMATICAS_H_


int IngresarNumero(void);

char IngresarCaracter(void);
char ValidarIsAlpha(char caracter);
char ValidarCaracter(char continuar);
char ConfirmarSalida(void);

int SumarNumeros(int num1, int num2);
int RestarNumeros(int num1, int num2);
int MultiplicarNumeros(int num1, int num2);
int DividirNumeros(int num1, int num2, float* pResultado);
long FactorearNumero(int operando);

void MostrarOperacionesEnteras(char letra, char operando,int num1, int num2, int resultado);
void MostrarOperacionesFlotante(char letra,char operando,int num1, int num2, float resultado);
void MostrarOperacionesLong(char letra,int num1, int num2, long resultado1, long resultado2);



#endif /* FUNCIONES_MATEMATICAS_H_ */
