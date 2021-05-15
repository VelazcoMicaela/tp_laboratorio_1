/*
 * menu.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utn.h"
#include "menu.h"
#include "ArrayEmployees.h"

#define TAM 1000

void menu(void)
{
	int opcion;
	char salir;
	int contador=-1;

	eEmployee emp[TAM];
	int id=2000;

	if(initEmployees(emp, TAM)==0)
	{
		printf("---------EMPLEADOS INICIALIZADOS---------\n");
	}

	do
	{
		if(utn_getNumeroEnteroConIntentos(&opcion, "\nIngrese una opcion \n 1. ALTAS\n 2. MODIFICAR\n 3. BAJA\n 4. INFORMAR\n 5. SALIR ", "ERROR reingrese una opcion ", 1, 5, 5)==0)
		{
			switch(opcion)
			{
				case 1:
					printf("\n---------------ALTAS---------------\n");
					if(addEmployee(emp, TAM, &id)==0)
					{
						if(printEmployees(emp, TAM)==0)
						{
							contador=1;
						}
					}
					break;

				case 2:
					if(contador==1)
					{
						printf("\n---------------MODIFICAR---------------\n");
						if(modifyEmployee(emp, TAM)==0)
						{
							printf("MODIFICACION EXITOSA\n\n");
							printEmployees(emp, TAM);
						}
					}
					else
					{
						printf("ERROR debe dar alta empleado \n");
					}

					break;

				case 3:
					if(contador==1)
					{
						printf("\n---------------BAJA---------------\n");
						if(removeEmployee(emp, TAM)==0)
						{
							printf("Baja exitosa\n");
							printEmployees(emp, TAM);
						}
					}
					else
					{
						printf("ERROR debe dar alta empleado \n");
					}

					break;

				case 4:
					if(contador==1)
					{
						printf("\n---------------INFORME---------------\n");

						if(menuInformes(emp, TAM)==0)
						{
							printf("\n");
						}
					}
					else
					{
						printf("ERROR debe dar alta empleado \n");
					}
					break;

				case 5:
					printf("\n---------------SALIR---------------\n");
					if(utn_getCaracterCorroboraDosCarac(&salir, "Seguro que desea salir? S/N ", "ERROR reingrese S/N ", 's', 'n')==0)
					{
						printf("Hasta luego\n");
					}
					break;
			}
		}
	}while(salir!='s');

}

int menuModify(eEmployee* list)
{
	int error=-1;
	int opcion;
	char salir;
	eEmployee aux;
	eEmployee cancelacion;

	cancelacion=*list;

	if(list!=NULL)
	{
		do
		{
			if(utn_getNumeroEnteroConIntentos(&opcion, "\nQue desea modificar? \n 1. NOMBRE\n 2. APELLIDO\n 3. SALARIO\n 4. SECTOR\n 5. GUARDAR ", "ERROR reingrese una opcion ", 1, 5, 5)==0)
			{
				switch(opcion)
				{
					case 1:
						printf("---------------NOMBRE---------------\n");
						if(utn_getString(aux.name, "Ingrese el nombre ", "ERROR Reingrese nombre ", 5)==0)
						{
							strcpy((*list).name,aux.name);
							printf("\nId      Nombre    Apellido  Sector Sueldo\n");
							printOneEmployee(*list);
							printf("-------------------------------------------------------\n");
						}
						break;

					case 2:
						printf("---------------APELLIDO---------------\n");
						if(utn_getString(aux.lastName, "Ingrese el apellido ", "ERROR Reingrese apellido ", 5)==0)
						{
							strcpy((*list).lastName,aux.lastName);
							printf("\nId      Nombre    Apellido  Sector Sueldo\n");
							printOneEmployee(*list);
							printf("-------------------------------------------------------\n");
						}
						break;

					case 3:
						printf("---------------SALARIO---------------\n");
						if(utn_getNumeroFlotante(&aux.salary, "Ingrese salario ",  "ERROR salario tiene q estar entre 0 y 999999. Reingrese ", 0, 999999, 5)==0)
						{
							(*list).salary=aux.salary;
							printf("\nId      Nombre    Apellido  Sector Sueldo\n");
							printOneEmployee(*list);
							printf("-------------------------------------------------------\n");
						}
						break;

					case 4:
						printf("---------------SECTOR---------------\n");
						if(utn_getNumeroEnteroConIntentos(&aux.sector, "Ingrese sector entre 100 y 200 ",  "ERROR Reingrese sector 100 y 200 ", 100, 200, 5)==0)
						{
							(*list).sector=aux.sector;
							printf("\nId      Nombre    Apellido  Sector Sueldo\n");
							printOneEmployee(*list);
							printf("-------------------------------------------------------\n");
						}
						break;

					case 5:
						printf("---------------GUARDAR---------------\n");
						printf("\nId      Nombre    Apellido  Sector Sueldo\n");
						printOneEmployee(*list);

						if(utn_getCaracterCorroboraDosCarac(&salir, "Desea guardar los cambios? S/N ", "ERROR reingrese S/N ", 's', 'n')==0)
						{
							if(salir=='n')
							{
								printf("Modificacion cancelada\n");
								(*list)=cancelacion;
								error=0;
							}
							else
							{
								error=0;
							}

						}
						break;
				}
			}

		}while(error!=0);

	}

	return error;

}

int menuInformes (eEmployee emp[], int len)
{
	int error=-1;
	int informes;
	int categorias;
	int orden;
	float total;
	float promedio;
	int cantidad;

	if(emp!=NULL && len>0)
	{
		if(utn_getNumeroEnteroConIntentos(&informes, "\nIngrese una opcion \n 1. Listado ordenado de empleados \n 2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio ", "ERROR reingrese una opcion ", 1, 2, 5)==0)
		{
			switch(informes)
			{
				case 1:
					printf("\n---------------ORDENAR EMPLEADOS---------------\n");
					if(utn_getNumeroEnteroConIntentos(&categorias, "\nIngrese una opcion \n 1. Listas por nombres \n 2. Listas por apellidos\n 3. Listas por salario\n 4. Listar por sectores \n", "ERROR reingrese una opcion ", 1, 4, 5)==0)
					{
						switch(categorias)
						{
							case 1:
								printf("\n---------------NOMBRE---------------\n");
								if(utn_getNumeroEnteroConIntentos(&orden, "\n 1-Listar ascendente 2- Listar descendente  ", "ERROR reingrese una opcion ", 1, 2, 5)==0)
								{
									if(sortEmployeesName(emp, len, orden)==0)
									{
										if(printEmployees(emp, len)==0)
										{
											printf("Ordenamiento realizado\n");
										}
									}
								}
								break;

							case 2:
								printf("\n---------------APELLIDO---------------\n");
								if(utn_getNumeroEnteroConIntentos(&orden, "\n 1-Listar ascendente 2- Listar descendente  ", "ERROR reingrese una opcion ", 1, 2, 5)==0)
								{
									if(sortEmployeesLastName(emp, len, orden)==0)
									{
										if(printEmployees(emp, len)==0)
										{
											printf("Ordenamiento realizado\n");
										}
									}
								}
								break;

							case 3:
								printf("\n---------------SALARIO---------------\n");
								if(utn_getNumeroEnteroConIntentos(&orden, "\n 1-Listar ascendente 2- Listar descendente  ", "ERROR reingrese una opcion ", 1, 2, 5)==0)
								{
									if(sortEmployeesSalary(emp, len, orden)==0)
									{
										if(printEmployees(emp, len)==0)
										{
											printf("Ordenamiento realizado\n");
										}
									}
								}
								break;

							case 4:
								printf("\n---------------SECTOR---------------\n");
								if(utn_getNumeroEnteroConIntentos(&orden, "\n 1-Listar ascendente 2- Listar descendente  ", "ERROR reingrese una opcion ", 1, 2, 5)==0)
								{
									if(sortEmployeesSector(emp, len, orden)==0)
									{
										if(printEmployees(emp, len)==0)
										{
											printf("Ordenamiento realizado\n");
										}
									}
								}
								break;
						}
					}
					break;

				case 2:
					printf("\n---------------TOTAL Y PROMEDIO SALARIOS---------------\n");
					if(averageSalary(emp, len, &total, &promedio)==0)
					{
						printf("EL total de los salarios es  $%.2f \n",total);
						printf("EL promedio de los salarios es $%.2f \n",promedio);
						if(exceedSalary(emp, len, promedio, &cantidad)==0)
						{
							printf("La cantidad de empleados que superan el promedio de $%.2f son %d\n",promedio,cantidad);
						}
					}
					break;
			}
			error=0;
		}
	}

	return error;

}
