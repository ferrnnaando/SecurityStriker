#pragma once
#include "dotenv.h"
#include "config.cpp"

#ifdef PLATFORM_WINDOWS_32x64
    #include <Windows.h>
#else
    #include <opencv2/opencv.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
    #include <X11/Xutil.h>
    #include <X11/XKBlib.h>
    #include <X11/extensions/Xinerama.h>
    #include <jpeglib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <linux/input.h>
    #include <fcntl.h>
#endif

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h> //diferrence betweeen stdlib.h and cstlid, stido and cstdio
#include <cerrno>
#include <dpp/dpp.h>
#include <thread>
#include <functional>
#include <exception>