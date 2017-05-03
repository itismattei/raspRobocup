
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

#include "campoGara.h"
#include <iterator>

extern "C" {	
	int funzione();
	int millis();
	int delay(int);
}


/// 
/// programma principale
///

int main(){
	
	int count, conteggio = 0, STATO = 0, num_cicli = 0;
	char CHK, FIX = 0xA9, buff[128];
	unsigned int nextTime ;
	int fd;
	ofstream outF("dati.txt", ios::app);
	cout << "Test Comunicazione!" << endl;
	outF << "Registrazione comunicazioni" << endl;
	SerialComm sc;
	TRcmd CMD;
	CMD.connect(&sc);
//	fd = sc.openSer();
//	printf("Num descrittore %d\n", fd);
//	if (fd < 0){
//		/// la seriale non e' presente o non ha risposto
//		exit(-1);
//	}
	/// campo di gara
	campoGara terreno;
	//cellaBase cella;
	//cella.e[0] = 0;
	//cella.e[1] = 1;
	//terreno.campo.push_back(cella);
	//cella.e[0] = 1;
	//cella.e[1] = 1;
	//terreno.campo.push_back(cella);
	/// stampala dimensione del vettore
	//cout << "dim " << terreno.campo.size()  << endl;
	//cout << "coord. sec elemento " << terreno.campo[1].e[0] << " : " << terreno.campo[1].e[1] << endl;
	//cout << "coord. primo elemento " << terreno.campo[0].e[0] << " : " << terreno.campo[0].e[1] << endl;

	/// iteratore
	//vector<int> pippo;
	//pippo.push_back(4);
	//vector<int>::iterator pp= find(pippo.begin(), pippo.end(), 4);
	//vector<cellaBase>::iterator it = find(terreno.campo.begin(), terreno.campo.end(), cella);

	nextTime = millis () + 500 ;

	while(1){
	  ///inivia un comando ogni 2 secondi
		//outF.open("dati.txt", ios::app);
		if (millis () > nextTime){
			terreno.onTimer();
			//cout << "Out: " << "F" << endl;
		  /*num_cicli++;
		  //printf ("\nOut: %3d: ", count) ;
		  fflush (stdout) ;
		  switch(STATO){
		  case 0:
		 	  CMD.sendCmd('D', 1);
		 	  STATO = 0;
			  cout << "Out: " << "D1 " << num_cicli <<endl;
			  outF << "Out: " << "D1 " << num_cicli <<endl;
		  break;

		  case 1:
		 	  CMD.sendCmd('D', 2);
		 	  STATO = 2;
			  cout << "Out: " << "D2 " << num_cicli <<endl;
			  outF << "Out: " << "D2 " << num_cicli <<endl;

		  break;

		  case 2:
		 	  CMD.sendCmd('D', 5);
		 	  STATO = 3;
			  cout << "Out: " << "D5 " << num_cicli << endl;
			  outF << "Out: " << "D5 " << num_cicli <<endl;
		  break;

		  case 3:
		 	  CMD.sendCmd('D', 3);
		 	  STATO = 4;
			  cout << "Out: " << "D3 " << num_cicli << endl;
			  outF << "Out: " << "D3 " << num_cicli <<endl;
		  break;

		  case 4:
		 	  CMD.sendCmd('D', 4);
		 	  STATO = 0;
			  cout << "Out: " << "D4 " << num_cicli << endl;
			  outF << "Out: " << "D4 " << num_cicli <<endl;
		  break;

		  case 5:
		 	  CMD.sendCmd('L');
		 	  STATO = 0;
			  cout << "Out: " << "L" << num_cicli << endl;
			  outF << "Out: " << "L" << num_cicli <<endl;
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
//		  serialPutchar (fd, '\r');*/
		  nextTime += 100;
		}

//		delay (3) ;
//		if (conteggio > 16){
//		  while (count = sc.readBuff(buff)){
//			cout << "ricevuto " << endl;
//			outF << "ricevuto " << endl;
////			//printf (" -> %3d", serialGetchar (fd)) ;
//			cout << "letti :" << count << "bytes" << endl;
//			outF << "letti :" << count << "bytes" << endl;
//			for (int i = 0 ; i < count; i++){
//				cout << "valore " << (int) buff[i] << endl;
//				outF << "valore " << (int) buff[i] << endl;
//			}
//		}
		/*if (CMD.receiveCmd()){
			/// il comando ricevuto e' valido e stampo i bytes

			cout << "ricezione ok" << endl;
			outF << "ricezione ok" << endl;


			if (CMD.rxBuff[0] < 6){
				/// ricevuto un sensore di distanza
/// scopi di debug
///				cout <<  (int) CMD.rxBuff[1] << endl <<  (int) CMD.rxBuff[2] << endl;
				int misura;
				misura = (CMD.rxBuff[1] & 0xFF) << 8;
				//misura <<= 8;
				misura += (CMD.rxBuff[2] & 0xFF);
				cout << "dist " << (int) CMD.rxBuff[0] << ": " << misura << endl;
				cout <<endl;
				/// scrive su file
				outF << "dist " << (int) CMD.rxBuff[0] << ": " << misura << endl;
				outF <<endl;
			}
			else{
				for (int i = 0; i < 5;i++){
					cout << "valore " << (int) CMD.rxBuff[i] << endl;
					outF << "valore " << (int) CMD.rxBuff[i] << endl;
				}
				cout << endl;
				outF << endl;
			}

		}*/
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
