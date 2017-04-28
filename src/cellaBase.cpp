/*
 * cellaBase.cpp
 *
 *  Created on: 27/apr/2017
 *      Author: tps8
 */

#include "cellaBase.h"

cellaBase::cellaBase(int riga, int colonna) {
	// TODO Auto-generated constructor stub
	e[0] = riga;
	e[1] = colonna;
	piastrellaInterdetta = false;
	for (int i = 0; i < 4; i++){
		muro[i] = 0;
		calore[i] = 0;
	}
	
}

cellaBase::~cellaBase() {
	// TODO Auto-generated destructor stub
}

