#include "managers/AppManager.h"

AppManager::AppManager(std::shared_ptr<UrlManager> um, std::shared_ptr<StateMachine> sm, std::shared_ptr<ExceptionHandler> exHandler)
    : urlManager(um), sm(sm), exHandler(exHandler) {
}

AppManager::~AppManager() {
    this->sm->destroy();
}

std::shared_ptr<StateMachine> AppManager::getStateMachine() {
    return this->sm;
}

std::shared_ptr<ExceptionHandler> AppManager::getExceptionHandler() {
    return this->exHandler;
}

std::shared_ptr<UrlManager> AppManager::getUrlManager() {
    return this->urlManager;
}