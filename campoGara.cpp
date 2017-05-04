/*
 * campoGara.cpp
 *
 *  Created on: 27/apr/2017
 *      Author: tps8
 */

#include "campoGara.h"
#include <stdint.h>
#include <iostream>
using namespace std;

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
	cout << "tentativo connessione \n";
	CMD.connect(&sc);
	if (CMD.isOK==true)
		cout << "cnnesso !\n";
	if (CMD.isOK == false)
		cout << "nonconnesso\n";
}

campoGara::~campoGara() {
	// TODO Auto-generated destructor stub

}

void campoGara::onTimer(){
	//Fase di analisi

	//Lettura sensori
	//Lettura dei 5 sensori di distanza
	int distanza[5];
	int angolo, colore, temperatura, velocita = 0;
	int contatore;
	cout << "giro sui sensori" << endl;
	for (int i=0;i<5;i++){
		contatore = 0;
		CMD.sendCmd('D', i+1);
		cout << "sensore n. " << i+1 << endl;

		while(CMD.receiveCmd() == 0 && contatore < 100000) contatore ++;
		//if (CMD.receiveCmd()){
			{cout << "ricevuto \n";
			if (CMD.rxBuff[0] < 6){
				cout << "contatore " <<  contatore << endl;
				distanza[i] = (CMD.rxBuff[1] & 0xFF) << 8;
				distanza[i] += (CMD.rxBuff[2] & 0xFF);
				cout << "distanza " << i+1 << ": " << distanza[i] << endl;
			}
		}
	}
	//Lettura giroscopio
	CMD.sendCmd('D', 6);
	cout << "giroscopio : ";
	contatore = 0;
	uint16_t ang;
	while(CMD.receiveCmd() == 0 && contatore < 100000) contatore ++;
	//if(CMD.receiveCmd()){
	if (contatore < 100000){
		ang = (CMD.rxBuff[1] & 0xFF) << 8;
		ang += (CMD.rxBuff[2] & 0xFF);
		/// ATTENZIONE ALLA CONVERSIONE DA UNSIGNED AD INT!!!!
		angolo = (int16_t)ang;
		cout << angolo << "°" << endl;
	} else{
		angolo = -1;
	}
	//Lettura colore mattonella
	CMD.sendCmd('D', 7);
	cout << "colore paistrella :";
	contatore = 0;
	while(CMD.receiveCmd() == 0 && contatore < 100000) contatore ++;
	if(contatore < 100000){
		colore = (CMD.rxBuff[1] & 0xFF) << 8;
		colore += (CMD.rxBuff[2] & 0xFF);
		cout << colore << endl;
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
	//Lettura velocità
	CMD.sendCmd('D', 9);
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
				if (distanza[i] < 25){
					posMuro[0] = posizione[0] + (distanza[i] * direzione[0]);
					posMuro[1] = posizione[1] + (distanza[i] * direzione[1]);
					cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
					int distX = posMuro[0] % 300;
					int distY = posMuro[1] % 300;
				}
				break;
			//Sensore SX
			case 1:
				if (distanza[i] < 25){
					posMuro[0] = posizione[0] + (distanza[i] * -direzione[1]);	
					posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
					cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
					int distX = posMuro[0] % 300;
					int distY = posMuro[1] % 300;
				}
				break;
			//Sensore SX
			case 2:
				if (distanza[i] < 25){
					posMuro[0] = posizione[0] + (distanza[i] * -direzione[1]);	
					posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
					cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
					int distX = posMuro[0] % 300;
					int distY = posMuro[1] % 300;
				}
				break;
			//Sensore DX
			case 3:
				if (distanza[i] < 25){
					posMuro[0] = posizione[0] + (distanza[i] * direzione[1]);	
					posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
					cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
					int distX = posMuro[0] % 300;
					int distY = posMuro[1] % 300;
				}
				break;
			//Sensore DX
			case 4:
				if (distanza[i] < 25){
					posMuro[0] = posizione[0] + (distanza[i] * direzione[1]);	
					posMuro[1] = posizione[1] + (distanza[i] * direzione[0]);
					cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
					int distX = posMuro[0] % 300;
					int distY = posMuro[1] % 300;
				}
				break;
			//giroscopio
			case 5:
				if (angolo != -1){
					//TODO
				}
				break;
			//velocità
			case 6:
				if (velocita != -1){
					posizione[0] += velocita*0.1*direzione[0]; //Considero che onTimer venga chiamato 10 volte al secondo;
					posizione[1] += velocita*0.1*direzione[1];
				}
				break;
			//temperatura
			case 7:
				if(temperatura != -1){
					if (temperatura > 30){ //Temperatura minima messa a caso.... Da decidere
						cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60; //Considero che il sensore è sempre rivolto in avanti
						campo[cella].muro[0] = 1;
					}
				}
				break;
			//colore
			case 8:
				if (colore != -1){
					if (colore < 50){ //Anche qui valore messo a caso....
						cella = (int)posMuro[0] / 300 + (int)posMuro[1] / 300*60;
						campo[cella].piastrellaInterdetta = true;
					}
				}
				break;
			default:
				break;
		}
	}
}

