#pragma once
#include <string>

#include <WebServer.h>

class FlashFileReader
{
public:
    FlashFileReader();
    bool loadFromSpiffs(String path, WebServer *server);
};