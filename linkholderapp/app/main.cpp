#include <iostream>
// #include <linkholder/core.h>

#include "StateMachine.h"

int main() {
	StateMachine sm;

	sm.change(MAIN);

	sm.next();

	return 0;
}