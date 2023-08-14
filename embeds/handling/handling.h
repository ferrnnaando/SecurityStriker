#pragma once
#include <dpp/dpp.h>
#include <thread>
#include <chrono>
#include <fstream>

dpp::embed disclaimer_warning();
dpp::embed equal_webhooks();
dpp::embed making_connection();
dpp::embed connection_result(bool&);
dpp::embed handle_catch(const std::exception&);
dpp::embed handle_kill();