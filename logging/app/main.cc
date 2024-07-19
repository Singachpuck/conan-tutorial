#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/log_record_exporter_factory.h"
#include "opentelemetry/logs/provider.h"
#include "opentelemetry/sdk/logs/logger.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/logs/logger_context_factory.h"

#include <iostream>

#include "project_config.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "opentelemetry/instrumentation/spdlog/sink.h"

namespace logs_api = opentelemetry::logs;
namespace logs_sdk = opentelemetry::sdk::logs;
namespace logs_exporter = opentelemetry::exporter::logs;

namespace {
    void initOtel() {
        // Exporters
        auto exporter = logs_exporter::OStreamLogRecordExporterFactory::Create();

        // Processors
        auto processor = logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(exporter));
        std::vector<std::unique_ptr<logs_sdk::LogRecordProcessor>> processors;
        processors.push_back(std::move(processor));

        auto resource = opentelemetry::sdk::resource::Resource::Create({{"service.name", PROJECT_NAME}});
        auto context = logs_sdk::LoggerContextFactory::Create(std::move(processors), resource);

        // LoggerProvider
        std::shared_ptr<logs_api::LoggerProvider> provider = logs_sdk::LoggerProviderFactory::Create(std::move(context));
        logs_api::Provider::SetLoggerProvider(provider);
    }

    void initLogger() {
        std::vector<spdlog::sink_ptr> sinks {};

        // Default sinks
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("example.log", true);
        file_sink->set_level(spdlog::level::warn);
        file_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);

        sinks.push_back(file_sink);
        sinks.push_back(console_sink);

        auto def_logger = std::make_shared<spdlog::logger> ("default_logger", sinks.begin(), sinks.end());
        def_logger->set_level(spdlog::level::trace);

        spdlog::set_default_logger(def_logger);
    }
}

int main() {
    initOtel();
    initLogger();

    spdlog::trace("Trace...");
    spdlog::debug("Debugging info.");
    spdlog::info("Info");
    spdlog::warn("Warning!");
    spdlog::error("Error occured!!");
    spdlog::critical("Fatal error!!!");
    
    spdlog::info("\n\nSwitching to OpenTelemetry logger...\n\n");
    /*
        Steps:
        1. Application uses logger library (ex. spdlog) and emits logs throughout it's runtime to record application flow.
        2. Opentelemetry appender is added to the logger to handle log messages emmited by the logger.
        3. The appender calls OpenTelemeetry Log Bridge API to invoke Logger::emit() -> LogRecord.
            Logger is obtained by the appender by calling LoggerProvider::GetLogger().
            Logger contains LogRecordProcessors that process the log message and delegate it to LogRecordExporter.
        4. LoggerProvider needs to be set through OpenTelemetry API. LoggerProvider should be normally initiallized once.
            LoggerProvider normally is configured at the beginning of the app. See initOtel() method.
    */
    auto otel_sink = std::make_shared<spdlog::sinks::opentelemetry_sink_mt>();
    otel_sink->set_level(spdlog::level::info);
    spdlog::logger otelLogger("otel_logger", otel_sink);

    otelLogger.info("Otel example {}", 1);
    
    return 0;
}