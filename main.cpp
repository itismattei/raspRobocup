
#include <iostream>
#include <fstream>
using namespace std;

#include "SerialComm.h"
#include "TRcmd.h"
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
	
	int count, conteggio = 0, STATO = 1, num_cicli = 0;
	char CHK, FIX = 0xA9, buff[128];
	unsigned int nextTime ;
	int fd;
	ofstream outF("dati.txt", ios::app);
	cout << "Test Comunicazione!" << endl;
	SerialComm sc;
	TRcmd CMD;
	CMD.connect(&sc);
//	fd = sc.openSer();
//	printf("Num descrittore %d\n", fd);
//	if (fd < 0){
//		/// la seriale non e' presente o non ha risposto
//		exit(-1);
//	}
	

	nextTime = millis () + 500 ;

	while(1){
	  ///inivia un comando ogni 2 secondi

		if (millis () > nextTime){
			//cout << "Out: " << "F" << endl;
		  num_cicli++;
		  //printf ("\nOut: %3d: ", count) ;
		  fflush (stdout) ;
		  switch(STATO){
		  case 0:
		 	  CMD.sendCmd('F');
		 	  STATO = 1;
			  cout << "Out: " << "F " << num_cicli <<endl;
		  break;

		  case 1:
		 	  CMD.sendCmd('B');
		 	  STATO = 0;
			  cout << "Out: " << "B" << num_cicli <<endl;
		  break;

		  case 2:
		 	  CMD.sendCmd('I');
		 	  STATO = 3;
			  cout << "Out: " << "I" << endl;
		  break;

		  case 3:
		 	  CMD.sendCmd('S');
		 	  STATO = 0;
			  cout << "Out: " << "S " << endl;
		  break;

		  }
//		  CHK = 'D';
//		  CHK ^= 1;
//		  CHK ^= FIX;
//		  buff[0] = 'D';
//		  buff[1] = 1;
//		  buff[2] = CHK;
//		  buff[3] = '*';
//		  /// scrive i 4 bytes sulla seriale
//		  sc.writeBuff(buff, 4);

//		  serialPutchar (fd, count) ;
//		  serialPutchar (fd, '\n');
//		  serialPutchar (fd, '\r');
		  nextTime += 100 ;
		}

//		delay (3) ;
//		if (conteggio > 16){
		  while (count = sc.readBuff(buff)){
			printf("ricevuto \n");
//			//printf (" -> %3d", serialGetchar (fd)) ;
			cout << "letti :" << count << "bytes" << endl;
			for (int i = 0 ; i < count; i++)
				cout << "valore " << (int) buff[i] << endl;
		}
//			printf("%c", serialGetchar(fd));
//			fflush (stdout) ;
//			//printf("\n");
//		  }
//		  /// reset di conteggio: aspetta altri 16 secondi
//		  conteggio = 0;
//		  printf("\n");
//		}
//
//	  outF.close();
		}

	//funzione();

}
