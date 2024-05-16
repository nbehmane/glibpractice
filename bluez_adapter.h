#ifndef BLUEZ_ADAPTER_H
#define BLUEZ_ADAPTER_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>

extern void bluez_adapter_scan(guint s);
extern void bluez_adapter_proxy_init(GDBusConnection *connection);

#endif
