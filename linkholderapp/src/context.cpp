#include <utility>

#include "Context.h"

namespace context {
    static std::shared_ptr<Context> appContext = std::make_shared<Context>();

    std::shared_ptr<Context> ContextFactory::initSharedContext(std::shared_ptr<dochkas::linkholder::UrlAppManager> urlManager)
    {
        appContext->setUrlManager(std::move(urlManager));
        return appContext;
    }

    std::shared_ptr<Context> get() {
        return appContext;
    }

    std::shared_ptr<dochkas::linkholder::UrlAppManager> Context::getUrlManager() const {
        return urlManager;
    }

    void Context::setUrlManager(std::shared_ptr<dochkas::linkholder::UrlAppManager> manager) {
        // TODO: ???
//	std::cout << manager->getName() << std::endl;
        this->urlManager = std::move(manager);
    }
}