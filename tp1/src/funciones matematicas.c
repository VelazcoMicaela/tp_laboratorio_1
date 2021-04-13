#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int IngresarNumero()
{
	int dato;

	scanf("%d",&dato);

	return dato;
}

char IngresarCaracter(void)
{
	char continuar;

	fflush(stdin);
	scanf("%c",&continuar);
	continuar=tolower(continuar);

	return continuar;
}

char ValidarIsAlpha(char caracter)
{
	while(isalpha(caracter)==0)
	{
		printf("ERROR, ingrese una letra\n");
		caracter=IngresarCaracter();
	}

	return caracter;
}

char ValidarCaracter(char continuar)
{

	continuar=ValidarIsAlpha(continuar);

	while(!(continuar=='n'||continuar=='s'))
	{
		printf("ERROR, Desea salir? S-si N-no ");
		continuar=IngresarCaracter();
	}

	return continuar;
}


char ConfirmarSalida(void)
{
	char continuar;

	continuar=IngresarCaracter();
	continuar=ValidarCaracter(continuar);

	return continuar;
}


int SumarNumeros(int num1, int num2)
{
	int resultado;

	resultado=num1+num2;

	return resultado;
}

int RestarNumeros(int num1, int num2)
{
	int resultado;

	resultado=num1-num2;

	return resultado;
}

int MultiplicarNumeros(int num1, int num2)
{
	int resultado;

	resultado=num1*num2;

	return resultado;
}

int DividirNumeros(int num1, int num2, float* pResultado)
{
	int error=1;

	if(pResultado!=NULL&&num2!=0)
	{
		*pResultado=(float)num1/num2;
		error=0;
	}

	return error;
}

void MostrarOperacionesEnteras(char letra,char operando,int num1, int num2, int resultado)
{
	printf("    %c- El resultado de %d  %c %d = %d \n",letra,num1,operando,num2,resultado);
}

void MostrarOperacionesFlotante(char letra,char operando,int num1, int num2, float resultado)
{
	printf("    %c- El resultado de %d  %c %d = %.2f \n",letra,num1,operando,num2,resultado);
}

void MostrarOperacionesLong(char letra,int num1, int num2, long resultado1, long resultado2)
{
	printf("    %c- El resultado de !%d = %ld  y !%d = %ld \n",letra,num1,resultado1,num2,resultado2);
}

long FactorearNumero(int operando)
{
    long factoreoNumeroFinal;
    int numeroAfactorear;

    factoreoNumeroFinal=1;
    for(numeroAfactorear=operando; numeroAfactorear>0; numeroAfactorear--)
    {
        factoreoNumeroFinal=factoreoNumeroFinal*numeroAfactorear;
    }
   return factoreoNumeroFinal;
}
