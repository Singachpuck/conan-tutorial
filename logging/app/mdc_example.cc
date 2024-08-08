#include <boost/move/utility.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

#include "common/commons.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;


BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(traceId, "TraceId", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(spanId, "SpanId", std::string)

BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(default_logger, src::severity_logger<logging::trivial::severity_level>) {
    src::severity_logger<logging::trivial::severity_level> lg;
    
    logging::attribute_name traceIdName("TraceId");
    logging::attribute_name spanIdName("SpanId");

    lg.add_attribute(traceIdName, TraceIdAttr("mdc-tracer"));
    lg.add_attribute(spanIdName, SpanIdAttr("mdc-tracer"));
    lg.add_attribute("BoolAttr", attrs::constant<bool>(0));

    formatters["TimeStamp"] = &to_json_node<boost::posix_time::ptime>;
    formatters["Severity"] = &to_json_node<logging::trivial::severity_level>;
    formatters["LineID"] = &to_json_node<std::uint32_t>;
    formatters[traceIdName.string()] = &to_json_node<std::string>;
    formatters[spanIdName.string()] = &to_json_node<std::string>;
    formatters["BoolAttr"] = &to_json_node<bool>;
    formatters["Message"] = &to_json_node<std::string>;

    return lg;
}

void initLogging() {
    logging::add_common_attributes();

    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

    // sink->set_formatter(logging::expressions::stream
    //     << "[" << timestamp << "] "
    //     << "[Trace: " << traceId << "] "
    //     << "[Span: " << spanId << "] "
    //     << "|" << severity << "| "
    //     << logging::expressions::smessage
    // );

    sink->set_formatter(&json_attrs_formatter);

    boost::shared_ptr<std::ostream> stream{&std::clog, boost::null_deleter()};
    sink->locked_backend()->add_stream(stream);

    logging::core::get()->add_sink(sink);
}

void initTraces() {
    std::vector<std::unique_ptr<trace_sdk::SpanProcessor>> processors{};
    auto exporter = trace_exporter::OStreamSpanExporterFactory::Create();
    auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));

    // processors.push_back(std::move(processor));

    std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
        trace_sdk::TracerProviderFactory::Create(std::move(processors));

    // set the global trace provider
    trace_api::Provider::SetTracerProvider(provider);
}

inline opentelemetry::nostd::shared_ptr<trace_api::Tracer> getTestTracer() {
    return trace_api::Provider::GetTracerProvider()->GetTracer("mdc-tracer");
}

void f1() {
    auto& lg = default_logger::get();
    auto tracer = getTestTracer();
    auto scoped_span = trace_api::Scope(tracer->StartSpan("nested-span"));
    BOOST_LOG_SEV(lg, logging::trivial::warning) << "Greetings from f1!";
}

void mdc_trace_example() {
    auto& lg = default_logger::get();

    auto tracer = getTestTracer();
    auto scoped_span = trace_api::Scope(tracer->StartSpan("mdc-test"));

    BOOST_LOG_SEV(lg, logging::trivial::warning) << "Greetings from mdc_trace_example!";

    tracer->GetCurrentSpan()->SetAttribute("attr1", "Value");
    tracer->GetCurrentSpan()->AddEvent("EventWithAttributes", {{"eventAttr1", "Value"}});

    tracer->GetCurrentSpan()->GetContext().trace_id().Id();

    f1();
}

int main() {
    /* Comments:
    1. To get access to TraceId/SpanId values need to call Tracer -> GetCurrentSpan() -> GetContext() -> span_id()/trace_id()
    2. Boost Log allows to attach attributed to the logger, globally or in the scope of a thread.
    3. Boost Log allows to customize the sinks and apply custom frontend and backend logic.
        Frontend is responsible for processing the log record (filtering, formatting, other preprocessing).
        Backend is responsible for exporting the log record.
    4. After sink is configured it needs to be registered in the boost::log::core.
    5. To make Boost logger log the TraceId and SpanId these values need to be extracted from the current SpanContext and passed as const attributes to the logger.
    6. Drawback: SpanId attribute inside the logger needs to be updated along with the new span creation.
    7. TraceId gets generated when the first root Span is initialized. Before it is equal to 0.
    */

    auto& lg = default_logger::get();

    initLogging();
    BOOST_LOG_SEV(lg, logging::trivial::info) << "Using Boost Log library";
    BOOST_LOG_SEV(lg, logging::trivial::info) << "Initializing traces...";
    initTraces();
    BOOST_LOG_SEV(lg, logging::trivial::info) << "Showing examples";
    mdc_trace_example();
    mdc_trace_example();
}