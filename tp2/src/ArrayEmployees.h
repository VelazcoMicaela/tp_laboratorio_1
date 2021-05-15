/*
 * ArrayEmployees.h
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

typedef struct
{
 int id;
 char name[51];
 char lastName[51];
 float salary;
 int sector;
 int isEmpty;
}eEmployee;

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int initEmployees(eEmployee* list, int len);


/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 */
int addEmployee(eEmployee* list, int len, int* id);

/** \brief searches for the first free index in the list
 * \param list employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 */
int searchFree(eEmployee* list, int len, int* id);


/** \brief print the content of an employee
 *
 * \param list Employee
 * \return void
 *
 */
void printOneEmployee(eEmployee list);

/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int
 *
 */
int printEmployees(eEmployee* list, int length);


/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */
int findEmployeeById(eEmployee* list, int len,int id);


/** \brief search for an employee by id and modify the data that the user wants
 *
 * \param list Employee*
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 *
 */
int modifyEmployee(eEmployee* list, int len);

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */
int removeEmployee(eEmployee* list, int len);


/** \brief Sort the elements in the array of employees for name, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployeesName(eEmployee* list, int len, int order);

/** \brief Sort the elements in the array of employees for Lastname, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployeesLastName(eEmployee* list, int len, int order);

/** \brief Sort the elements in the array of employees for salary, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployeesSalary(eEmployee* list, int len, int order);

/** \brief Sort the elements in the array of employees for sector, the argument order
 * indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployeesSector(eEmployee* list, int len, int order);

/** \brief adds the salary of all the employees with the loaded isEmpty and makes the average of it,
 * returning the total and the average by value
 *
 * \param list Employee*
 * \param len int
 * \param total float*
 * \param promedio float*
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int averageSalary(eEmployee list[], int len, float* total, float* promedio);


/** \brief traverses the array comparing salaries with the average passed by reference,
 * returning by value the number of employees that exceed the average
 *
 * \param list Employee*
 * \param len int
 * \param cantidad int*
 * \param promedio float
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int exceedSalary(eEmployee list[], int len, float promedio, int* cantidad);


#endif /* ARRAYEMPLOYEES_H_ */
