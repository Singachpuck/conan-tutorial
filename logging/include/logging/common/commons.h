#ifndef LOGGING_COMMON_H
#define LOGGING_COMMON_H

#include <sstream>

#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/attributes/attribute_cast.hpp>

#include <unordered_map>

#include <nlohmann/json.hpp>

#include "opentelemetry/sdk/trace/tracer_provider_factory.h"

#define OTEL_TRACE_LENGTH 32
#define OTEL_SPAN_LENGTH 16

namespace logging = boost::log;
namespace attrs = boost::log::attributes;

namespace trace_api = opentelemetry::trace;


class TraceIdAttrImpl :
    public logging::attribute::impl {
private:
    std::string tracerName;

public:
    TraceIdAttrImpl(std::string tracerName) : tracerName(tracerName) {}

    logging::attribute_value get_value()
    {
        auto&& tracer = trace_api::Provider::GetTracerProvider()->GetTracer(this->tracerName);

        char trace_id[OTEL_TRACE_LENGTH] = {0};
        tracer->GetCurrentSpan()->GetContext().trace_id().ToLowerBase16(trace_id);

        return attrs::make_attribute_value(std::string(trace_id, OTEL_TRACE_LENGTH));
    }
};

class TraceIdAttr :
    public logging::attribute {
public:
    TraceIdAttr(std::string tracerName) : logging::attribute(new TraceIdAttrImpl(tracerName))
    {
    }
    explicit TraceIdAttr(attrs::cast_source const& source) : logging::attribute(source.as< TraceIdAttrImpl >())
    {
    }
};

class SpanIdAttrImpl :
    public logging::attribute::impl {
private:
    std::string tracerName;

public:
    SpanIdAttrImpl(std::string tracerName) : tracerName(tracerName) {}

    logging::attribute_value get_value()
    {
        auto&& tracer = trace_api::Provider::GetTracerProvider()->GetTracer(this->tracerName);

        char span_id[OTEL_SPAN_LENGTH] = {0};
        tracer->GetCurrentSpan()->GetContext().span_id().ToLowerBase16(span_id);

        return attrs::make_attribute_value(std::string(span_id, OTEL_SPAN_LENGTH));
    }
};

class SpanIdAttr :
    public logging::attribute {
public:
    SpanIdAttr(std::string tracerName) : logging::attribute(new SpanIdAttrImpl(tracerName))
    {
    }
    explicit SpanIdAttr(attrs::cast_source const& source) : logging::attribute(source.as< SpanIdAttrImpl >())
    {
    }
};

std::unordered_map<
    std::string,
    std::function< void(std::ostream&, logging::attribute_value const&) >
> formatters {};

/**
 * Note: Array and nested object are not supported.
 */
template< typename T >
void to_json_node(std::ostream& strm, logging::attribute_value const& attr)
{
    auto val = logging::extract< T >(attr);
    if (val) {
        if (boost::is_arithmetic<T>::value) {
            strm << val.get();
        } else {
            std::stringstream ss;
            ss << val.get();
            strm << std::quoted(ss.str());
        }
    }
}

void json_attrs_formatter(const logging::record_view &view, logging::formatting_ostream &os) {
    os << "{\n";
    bool first = true;
    for (auto& attribute : view.attribute_values()) {
        auto it = formatters.find(attribute.first.string());
        if (it != formatters.end()) {
            if (!first) {
                os << ",\n";
            }
            os << "\t" << std::quoted(attribute.first.string()) << ": ";
            std::stringstream ss;
            it->second(ss, attribute.second);
            os << ss.str();
            first = false;
        }
    }

    os << "\n}\n";
}

#endif