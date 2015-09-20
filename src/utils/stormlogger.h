#pragma once
#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

namespace stormrider
{
#define INFO  BOOST_LOG_SEV(stormlogger::get(), boost::log::trivial::info)
#define WARN  BOOST_LOG_SEV(stormlogger::get(), boost::log::trivial::warning)
#define ERROR BOOST_LOG_SEV(stormlogger::get(), boost::log::trivial::error)

typedef boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger_t;
BOOST_LOG_GLOBAL_LOGGER(stormlogger, logger_t)

} // namespace stormrider
