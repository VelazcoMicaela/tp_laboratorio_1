/*
 * menu.h

 */

#ifndef MENU_H_
#define MENU_H_
#include "ArrayEmployees.h"

/** \brief shows the options menu and contains all the logic to develop them
 * \param void
 * \return void
 *
 */
void menu(void);

/** \brief shows the options to modify an employee and contains all the logic of the same
 * \param list Employee* Pointer of one employees
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int menuModify(eEmployee* list);

/** \brief shows the report options and contains the logic of the same
 * \param list Employee* Pointer of one employees
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int menuInformes (eEmployee emp[], int len);

#endif /* MENU_H_ */
