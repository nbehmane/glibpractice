#ifndef BLUEZ_ADAPTER_H
#define BLUEZ_ADAPTER_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>

/**
 * @brief Initiates scanning, populating the bluez.org namespace with device objects.
 *
 * @param s Set 1 to start scanning and 0 to stop scanning.
 */
extern void bluez_adapter_scan(guint s);

/**
 * @brief Initializes the GDBusProxy object to get access to the org.bluez.Adapter1 methods.
 * 	Connects to two signals: g-properties-changed and g-signal. Currently, neither of 
 * 	these signals are used. 
 *
 * 	TODO: Make the selection of the controller dynamic.
 *
 * @param connection Not used.
 */
extern void bluez_adapter_proxy_init(GDBusConnection *connection);

#endif
