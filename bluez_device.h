#ifndef BLUEZ_DEVICE_H
#define BLUEZ_DEVICE_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"

#define MAX_CONNECTIONS 2

extern GDBusProxy **bluez_device_get_proxies();

extern void bluez_device_connect(const gchar *object_path);

extern void bluez_device_disconnect(const gchar *object_path);


#endif
