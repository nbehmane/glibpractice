#include "bluez_adapter.h"

/* Globals */
static GDBusProxy *bluez_adapter_proxy = NULL; // this proxy handle needs to be global

/*  
 * @brief XML definition for interface ti.example.Adapter.xml
 *  <node>
 * 	<interface name="ti.example.Adapter">
 * 		<method name="SetPower">
 * 			<arg name="power" direction="in" type="u"/>
 * 		</method>
 * 	</interface>
 * </node>
 */
static gboolean on_handle_set_power(Adapter *interface, 
		GDBusMethodInvocation *invocation,
		guint power,
		gpointer user_data)
{
	g_print("Adapter: power set to %d\n", power);

	adapter_complete_set_power(interface, invocation);
	return TRUE;
}


/**** SIGNAL HANDLERS START ****/
static void on_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data)
{
	g_print("Adapter: Signal\n");
}


static void on_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data)
{
	g_print("Adapter: Properties Changed\n");
}
/**** SIGNAL HANDLERS END ****/


/* @brief Prints the app ID to find in D-feet.
 *
 */
static void print_proxy(GDBusProxy *proxy)
{
	gchar *name_owner;
	name_owner = g_dbus_proxy_get_name_owner(proxy);
	g_print("Owner: %s\n", name_owner);
}

/**
 * To be placed in on_name_aquired by main app
 *
 *
 *
 */
extern void bluez_adapter_proxy_setup(GDBusConnection *connection)
{
	Adapter *adapter_interface = NULL;
	GError *error = NULL;

	/* Setting up bluez adapter interface ti.example.Adapter */
	adapter_interface = adapter_skeleton_new();

	g_signal_connect(adapter_interface,
			"handle-set-power",
			G_CALLBACK (on_handle_set_power),
			NULL);

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON (adapter_interface), 
			connection, 
			"/ti/example/Adapter",
			&error);

	// Adapter interface proxy.
	bluez_adapter_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"org.bluez",
			"/org/bluez/hci0", // TODO: make this dynamic. Select the controller during runtime.
			"org.bluez.Adapter1",
			NULL,
			&error);	
	
	if (bluez_adapter_proxy == NULL)
	{
		g_printerr("Error in creating proxy: %s\n", error->message);
		g_error_free(error);
		goto out;
	}

	/**** SIGNAL CONNECTS START ****/
	g_signal_connect(bluez_adapter_proxy,
			"g-properties-changed",
			G_CALLBACK (on_properties_changed),
			NULL);

	g_signal_connect(bluez_adapter_proxy,
			"g-signal",
			G_CALLBACK(on_signal),
			NULL);
	/**** SIGNAL CONNECTS END ****/


	// Print the owner ID of the proxy object.
	print_proxy(bluez_adapter_proxy);

	return;

out:
	if (bluez_adapter_proxy != NULL)
		g_object_unref(bluez_adapter_proxy);
}

