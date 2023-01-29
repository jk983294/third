#include <chrono>
#include <cstdio>

void stdout_logger_example();
void basic_example();
void rotating_example();
void daily_example();
void async_example();
void binary_example();
void vector_example();
void stopwatch_example();
void multi_sink_example();
void user_defined_example();
void err_handler_example();
void file_events_example();
void replace_default_logger_example();
void backtrace_example();

#include "spdlog/cfg/env.h"   // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h"  // support for user defined types
#include "spdlog/spdlog.h"

int main(int, char *[]) {
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");

    // Runtime log levels
    spdlog::set_level(spdlog::level::info);  // Set global log level to info
    spdlog::debug("This message should not be displayed!");
    spdlog::set_level(spdlog::level::trace);  // Set specific logger's log level
    spdlog::debug("This message should be displayed..");

    // Customize msg format for all loggers
    spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
    spdlog::info("This an info message with custom format");
    spdlog::set_pattern("%+");  // back to default format
    spdlog::set_level(spdlog::level::info);

    vector_example();
    user_defined_example();
    err_handler_example();
    stopwatch_example();

    backtrace_example();
    stdout_logger_example();
    basic_example();
    rotating_example();
    daily_example();
    async_example();
    binary_example();
    multi_sink_example();
    file_events_example();
    replace_default_logger_example();

    try {
        // Flush all *registered* loggers using a worker thread every 3 seconds.
        // note: registered loggers *must* be thread safe for this to work correctly!
        spdlog::flush_every(std::chrono::seconds(3));

        // Apply some function on all registered loggers
        spdlog::apply_all([&](const std::shared_ptr<spdlog::logger>& l) { l->info("End of example."); });

        // Release all spdlog resources, and drop all loggers in the registry.
        // This is optional (only mandatory if using windows + async log).
        spdlog::shutdown();
    } catch (const spdlog::spdlog_ex &ex) {
        // Exceptions will only be thrown upon failed logger or sink construction (not during logging).
        std::printf("Log initialization failed: %s\n", ex.what());
        return 1;
    }
}

void backtrace_example() {
    // Backtrace support
    // Loggers can store in a ring buffer all messages (including debug/trace) for later inspection.
    // When needed, call dump_backtrace() to see what happened:
    spdlog::enable_backtrace(10);  // create ring buffer with capacity of 10  messages
    for (int i = 0; i < 100; i++) {
        spdlog::debug("Backtrace message {}", i);  // not logged..
    }
    // e.g. if some error happened:
    spdlog::dump_backtrace();  // log them now!
}

#include "spdlog/sinks/stdout_color_sinks.h"
// or #include "spdlog/sinks/stdout_sinks.h" if no colors needed.
void stdout_logger_example() {
    // Create color multi threaded logger.
    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(console)");
    spdlog::get("stderr")->info("loggers can be retrieved from a global registry using the spdlog::get(stderr)");
}

#include "spdlog/sinks/basic_file_sink.h"
void basic_example() {
    // Create basic file logger (not rotated).
    auto my_logger = spdlog::basic_logger_mt("file_logger", "/tmp/logs/basic-log.txt", true);
    my_logger->info("test basic file logger!");
}

#include "spdlog/sinks/rotating_file_sink.h"
void rotating_example() {
    // Create a file rotating logger with 5mb size max and 3 rotated files.
    auto rotating_logger = spdlog::rotating_logger_mt("some_logger_name", "/tmp/logs/rotating.txt", 1048576 * 5, 3);
    rotating_logger->info("test rotating file logger!");
}

#include "spdlog/sinks/daily_file_sink.h"
void daily_example() {
    // Create a daily logger - a new file is created every day on 2:30am.
    auto daily_logger = spdlog::daily_logger_mt("daily_logger", "/tmp/logs/daily.txt", 2, 30);
    daily_logger->info("test daily file logger!");
}

#include "spdlog/async.h"
void async_example() {
    // Default thread pool settings can be modified *before* creating the async logger:
    // spdlog::init_thread_pool(32768, 1); // queue with max 32k items 1 backing thread.
    auto async_file = spdlog::daily_logger_mt<spdlog::async_factory>("async_file_logger", "/tmp/logs/async_log.txt");

    for (int i = 1; i < 101; ++i) {
        async_file->info("Async message #{}", i);
    }
}

