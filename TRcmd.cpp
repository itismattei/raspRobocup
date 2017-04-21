/*
 * TRcmd.cpp
 *
 *  Created on: 20/apr/2017
 *      Author: massimo
 */

#include <iostream>
using namespace std;
#include "TRcmd.h"
#include <stdlib.h>

int TRcmd::numSer = 0;

TRcmd::TRcmd() {
	// TODO Auto-generated constructor stub
	scPtr = NULL;
	CHS = 0xA9;
	if (numSer == 0){
		numSer++;
		/// si ricorda che puo' funzionare
		ID = 1;
	}
	else
		ID = 0;
	isOK = false;
}

TRcmd::~TRcmd() {
	// TODO Auto-generated destructor stub
}


/// invio del comando con solo carattere
void TRcmd::sendCmd(char c){

	int def_ = 0;
	/// per questo ripo di comandi il byte n. 1 e' sempre pari a '0'
	txBuff[1] = '0';
	//CHS ^= '0';
	/// terminatore di stringa
	txBuff[4] = '\0';

	switch(c){
	case 'F':
		txBuff[0] = 'F';
		txBuff[2] = 'F' ^ CHS ^ '0';
		txBuff[3] = '*';
	break;

	case 'B':
		txBuff[0] = 'B';
		txBuff[2] = 'B' ^ CHS ^ '0';
		txBuff[3] = '*';
	break;

	case 'I':
		txBuff[0] = 'I';
		txBuff[2] = 'I' ^ CHS ^ '0';
		txBuff[3] = '*';
	break;

	case 'S':
		txBuff[0] = 'S';
		txBuff[2] = 'S' ^ CHS ^ '3';
		txBuff[3] = '*';
	break;

	case 'R':
		txBuff[0] = 'R';
		txBuff[2] = 'R' ^ CHS ^ '0';
		txBuff[3] = '*';
	break;

	case 'L':
		txBuff[0] = 'L';
		txBuff[2] = 'L' ^ CHS ^ '0';
		txBuff[3] = '*';
	break;

	default:
		cout << "comando non valido. " << endl;
		def_ = 1;
	break;
	}

	if (scPtr != NULL && def_ == 0){
//		cout << "scritto txbuff" << endl;
//		cout << txBuff[0] << endl;
//		cout << txBuff[3] << endl;
		scPtr->writeBuff(txBuff, 4);
	}
}

///
/// comando da 2 caratteri
void TRcmd::sendCmd(char c, int num){

	int def_ = 0;

	switch(c){
		case 'G':
			txBuff[0] = 'G';
			txBuff[1] = num & 0xFF;
			txBuff[2] = 'G' ^ CHS ^ txBuff[1];
			txBuff[3] = '*';

		break;

		case 'D':
			txBuff[0] = 'D';
			txBuff[1] = num & 0xFF;
			txBuff[2] = 'D' ^ CHS ^ txBuff[1];
			txBuff[3] = '*';
		break;

		default:
			def_ = 1;
		break;

	}

	if (scPtr != NULL && def_ == 0){
		scPtr->writeBuff(txBuff, 4);
	}
}

///
/// si connette alla seriale
void TRcmd::connect(SerialComm * p){

	if (ID == 0)
		/// non puo' avere la seriale
		return;
	if (p != NULL){
		scPtr = p;
		/// apre la seriale
		scPtr->openSer();
		if (scPtr->mfd != -1)
			isOK = true;
		else
			isOK = false;
	}
}