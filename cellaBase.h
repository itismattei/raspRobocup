/*
 * cellaBase.h
 *
 *  Created on: 27/apr/2017
 *      Author: tps8
 */

#ifndef CELLABASE_H_
#define CELLABASE_H_

class cellaBase {
public:
	cellaBase(int riga, int colonna);
	virtual ~cellaBase();
	/// proprieta'
	/// coordinate rispetto alla base assoluta
	int e[2];
	///pos del muro rispetto alle coordinate assolute
	/*     0
	*    ______
	*	|      |
	*  3|      | 1
	*	|______|
	*		2
	*/
	bool muro[4];
	bool calore[4];
	bool piastrellaInterdetta;

};

#endif /* CELLABASE_H_ */
