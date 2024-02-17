#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "objecttest.h"

guint a = 0;
guint b = 0;

static gboolean on_handle_add(ObjectTest *interface, 
		GDBusMethodInvocation *invocation,
		guint output,
		gpointer user_data)
{
	gchar *response = NULL;
	response = g_strdup_printf("Output = %d.", a + b);
	object_test_complete_set_a(interface, invocation, output);
	g_print("%s\n", response);
	g_free(response);
	return TRUE;
}

static gboolean on_handle_set_b(ObjectTest *interface, 
		GDBusMethodInvocation *invocation,
		guint received_b,
		gpointer user_data)
{
	gchar *response = NULL;
	response = g_strdup_printf("Set b = %d.", received_b);
	object_test_complete_set_a(interface, invocation, received_b);
	b = received_b;
	g_print("%s\n", response);
	g_free(response);
	return TRUE;
}

static gboolean on_handle_set_a(ObjectTest *interface, 
		GDBusMethodInvocation *invocation,
		guint received_a,
		gpointer user_data)
{
	gchar *response = NULL;
	response = g_strdup_printf("Set a = %d.", received_a);
	object_test_complete_set_a(interface, invocation, received_a);
	a = received_a;
	g_print("%s\n", response);
	g_free(response);
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
			"handle-set-a",
			G_CALLBACK (on_handle_set_a),
			NULL);

	g_signal_connect(interface,
			"handle-set-b",
			G_CALLBACK (on_handle_set_b),
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


int main(void)
{
	g_print("---- Example Application ----\n");
	GMainLoop *loop;

	loop = g_main_loop_new(NULL, FALSE);

	g_bus_own_name(G_BUS_TYPE_SESSION,
			"ti.example",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			NULL,
			on_name_acquired,
			NULL,
			NULL,
			NULL);
	g_main_loop_run(loop);

	return 0;
}
