/* ******************************************************************

		@Author : Ahmed Khaled Abdelmaksod

		username : Ahmed-Khaled-Abdelmaksod 

		ID : 2000218 

		Date : 19 / 4 / 2023

		time : 15:00
		
		gps file 

		*******************************************************************
*/
#ifndef GPS_H_
#define GPS_H_
#include "lcd.h"
#include "string.h"
#include <math.h>
#include "stdlib.h"


          /*  ______global variables________ */

#define PI (3.14159)
#define R (6371000) // Raduis of the earth in km 

           /* _______functions prototypes_______ */

double MAKE_RADIAN(double deg);
void GET_DISTANCE(void);
void GET_READINGS(void);

#endif
