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
	int direzione[2];
	int dirGiroscopio[2];
	bool rotazione;
	campoGara();
	virtual ~campoGara();
	void onTimer();
	int ricercaBinariaNonRicorsiva(int lista[8][2], int n, int x);
	int interpolazione(int valore);
	///proprietà
	vector<cellaBase> campo;
	SerialComm sc;
	TRcmd CMD;
};

#endif /* CAMPOGARA_H_ */
