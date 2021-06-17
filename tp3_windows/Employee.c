#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "LinkedList.h"
#include "employee.h"



Employee* employee_new()
{
	Employee* aux;

	aux= (Employee*) malloc (sizeof(Employee));
	if(aux!=NULL)
	{
		aux->id=0;
		strcpy( aux->nombre, " ");
		aux->horasTrabajadas=0;
		aux->sueldo=0;
	}

	return aux;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* aux;

	aux=employee_new();

	if(aux!=NULL && idStr!=NULL && nombreStr!=NULL && horasTrabajadasStr!=NULL && sueldoStr!=NULL)
	{
		if(!(employee_setId(aux, atoi(idStr))==0 &&
			employee_setNombre(aux, nombreStr)==0 &&
			employee_setHorasTrabajadas(aux, atoi(horasTrabajadasStr))==0 &&
			employee_setSueldo(aux, atoi(sueldoStr))==0))
		{
			free(aux);
			aux=NULL;
		}
	}

	return aux;
}

////// EMPIEZAN SET ///////

int employee_setId(Employee* this,int id)
{
	int error=-1;

	if(this!=NULL && id>0 && id<2000)
	{
		this->id=id;
		error=0;
	}

	return error;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int error=-1;


	if(this!=NULL && strlen(nombre)<100 && strlen(nombre)>1 )

	{
		strcpy( this->nombre, nombre);
		error=0;
	}

	return error;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int error=-1;

	if(this!=NULL && horasTrabajadas>0 && horasTrabajadas<1000)
	{
		this->horasTrabajadas=horasTrabajadas;
		error=0;
	}

	return error;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int error=-1;

	if(this!=NULL && sueldo>10 && sueldo<1000000)
	{
		this->sueldo=sueldo;
		error=0;
	}

	return error;
}

/////////////// EMPIEZAN GET////////////

int employee_getId(Employee* this,int* id)
{
	int error=-1;

	if(this!=NULL && id!=NULL)
	{
		*id= this->id;
		error=0;
	}

	return error;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int error=-1;

	if(this!=NULL && nombre!=NULL)
	{
		strcpy(nombre, this->nombre);
		error=0;
	}

	return error;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int error=-1;

	if(this!=NULL && horasTrabajadas!=NULL)
	{
		*horasTrabajadas= this->horasTrabajadas;
		error=0;
	}

	return error;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int error=-1;

	if(this!=NULL && sueldo!=NULL)
	{
		*sueldo= this->sueldo;
		error=0;
	}

	return error;
}

int employee_mostrarEmpleado(Employee* emp)
{
	int error=-1;
	int id;
	char nombre[128];
	int horasTrabajadas;
	int sueldo;

	if(emp!=NULL)
	{
		if(employee_getId(emp, &id)==0 &&
			employee_getNombre(emp, nombre)==0 &&
			employee_getHorasTrabajadas(emp, &horasTrabajadas)==0 &&
			employee_getSueldo(emp,&sueldo)==0)
		{
			printf("%d %s %d %d\n", id,nombre, horasTrabajadas, sueldo);
		}

		error=0;
	}
    return error;
}

void employee_employee_delete()
{
	//free(array);
}
///////////// comparaciones ////////////

int employee_empleadoCmpSueldo(void* a, void* b)
{
	int retorno=0;

	Employee* emp1;
	Employee* emp2;

	if(a!=NULL && b!=NULL)
	{
		emp1= (Employee*) a;
		emp2= (Employee*) b;

		if(emp1->sueldo > emp2->sueldo)
		{
			retorno=1;
		}
		else if(emp1->sueldo < emp2->sueldo)
		{
			retorno=-1;
		}
	}
	return retorno;
}

int employee_buscarId(LinkedList* pArrayListEmployee, int tam, int id)
{
	Employee* aux=NULL;
	int indice=-1;

	if(pArrayListEmployee!=NULL && tam>0 && id>0)
	{
		for(int i=0; i<tam; i++)
		{
			aux=(Employee*) ll_get(pArrayListEmployee, i);
			if(aux->id == id)
			{
				indice=i;
				break;
			}
		}
	}

	return indice;
}

Employee* employee_menuModificar(Employee* empleado)
{
	int opcion;
	char salir;

	if(empleado!=NULL)
	{
		do
		{
			if(utn_getNumeroEnteroConIntentos(&opcion, "Modificar \n 1-Nombre\n 2-Horas trabajadas\n 3-Sueldo\n 4-Guardar  ",
							"ERROR reingrese una opcion ", 0, 4, 5)==0)
			{
				switch(opcion)
				{
					case 1:
						printf("Modificar Nombre\n");
						if(utn_getString(empleado->nombre, "Ingrese nombre ", "ERROR ingrese solo letras ", 5)==0)
						{
							employee_mostrarEmpleado(empleado);
						}
						else
						{
							printf("ERROR\n");
						}
						break;

					case 2:
						printf("Modificar Horas Trabajadas\n");
						if(utn_getNumeroEnteroConIntentos(&empleado->horasTrabajadas, "Ingrese las horas trabajadas ",
								"ERROR reingrese las horas trabajadas entre 0-1000 ", 0, 1000, 5)==0)
						{
							employee_mostrarEmpleado(empleado);
						}
						break;

					case 3:
						printf("Modificar Sueldo\n");
						if(utn_getNumeroEnteroConIntentos(&empleado->sueldo, "Ingrese sueldo ",
								"ERROR reingrese sueldo entre 10-1000000 ", 10, 1000000, 5)==0)
						{
							employee_mostrarEmpleado(empleado);
						}
						break;

					case 4:
						printf("Guardar\n");
						if(utn_getCaracterCorroboraDosCarac(&salir, "Guardar los cambios s/n", "ERROR ingrese s/n", 's', 'n')==0)
						{
							if(salir=='s')
							{
								return empleado;
							}
							else
							{
								empleado->id=-1;

							}

						}
						break;
				}
			}
		}while(opcion!=4);
	}

	return empleado;
}

Employee* employee_pedirIdyMostrar(LinkedList* pArrayListEmployee, int* indice)
{
	int tam;
	Employee* aux=NULL;
	int id;
	int idAux;

	if(pArrayListEmployee!=NULL && indice!=NULL)
	{
		if(controller_ListEmployee(pArrayListEmployee)==0 &&
				utn_getNumeroEnteroConIntentos(&id, "Ingrese el id del empleado ",
				"ERROR reingrese id ", 0, 5000, 5)==0)
		{
			tam= ll_len(pArrayListEmployee);

			idAux= employee_buscarId(pArrayListEmployee, tam, id);

			if(idAux>=0)
			{
				aux=(Employee*) ll_get(pArrayListEmployee, idAux);
				employee_mostrarEmpleado(aux);
				*indice=idAux;
			}
		}
	}

	return aux;
}




