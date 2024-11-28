#ifndef ROLL_DICE_METRICS_COMMON
#define ROLL_DICE_METRICS_COMMON

#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"

inline void initMetrics() {
    auto provider = std::shared_ptr<opentelemetry::metrics::MeterProvider>(new opentelemetry::sdk::metrics::MeterProvider());
    auto p = std::static_pointer_cast<opentelemetry::sdk::metrics::MeterProvider>(provider);
    p->AddMetricReader(std::move(reader));
}

#endif