/*
 * campoGara.cpp
 *
 *  Created on: 27/apr/2017
 *      Author: tps8
 */

#include "campoGara.h"

campoGara::campoGara() {
	// TODO Auto-generated constructor stub
	for (int i=0;i<60;i++){
		for(int j=0;j<60;j++){
			campo.push_back(cellaBase(i, j));
		}
	} 
	posizione[0] = 9000;  //X
	posizione[1] = -9000; //Y
	direzione[0] = 0;
	direzione[1] = 1;
}

campoGara::~campoGara() {
	// TODO Auto-generated destructor stub

}

void campoGara::onTimer(){

}

