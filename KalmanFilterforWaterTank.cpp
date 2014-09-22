#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <conio.h>
#include <iostream>

using namespace std;

double frand() { 
    return 2*((rand()/(double)RAND_MAX) - 0.5); 
} 

int main() { 

    //initial values for the kalman filter 
    float x_estimatedlast = 0;
    float P_last = 0; 
    //the noise in the system 
    float Q = 0.022;
    float R = 0.617;
     
    float K; 
    float P; 
    float P_temp; 
    float x_tempestimated; 
    float x_estimated; 
    float z_measured; //the 'noisy' value we measured
    float z_real = 0.5; //the ideal value we wish to measure
     
    srand(0);		// initializes random number generator with seed 0
     
    //initialize with a measurement 
    x_estimatedlast = z_real + frand()*0.09;
     
    float sum_errorkalman = 0;
    float sum_errormeasure = 0;
     
    for (int i=0;i<30;i++) {
												 //do a prediction 
        x_tempestimated = x_estimatedlast; 
        P_temp = P_last + Q; 
											//calculate the Kalman gain 
        K = P_temp * (1.0/(P_temp + R));
        //measure 
        z_measured = z_real + frand()*0.09; //the real measurement plus noise
        //correct 
        x_estimated = x_tempestimated + K * (z_measured - x_tempestimated);  
        P = (1- K) * P_temp; 
														 //we have our new system 
         
        printf("Ideal    position: %6.3f \n",z_real); 
        printf("Mesaured position: %6.3f [diff:%.3f]\n",z_measured,fabs(z_real-z_measured)); 
        printf("Kalman   position: %6.3f [diff:%.3f]\n\n\n\n",x_estimated,fabs(z_real - x_estimated)); 
        getch(); 
        sum_errorkalman += fabs(z_real - x_estimated); 
        sum_errormeasure += fabs(z_real-z_measured); 
         
        //update our last's 
        P_last = P; 
        x_estimatedlast = x_estimated; 
    } 
     
    printf("Total error if using raw measured:  %f\n",sum_errormeasure);
    printf("Total error if using kalman filter: %f\n",sum_errorkalman);
    printf("Reduction in error: %d%% \n\n\n\n\n",100-(int)((sum_errorkalman/sum_errormeasure)*100));
   
	
	getch();

     
    return 0; 
}
