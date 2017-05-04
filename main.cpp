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

//	SerialComm sc;
//	TRcmd CMD;
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
	//CMD.connect(&sc);
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
			//terreno.onTimer();
			//cout << "Out: " << "F" << endl;
		//  num_cicli++;
		  //printf ("\nOut: %3d: ", count) ;
		  fflush (stdout) ;
		 /* switch(STATO){
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

		  }*/
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
		  nextTime += 200;
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


/// 
/// programma principale
///

/*void onTimer(){
	volatile int y = 0;
	if (!terreno.start){
		CMD.sendCmd('S');
		if (CMD.receiveCmd()){
			terreno.start = true;
			cout << "OK" << endl;
		}
		cout << "Test Comunicazione!" << endl;
	}else{
		if (!terreno.rotazione){
			int distanza[5];
			int angolo, colore, temperatura, velocita = 0;
			for (int i = 0;i < 1;i++){
				CMD.sendCmd('D', 5);
				cout << "trasmesso richeista lettura D"<< i+1 << endl;
//				while(y<100000){
//					y++;
//				}
				
				while (CMD.receiveCmd() == 0 && y < 1000000)
					y += 1;
				
				if (y < 100000){
					if (CMD.rxBuff[0] < 6){
						distanza[i] = (CMD.rxBuff[1] & 0xFF) << 8;
						distanza[i] += (CMD.rxBuff[2] & 0xFF);
						cout << "Sensore D" << i+1 << distanza[i] << endl;
					}
				} else{
					distanza[i] = -1;
					cout << "timeout" << endl;
				}
			}
			//Lettura giroscopio
			CMD.sendCmd('D', 6);
			if(CMD.receiveCmd()){
				angolo = (CMD.rxBuff[1] & 0xFF) << 8;
				angolo += (CMD.rxBuff[2] & 0xFF);
			} else{
				angolo = -1;
			}
			//Lettura colore mattonella
			CMD.sendCmd('D', 7);
			if(CMD.receiveCmd()){
				colore = (CMD.rxBuff[1] & 0xFF) << 8;
				colore += (CMD.rxBuff[2] & 0xFF);
			} else{
				colore = -1;
			}
			//Lettura temperatura
			CMD.sendCmd('D', 8);
			if(CMD.receiveCmd()){
				temperatura = (CMD.rxBuff[1] & 0xFF) << 8;
				temperatura += (CMD.rxBuff[2] & 0xFF);
			} else{
				temperatura = -1;
			}
			//Lettura velocitÃ 
			CMD.sendCmd('D', 10);
			if(CMD.receiveCmd()){
				velocita = (CMD.rxBuff[1] & 0xFF) << 8;
				velocita += (CMD.rxBuff[2] & 0xFF);
			} else{
				velocita = -1;
			}
	
	
			//Analizzo i dati dei sensori
			int posMuro[2];
			int cella = 0;
			for (int i=0;i<9;i++){
				switch (i){
					//Sensore frontale
					case 0:
						if (distanza[i] < 4000 && distanza[i] > 1500 && distanza[i] != -1){
							posMuro[0] = terreno.posizione[0] + (distanza[i] * terreno.direzione[0])*100;
							posMuro[1] = terreno.posizione[1] + (distanza[i] * terreno.direzione[1])*100;
							cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
							if (terreno.direzione[0] = 0){
								int distX = posMuro[0] % 300;
								if (terreno.direzione[1] = 1){
									if (distX > 200){
										terreno.inserisciMuro(cella, 0);
									} else if(distX < 100){
										terreno.inserisciMuro(cella, 2);
									}
								} else{
									if (distX > 200){
										terreno.inserisciMuro(cella, 2);
									} else if(distX < 100){
										terreno.inserisciMuro(cella, 0);
									}
								}
							} else if(terreno.direzione[0] = 1){
								int distY = posMuro[1] % 300;
								if (distY > 200){
									terreno.inserisciMuro(cella, 1);
								} else if(distY < 100){
									terreno.inserisciMuro(cella, 3);
								}
							} else{
								int distY = posMuro[1] % 300;
								if (distY > 200){
									terreno.inserisciMuro(cella, 3);
								} else if(distY < 100){
									terreno.inserisciMuro(cella, 1);
								}
							}
						}
						break;
					//Sensore SX
					case 1:
						if (distanza[i] < 1500 && distanza[i] != -1){
							//posMuro[0] = posizione[0] + (distanza[i] * -direzione[1]);	
							//posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
							cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60;
							if (terreno.direzione[0] = 0){
								if (terreno.direzione[1] = 1){
									terreno.inserisciMuro(cella, 3);
								} else{
									terreno.inserisciMuro(cella, 1);
								}
							} else if(terreno.direzione[0] = 1){
								terreno.inserisciMuro(cella, 0);
							} else{
								terreno.inserisciMuro(cella, 2);
							}
							//int distX = posMuro[0] % 300;
							//int distY = posMuro[1] % 300;
						}
						break;
					//Sensore SX
					case 2:
						if (distanza[i] < 1500 && distanza[i] != -1){
							//posMuro[0] = posizione[0] + (distanza[i] * -direzione[1]);	
							//posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
							cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60;
							if (terreno.direzione[0] = 0){
								if (terreno.direzione[1] = 1){
									terreno.inserisciMuro(cella, 3);
								} else{
									terreno.inserisciMuro(cella, 1);
								}
							} else if(terreno.direzione[0] = 1){
								terreno.inserisciMuro(cella, 0);
							} else{
								terreno.inserisciMuro(cella, 2);
							}
							//int distX = posMuro[0] % 300;
							//int distY = posMuro[1] % 300;
						}
						break;
					//Sensore DX
					case 3:
						if (distanza[i] < 1500 && distanza[i] != -1){
							//posMuro[0] = posizione[0] + (distanza[i] * direzione[1]);	
							//posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
							cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60;
							if (terreno.direzione[0] = 0){
								if (terreno.direzione[1] = 1){
									terreno.inserisciMuro(cella, 1);
								} else{
									terreno.inserisciMuro(cella, 3);
								}
							} else if(terreno.direzione[0] = 1){
								terreno.inserisciMuro(cella, 2);
							} else{
								terreno.inserisciMuro(cella, 0);
							}
							
							//int distX = posMuro[0] % 300;
							//int distY = posMuro[1] % 300;
						}
						break;
					//Sensore DX
					case 4:
						if (distanza[i] < 1500 && distanza[i] != -1){
							//posMuro[0] = posizione[0] + (distanza[i] * direzione[1]);	
							//posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
							cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60;
							if (terreno.direzione[0] = 0){
								if (terreno.direzione[1] = 1){
									terreno.inserisciMuro(cella, 1);
								} else{
									terreno.inserisciMuro(cella, 3);
								}
							} else if(terreno.direzione[0] = 1){
								terreno.inserisciMuro(cella, 2);
							} else{
								terreno.inserisciMuro(cella, 0);
							}
							
							//int distX = posMuro[0] % 300;
							//int distY = posMuro[1] % 300;
						}
						break;
					//giroscopio
					case 5:
						if (angolo != -1){
							terreno.dirGiroscopio[0] = angolo;
						}
						break;
					//velocitÃ 
					case 6:
						if (velocita != -1){
							int imp = velocita - terreno.impulsi;
							int vel = imp/40*10;
							terreno.impulsi = velocita;
							terreno.posizione[0] += vel*0.2*terreno.direzione[0]; //Considero che onTimer venga chiamato 10 volte al secondo;
							terreno.posizione[1] += vel*0.2*terreno.direzione[1];
						}
						break;
					//temperatura
					case 7:
						if(temperatura != -1){
							if (temperatura > 30){ //Temperatura minima messa a caso.... Da decidere
								cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60; //Considero che il sensore Ã¨ sempre rivolto in avanti
								terreno.campo[cella].calore[3] = 1;
								CMD.sendCmd('P');
							}
						}
						break;
					//colore
					case 8:
						if (colore != -1){
							if (colore < 50){ //Anche qui valore messo a caso....
								cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60;
								terreno.campo[cella].piastrellaInterdetta = true;
							}
						}
						break;
					default:
						break;
				}
			}
			cella = (int)terreno.posizione[0] / 300 + (int)terreno.posizione[1] / 300*60;
			if (terreno.direzione[0] = 0){
				if (terreno.direzione[1] = 1){
					if (terreno.campo[cella].muro[0] = 0){
						CMD.sendCmd('F');
					} else if(terreno.campo[cella].muro[1] = 0){
						CMD.sendCmd('R');
						terreno.rotazione = true;
						terreno.dirGiroscopio[1] = 90;
					} else if(terreno.campo[cella].muro[3] = 0){
						CMD.sendCmd('L');
						terreno.rotazione = true;
						terreno.dirGiroscopio[1] = -90;
					} else{
						CMD.sendCmd('I');
						terreno.rotazione = true;
						terreno.dirGiroscopio[1] = 180;
					}
				} else{
					if (terreno.campo[cella].muro[2] = 0){
						CMD.sendCmd('F');
					} else if(terreno.campo[cella].muro[3] = 0){
						CMD.sendCmd('R');
						terreno.rotazione = true;
						terreno.dirGiroscopio[1] = 90;
					} else if(terreno.campo[cella].muro[1] = 0){
						CMD.sendCmd('L');
						terreno.rotazione = true;
						terreno.dirGiroscopio[1] = -90;
					} else{
						CMD.sendCmd('I');
						terreno.rotazione = true;
						terreno.dirGiroscopio[1] = 180;
					}
				}
			} else if(terreno.direzione[0] = 1){
				if (terreno.campo[cella].muro[1] = 0){
					CMD.sendCmd('F');
				} else if(terreno.campo[cella].muro[2] = 0){
					CMD.sendCmd('R');
					terreno.rotazione = true;
					terreno.dirGiroscopio[1] = 90;
				} else if(terreno.campo[cella].muro[0] = 0){
					CMD.sendCmd('L');
					terreno.rotazione = true;
					terreno.dirGiroscopio[1] = -90;
				} else{
					CMD.sendCmd('I');
					terreno.rotazione = true;
					terreno.dirGiroscopio[1] = 180;
				}
			} else{
				if (terreno.campo[cella].muro[3] = 0){
					CMD.sendCmd('F');
				} else if(terreno.campo[cella].muro[0] = 0){
					CMD.sendCmd('R');
					terreno.rotazione = true;
					terreno.dirGiroscopio[1] = 90;
				} else if(terreno.campo[cella].muro[2] = 0){
					CMD.sendCmd('L');
					terreno.rotazione = true;
					terreno.dirGiroscopio[1] = -90;
				} else{
					CMD.sendCmd('I');
					terreno.rotazione = true;
					terreno.dirGiroscopio[1] = 180;
				}
		}
	//Robot in rotazione
	} else{
		terreno.count++;
		if (terreno.count > 100){
			CMD.sendCmd('B');
			terreno.rotazione = false;
			terreno.count = 0;
		} else{
			CMD.sendCmd('D', 6);
			int dir = 0;
			if(CMD.receiveCmd()){
				dir = (CMD.rxBuff[1] & 0xFF) << 8;
				dir += (CMD.rxBuff[2] & 0xFF);
				if ((terreno.dirGiroscopio[0]+ abs(terreno.dirGiroscopio[1]) < (dir + 5)) && (terreno.dirGiroscopio[0]+ abs(terreno.dirGiroscopio[1]) > (dir - 5))){ //Condizione di avvenuta rotazione
					terreno.count = 0;
					terreno.rotazione = false;
					//Rotazione di 180°
					if (terreno.dirGiroscopio[1] = 180){
						terreno.direzione[0] = -terreno.direzione[0];
						terreno.direzione[1] = -terreno.direzione[1];
					//Rotazione a destra
					} else if(terreno.dirGiroscopio[1] = 90){
						if (terreno.direzione[0] = 0){
							terreno.direzione[0] = terreno.direzione[1];
							terreno.direzione[1] = 0;
						} else{
							terreno.direzione[1] = -terreno.direzione[0];
							terreno.direzione[0] = 0;
						}
					//Rotazione a sinistra
					} else{
						if (terreno.direzione[0] = 0){
							terreno.direzione[0] = -terreno.direzione[1];
							terreno.direzione[1] = 0;
						} else{
							terreno.direzione[1] = terreno.direzione[0];
							terreno.direzione[0] = 0;
						}
					}
				}
			}
		}
	}
	}
}*/

