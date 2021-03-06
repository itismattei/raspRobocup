/*
 * TRcmd.h
 *
 *  Created on: 20/apr/2017
 *      Author: massimo
 */

#ifndef TRCMD_H_
#define TRCMD_H_

#include "SerialComm.h"

/*
 *
F - avanti
B - indietro (retromarcia)
I - indietro (180 gradi)
S - stop
R - gira a destra (+90gradi)
L - gira a sinistra (-90gradi)
G - direzione in gradi assoluta (relativa all'angolo di inizio percorso)
D - richiesta di informazione di un determinato sensore

 *
 * */


///
/// classe che invia e riceve i comandi alla scheda del robot
class TRcmd {
public:
	TRcmd();
	virtual ~TRcmd();


	void connect(SerialComm *p);
	void sendCmd(char);
	void sendCmd(char, int);

	int receiveCmd();

	/// buffer di trasmissione del comando
	char txBuff[16];
	/// buffer di ricezione del comando
	char rxBuff[128];
	///
	char CHS;

	SerialComm *scPtr;
	int ID;
	bool isOK;
	static int numSer;
};

#endif /* TRCMD_H_ */
