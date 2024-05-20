
/**
 * @brief All application specific functions (signal handlers, interface definitions, etc.)
 * 	should go into a .c file. These functions should not be called directly (hence they're static).
 * 	The only exposed function to main.c should be <object>_register_<object>. In this case
 * 	it's app_register_application.
 *
 *
 */
#include "app.h"

/*  
 * @brief XML definition for interface ti.example.App.xml
 *  <node>
 * 	<interface name="ti.example.App">
 * 		<method name="Scan">
 * 			<arg name="time" direction="in" type="u"/>
 * 		</method>
 * 	</interface>
 * </node>
 */
static gboolean on_handle_scan(App *interface, 
		GDBusMethodInvocation *invocation,
		guint s,
		gpointer user_data)
{

	//! Make proxy method call to Adapter1.StartDiscovery
	bluez_adapter_scan(s);
	app_complete_scan(interface, invocation);
	return TRUE;
}


/*  
 * @brief XML definition for interface ti.example.App.xml
 *  <node>
 * 	<interface name="ti.example.App">
 * 		<method name="GetScanResults">
 * 		</method>
 * 	</interface>
 * </node>
 */
static gboolean on_handle_get_scan_results(App *interface, 
		GDBusMethodInvocation *invocation,
		gpointer user_data)
{
	gchar **devices = NULL;
	gsize num_devices = 0;
	devices = bluez_object_get_devices(&num_devices);

	for (int i = 0; i < num_devices; i++)
		g_print("%s\n", devices[i]);


	app_complete_get_scan_results(interface, invocation, devices);
	return TRUE;
}



static void on_name_acquired(GDBusConnection *connection, 
		const gchar *name, 
		gpointer user_data)
{
	App *app_interface = NULL;
	GError *error = NULL;

	/* Setting up AppInfo interface */
	app_interface = app_skeleton_new();

	g_signal_connect(app_interface,
			"handle-scan",
			G_CALLBACK (on_handle_scan),
			NULL);

	g_signal_connect(app_interface,
			"handle-get-scan-results",
			G_CALLBACK (on_handle_get_scan_results),
			NULL);

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON (app_interface), 
			connection, 
			"/ti/example/Application",
			&error);
	
	bluez_adapter_proxy_init(connection);
	bluez_object_proxy_init(connection);

}


extern void app_register_application()
{
	// This is the MAIN application session.
	g_bus_own_name(G_BUS_TYPE_SESSION,
			"ti.example",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			NULL,
			on_name_acquired,
			NULL,
			NULL,
			NULL);

}

