/*
 * campoGara.cpp
 *
 *  Created on: 27/apr/2017
 *      Author: tps8
 */

#include "campoGara.h"

extern "C" {	
	int funzione();
	int millis();
	int delay(int);
}

campoGara::campoGara() {
	// TODO Auto-generated constructor stub
	for (int i=0;i<60;i++){
		for(int j=0;j<60;j++){
			campo.push_back(cellaBase(i, j));
		}
	}
	posizione[0] = 9150;  //X
	posizione[1] = -9150; //Y
	direzione[0] = 0;
	direzione[1] = 1;
	rotazione = false;
	dirGiroscopio[0] = 0;
	dirGiroscopio[1] = 0;
	count = 0;
	impulsi = 0;
	start = false;
	CMD.connect(&sc);
	if (CMD.isOK == true){
		cout << "connesso\n";
	} else if(CMD.isOK == false){
		cout << "Non connesso\n";
	}
}

campoGara::~campoGara() {
	// TODO Auto-generated destructor stub

}

void campoGara::onTimer(){
	volatile int y = 0;
	if (!start){
		cout << "Inviato comando di avvio" << endl;
		CMD.sendCmd('S');
		if (CMD.receiveCmd()){
			start = true;
			cout << "Connessione avvenuta" << endl;
			//CMD.sendCmd('F');
			for(int x=0;x<10000;x++){

			}
		}
	}else{
		if (!rotazione){
			int distanza[5] = {-1};
			int angolo, colore, temperatura, velocita = -1;
			
			for (int i = 5;i > 0;i--){
				y = 0;
				CMD.sendCmd('D', i);
				cout << "trasmesso richiesta lettura D" << i << endl;
//				while(y<100000){
//					y++;
//				}
				
				while (CMD.receiveCmd() == 0 && y < 1000000)
					y += 1;
				//cout << "numero cicli while: " << y << endl;
				if (y < 100000){
					if (CMD.rxBuff[0] < 6){
						distanza[i-1] = (CMD.rxBuff[1] & 0xFF) << 8;
						distanza[i-1] += (CMD.rxBuff[2] & 0xFF);
						cout << "Sensore D" << i << " " << distanza[i-1] << endl;
					}
				} else{
					distanza[i-1] = -1;
					cout << "timeout" << endl;
				}
			}
			//Lettura giroscopio
			CMD.sendCmd('D', 6);
			uint16_t ang; 
			y = 0;
			while (CMD.receiveCmd() == 0 && y < 100000)
					y += 1;
			if(y < 100000){
				ang = (CMD.rxBuff[1] & 0xFF) << 8;
				ang += (CMD.rxBuff[2] & 0xFF);
				angolo = (int16_t)ang;
				cout << "Sensore D6: " << angolo << endl;
			} else{
				angolo = -1;
			}
			//Lettura colore mattonella
			/*CMD.sendCmd('D', 7);
			y = 0;
			while (CMD.receiveCmd() == 0 && y < 1000)
					y += 1;
			if(y < 1000){
				colore = (CMD.rxBuff[1] & 0xFF) << 8;
				colore += (CMD.rxBuff[2] & 0xFF);
				cout << "Sensore D7: " << colore << endl;
			} else{
				colore = -1;
			}
			//Lettura temperatura
			CMD.sendCmd('D', 8);
			y = 0;
			while (CMD.receiveCmd() == 0 && y < 1000)
					y += 1;
			if(y < 1000){
				temperatura = (CMD.rxBuff[1] & 0xFF) << 8;
				temperatura += (CMD.rxBuff[2] & 0xFF);
				cout << "Sensore D8: " << temperatura << endl;
			} else{
				temperatura = -1;
			}*/
			//Lettura velocitÃ 
			CMD.sendCmd('D', 10);
			y = 0;
			while (CMD.receiveCmd() == 0 && y < 100000)
					y += 1;
			if(y < 100000){
				velocita = (CMD.rxBuff[1] & 0xFF) << 8;
				velocita += (CMD.rxBuff[2] & 0xFF);
				cout << "Sensore D10: " << velocita << endl;
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
							posMuro[0] = posizione[0] + (distanza[i] * direzione[0])*100;
							posMuro[1] = posizione[1] + (distanza[i] * direzione[1])*100;
							cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
							if (direzione[0] == 0){
								int distX = posMuro[0] % 300;
								if (direzione[1] == 1){
									if (distX > 200){
										inserisciMuro(cella, 0);
									} else if(distX < 100){
										inserisciMuro(cella, 2);
									}
								} else{
									if (distX > 200){
										inserisciMuro(cella, 2);
									} else if(distX < 100){
										inserisciMuro(cella, 0);
									}
								}
							} else if(direzione[0] == 1){
								int distY = posMuro[1] % 300;
								if (distY > 200){
									inserisciMuro(cella, 1);
								} else if(distY < 100){
									inserisciMuro(cella, 3);
								}
							} else{
								int distY = posMuro[1] % 300;
								if (distY > 200){
									inserisciMuro(cella, 3);
								} else if(distY < 100){
									inserisciMuro(cella, 1);
								}
							}
						}
						break;
					//Sensore SX
					case 1:
						if (distanza[i] < 1500 && distanza[i] != -1){
							//posMuro[0] = posizione[0] + (distanza[i] * -direzione[1]);	
							//posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
							cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60;
							if (direzione[0] == 0){
								if (direzione[1] == 1){
									inserisciMuro(cella, 3);
								} else{
									inserisciMuro(cella, 1);
								}
							} else if(direzione[0] == 1){
								inserisciMuro(cella, 0);
							} else{
								inserisciMuro(cella, 2);
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
							cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60;
							if (direzione[0] == 0){
								if (direzione[1] == 1){
									inserisciMuro(cella, 3);
								} else{
									inserisciMuro(cella, 1);
								}
							} else if(direzione[0] == 1){
								inserisciMuro(cella, 0);
							} else{
								inserisciMuro(cella, 2);
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
							cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60;
							if (direzione[0] == 0){
								if (direzione[1] == 1){
									inserisciMuro(cella, 1);
								} else{
									inserisciMuro(cella, 3);
								}
							} else if(direzione[0] == 1){
								inserisciMuro(cella, 2);
							} else{
								inserisciMuro(cella, 0);
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
							cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60;
							if (direzione[0] == 0){
								if (direzione[1] == 1){
									inserisciMuro(cella, 1);
								} else{
									inserisciMuro(cella, 3);
								}
							} else if(direzione[0] == 1){
								inserisciMuro(cella, 2);
							} else{
								inserisciMuro(cella, 0);
							}
							
							//int distX = posMuro[0] % 300;
							//int distY = posMuro[1] % 300;
						}
						break;
					//giroscopio
					case 5:
						if (angolo != -1){
							dirGiroscopio[0] = angolo;
						}
						break;
					//velocitÃ 
					case 6:
						if (velocita != -1){
							int imp = velocita - impulsi;
							int vel = imp/40*10;
							impulsi = velocita;
							posizione[0] += vel*0.2*direzione[0]; //Considero che onTimer venga chiamato 10 volte al secondo;
							posizione[1] += vel*0.2*direzione[1];
						}
						break;
					//temperatura
					case 7:
						if(temperatura != -1){
							if (temperatura > 30){ //Temperatura minima messa a caso.... Da decidere
								cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60; //Considero che il sensore Ã¨ sempre rivolto in avanti
								campo[cella].calore[3] = 1;
								CMD.sendCmd('P');
							}
						}
						break;
					//colore
					case 8:
						if (colore != -1){
							if (colore < 50){ //Anche qui valore messo a caso....
								cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60;
								campo[cella].piastrellaInterdetta = true;
							}
						}
						break;
					default:
						break;
				}
			}
			cella = (int)posizione[0] / 300 + (int)posizione[1] / 300*60;
			/*if (direzione[0] == 0){
				if (direzione[1] == 1){
					if (campo[cella].muro[0] == 0){
						CMD.sendCmd('F');
					} else if(campo[cella].muro[1] == 0){
						CMD.sendCmd('R');
						rotazione = true;
						dirGiroscopio[1] = 90;
					} else if(campo[cella].muro[3] == 0){
						CMD.sendCmd('L');
						rotazione = true;
						dirGiroscopio[1] = -90;
					} else{
						CMD.sendCmd('I');
						rotazione = true;
						dirGiroscopio[1] = 180;
					}
				} else{
					if (campo[cella].muro[2] == 0){
						CMD.sendCmd('F');
					} else if(campo[cella].muro[3] == 0){
						CMD.sendCmd('R');
						rotazione = true;
						dirGiroscopio[1] = 90;
					} else if(campo[cella].muro[1] == 0){
						CMD.sendCmd('L');
						rotazione = true;
						dirGiroscopio[1] = -90;
					} else{
						CMD.sendCmd('I');
						rotazione = true;
						dirGiroscopio[1] = 180;
					}
				}
			} else if(direzione[0] == 1){
				if (campo[cella].muro[1] == 0){
					CMD.sendCmd('F');
				} else if(campo[cella].muro[2] == 0){
					CMD.sendCmd('R');
					rotazione = true;
					dirGiroscopio[1] = 90;
				} else if(campo[cella].muro[0] == 0){
					CMD.sendCmd('L');
					rotazione = true;
					dirGiroscopio[1] = -90;
				} else{
					CMD.sendCmd('I');
					rotazione = true;
					dirGiroscopio[1] = 180;
				}
			} else{
				if (campo[cella].muro[3] == 0){
					CMD.sendCmd('F');
				} else if(campo[cella].muro[0] == 0){
					CMD.sendCmd('R');
					rotazione = true;
					dirGiroscopio[1] = 90;
				} else if(campo[cella].muro[2] == 0){
					CMD.sendCmd('L');
					rotazione = true;
					dirGiroscopio[1] = -90;
				} else{
					CMD.sendCmd('I');
					rotazione = true;
					dirGiroscopio[1] = 180;
				}
		}*/
	//Robot in rotazione
		CMD.sendCmd('F');
	} else{
		count++;
		if (count > 100){
			CMD.sendCmd('B');
			rotazione = false;
			count = 0;
		} else{
			CMD.sendCmd('D', 6);
			int dir = 0;
			if(CMD.receiveCmd()){
				dir = (CMD.rxBuff[1] & 0xFF) << 8;
				dir += (CMD.rxBuff[2] & 0xFF);
				if ((dirGiroscopio[0]+ abs(dirGiroscopio[1]) < (dir + 5)) && (dirGiroscopio[0]+ abs(dirGiroscopio[1]) > (dir - 5))){ //Condizione di avvenuta rotazione
					count = 0;
					rotazione = false;
					//Rotazione di 180°
					if (dirGiroscopio[1] == 180){
						direzione[0] = -direzione[0];
						direzione[1] = -direzione[1];
					//Rotazione a destra
					} else if(dirGiroscopio[1] == 90){
						if (direzione[0] = 0){
							direzione[0] = direzione[1];
							direzione[1] = 0;
						} else{
							direzione[1] = -direzione[0];
							direzione[0] = 0;
						}
					//Rotazione a sinistra
					} else{
						if (direzione[0] = 0){
							direzione[0] = -direzione[1];
							direzione[1] = 0;
						} else{
							direzione[1] = direzione[0];
							direzione[0] = 0;
						}
					}
				}
			}
		}
	}
	}
}

int campoGara::ricercaBinariaNonRicorsiva(int lista[8][2], int n, int x){
	int start,end,m;
	start = 0;
	end = n-1;
	while(start<=end){
		m = (start+end)/2;
		if(lista[m][1]<=x && lista[m+1][1]>=x){
			return m; // valore x trovato alla posizione m
		}
		if(lista[m][1]<x){
			start = m+1;
		} else{
			end = m-1;
		}
	}
	return -1;
}

int campoGara::interpolazione(int valore){
	int tabella[9][2] = {{60, 1550}, {50, 1800}, {45, 2200}, {40, 2400}, {30, 2700}, {25, 2850}, {20, 3240}, {15, 3690}};
	int r = ricercaBinariaNonRicorsiva(tabella, 8, valore);
	int Ya = tabella[r][0];
	int Xa = tabella[r][1];
	int Yb = tabella[r+1][0];
	int Xb = tabella[r+1][1];
	float y = (valore-Xa)*((float)(Yb-Ya)/(Xb-Xa))+Ya;
	return (int)y;
}

void campoGara::inserisciMuro(int cella, int muro){
	campo[cella].muro[muro] = 1;
	if (muro = 0){
		if (cella > 59){
			campo[cella-60].muro[2] = 1;
		}
	} else if(muro = 1){
		if (cella % 59 != 0){
			campo[cella++].muro[3] = 1;
		}
	} else if(muro = 2){
		if (cella < 3539){
			campo[cella+60].muro[0] = 1;
		}
	} else{
		if (cella % 60 != 0){
			campo[cella--].muro[1] = 1;
		}
	}
}

