#include <string>

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "common.h"
#include "telemetry/logger_common.h"

#ifdef WITH_OTEL_LOGS
	#ifndef LOG_FILE_PATH
		#define LOG_FILE_PATH "otel.log"
	#endif
	#include "telemetry/otel_config.h"
#endif

#ifdef WITH_TRACES
	#include "telemetry/tracer_common.h"
#endif



class Handler : public oatpp::web::server::HttpRequestHandler
{
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> & /*request*/) override
	{
		auto logger = getLogger();
#ifdef WITH_TRACES
		auto tracer = getTracer();
		auto span = tracer->StartSpan("RollDiceServer");
#endif

		auto roll = roll_dice();

		const std::string response = std::to_string(roll);
		logger->trace("Generated HTTP Response Body: {}", response);
#ifdef WITH_TRACES
		span->End();
#endif
		return ResponseFactory::createResponse(Status::CODE_200, response.c_str());
	}
};

void run()
{
	auto logger = getLogger();
	auto router = oatpp::web::server::HttpRouter::createShared();
	// const char* rollDicePath = "/rolldice";
	std::string rollDicePath("/rolldice");
	logger->trace("Routing dice roll to {}", rollDicePath);
	router->route("GET", rollDicePath, std::make_shared<Handler>());
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({ROLL_DICE_HOST, ROLL_DICE_PORT, oatpp::network::Address::IP_4});
	oatpp::network::Server server(connectionProvider, connectionHandler);
	logger->info("Server running on port {}", static_cast<const char *>(connectionProvider->getProperty("port").getData()));
	logger->info("Dice Roll routed to {}", rollDicePath);
	server.run();
}

int main()
{
#ifdef WITH_OTEL_LOGS
	std::ofstream logFile;
	logFile.open(LOG_FILE_PATH);
	auto t = config_otel_logger(logFile);
#endif
#ifdef WITH_TRACES
	initTracer();
#endif
	initLogger();
	oatpp::base::Environment::init();
	roll_dice_init();
	run();
	oatpp::base::Environment::destroy();
#ifdef WITH_OTEL_LOGS
	t->~thread();
	logFile.close();
#endif
	return 0;
}