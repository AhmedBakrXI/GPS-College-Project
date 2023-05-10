/* ******************************************************************

		Author : Ahmed-Khaled-Abdelmaksod

		ID : 2000218 

		Date : 19 / 4 / 2023

		gps file 

		*******************************************************************
*/

// include header files

#include "gps.h"
#include "UART.h"
#include "systick.h"

// _________ global variable ________________ 

static volatile double arr[4]; // it will store two latitude & longitude of two points
volatile double distance = 0.0; // the overall walked distance
static volatile int i = 0; // global counter
volatile double latitude = 0.0, longitude = 0.0;

// __________functions implementation_____________


/* *********************************************
purpose  : to read from GPS module and extract latitude & longitude
argument : void
return	 : void
	 *********************************************
*/

//$GPGGA, 123519, 4807.038, N, 01131.000, E, 1, 08, 0.9, 545.4, M, 46.9, M, , *47
void GET_READINGS(void){
	// variables decleration 
	char c0; // use it to recieve
	char GPSValues[100];  // Values of gps before seperation
	char parseValues[12][20]; // to store the seperated strings after receive it from gps
	char  *token; // pointer to a string
  	double min = 0.0, sec = 0.0, result = 0.0;
	int j = 0; // counter
	int deg;
	
	c0 = RECEIVE_BYTE(); // receive the first char from uart
	// if the first char is '$' ,then start to test to store the value of gps
	if(c0 == '$'){
		// receive the second char
		char c1 = RECEIVE_BYTE();
		// test it
		if(c1 == 'G'){
			// receive the second char
			char c2 = RECEIVE_BYTE();
			// test it
			if(c2 == 'P'){
				// receive the second char
				char c3 = RECEIVE_BYTE();
				// test it
				if(c3 == 'G'){
					// receive the second char
					char c4 = RECEIVE_BYTE();
					// test it
					if(c4 == 'G'){
						// receive the second char
						char c5 = RECEIVE_BYTE();
						// test it
						if(c5 == 'A'){
							// receive the second char
							char c6 = RECEIVE_BYTE();
							// test it
							if(c6 == ','){
								// receive the second char
								char c7 = RECEIVE_BYTE();
								/* **************
									this loop used to get the full string from gps and it will terminate @ this char'*'
									example : $GPGGA, 123519, 4807.038, N, 01131.000, E, 1, 08, 0.9, 545.4, M, 46.9, M, , *47  <-- it will terminate at '*'
									*****************
								*/
								while(c7 != '*'){
									GPSValues[i] = c7; // store the gps value in this array char by char
									c7 = RECEIVE_BYTE(); // receive a char from gps
									i++; // increament the counter 
								}
								
								i = 0; // clear the global counter
								
								/* **************************
									this line will cut _@ every ',' char_ the string (gpsvalue) to some strings 
									token pointer will point to this strings
									*************************
								*/
								token = strtok(GPSValues, ","); 
								/* **************************
									this loop will copy every string token that token pointer point to to parseValues array
									*************************
								*/
								while(token != NULL){
									strcpy(parseValues[i], token);
									token = strtok(NULL, ",");
									i++;
								}

								// start processing to extract lat and long
								/*  **************************
									 this condition is true if the gps read correct
									 the gps will read correct if the sixth string is "1"
									 $GPGGA, 123519, 4807.038, N, 01131.000, E, 1, 08, 0.9, 545.4, M, 46.9, M, , *47  <-- it will terminate at '*'
								    *************************
								*/
								if( strcmp(parseValues[5], "1") == 0) 
								{
									Command(Clear);
									Command(HOME);
									DISPLAY_STRING("Lat:");
									Command(ROW_2);
									DISPLAY_STRING(parseValues[1]);
									DelayMilli(500);
									Command(Clear);
									Command(HOME);
									DISPLAY_STRING("Lon:");
									Command(ROW_2);
									DISPLAY_STRING(parseValues[3]);
									DelayMilli(500);
									latitude = atof(parseValues[1]); // extract latitude from the string and convert it to double using atof function
									longitude = atof(parseValues[3]);// extract longitude from the string and convert it to double using atof function
									
									// adjust latitude and convert it to degrees , minutes and seconds
									deg = latitude/100; // calc degrees
									min = latitude - (double)(deg*100); // calc minutes
									sec = min/60.0; // calc seconds
									result = deg + sec; // summation of degrees and minutes
									
									arr[j] = result; // store the latitude in the global array
									j++; // increament global counter (j)
									
									// calculate longitude
									deg = longitude/100; // calc degrees
									min = longitude - (double)(deg*100); // calc minutes
									sec = min/60.0; // calc seconds
									result = deg + sec; // summation of degrees and minutes
									
									arr[j] = result; // store the longitude in the global array
									j++; // increament global counter (j)
									/*
										this condition is used to calculate the distance between the two points
										after calculation make the second point is the first to calc the distance with the next one and delete the first point
									*/
									if(j==4){
										GET_DISTANCE(); // calculate the distance
										arr[0] = arr[2];
										arr[1] = arr[3];
									}
									j = 2; // assign the global counter j with 2 to be able to add another point and calc distance
								}
							}
						}
					}
				}
			}
		}
	}
}

/* *********************************************
purpose  : to convert degress to radian to use haversine formula
argument : value in degrees (double)
return	 : value in radians (double)
	 *********************************************
*/
double MAKE_RADIAN(double deg)
{
	return deg * (PI/180);
}
/* *********************************************
purpose  : to calculate the total distance
argument : void
return   : void
	 *********************************************
*/

void GET_DISTANCE(void)
{
	char str[50];
	double lat1 = MAKE_RADIAN(arr[0]); // latitude point 1 in Rad
	double lat2 = MAKE_RADIAN(arr[2]); // latitude point 2 in Rad
	double diff_lat = lat1 - lat2; // subtract lat1 - lat2
	double diff_long = MAKE_RADIAN(arr[1]) - MAKE_RADIAN(arr[3]); // subtract long1 - long2
	/* *********************
		Hint : heversine is a formula that calculate the distance between two points using latitude & longitude
	*/
	// calculate distance between the two points  
	double x = pow(sin(diff_lat/2),2) + cos(lat1) * cos(lat2) * pow(sin(diff_long/2),2);
	double y = atan2(sqrt(x),sqrt(x-1));
	double d = y*R*1000; // d in meter 
	
	distance += d; // add the calculated distance to the comulative distance 
	/*
	// print distance on lcd 
	sprintf((char*)str,"%f",distance); // convert distanc to a string to print it on lcd
	Command(lcd_Clear); // clear lcd
	DISPLAY_STRING((unsigned char*)"Distance : ");
	DISPLAY_STRING(str);
	*/
	
}
