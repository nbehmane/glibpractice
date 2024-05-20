#include "bluez_object.h"

#define DEV_ARR_SIZE 25

static GDBusProxy *bluez_object_proxy = NULL;
static gchar *device_array[DEV_ARRAY_SIZE];
static gsize num_devices = 0;


/**
 * The owner is responsible for free both the strings and the array itself 
 *
 */
extern  gchar** bluez_object_get_devices(gsize *n_devices)
{
	*n_devices = num_devices;

	gchar **array = g_malloc(sizeof(gchar*) * num_devices);

	for (int i = 0; i < num_devices; i++)
	{
		array[i] = device_array[i];
		device_array[i] = NULL;
	}
	num_devices = 0;

	return array;
}


/**
 * @brief When an interface is added (a device) this callback occurs.
 * 	@param parameters We own this pointer. so we must unreference it when we don't want it anymore
 *
 */
static void on_signal_interfaces_added(GDBusProxy* self, gchar* sender_name, gchar* signal_name, GVariant* parameters, gpointer user_data)
{
	const gchar *temp_object_path = NULL;
	GVariant *interfaces = NULL;

	//! We are extracting the object string (the device address).
	//! We don't need this to return anything except the object_path because
	//! We won't be calling any interfaces yet.
	g_variant_get(parameters, "(&oa{sa{sv}})", &temp_object_path, &interfaces);

	if (num_devices < DEV_ARRAY_SIZE)
	{
		device_array[num_devices] = g_strdup(temp_object_path);
		num_devices += 1;
	}
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
			G_CALLBACK (on_signal_interfaces_added),
			NULL);

	return;

out:
	if (bluez_object_proxy != NULL)
		g_object_unref(bluez_object_proxy);

}
