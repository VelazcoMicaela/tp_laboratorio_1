#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"


/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
	setbuf(stdout,NULL);

    int opcion;
    char salir;
    int error;
    int idNext=1;
    char path[50];


    LinkedList* listaEmpleados = ll_newLinkedList();


	if(listaEmpleados!=NULL)
	{
	   do{
		   if(utn_getNumeroEnteroConIntentos(&opcion, "\nIngrese una opcion\n 1-Cargar modo texto\n 2-Cargas modo binario\n "
				   "3-Alta\n 4-Modificacion\n 5-Baja\n 6-Listar\n 7-Ordenar\n 8-Guardar modo texto\n 9-Guardar modo binario\n 10-Salir ",
				   "ERROR ingrese una opcion entre 1-10 ", 1, 10, 5)==0)
		   {
				switch(opcion)
				{
					case 1:
						printf(" Cargar datos (modo texto)\n");
						ingresarPath(path);

						error=controller_loadFromText(path,listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados cargados exitosamente\n", "ERROR hubo un problema para cargar el empleado\n",
											"ERROR hubo un problema en el parseo\n", "ERROR hubo un problema con el levantar datos\n", "ERROR hubo problema al abrir\n",
											"Datos no sobreescritos\n");
						break;

					case 2:
						printf(" Cargar datos (modo binario)\n");
						ingresarPath(path);
						error=controller_loadFromBinary(path,listaEmpleados);
						menuErrores(error, "ERROR hubo un problema\n", "Empleados cargados exitosamente\n", "ERROR hubo un problema para cargar el empleado\n",
											"ERROR hubo un problema en el parseo\n", "ERROR hubo un problema con el levantar datos\n", "ERROR hubo problema al abrir\n",
											"Datos no sobreescritos\n");
						break;

					case 3:
						printf(" Alta de empleado\n");
						if(controller_addEmployee(listaEmpleados,&idNext)==0)
						{
							printf("Alta exitosa\n");
							controller_ListEmployee(listaEmpleados);
						}

						break;

					case 4:
						printf(" Modificar empleado\n");
						error=controller_editEmployee(listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados modificado exitosamente\n", "Modificacion cancelada\n",
														"ERROR no existe empleado con ese id\n", " ", " ", " ");
						break;

					case 5:
						printf(" Baja de empleado\n");
						error=controller_removeEmployee(listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados dado de baja exitosamente\n", "Baja cancelada\n",
											"ERROR no existe empleado con ese id\n", " ", " ", " ");
						break;

					case 6:
						printf(" Listar de empleado\n");

						if(controller_ListEmployee(listaEmpleados)==0)
						{

							printf("listar exitoso\n");
						}

						break;

					case 7:
						printf(" Ordenar de empleado\n");
						if(controller_sortEmployee(listaEmpleados)==0)
						{
							controller_ListEmployee(listaEmpleados);
							printf("Oredenados exitosamente\n");
						}

						break;

					case 8:
						printf(" Guardar datos (modo texto)\n");
						ingresarPath(path);
						error=controller_saveAsText(path, listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados guardados exitosamente\n", "ERROR hubo problema en el fprintf\n",
											"ERROR hubo problema en abrir el archivo\n", "Archivo no guardado. Datos no sobreescritos", " ", " ");
						break;

					case 9:
						printf(" Guardar datos (modo binario)\n");
						ingresarPath(path);
						error=controller_saveAsBinary(path, listaEmpleados);
						menuErrores(error, "ERROR hubo un problema\n", "Empleados guardados exitosamente\n", "ERROR hubo problema en el guardado\n",
											"ERROR hubo problema en abrir el archivo\n", "Archivo no guardado. Datos no sobreescritos", " ", " ");

						break;

					case 10:
						printf(" Salir\n");
						if(utn_getCaracterCorroboraDosCarac(&salir, "Desea salir? S/N\n", "ERROR Ingrese S para salir o N para quedarse", 's', 'n')==0)
						{
							if(salir=='s')
							{
								printf("Hasta luego\n");
							}
						}
						break;
				}
		   }

		}while(salir !='s');
	}

   ll_deleteLinkedList(listaEmpleados);
    return 0;
}

