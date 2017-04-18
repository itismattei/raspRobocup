
#include <iostream>
#include <fstream>
using namespace std;

#include "SerialComm.h"
#include <stdio.h>
#include <stdlib.h>
#include <wiringSerial.h>
#include <string.h>
#include <errno.h>

extern "C" {	
	int funzione();
	int millis();
	int delay(int);
}


/// 
/// programma principale
///

int main(){
	
	int count, conteggio = 0;
	unsigned int nextTime ;
	int fd;
	ofstream outF("dati.txt", ios::app);
	cout << "Ciao Mondo!" << endl;
	SerialComm sc;
	fd = sc.openSer();
	printf("Num descrittore %d\n", fd);
	if (fd < 0){
		/// la seriale non e' presente o non ha risposto
		exit(-1);
	}
	

	nextTime = millis () + 500 ;

	while(1){
	  
	  for (count = 48 ; count < 58 ; ){
	    if (millis () > nextTime){
	    	cout << "Out: " << count<< endl;
	      //printf ("\nOut: %3d: ", count) ;
	      fflush (stdout) ;
	      serialPutchar (fd, count) ;
	      serialPutchar (fd, '\n');
	      serialPutchar (fd, '\r');
	      nextTime += 1000 ;
	      ++count ;
	      conteggio++;
	      outF << "Out:" << count << endl;
	      //fprintf(fp, "\nOut: %d: ", count);
	    }

	    delay (3) ;
	    if (conteggio > 16){
	      while (serialDataAvail (fd)){
	        //printf("ricevuto \n");
	        //printf (" -> %3d", serialGetchar (fd)) ;
	        printf("%c", serialGetchar(fd));
	        fflush (stdout) ;
	        //printf("\n");	
	      }
	      /// reset di conteggio: aspetta altri 16 secondi
	      conteggio = 0;
	      printf("\n");
	    }
	  }
	  outF.close();
	}
	 
	
	//funzione();

}