// Log binary data as hex.
// Many types of std::container<char> types can be used.
// Iterator ranges are supported too.
// Format flags:
// {:X} - print in uppercase.
// {:s} - don't separate each byte with space.
// {:p} - don't print the position on each line start.
// {:n} - don't split the output to lines.

#include "spdlog/fmt/bin_to_hex.h"
void binary_example() {
    std::vector<char> buf(80);
    for (int i = 0; i < 80; i++) {
        buf.push_back(static_cast<char>(i & 0xff));
    }
    spdlog::info("Binary example: {}", spdlog::to_hex(buf));
    spdlog::info("Another binary example:{:n}", spdlog::to_hex(std::begin(buf), std::begin(buf) + 10));
    // more examples:
    spdlog::info("uppercase: {:X}", spdlog::to_hex(buf));
    spdlog::info("uppercase, no delimiters: {:Xs}", spdlog::to_hex(buf));
    spdlog::info("uppercase, no delimiters, no position info: {:Xsp}", spdlog::to_hex(buf));
    spdlog::info("hexdump style: {:a}", spdlog::to_hex(buf));
    spdlog::info("hexdump style, 20 chars per line {:a}", spdlog::to_hex(buf, 20));
}

// Log a vector of numbers
#ifndef SPDLOG_USE_STD_FORMAT
#include "spdlog/fmt/ranges.h"
void vector_example() {
    std::vector<int> vec = {1, 2, 3};
    spdlog::info("Vector example: {}", vec);
}

#else
void vector_example() {}
#endif

// stopwatch example
#include <thread>
#include "spdlog/stopwatch.h"
void stopwatch_example() {
    spdlog::stopwatch sw;
    std::this_thread::sleep_for(std::chrono::milliseconds(123));
    spdlog::info("Stopwatch: {} seconds", sw);
}

// A logger with multiple sinks (stdout and file) - each with a different format and log level.
void multi_sink_example() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("/tmp/logs/multisink.txt", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);
    logger.warn("this should appear in both console and file");
    logger.info("this message should not appear in the console, only in the file");
}

// User defined types logging
struct my_type {
    int i = 0;
    explicit my_type(int i) : i(i){};
};

#ifndef SPDLOG_USE_STD_FORMAT  // when using fmtlib
template <>
struct fmt::formatter<my_type> : fmt::formatter<std::string> {
    auto format(my_type my, format_context &ctx) -> decltype(ctx.out()) {
        return format_to(ctx.out(), "[my_type i={}]", my.i);
    }
};

#else  // when using std::format
template <>
struct std::formatter<my_type> : std::formatter<std::string> {
    auto format(my_type my, format_context &ctx) -> decltype(ctx.out()) {
        return format_to(ctx.out(), "[my_type i={}]", my.i);
    }
};
#endif

void user_defined_example() { spdlog::info("user defined type: {}", my_type(14)); }

// Custom error handler. Will be triggered on log failure.
void err_handler_example() {
    // can be set globally or per logger(logger->set_error_handler(..))
    spdlog::set_error_handler(
        [](const std::string &msg) { printf("*** Custom log error handler: %s ***\n", msg.c_str()); });
}

void file_events_example() {
    // pass the spdlog::file_event_handlers to file sinks for open/close log file notifications
    spdlog::file_event_handlers handlers;
    handlers.before_open = [](const spdlog::filename_t& filename) { spdlog::info("Before opening {}", filename); };
    handlers.after_open = [](const spdlog::filename_t& filename, std::FILE *fstream) {
        spdlog::info("After opening {}", filename);
        fputs("After opening\n", fstream);
    };
    handlers.before_close = [](const spdlog::filename_t& filename, std::FILE *fstream) {
        spdlog::info("Before closing {}", filename);
        fputs("Before closing\n", fstream);
    };
    handlers.after_close = [](const spdlog::filename_t& filename) { spdlog::info("After closing {}", filename); };
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("/tmp/logs/events-sample.txt", true, handlers);
    spdlog::logger my_logger("some_logger", file_sink);
    my_logger.info("Some log line");
}

void replace_default_logger_example() {
    // store the old logger so we don't break other examples.
    auto old_logger = spdlog::default_logger();

    auto new_logger = spdlog::basic_logger_mt("new_default_logger", "/tmp/logs/new-default-log.txt", true);
    spdlog::set_default_logger(new_logger);
    spdlog::set_level(spdlog::level::info);
    spdlog::debug("This message should not be displayed!");
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("This message should be displayed..");

    spdlog::set_default_logger(old_logger);
}
