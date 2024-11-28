#include "Context.h"

std::shared_ptr<Context> ContextFactory::initSharedContext(std::shared_ptr<dochkas::linkholder::UrlAppManager> urlManager)
{
    auto context = std::shared_ptr<Context>();
    context->setUrlManager(urlManager);
    return context;
}

std::shared_ptr<dochkas::linkholder::UrlAppManager> Context::getUrlManager() const {
    return urlManager;
}

void Context::setUrlManager(std::shared_ptr<dochkas::linkholder::UrlAppManager> manager) {
    // TODO: ???
	std::cout << manager->getName() << std::endl;
    // this->urlManager = manager;
}