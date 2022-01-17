#include "directions.h"
#include "random.h"

// Count the number of directions in a list of Directions.
int countConnections(Connections c) {
	return c.up + c.right + c.left + c.down;
}

int getRandomSide(Connections c) {
	int cFreeSides = countConnections(c);
	if (cFreeSides == 0) return -1; 

	std::vector<int> freeSides;
	if (c.up) freeSides.push_back(UP);
	if (c.right) freeSides.push_back(RIGHT);
	if (c.down) freeSides.push_back(DOWN);
	if (c.left) freeSides.push_back(LEFT);
	return freeSides[randint(0, cFreeSides - 1)()];
}