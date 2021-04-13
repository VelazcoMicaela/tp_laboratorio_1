/*
 ============================================================================
 Name        : TP1.c
 Author      : Velazco Micaela
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones matematicas.h"

int main(void) {
	setbuf(stdout,NULL);

	int opcionMenu;
	char confirmacionSalida;
	int primerNumero=0;
	int segundoNumero=0;
	int resultadoSuma;
	int resultadoResta;
	int resultadoMultiplicacion;
	float resultadoDivision;
	long resultadoFactorial1;
	long resultadoFactorial2;
	int flag=0;
	int errorDiv;


	do
	{
		printf("**** MENU ****\n");
		printf("1-Ingresar 1er operando (A=%d)\n",primerNumero);
		printf("2-Ingresar 2do operando (B=%d)\n",segundoNumero);
		printf("3-Calcular todas las operaciones\n");
		printf("4-Informar resultados\n");
		printf("5-Salir\n");

		opcionMenu=IngresarNumero();

		switch (opcionMenu)
		{
			case 1:
				printf("1-Ingresar 1er operando\n");
				primerNumero=IngresarNumero();
				flag=1;
				break;

			case 2:

				if(flag==1)
				{
					printf("2-Ingresar 2do operando\n");
					segundoNumero=IngresarNumero();
					flag=2;
				}
				else
				{
					printf("ERROR Ingrese el 1er operando\n");
				}

				break;

			case 3:
				if(flag==2)
				{
					printf("3-Calcular todas las operaciones\n");
					printf("    a- Calcular la suma (%d+%d)\n",primerNumero,segundoNumero);
					resultadoSuma=SumarNumeros(primerNumero,segundoNumero);

					printf("    b- Calcular la resta (%d-%d)\n",primerNumero,segundoNumero);
					resultadoResta=RestarNumeros(primerNumero,segundoNumero);

					printf("    c- Calcular la division (%d/%d)\n",primerNumero,segundoNumero);
					errorDiv=DividirNumeros(primerNumero,segundoNumero,&resultadoDivision);


					printf("    d- Calcular la multiplicacion (%d*%d)\n",primerNumero,segundoNumero);
					resultadoMultiplicacion=MultiplicarNumeros(primerNumero,segundoNumero);

					printf("    e- Calcular el factorial (%d!) y el factorial (%d!)\n",primerNumero, segundoNumero);
					resultadoFactorial1=FactorearNumero(primerNumero);
					resultadoFactorial2=FactorearNumero(segundoNumero);

					flag=3;
				}
				else
				{
					printf("Primero ingrese ambos operando\n");
				}

				break;

			case 4:
				if(flag==3)
				{
					printf("4-Informar resultados\n");
					MostrarOperacionesEnteras('a', '+',primerNumero, segundoNumero, resultadoSuma);
					MostrarOperacionesEnteras('b', '-',primerNumero, segundoNumero, resultadoResta);

					if(errorDiv==1)
					{
						printf("    c- ERROR no se puede realizar por ser el 2do operando =0\n");
					}
					else
					{

						MostrarOperacionesFlotante('c','/',primerNumero, segundoNumero, resultadoDivision);
					}

					MostrarOperacionesEnteras('d', '*',primerNumero, segundoNumero, resultadoMultiplicacion);

					MostrarOperacionesLong('e',primerNumero, segundoNumero, resultadoFactorial1, resultadoFactorial2);

				}
				else
				{
					printf("ERROR. Primero debe pasar por los anteriores opciones\n");
				}

				break;

			case 5:
				printf("Seguro que desea salir?\n");
				confirmacionSalida=ConfirmarSalida();
				break;

			default:
				printf("ERROR no ingreso una opcion valida\n");
				break;
		}

	}while(confirmacionSalida!='s');

printf("Gracias por utilizar la calculadora");


	return EXIT_SUCCESS;
}


