#include "header.h"

int main() {
    dotenv::init();
    const std::string MAIN_WEBHOOK_env{std::getenv("MAIN_WEBHOOK")};
    const std::string WORDS_WEBHOOK_env{std::getenv("WORDS_WEBHOOK")};
    dpp::webhook MAIN_WEBHOOK(MAIN_WEBHOOK_env);
    dpp::webhook WORDS_WEBHOOK(WORDS_WEBHOOK_env);
    dpp::cluster BOT_TOKEN("");
    std::string output_word;

    return 0;
}