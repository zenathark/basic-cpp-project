#include "spdlog/spdlog.h"


#define console_log_start() auto console = spdlog::stdout_logger_mt("console")
#define LOG(msg) console->info(msg)

console_log_start();
