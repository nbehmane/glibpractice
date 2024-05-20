#ifndef BLUEZ_OBJECT_H
#define BLUEZ_OBJECT_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"

#define DEV_ARR_SIZE 25

extern GVariant *bluez_object_get_devices();
extern void bluez_object_proxy_init(GDBusConnection *connection);


#endif
