#ifndef BLUEZ_OBJECT_H
#define BLUEZ_OBJECT_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"

#define DEBUG
#define DEV_ARRAY_SIZE 50


extern gchar **bluez_object_get_devices(gsize *num_devices);

extern void bluez_object_proxy_init(GDBusConnection *connection);


#endif
