/*
 * This file is generated by gdbus-codegen, do not modify it.
 *
 * The license of this code is the same as for the D-Bus interface description
 * it was derived from. Note that it links to GLib, so must comply with the
 * LGPL linking clauses.
 */

#ifndef __OBJECTTEST_H__
#define __OBJECTTEST_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for ti.example.ObjectTest */

#define TYPE_OBJECT_TEST (object_test_get_type ())
#define OBJECT_TEST(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_TEST, ObjectTest))
#define IS_OBJECT_TEST(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_TEST))
#define OBJECT_TEST_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_OBJECT_TEST, ObjectTestIface))

struct _ObjectTest;
typedef struct _ObjectTest ObjectTest;
typedef struct _ObjectTestIface ObjectTestIface;

struct _ObjectTestIface
{
  GTypeInterface parent_iface;

  gboolean (*handle_add) (
    ObjectTest *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_hello_world) (
    ObjectTest *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_greeting);

  gboolean (*handle_set_numbers) (
    ObjectTest *object,
    GDBusMethodInvocation *invocation,
    GVariant *arg_numbers);

};

GType object_test_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *object_test_interface_info (void);
guint object_test_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void object_test_complete_hello_world (
    ObjectTest *object,
    GDBusMethodInvocation *invocation,
    const gchar *response);

void object_test_complete_set_numbers (
    ObjectTest *object,
    GDBusMethodInvocation *invocation,
    GVariant *response);

void object_test_complete_add (
    ObjectTest *object,
    GDBusMethodInvocation *invocation,
    guint output);



/* D-Bus method calls: */
void object_test_call_hello_world (
    ObjectTest *proxy,
    const gchar *arg_greeting,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean object_test_call_hello_world_finish (
    ObjectTest *proxy,
    gchar **out_response,
    GAsyncResult *res,
    GError **error);

gboolean object_test_call_hello_world_sync (
    ObjectTest *proxy,
    const gchar *arg_greeting,
    gchar **out_response,
    GCancellable *cancellable,
    GError **error);

void object_test_call_set_numbers (
    ObjectTest *proxy,
    GVariant *arg_numbers,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean object_test_call_set_numbers_finish (
    ObjectTest *proxy,
    GVariant **out_response,
    GAsyncResult *res,
    GError **error);

gboolean object_test_call_set_numbers_sync (
    ObjectTest *proxy,
    GVariant *arg_numbers,
    GVariant **out_response,
    GCancellable *cancellable,
    GError **error);

void object_test_call_add (
    ObjectTest *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean object_test_call_add_finish (
    ObjectTest *proxy,
    guint *out_output,
    GAsyncResult *res,
    GError **error);

gboolean object_test_call_add_sync (
    ObjectTest *proxy,
    guint *out_output,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_OBJECT_TEST_PROXY (object_test_proxy_get_type ())
#define OBJECT_TEST_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_TEST_PROXY, ObjectTestProxy))
#define OBJECT_TEST_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_TEST_PROXY, ObjectTestProxyClass))
#define OBJECT_TEST_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_TEST_PROXY, ObjectTestProxyClass))
#define IS_OBJECT_TEST_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_TEST_PROXY))
#define IS_OBJECT_TEST_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_TEST_PROXY))

typedef struct _ObjectTestProxy ObjectTestProxy;
typedef struct _ObjectTestProxyClass ObjectTestProxyClass;
typedef struct _ObjectTestProxyPrivate ObjectTestProxyPrivate;

struct _ObjectTestProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ObjectTestProxyPrivate *priv;
};

struct _ObjectTestProxyClass
{
  GDBusProxyClass parent_class;
};

GType object_test_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (ObjectTestProxy, g_object_unref)
#endif

void object_test_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ObjectTest *object_test_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ObjectTest *object_test_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void object_test_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ObjectTest *object_test_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ObjectTest *object_test_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_OBJECT_TEST_SKELETON (object_test_skeleton_get_type ())
#define OBJECT_TEST_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_TEST_SKELETON, ObjectTestSkeleton))
#define OBJECT_TEST_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_TEST_SKELETON, ObjectTestSkeletonClass))
#define OBJECT_TEST_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_TEST_SKELETON, ObjectTestSkeletonClass))
#define IS_OBJECT_TEST_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_TEST_SKELETON))
#define IS_OBJECT_TEST_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_TEST_SKELETON))

typedef struct _ObjectTestSkeleton ObjectTestSkeleton;
typedef struct _ObjectTestSkeletonClass ObjectTestSkeletonClass;
typedef struct _ObjectTestSkeletonPrivate ObjectTestSkeletonPrivate;

struct _ObjectTestSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ObjectTestSkeletonPrivate *priv;
};

struct _ObjectTestSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType object_test_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (ObjectTestSkeleton, g_object_unref)
#endif

ObjectTest *object_test_skeleton_new (void);


G_END_DECLS

#endif /* __OBJECTTEST_H__ */
