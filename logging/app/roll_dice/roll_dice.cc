#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

// Traces
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

// Logs
#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/log_record_exporter_factory.h"
#include "opentelemetry/logs/provider.h"
#include "opentelemetry/sdk/logs/logger.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/logs/logger_context_factory.h"

#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;

namespace logs_api = opentelemetry::logs;
namespace logs_sdk = opentelemetry::sdk::logs;
namespace logs_exporter = opentelemetry::exporter::logs;

namespace
{
	void InitTracer()
	{
		auto exporter = trace_exporter::OStreamSpanExporterFactory::Create();
		auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
		std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
			trace_sdk::TracerProviderFactory::Create(std::move(processor));
		// set the global trace provider
		trace_api::Provider::SetTracerProvider(provider);
	}
	void CleanupTracer()
	{
		std::shared_ptr<opentelemetry::trace::TracerProvider> none;
		trace_api::Provider::SetTracerProvider(none);
	}

	void initLogger()
	{
		auto exporter = logs_exporter::OStreamLogRecordExporterFactory::Create();
		auto processor = logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(exporter));
		std::vector<std::unique_ptr<logs_sdk::LogRecordProcessor>> processors;
		processors.push_back(std::move(processor));
		auto context = logs_sdk::LoggerContextFactory::Create(std::move(processors));
		std::shared_ptr<logs_api::LoggerProvider> provider = logs_sdk::LoggerProviderFactory::Create(std::move(context));
		logs_api::Provider::SetLoggerProvider(provider);
	}

	opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> getLogger(std::string name)
	{
		auto provider = logs_api::Provider::GetLoggerProvider();
		return provider->GetLogger(name + "_logger", name, OPENTELEMETRY_SDK_VERSION);
	}

}

class Handler : public oatpp::web::server::HttpRequestHandler
{
public:
	shared_ptr<OutgoingResponse> handle(const shared_ptr<IncomingRequest> &request) override
	{
		auto tracer = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("roll-dice-tracer");
		auto span = tracer->StartSpan("RollDiceServer");
		int low = 1;
		int high = 7;
		int random = rand() % (high - low) + low;
		// Convert a std::string to oatpp::String
		const string response = to_string(random);
		span->End();
		return ResponseFactory::createResponse(Status::CODE_200, response.c_str());
	}
};

void run()
{
	auto router = oatpp::web::server::HttpRouter::createShared();
	router->route("GET", "/rolldice", std::make_shared<Handler>());
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8080, oatpp::network::Address::IP_4});
	oatpp::network::Server server(connectionProvider, connectionHandler);
	auto logger = getLogger("roll_dice");
	logger->Info("Random log");
	OATPP_LOGI("Dice Server", "Server running on port %s", static_cast<const char *>(connectionProvider->getProperty("port").getData()));
	server.run();
}

int main()
{
	oatpp::base::Environment::init();
	InitTracer();
	initLogger();
	srand((int)time(0));
	run();
	oatpp::base::Environment::destroy();
	CleanupTracer();
	return 0;
}