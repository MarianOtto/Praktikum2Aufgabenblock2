/*
 * Tempolimit.h
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_
#include <math.h>

enum class Tempolimit
{
	Innerorts = 50,
	Landstrasse = 100,
	Autobahn = std::numeric_limits<int>::max()
};

#endif /* TEMPOLIMIT_H_ */
