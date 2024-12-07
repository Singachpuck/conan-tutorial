#include <iostream>
// #include <linkholder/core.h>

#include "managers/OneStepManager.h"
#include "exceptions/handlers/DefaultExceptionHandler.h"
#include "StateMachine.h"
#include "context.h"

int main() {
	auto um = std::make_shared<UrlManager>("Name");
	auto sm = std::make_shared<StateMachine>();
	auto ex = std::make_shared<DefaultExceptionHandler>();
    auto context = context::ContextFactory::initSharedContext(um);

	OneStepManager manager(sm, ex);

	manager.launch();

	// sm.change(MAIN);

	// sm.next();

	return 0;
}