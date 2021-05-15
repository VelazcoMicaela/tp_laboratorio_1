/*
 * ArrayEmployees.c
 *
 *  Created on: 12 may. 2021
 *      Author: Asus
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utn.h"
#include "menu.h"
#include "ArrayEmployees.h"

#define VACIO 0
#define LLENO 1

int initEmployees(eEmployee* list, int len)
{
	int error=-1;

	if(list!=NULL && len>0)
	{
		for(int i=0; i<len; i++)
		{
			list[i].isEmpty=VACIO;
		}
		error=0;
	}

 return error;
}

int searchFree(eEmployee* list, int len, int* id)
{
	int error=-1;

	if(list!=NULL && len>0 && id!=NULL)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty==VACIO)
			{
				(*id)=i;
			}

		}
		error=0;
	}

 return error;
}

int addEmployee(eEmployee* list, int len, int* id)
{
	int error=-1;
	eEmployee aux;
	char salir;
	int idAux;

	if(list!=NULL && len>0 && id!=NULL)
	{
		do
		{
			if(searchFree(list, len, &idAux)==0)
			{
				if(idAux>=0 && idAux<1000)
				{
					if(utn_getString(aux.name, "Ingrese el nombre ", "ERROR Reingrese nombre ", 5)==0)
					{
						if(utn_getString(aux.lastName, "Ingrese el apellido ", "ERROR Reingrese apellido ", 5)==0)
						{
							if(utn_getNumeroFlotante(&aux.salary, "Ingrese salario ",  "ERROR salario tiene q estar entre 0 y 999999. Reingrese ", 0, 999999, 5)==0)
							{
								if(utn_getNumeroEnteroConIntentos(&aux.sector, "Ingrese sector entre 100 y 200 ",  "ERROR Reingrese sector 100 y 200 ", 100, 200, 5)==0)
								{
									aux.isEmpty=LLENO;
									list[idAux]=aux;
									list[idAux].id=*id;
									(*id)++;
									error=0;
								}
							}
						}
					}
				}else
				{
					printf("Se llego al tope de empleados\n");
					break;
				}
			}


			if(utn_getCaracterCorroboraDosCarac(&salir, "Desea cargar mas empleados? S/N ", "ERROR reingrese S/N ", 's', 'n')==0)
			{
				printf("\n");
			}

		}while(salir!='n');
	}

 return error;
}


void printOneEmployee(eEmployee list)
{
	printf("%4d %10s %10s  %4d   %6.2f\n", list.id, list.name, list.lastName, list.sector,list.salary);
}

int printEmployees(eEmployee* list, int length)
{
	int error=-1;
	int flag=0;

	if(list!=NULL && length>0)
	{

		printf("Id      Nombre    Apellido  Sector Sueldo\n");
		for(int i=0; i<length; i++)
		{
			if(list[i].isEmpty==LLENO)
			{
				printOneEmployee(list[i]);
				flag=1;
			}
		}

		if(flag==0)
		{
			printf("No hay empleado para mostrar\n");
		}
		error=0;
	}

 return error;
}


int findEmployeeById(eEmployee* list, int len,int id)
{
	int indice=-1;

	if(list!=NULL && len>0 && id>0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].id==id && list[i].isEmpty==LLENO)
			{
				indice=i;
				break;
			}
		}
	}

	return indice;
}

int modifyEmployee(eEmployee* list, int len)
{
	int error=-1;
	int id;
	int indice;

	if(list!=NULL && len>0)
	{
		if(printEmployees(list, len)==0)
		{
			if(utn_getNumeroEnteroConIntentos(&id, "Ingrese el id a modificar ", "ERROR id debe esta entre 2000 a 3000. Reingrese ", 2000, 3000, 5)==0)
			{
				indice=findEmployeeById(list, len, id);
				printOneEmployee(list[indice]);
				if(menuModify(&list[indice])==0)
				{
					error=0;
				}
			}
		}
	}

	return error;
}

int removeEmployee(eEmployee* list, int len)
{
	int error=-1;
	int id;
	int indice;
	char confirmacion;

	if(list!=NULL && len>0)
		{
			if(printEmployees(list, len)==0)
			{
				if(utn_getNumeroEnteroConIntentos(&id, "Ingrese el id a dar de baja ", "ERROR id debe esta entre 2000 a 3000. Reingrese ", 2000, 3000, 5)==0)
				{
					indice=findEmployeeById(list, len, id);
					printOneEmployee(list[indice]);

					if(utn_getCaracterCorroboraDosCarac(&confirmacion, "Seguro que desea eliminar? S/N ", "ERROR, reingrese S/N ", 's', 'n')==0)
					{
						if(confirmacion=='s')
						{
							list[indice].isEmpty=VACIO;
							error=0;
						}
						else
						{
							printf("Baja cancelada\n");
						}
					}
				}
			}
		}

	return error;
}


int sortEmployeesName(eEmployee* list, int len, int order)
{
	int error=-1;
	eEmployee aux;

	if(list!=NULL && len>0 && order>0)
	{
		for(int i=0; i<len-1; i++)
		{
			for(int j=i+1; j<len; j++)
			{
				if(list[i].isEmpty==LLENO)
				{
					if(order==1)
					{
						if(strcmp(list[i].name,list[j].name)>0 ||
							(strcmp(list[i].name,list[j].name)==0 &&
									list[i].sector>list[j].sector))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
					else
					{
						if(strcmp(list[i].name,list[j].name)<0 ||
							(strcmp(list[i].name,list[j].name)==0 &&
							list[i].sector>list[j].sector))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
				}
			}
		}
		error=0;
	}

	return error;
}

int sortEmployeesLastName(eEmployee* list, int len, int order)
{
	int error=-1;
	eEmployee aux;

	if(list!=NULL && len>0 && order>0)
	{
		for(int i=0; i<len-1; i++)
		{
			for(int j=i+1; j<len; j++)
			{
				if(list[i].isEmpty==LLENO)
				{
					if(order==1)
					{
						if(strcmp(list[i].lastName,list[j].lastName)>0 ||
							(strcmp(list[i].lastName,list[j].lastName)==0 &&
							list[i].sector>list[j].sector))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
					else
					{
						if(strcmp(list[i].lastName,list[j].lastName)<0 ||
							(strcmp(list[i].lastName,list[j].lastName)==0 &&
							list[i].sector<list[j].sector))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
				}
			}
		}
		error=0;
	}

	return error;
}

int sortEmployeesSalary(eEmployee* list, int len, int order)
{
	int error=-1;
	eEmployee aux;

	if(list!=NULL && len>0 && order>0)
	{
		for(int i=0; i<len-1; i++)
		{
			for(int j=i+1; j<len; j++)
			{
				if(list[i].isEmpty==LLENO)
				{
					if(order==1)
					{
						if(list[i].salary>list[j].salary ||
							(list[i].salary==list[j].salary &&
							list[i].sector>list[j].sector))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
					else
					{
						if(list[i].salary<list[j].salary||
							(list[i].salary==list[j].salary &&
							list[i].sector<list[j].sector))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
				}
			}
		}
		error=0;
	}

	return error;
}

int sortEmployeesSector(eEmployee* list, int len, int order)
{
	int error=-1;
	eEmployee aux;

	if(list!=NULL && len>0 && order>0)
	{
		for(int i=0; i<len-1; i++)
		{
			for(int j=i+1; j<len; j++)
			{
				if(list[i].isEmpty==LLENO)
				{
					if(order==1)
					{
						if(list[i].sector>list[j].sector ||
						(list[i].sector==list[j].sector &&
						strcmp(list[i].lastName,list[j].lastName)>0))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
					else
					{
						if(list[i].sector<list[j].sector||
						(list[i].sector==list[j].sector &&
						strcmp(list[i].lastName,list[j].lastName)<0))
						{
							aux=list[i];
							list[i]=list[j];
							list[j]=aux;
						}
					}
				}
			}
		}
		error=0;
	}

	return error;
}

int averageSalary(eEmployee list[], int len, float* total, float* promedio)
{
	int error=-1;
	float acomulador;
	int flag=0;
	int contador=0;

	if(list!=NULL && len>0 && total!=NULL && promedio!=NULL)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty==LLENO)
			{
				if(flag==0)
				{
					acomulador=list[i].salary;
					flag=1;
				}
				else
				{
					acomulador= acomulador+list[i].salary;
				}
				contador++;
			}
		}

		*total=acomulador;
		*promedio=(float)acomulador/contador;
		error=0;
	}

	return error;
}

int exceedSalary(eEmployee list[], int len, float promedio, int* cantidad)
{
	int error=-1;
	int contador=0;

	if(list!=NULL && len>0 && cantidad!=NULL && promedio>0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].salary>promedio && list[i].isEmpty==LLENO)
			{
				contador++;
			}
		}

		*cantidad=contador;
		error=0;
	}

	return error;
}



