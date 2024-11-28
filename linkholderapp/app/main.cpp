#include <iostream>
// #include <linkholder/core.h>

#include "managers/OneStepManager.h"
#include "exceptions/handlers/DefaultExceptionHandler.h"
#include "StateMachine.h"

int main() {
	auto um = std::make_shared<UrlManager>("Name");
	auto sm = std::make_shared<StateMachine>();
	auto ex = std::make_shared<DefaultExceptionHandler>();
	OneStepManager manager(um, sm, ex);

	manager.launch();

	// sm.change(MAIN);

	// sm.next();

	return 0;
}