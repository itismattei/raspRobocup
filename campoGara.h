/*
 * campoGara.h
 *
 *  Created on: 27/apr/2017
 *      Author: tps8
 */

#ifndef CAMPOGARA_H_
#define CAMPOGARA_H_

#include "cellaBase.h"
#include <vector>
#include "SerialComm.h"
#include "TRcmd.h"

using namespace std;

class campoGara {
public:
	int posizione[2]; //in millimetri
	double direzione[2];
	campoGara();
	virtual ~campoGara();
	void onTimer();
	///proprietà
	vector<cellaBase> campo;
	SerialComm sc;
	TRcmd CMD;
};

#endif /* CAMPOGARA_H_ */
