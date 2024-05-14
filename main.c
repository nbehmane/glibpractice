#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "objecttest.h"
#include "app.h"


int main(void)
{
	g_print("---- Example Application ----\n");
	GMainLoop *loop;

	loop = g_main_loop_new(NULL, FALSE);

	app_register_application();

	g_main_loop_run(loop);

	return 0;
}
