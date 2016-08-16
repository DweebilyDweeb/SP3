#include "GenerateRange.h"

/****************************************************************************/
/*!

\brief
Generates a random unsigned integer.

\param from
The minimum possible value of the unsigned integer.

\param to
The maximum possible value of the unsigned integer.

*/
/****************************************************************************/
unsigned int GenerateRange(unsigned int from, unsigned int to) {

	return (rand() % (to - from)) + from;

}

/****************************************************************************/
/*!

\brief
Generates a random integer.

\param from
The minimum possible value of the integer.

\param to
The maximum possible value of the integer.

*/
/****************************************************************************/
int GenerateRange(int from, int to) {

	return (rand() % (to - from)) + from;

}

/****************************************************************************/
/*!

\brief
Generates a random float.

\param from
The minimum possible value of the float.

\param to
The maximum possible value of the float.

*/
/****************************************************************************/
float GenerateRange(float from, float to) {

	return (static_cast<float>(rand())/(static_cast <float>(RAND_MAX/(to - from))) + from);

}