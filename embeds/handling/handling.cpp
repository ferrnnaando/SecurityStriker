#include "handling.h"

struct list_error {
    std::string no_found_cpu;
};

struct system_specs {
    std::string cpu_model;
    std::string cpu_cores;
};

list_error handled_err;
system_specs hardware_specs;

dpp::embed making_connection(std::string& username) {
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

    hardware_specs.cpu_cores = std::to_string(std::thread::hardware_concurrency());
    std::string new_device = "```A new device found.```";
    std::string status = "```Loading... (Inyecting malware)```";

    dpp::embed connection = dpp::embed()
        .set_author("", "", "https://w7.pngwing.com/pngs/253/931/png-transparent-security-hacker-anonymous-ultra-high-definition-television-internet-v-for-vendetta-face-computer-desktop-wallpaper.png")
        .set_color(dpp::colors::yellow)
        .add_field("<:websit:1140446138177179860> Status", new_device, true)
        .add_field("<:blueshie:1127620004955836416> Process", status, true)
    ;

    return connection;
}

dpp::embed connection_result(bool& result) {;
    if(result == false) {
        std::string result_wrong = "```Inyection was unsucessful.```";
        std::string output_wrong = "```" + handled_err.no_found_cpu + "```";
        dpp::embed wrong = dpp::embed()
            .set_color(dpp::colors::red_blood)
            .add_field("<:websit:1140446138177179860> Status", result_wrong, true)
            .add_field("<:blueshie:1127620004955836416> Output", output_wrong, true)
        ;

        return wrong;
    } else {
        std::string result_success = "```Inyection was sucessful.```";
        std::string output_success = "```No errors.```";
        std::string sys_about = "```CPU: " + hardware_specs.cpu_model + " || " + hardware_specs.cpu_cores + " cores.\nGPU: ```";

        dpp::embed success = dpp::embed()
            .set_color(dpp::colors::green)
            .add_field("<:websit:1140446138177179860> Status", result_success, true)
            .add_field("<:blueshie:1127620004955836416> Output", output_success, true)
            .add_field("System", sys_about, false)
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