/*int main(){
	//campoGara terreno;
	SerialComm sc;
	TRcmd CMD;
	CMD.connect(&sc);
	
	int count, conteggio = 0, STATO = 0, num_cicli = 0;
	//char CHK, FIX = 0xA9, buff[128];
	unsigned int nextTime;
	//int fd;
	//ofstream outF("dati.txt", ios::app);
	//outF << "Registrazione comunicazioni" << endl;
	//SerialComm sc;
	//TRcmd *CMD;
	//CMD->connect(&sc);
//	fd = sc.openSer();
//	printf("Num descrittore %d\n", fd);
//	if (fd < 0){
//		/// la seriale non e' presente o non ha risposto
//		exit(-1);
//	}
	/// campo di gara
	//terreno.timer();
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
//	bool start = false;




	while(1){
	  ///inivia un comando ogni 2 secondi
		//outF.open("dati.txt", ios::app);
		if (millis () > nextTime){
			//onTimer();
			//cout << "Out: " << "F" << endl;
		  num_cicli++;
//		  //printf ("\nOut: %3d: ", count) ;
//		  fflush (stdout) ;
		  switch(STATO){
		  case 0:
		 	  CMD.sendCmd('D', 1);
		 	  STATO = 1;
			  cout << "Out: " << "D1 " << num_cicli <<endl;
			  //outF << "Out: " << "D1 " << num_cicli <<endl;
		  break;

		  case 1:
		 	  CMD.sendCmd('D', 2);
		 	  STATO = 2;
			  cout << "Out: " << "D2 " << num_cicli <<endl;
			  //outF << "Out: " << "D2 " << num_cicli <<endl;

		  break;

		  case 2:
		 	  CMD.sendCmd('D', 5);
		 	  STATO = 3;
			  cout << "Out: " << "D5 " << num_cicli << endl;
			  //outF << "Out: " << "D5 " << num_cicli <<endl;
		  break;

		  case 3:
		 	  CMD.sendCmd('D', 3);
		 	  STATO = 4;
			  cout << "Out: " << "D3 " << num_cicli << endl;
			  //outF << "Out: " << "D3 " << num_cicli <<endl;
		  break;

		  case 4:
		 	  CMD.sendCmd('D', 4);
		 	  STATO = 0;
			  cout << "Out: " << "D4 " << num_cicli << endl;
			  //outF << "Out: " << "D4 " << num_cicli <<endl;
		  break;

		  case 5:
		 	  CMD.sendCmd('L');
		 	  STATO = 0;
			  cout << "Out: " << "L" << num_cicli << endl;
			  //outF << "Out: " << "L" << num_cicli <<endl;
		  break;

		  }
////		  CHK = 'D';
////		  CHK ^= 1;
////		  CHK ^= FIX;
////		  buff[0] = 'D';
////		  buff[1] = 1;
////		  buff[2] = CHK;
////		  buff[3] = '*';
////		  /// scrive i 4 bytes sulla seriale
////		  sc.writeBuff(buff, 4);
//
////		  serialPutchar (fd, count) ;
////		  serialPutchar (fd, '\n');
////		  serialPutchar (fd, '\r');
			  nextTime += 1000;
		}
//
////		delay (3) ;
////		if (conteggio > 16){
////		  while (count = sc.readBuff(buff)){
////			cout << "ricevuto " << endl;
////			outF << "ricevuto " << endl;
//////			//printf (" -> %3d", serialGetchar (fd)) ;
////			cout << "letti :" << count << "bytes" << endl;
////			outF << "letti :" << count << "bytes" << endl;
////			for (int i = 0 ; i < count; i++){
////				cout << "valore " << (int) buff[i] << endl;
////				outF << "valore " << (int) buff[i] << endl;
////			}
////		}
		if (CMD.receiveCmd()){
			/// il comando ricevuto e' valido e stampo i bytes

			cout << "ricezione ok" << endl;
//			outF << "ricezione ok" << endl;


			if (CMD.rxBuff[0] < 6){
				/// ricevuto un sensore di distanza
//// scopi di debug
/////				cout <<  (int) CMD.rxBuff[1] << endl <<  (int) CMD.rxBuff[2] << endl;
				int misura;
				misura = (CMD.rxBuff[1] & 0xFF) << 8;
				//misura <<= 8;
				misura += (CMD.rxBuff[2] & 0xFF);
				cout << "dist " << (int) CMD.rxBuff[0] << ": " << misura << endl;
//				cout <<endl;
//				/// scrive su file
//				outF << "dist " << (int) CMD.rxBuff[0] << ": " << misura << endl;
//				outF <<endl;
			}
			else{
				for (int i = 0; i < 5;i++){
					cout << "valore " << (int) CMD.rxBuff[i] << endl;
//					outF << "valore " << (int) CMD.rxBuff[i] << endl;
				}
//				cout << endl;
//				outF << endl;
			}
//
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

}*/


