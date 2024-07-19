#ifndef ROLL_DICE_OTEL_CONFIG
#define ROLL_DICE_OTEL_CONFIG

#include <fstream>
#include <thread>

#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/log_record_exporter_factory.h"
#include "opentelemetry/logs/provider.h"
#include "opentelemetry/sdk/logs/logger.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/logs/logger_context_factory.h"

namespace logs_api = opentelemetry::logs;
namespace logs_sdk = opentelemetry::sdk::logs;
namespace logs_exporter = opentelemetry::exporter::logs;

#ifndef LOG_FLUSH_PERIOD 
    #define LOG_FLUSH_PERIOD 5000
#endif

inline std::unique_ptr<std::thread> config_otel_logger(std::ostream& logOutput) {
    // Exporters
    auto exporter = logs_exporter::OStreamLogRecordExporterFactory::Create();

    auto exporter2 = logs_exporter::OStreamLogRecordExporterFactory::Create(logOutput);
    std::unique_ptr<std::thread> flushLogThread = std::make_unique<std::thread>([&logOutput]() {
        while (true) {
            logOutput.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(LOG_FLUSH_PERIOD));
        }
    });

    // Processors
    auto processor = logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(exporter));
    auto processor2 = logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(exporter2));
    std::vector<std::unique_ptr<logs_sdk::LogRecordProcessor>> processors;
    processors.push_back(std::move(processor));
    processors.push_back(std::move(processor2));

    auto context = logs_sdk::LoggerContextFactory::Create(std::move(processors));

    // LoggerProvider
    std::shared_ptr<logs_api::LoggerProvider> provider = logs_sdk::LoggerProviderFactory::Create(std::move(context));
    logs_api::Provider::SetLoggerProvider(provider);
    return flushLogThread;
}

opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> getNativeLogger(std::string name)
{
	auto provider = logs_api::Provider::GetLoggerProvider();
	return provider->GetLogger(name + "_logger", name, OPENTELEMETRY_SDK_VERSION);
}

#endif