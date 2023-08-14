#pragma once
#include <dpp/dpp.h>
#include <thread>
#include <chrono>
#include <fstream>

dpp::embed making_connection(std::string& username);
dpp::embed connection_result(bool& result);
dpp::embed handle_catch(const std::exception& e);