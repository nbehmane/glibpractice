#include "bluez_device.h"

/* Forward Declarations */
static void on_device_properties_changed(GDBusProxy *proxy, GVariant *changed_properties, const gchar* const *invalidated_properties, gpointer user_data);
static void on_device_signal(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name, GVariant *parameters, gpointer user_data);
static GDBusProxy *bluez_device_setup_proxy(const gchar *object_path);

/* Static variables and arrays */
static GDBusProxy *device_proxies[MAX_CONNECTIONS] = { NULL };

static int num_proxies = 0;

/*
 *  ======== bluez_device_get_proxies ========
 */
extern GDBusProxy **bluez_device_get_proxies()
{
	return NULL;
}

/*
 *  ======== bluez_device_disconnect ========
 */
extern void bluez_device_disconnect(const gchar *object_path)
{
	GError *error = NULL;
	int i = 0;
	for (i = 0; i < num_proxies; i++)
	{
		if (!g_strcmp0(object_path, g_dbus_proxy_get_object_path(device_proxies[i])))
		{
			g_dbus_proxy_call_sync(device_proxies[i],
					"Disconnect",
					g_variant_new("()", NULL),
					G_DBUS_CALL_FLAGS_NONE,
					-1,
					NULL,
					&error);

			print_error(error);
			break;
	
		}
	}

	// Free the proxy ebfore we return.
	return;
}

/*
 *  ======== bluez_device_connect ========
 */
extern void bluez_device_connect(const gchar *object_path)
{
	GError *error = NULL;

	//1. Create the proxy object for the object path and store it somewhere. 
	GDBusProxy *proxy_to_add = bluez_device_setup_proxy(object_path);

	//! store the proxy
	device_proxies[num_proxies] = proxy_to_add;

	//! Increment the number of connections (proxies) we have
	num_proxies += 1;

	//! Call the Connect method 
	g_dbus_proxy_call_sync(proxy_to_add,
			"Connect",
			g_variant_new("()", NULL),
			G_DBUS_CALL_FLAGS_NONE,
			-1,
			NULL,
			&error);

	print_error(error);

	return;
}

/*
 *  ======== bluez_device_setup_proxy ========
 */
static GDBusProxy *bluez_device_setup_proxy(const gchar *object_path)
{
	//1. Create the proxy object from the path and connect it to the right interface org.bluez.Device1
	//
	GError *error = NULL;
	GDBusProxy *bluez_device_proxy = NULL;


	// Adapter interface proxy.
	// This will allow us to call methods via the proxy.
	bluez_device_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"org.bluez",
			object_path, 
			"org.bluez.Device1",
			NULL,
			&error);	
	
	if (bluez_device_proxy == NULL)
	{
		print_error(error);
		goto out;
	}

	//2. setup the signal handlers for this particular proxy.
	g_signal_connect(bluez_device_proxy,
			"g-properties-changed",
			G_CALLBACK (on_device_properties_changed),
			NULL);

	g_signal_connect(bluez_device_proxy,
			"g-signal",
			G_CALLBACK(on_device_signal),
			NULL);


	//3. return the proxy if it was successfull otherwise return null.
	return bluez_device_proxy;

out:
	if (bluez_device_proxy != NULL)
		g_object_unref(bluez_device_proxy);
	return NULL;

}

/*
 *  ======== on_device_signal ========
 */
static void on_device_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data)
{
#if DEBUG
	g_print("Device: Signal\n");
#endif
}

/*
 *  ======== on_device_properties_changed ========
 */
static void on_device_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data)
{
#if DEBUG 
	g_print("Device: Properties Changed\n");
#endif
}





