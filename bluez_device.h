#ifndef BLUEZ_DEVICE_H
#define BLUEZ_DEVICE_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>

#define MAX_CONNECTIONS 2


static GDBusProxy *bluez_device_setup_proxy(const gchar *object_path);

extern void bluez_device_connect(const gchar *object_path);

extern void bluez_device_disconnect(const gchar *object_path);


#endif
