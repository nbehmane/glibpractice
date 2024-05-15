#include "bluez_object.h"

static GDBusProxy *bluez_object_proxy = NULL;

extern GVariant *bluez_object_get_objects()
{
	GError *error = NULL;
	GVariant *results = NULL;

	results = g_dbus_proxy_call_sync( bluez_object_proxy,
			"GetManagedObjects",
			g_variant_new("()", NULL),
			G_DBUS_CALL_FLAGS_NONE,
			-1,
			NULL,
			&error);

	print_error(error);

	return results;
}


static void on_signal(GDBusProxy* self, gchar* sender_name, gchar* signal_name, GVariant* parameters, gpointer user_data)
{

#ifdef DEBUG
	g_print("Interface added:%s\n", g_variant_get_type_string(parameters));
#endif

}

extern void bluez_object_proxy_init(GDBusConnection *connection)
{
	GError *error = NULL;
	// Adapter interface proxy.
	// This will allow us to call methods via the proxy.
	bluez_object_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"org.bluez",
			"/", 
			"org.freedesktop.DBus.ObjectManager",
			NULL,
			&error);	
	
	if (bluez_object_proxy == NULL)
	{
		print_error(error);
		goto out;
	}

	g_signal_connect(bluez_object_proxy,
			"g-signal::InterfacesAdded",
			G_CALLBACK (on_signal),
			NULL);

#ifdef DEBUG
	// Print the owner ID of the proxy object.
	print_proxy(bluez_object_proxy);
#endif

	return;

out:
	if (bluez_object_proxy != NULL)
		g_object_unref(bluez_object_proxy);

}
