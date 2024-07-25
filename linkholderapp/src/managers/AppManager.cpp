#include "AppManager.h"

AppManager::AppManager(StateMachine *sm) : sm(sm) {
}

StateMachine* AppManager::getStateMachine() {
    return this->sm;
}
