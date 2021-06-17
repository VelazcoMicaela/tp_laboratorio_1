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
    int idNext=1001;


    LinkedList* listaEmpleados = ll_newLinkedList();

   do{
	   if(utn_getNumeroEnteroConIntentos(&opcion, "\nIngrese una opcion\n 1-Cargar modo texto\n 2-Cargas modo binario\n "
			   "3-Alta\n 4-Modificacion\n 5-Baja\n 6-Listar\n 7-Ordenar\n 8-Guardar modo texto\n 9-Guardar modo binario\n 10-Salir ",
			   "ERROR ingrese una opcion entre 1-10 ", 1, 10, 5)==0)
	   {
			switch(opcion)
			{
				case 1:
					printf(" Cargar datos (modo texto)\n");

					error=controller_loadFromText("data.csv",listaEmpleados);
					if(error==-1)
					{
						printf("ERROR hubo un problema\n");
					}
					if(error==0)
					{
						printf("Empleados cargados exitosamente\n");
					}
					else if(error==1)
					{
						printf("ERROR hubo un problema para conseguir lugar\n");
					}
					else if(error==2)
					{
						printf("ERROR hubo un problema para conseguir empleado\n");
					}
					else if(error==3)
					{
						printf("ERROR hubo problema en el parseo\n");
					}
					break;

				case 2:
					printf(" Cargar datos (modo binario)\n");
					error=controller_loadFromBinary("data.bin",listaEmpleados);

					switch(error)
					{
						case -1:
							printf("ERROR hubo un problema\n");
							break;

						case 0:
							printf("Empleados cargados exitosamente\n");
							break;

						case 1:
							printf("ERROR hubo un problema para cargar el empleado\n");
							break;

						case 2:
							printf("ERROR hubo un problema en el parseo\n");
							break;

						case 3:
							printf("ERROR hubo un problema con el levantar datos\n");
							break;

						case 4:
							printf("ERROR hubo problema al abrir\n");
							break;
					}
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

					switch(error)
					{
						case -1:
							printf("ERROR hubo un problema\n");
							break;

						case 0:
							printf("Empleados modificado exitosamente\n");
							break;

						case 1:
							printf("Modificacion cancelada\n");
							break;

						case 2:
							printf("ERROR no existe empleado con ese id\n");
							break;
					}

					break;

				case 5:
					printf(" Baja de empleado\n");
					error=controller_removeEmployee(listaEmpleados);

					switch(error)
					{
						case -1:
							printf("ERROR hubo un problema\n");
							break;

						case 0:
							printf("Empleado dado de baja exitosamente\n");
							break;

						case 1:
							printf("eliminacion cancelada\n");
							break;

						case 2:
							printf("ERROR no existe empleado con ese id\n");
							break;
					}

					break;

				case 6:
					printf(" Listar de empleado\n");


					if(controller_ListEmployee(listaEmpleados)==0)
					{

						printf("listar exitoso\n");
					}
					else
					{
						printf("ERROR\n");
					}

					break;

				case 7:
					printf(" Ordenar de empleado\n");
					error=controller_sortEmployee(listaEmpleados);
					printf("error %d\n",error);
					if(error==0){
						controller_ListEmployee(listaEmpleados);
					}
					else
					{
						printf("ERROR\n\n");
					}

					break;

				case 8:
					printf(" Guardar datos (modo texto)\n");
					error=controller_saveAsText("data.csv", listaEmpleados);
					switch(error)
					{
						case -1:
							printf("ERROR hubo un problema\n");
							break;

						case 0:
							printf("Empleados guardados exitosamente\n");
							break;

						case 1:
							printf("ERROR hubo problema en el fprintf\n");
							break;

						case 2:
							printf("ERROR hubo problema en abrir el archivo\n");
							break;
					}
					break;

				case 9:
					printf(" Guardar datos (modo binario)\n");
					error=controller_saveAsBinary("data.bin", listaEmpleados);
					switch(error)
					{
						case -1:
							printf("ERROR hubo un problema\n");
							break;

						case 0:
							printf("Empleados guardados exitosamente\n");
							break;

						case 1:
							printf("ERROR hubo un problema en el guardado\n");
							break;

						case 2:
							printf("ERROR hubo problema en abrir el archivo\n");
							break;
					}
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

   ll_deleteLinkedList(listaEmpleados);
    return 0;
}

