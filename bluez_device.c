#include "bluez_device.h"

static void on_device_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data);

static void on_device_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data);

	
typedef struct _device_proxy
{
	gchar *device_path;
	GDBusProxy *proxy;
} DeviceProxy;

static DeviceProxy *device_proxies[MAX_CONNECTIONS] = { NULL };
static int num_proxies = 0;


extern GDBusProxy **bluez_device_get_proxies()
{
	return NULL;
}



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

extern void bluez_device_connect(const gchar *object_path)
{
	//1. Create the proxy object for the object path and store it somewhere. 
	//2. Setup the signal handlers for the proxy object so we can manage the connection
	//3. return
	return;
}

extern void bluez_device_disconnect(const gchar *object_path)
{
	//1. grab the correct proxy object.
	//2. disconnect
	//3. remove it from the list of device proxies.
	return;
}



/**** SIGNAL HANDLERS START ****/
static void on_device_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data)
{
#ifdef DEBUG
	g_print("Device: Signal\n");
#endif
}


static void on_device_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data)
{
#ifdef DEBUG
	g_print("Device: Properties Changed\n");
#endif
}





