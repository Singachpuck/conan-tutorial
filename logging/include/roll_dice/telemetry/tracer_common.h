#ifndef ROLL_DICE_TRACER_COMMON
#define ROLL_DICE_TRACER_COMMON

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;

opentelemetry::nostd::shared_ptr<trace_api::Tracer> tracer;

inline void initTracer()
{
    auto exporter = trace_exporter::OStreamSpanExporterFactory::Create();
    auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
    std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
        trace_sdk::TracerProviderFactory::Create(std::move(processor));
    // set the global trace provider
    trace_api::Provider::SetTracerProvider(provider);
    tracer = trace_api::Provider::GetTracerProvider()->GetTracer("roll-dice-tracer");
}

inline opentelemetry::nostd::shared_ptr<trace_api::Tracer> getTracer()
{
    return tracer;
}

#endif
