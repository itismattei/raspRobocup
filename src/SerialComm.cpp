/*
 * SerialComm.cpp
 *
 *  Created on: 18/apr/2017
 *      Author: massimo
 */


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>

using namespace std;

//#include <wiringPi.h>
#include <wiringSerial.h>

#include "SerialComm.h"

SerialComm::SerialComm() {
	// TODO Auto-generated constructor stub

	mBaud = 115200;
	ind = 0;
	mfd = -1;
}

SerialComm::~SerialComm() {
	// TODO Auto-generated destructor stub
	serClose();
}

///
/// apre la seriale: ttyAM0
int SerialComm::openSer(){

	if ((mfd = serialOpen ("/dev/ttyAMA0", mBaud)) < 0){
		printf("Unable to open serial device. \n");
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		mfd = -1 ;
	}

	return mfd;
}

///
///
/// scrive N byte sul canale seriale
int SerialComm::writeBuff(char * buff, int num){

	int fd;
	if (num > 127){
		/// limita il buffer a 127 caratteri
		mBuff[127] = '\0';
		num = 127;
	}

	strncpy(mBuff, buff, num);
	mBuff[num] = '\0';
//	cout << "copiati " << num << "bytes" << endl;
//	cout << mBuff[0] << endl;
//	cout << mBuff[3] << endl;
//	cout << buff[0] << endl;
//	cout << buff[3] << endl;
	fd = sendBuff(num);
	return num;
}


///
/// legge N byte dal canale e restituisce il numero di bytes effettivamente letti
int SerialComm::readBuff(char *buff){
	ind = 0;
	/// interroga la seriale sulla disponibilita' di bytes
	while (serialDataAvail (mfd)){
		//printf("ricevuto \n");
		//printf (" -> %3d", serialGetchar (fd)) ;
		mBuff[ind] = serialGetchar(mfd);
		//printf("%c", mBuff[ind]);
		fflush (stdout) ;
		ind++;
		/// modulo 128
		ind &= 0x7F;
		if (ind == 0){
			/// nel caso in cui raggiungesse la fine del buffer verra' troncato
			/// l'ultimo byte
			mBuff[127] = '\0';
			strncpy(buff, mBuff, 127);
		}
		else{
			mBuff[ind] = '\0';
			/// inserita questa,perche' se una lettura del sensore ha un byte a 0,
			/// la strcpy si arresta nella copia ed il dato inviato e' sbagliato
			for (int i = 0; i < ind; i++)
				buff[i] = mBuff[i];
			//strcpy(buff, mBuff);
		}
	}
	return ind;
}

///
///
/// invia sul buffer tx della scheda
int SerialComm::sendBuff(int n){
	if (n == 1)
		serialPutchar (mfd, mBuff[0]);
	else
		if(n > 1){
			serialPuts (mfd, mBuff);
//			cout << "inviati " << n << "bytes" << endl;
//			cout << mBuff[0] << endl;
//			cout << "CHK " << (int) mBuff[2] << endl;
//			cout << mBuff[3] << endl;
		}
		else return -1;
	return 0;
}


///
///
/// chiude la seriale
void SerialComm::serClose(){

	if(mfd > 0){
		serialClose(mfd);
		printf("Seriale chiusa\n");
	}
	else
		printf("Seriale gia' chiusa.\n");
	mfd = -1;
}
