/*
 * SerialComm.h
 *
 *  Created on: 18/apr/2017
 *      Author: massimo
 */

#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_

class SerialComm {
public:
	SerialComm();
	virtual ~SerialComm();

	int openSer();
	void serClose();
	int writeBuff(char *, int n);
	int sendBuff(int);
	int readBuff(char *);

	int  mBaud;
	int  mfd;
	int  ind;
	char mBuff[128];
};

#endif /* SERIALCOMM_H_ */
