#pragma once
#include <dpp/dpp.h>
#include <thread>
#include <chrono>
#include <fstream>

void detect_execution_enviroment();
dpp::embed isnt_root();
dpp::embed disclaimer_warning();
dpp::embed equal_webhooks();
dpp::embed making_connection();
dpp::embed connection_result(bool&);
dpp::embed handle_catch(const std::exception&);
void take_screenshot(const int&, const int&);
dpp::embed handle_kill();
void track_kill(dpp::cluster& temp_token, dpp::webhook& MAIN_WEBHOOK);