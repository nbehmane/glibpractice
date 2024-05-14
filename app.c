
/**
 * @brief All application specific functions (signal handlers, interface definitions, etc.)
 * 	should go into a .c file. These functions should not be called directly (hence they're static).
 * 	The only exposed function to main.c should be <object>_register_<object>. In this case
 * 	it's app_register_application.
 *
 *
 */


#include "app.h"

guint32 a = 0;
guint32 b = 0;

static gboolean on_handle_add(ObjectTest *interface, 
		GDBusMethodInvocation *invocation,
		guint output,
		gpointer user_data)
{
	gchar *response = NULL;
	response = g_strdup_printf("Output = %d.", a + b);
	object_test_complete_add(interface, invocation, output);
	g_print("%s\n", response);
	g_free(response);
	return TRUE;
}

static gboolean on_handle_set_numbers(ObjectTest *interface, 
		GDBusMethodInvocation *invocation,
		GVariant *numbers,
		gpointer user_data)
{
	gsize n_elements = 0; 
	gconstpointer elements = g_variant_get_fixed_array(numbers, &n_elements, sizeof(guint32));

	const guint32 *array_numbers = elements;

	a = array_numbers[0];
	b = array_numbers[1];

	g_print("a: %d | b: %d\n", a, b);
	object_test_complete_set_numbers(interface, invocation, numbers);
	return TRUE;
}

static gboolean on_handle_hello_world(ObjectTest *interface, 
		GDBusMethodInvocation *invocation,
		const char *greeting,
		gpointer user_data)
{
	gchar *response = NULL;
	response = g_strdup_printf("Hello world %s!!", greeting);
	object_test_complete_hello_world(interface, invocation, response);
	g_print("%s\n", response);
	g_free(response);
	return TRUE;
}

static void on_name_acquired(GDBusConnection *connection, 
		const gchar *name, 
		gpointer user_data)
{
	ObjectTest *interface = NULL;
	GError *error = NULL;

	interface = object_test_skeleton_new();
	g_signal_connect(interface,
			"handle-hello-world",
			G_CALLBACK (on_handle_hello_world),
			NULL);

	g_signal_connect(interface,
			"handle-set-numbers",
			G_CALLBACK (on_handle_set_numbers),
			NULL);

	g_signal_connect(interface,
			"handle-add",
			G_CALLBACK (on_handle_add),
			NULL);

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON (interface), 
			connection, 
			"/ti/example/ObjectTest",
			&error);
}

extern void app_register_application()
{
	g_bus_own_name(G_BUS_TYPE_SESSION,
			"ti.example",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			NULL,
			on_name_acquired,
			NULL,
			NULL,
			NULL);
}




