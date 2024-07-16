#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include <string>

#include "common.h"
#include "telemetry/logger_common.h"
#include "telemetry/otel_config.h"
#include "telemetry/tracer_common.h"


class Handler : public oatpp::web::server::HttpRequestHandler
{
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> & /*request*/) override
	{
		auto logger = getLogger();
		auto tracer = getTracer();
		auto span = tracer->StartSpan("RollDiceServer");

		auto roll = roll_dice();

		const std::string response = std::to_string(roll);
		logger->trace("Generated HTTP Response Body: {}", response);
		span->End();
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
	// logger->info("Random formatted log: {:.2f}", 0.5f);
	// logger->Info("Random log");
	logger->info("Server running on port {}", static_cast<const char *>(connectionProvider->getProperty("port").getData()));
	logger->info("Dice Roll routed to {}", rollDicePath);
	server.run();
}

int main()
{
	oatpp::base::Environment::init();
	config_otel_logger();
	initTracer();
	initLogger();
	roll_dice_init();
	run();
	oatpp::base::Environment::destroy();
	return 0;
}