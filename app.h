#ifndef APP_H
#define APP_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "appinfo.h"
#include "adapter.h"

extern void app_register_application(GDBusProxy *bluez_adapter_proxy);

#endif 
