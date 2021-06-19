#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int flag=-1;
	FILE* f;
	char confirmacion;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		f= fopen(path, "r");

		if(f!=NULL)
		{
			if(ll_len(pArrayListEmployee)>0 && utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n')==0)
			{
				if(confirmacion!='s')
				{
					flag=5;
				}
			}
			if(ll_len(pArrayListEmployee)==0 || confirmacion=='s')
			{
				ll_clear(pArrayListEmployee);
				flag=parser_EmployeeFromText(f, pArrayListEmployee);
			}

		}
		else
		{
			flag=4;
		}
	}

	fclose(f);

    return flag;
}

/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int error=-1;
	FILE* f;
	char confirmacion;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		f= fopen(path,"rb");
		if(f!=NULL)
		{
			if(ll_len(pArrayListEmployee)>0 && utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n')==0)
			{
				if(confirmacion!='s')
				{
					error=5;
				}
			}
			if(ll_len(pArrayListEmployee)==0 || confirmacion=='s')
			{
				ll_clear(pArrayListEmployee);
				error=parser_EmployeeFromBinary(f, pArrayListEmployee);
			}
		}
		else
		{
			error=3;//no se pudo abrir
		}
	}

	fclose(f);
    return error;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int* id)
{
	int error=-1;
	Employee* aux=NULL;
	int idAux;

	if(pArrayListEmployee!=NULL && id!=NULL && employee_buscarMayorId(pArrayListEmployee,&idAux)==0)
	{
		printf("\nid %d\n", idAux);
		aux= employee_new();

		if(aux!=NULL &&
			utn_getString(aux->nombre, "Ingrese nombre ", "ERROR ingrese solo letras ", 5)==0 &&
			utn_getNumeroEnteroConIntentos(&aux->horasTrabajadas, "Ingrese las horas trabajadas entre 50-500 ",
					"ERROR reingrese las horas trabajadas entre 50-500 ", 50, 500, 5)==0 &&
			utn_getNumeroEnteroConIntentos(&aux->sueldo, "Ingrese sueldo entre 1000-1000000 ",
					"ERROR reingrese sueldo entre 1000-1000000 ", 1000, 1000000, 5)==0)
		{
			aux->id= idAux;

			if(ll_add(pArrayListEmployee, aux)==0)
			{
				*id=idAux+1;
				aux=NULL;
				error=0;
			}
		}
	}

    return error;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)// ll_set
{
	int error=-1;
	Employee* aux=NULL;
	Employee* auxGuardado=NULL;
	int indice;

	if(pArrayListEmployee!=NULL)
	{
		aux=employee_pedirIdyMostrar(pArrayListEmployee, &indice);

		if(aux!=NULL && indice>=0)
		{
			auxGuardado=employee_menuModificar(aux);
			if(auxGuardado->id>0)
			{
				if(ll_set(pArrayListEmployee, indice, aux)==0)
				{
					error=0;
					aux=NULL;
					auxGuardado=NULL;
				}
			}
			else
			{
				error=1;
				aux=NULL;
				auxGuardado=NULL;
			}
		}
		else
		{
			error=2;
		}
	}
    return error;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	Employee* aux=NULL;
	int indice;
	char confirmacion;

	if(pArrayListEmployee!=NULL)
	{
		aux=employee_pedirIdyMostrar(pArrayListEmployee, &indice);

		if(aux!=NULL && indice>=0)
		{
			if(utn_getCaracterCorroboraDosCarac(&confirmacion, "Eliminar empleado s/n", "ERROR ingrese s/n", 's', 'n')==0)
			{
				if(confirmacion=='s' && ll_remove(pArrayListEmployee, indice)==0)
				{
					aux=NULL;
					error=0;
				}
				else
				{
					error=1;

				}
			}
		}
		else
		{
			error=2;
		}
	}
    return error;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	int tam;
	Employee* aux=NULL;

	tam= ll_len(pArrayListEmployee);

	if(pArrayListEmployee!=NULL && tam>0)
	{
		printf("\n Id HsTrb Sueldo Nombre\n");

		for(int i=0; i<tam; i++)
		{
			aux=(Employee*) ll_get(pArrayListEmployee, i);
			employee_mostrarEmpleado(aux);
			//aux=NULL;
		}

		error=0;
	}

    return error;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	int opcion;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumeroEnteroConIntentos(&opcion, "\nOrdenar por\n 1-Nombre Ascendente\n 2-Nombre Descendente\n "
				"3-Hs Trabajadas Ascendente\n 4-Hs Trabajadas Descendente\n "
				"5-Sueldo Ascendente\n 6-Sueldo Descendente", "ERROR ingrese 1-7 ", 1, 7, 5)==0)
		{
			switch (opcion)
			{
				case 1:
					printf("Nombre Ascendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpNombre, 0);
					break;

				case 2:
					printf("Nombre Descendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpNombre, 1);
					break;

				case 3:
					printf("Hs Trabajadas Ascendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpHsTrab, 0);
					break;

				case 4:
					printf("Hs Trabajadas Descendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpHsTrab, 1);
					break;

				case 5:
					printf("Sueldo Ascendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpSueldo, 0);
					break;

				case 6:
					printf("Sueldo Descendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpSueldo, 1);
					break;
			}
		}
		error=0;
	}


    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int error=-1;
	FILE* f;
	int tam;
	Employee* aux=NULL;
	char confirmacion='s';

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		f= fopen(path, "r");
		if(f!=NULL)
		{
			utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n');
		}

		fclose(f);

		if(confirmacion=='s')
		{
			f= fopen(path, "w");

			if(f!=NULL)
			{
				fprintf(f,"Id,Nombre,HorasTrabajadas,Sueldo\n");

				tam= ll_len(pArrayListEmployee);

				for(int i=0; i<tam; i++)
				{
					aux=(Employee*) ll_get(pArrayListEmployee, i);
					if(aux!=NULL)
					{
						fprintf(f,"%d,%s,%d,%d\n",
									aux->id,
									aux->nombre,
									aux->horasTrabajadas,
									aux->sueldo);
						aux=NULL;
					}
					else
					{
						error=1;// hubo problema en el fprintf
						break;
					}
				}
			}
			else
			{
				error=2; // hubo problema en abrir el archivo
			}
			error=0;
		}
		else
		{
			error=3; // cancelacion de sobreescribir
		}
	}

	fclose(f);

    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int error=-1;
	int tam;
	Employee* aux=NULL;
	FILE* f;
	char confirmacion='s';

	tam=ll_len(pArrayListEmployee);

	if(path!=NULL && pArrayListEmployee!=NULL && tam>0)
	{
		f= fopen(path, "rb");
		if(f!=NULL)
		{
			utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n');

		}

		fclose(f);
		if(confirmacion=='s')
		{
			f= fopen(path, "wb");
			if(f!=NULL)
			{
				for(int i=0; i<tam; i++)
				{
					aux=(Employee*) ll_get(pArrayListEmployee, i);
					if(aux!=NULL)
					{
						if(fwrite(aux, sizeof(Employee),1,f)<1)
						{
							error=1;// hubo un problema en el guardado
							break;
						}
						else
						{
							error=0;
						}
					}
					else
					{
						error=2;// hubo un problema en cargar el empleado
						break;
					}
				}
			}
		}
		else
		{
			error=3;
		}
	}
fclose(f);
    return error;
}

