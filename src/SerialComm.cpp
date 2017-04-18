/*
 * SerialComm.cpp
 *
 *  Created on: 18/apr/2017
 *      Author: massimo
 */


#include <stdio.h>
#include <string.h>
#include <errno.h>

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
	strncpy(buff, mBuff, num);
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
	        printf("%c", mBuff[ind]);
	        fflush (stdout) ;
	        ind++;
	        /// modulo 128
	        ind &= 0x7F;
	        //printf("\n");
	      }
	strncpy(mBuff, buff, ind - 1);
	return ind;
}

///
///
/// invia sul buffer tx della scheda
int SerialComm::sendBuff(int n){

	if (n == 1)
		serialPutchar (mfd, mBuff[0]);
	else
		if(n > 1)
			serialPuts (mfd, mBuff);
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
