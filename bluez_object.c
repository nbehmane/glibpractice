#include "bluez_object.h"

#define DEBUG

static GDBusObjectManager *bluez_object_proxy = NULL;

extern void bluez_object_proxy_init(GDBusConnection *connection)
{
	GError *error = NULL;

	bluez_object_proxy = g_dbus_object_manager_client_new_for_bus_sync(
			G_BUS_TYPE_SYSTEM,
			G_DBUS_OBJECT_MANAGER_CLIENT_FLAGS_NONE,
			"org.bluez",
			"/",
			NULL,
			NULL,
			NULL,
			NULL,
			&error);

	print_error(error);

#ifdef DEBUG 
	 
	gchar *owner = g_dbus_object_manager_client_get_name_owner((GDBusObjectManagerClient*)bluez_object_proxy);
	g_print("Object Owner: %s", owner);
	if (owner != NULL)
		g_free(owner);
#endif
}
