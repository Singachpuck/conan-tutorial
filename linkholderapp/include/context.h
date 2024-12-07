#ifndef LINKHOLDER_CONSOLE_CONTEXT_H
#define LINKHOLDER_CONSOLE_CONTEXT_H

#include <memory>

#include "linkholder/core.h"

namespace context {
    class Context {
    private:
        std::shared_ptr<dochkas::linkholder::UrlAppManager> urlManager;

    public:
        std::shared_ptr<dochkas::linkholder::UrlAppManager> getUrlManager() const;

        void setUrlManager(std::shared_ptr<dochkas::linkholder::UrlAppManager> manager);
    };

    class ContextFactory {
    public:
        static std::shared_ptr<Context> initSharedContext(std::shared_ptr<dochkas::linkholder::UrlAppManager> urlManager);
    };

    std::shared_ptr<Context> get();
};

#endif