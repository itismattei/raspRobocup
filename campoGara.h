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
};

#endif /* CAMPOGARA_H_ */
