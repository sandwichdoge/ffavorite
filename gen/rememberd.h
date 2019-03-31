/*
 * Generated by gdbus-codegen 2.50.3. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __REMEMBERD_H__
#define __REMEMBERD_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.remember */

#define REMEMBER_DAEMON_TYPE_ (remember_daemon__get_type ())
#define REMEMBER_DAEMON_(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), REMEMBER_DAEMON_TYPE_, RememberDaemon))
#define REMEMBER_DAEMON_IS_(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), REMEMBER_DAEMON_TYPE_))
#define REMEMBER_DAEMON__GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), REMEMBER_DAEMON_TYPE_, RememberDaemonIface))

struct _RememberDaemon;
typedef struct _RememberDaemon RememberDaemon;
typedef struct _RememberDaemonIface RememberDaemonIface;

struct _RememberDaemonIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_access) (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation,
    guint arg_index);

  gboolean (*handle_add) (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_filename);

  gboolean (*handle_list) (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_rm) (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_filename);

  void (*mysignal) (
    RememberDaemon *object,
    gint arg_ret);

};

GType remember_daemon__get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *remember_daemon__interface_info (void);
guint remember_daemon__override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void remember_daemon__complete_list (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation,
    const gchar *files);

void remember_daemon__complete_access (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation,
    const gchar *filename);

void remember_daemon__complete_add (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation);

void remember_daemon__complete_rm (
    RememberDaemon *object,
    GDBusMethodInvocation *invocation);



/* D-Bus signal emissions functions: */
void remember_daemon__emit_mysignal (
    RememberDaemon *object,
    gint arg_ret);



/* D-Bus method calls: */
void remember_daemon__call_list (
    RememberDaemon *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean remember_daemon__call_list_finish (
    RememberDaemon *proxy,
    gchar **out_files,
    GAsyncResult *res,
    GError **error);

gboolean remember_daemon__call_list_sync (
    RememberDaemon *proxy,
    gchar **out_files,
    GCancellable *cancellable,
    GError **error);

void remember_daemon__call_access (
    RememberDaemon *proxy,
    guint arg_index,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean remember_daemon__call_access_finish (
    RememberDaemon *proxy,
    gchar **out_filename,
    GAsyncResult *res,
    GError **error);

gboolean remember_daemon__call_access_sync (
    RememberDaemon *proxy,
    guint arg_index,
    gchar **out_filename,
    GCancellable *cancellable,
    GError **error);

void remember_daemon__call_add (
    RememberDaemon *proxy,
    const gchar *arg_filename,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean remember_daemon__call_add_finish (
    RememberDaemon *proxy,
    GAsyncResult *res,
    GError **error);

gboolean remember_daemon__call_add_sync (
    RememberDaemon *proxy,
    const gchar *arg_filename,
    GCancellable *cancellable,
    GError **error);

void remember_daemon__call_rm (
    RememberDaemon *proxy,
    const gchar *arg_filename,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean remember_daemon__call_rm_finish (
    RememberDaemon *proxy,
    GAsyncResult *res,
    GError **error);

gboolean remember_daemon__call_rm_sync (
    RememberDaemon *proxy,
    const gchar *arg_filename,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define REMEMBER_DAEMON_TYPE__PROXY (remember_daemon__proxy_get_type ())
#define REMEMBER_DAEMON__PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), REMEMBER_DAEMON_TYPE__PROXY, RememberDaemonProxy))
#define REMEMBER_DAEMON__PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), REMEMBER_DAEMON_TYPE__PROXY, RememberDaemonProxyClass))
#define REMEMBER_DAEMON__PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), REMEMBER_DAEMON_TYPE__PROXY, RememberDaemonProxyClass))
#define REMEMBER_DAEMON_IS__PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), REMEMBER_DAEMON_TYPE__PROXY))
#define REMEMBER_DAEMON_IS__PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), REMEMBER_DAEMON_TYPE__PROXY))

typedef struct _RememberDaemonProxy RememberDaemonProxy;
typedef struct _RememberDaemonProxyClass RememberDaemonProxyClass;
typedef struct _RememberDaemonProxyPrivate RememberDaemonProxyPrivate;

struct _RememberDaemonProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  RememberDaemonProxyPrivate *priv;
};

struct _RememberDaemonProxyClass
{
  GDBusProxyClass parent_class;
};

GType remember_daemon__proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (RememberDaemonProxy, g_object_unref)
#endif

void remember_daemon__proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
RememberDaemon *remember_daemon__proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
RememberDaemon *remember_daemon__proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void remember_daemon__proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
RememberDaemon *remember_daemon__proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
RememberDaemon *remember_daemon__proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define REMEMBER_DAEMON_TYPE__SKELETON (remember_daemon__skeleton_get_type ())
#define REMEMBER_DAEMON__SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), REMEMBER_DAEMON_TYPE__SKELETON, RememberDaemonSkeleton))
#define REMEMBER_DAEMON__SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), REMEMBER_DAEMON_TYPE__SKELETON, RememberDaemonSkeletonClass))
#define REMEMBER_DAEMON__SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), REMEMBER_DAEMON_TYPE__SKELETON, RememberDaemonSkeletonClass))
#define REMEMBER_DAEMON_IS__SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), REMEMBER_DAEMON_TYPE__SKELETON))
#define REMEMBER_DAEMON_IS__SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), REMEMBER_DAEMON_TYPE__SKELETON))

typedef struct _RememberDaemonSkeleton RememberDaemonSkeleton;
typedef struct _RememberDaemonSkeletonClass RememberDaemonSkeletonClass;
typedef struct _RememberDaemonSkeletonPrivate RememberDaemonSkeletonPrivate;

struct _RememberDaemonSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  RememberDaemonSkeletonPrivate *priv;
};

struct _RememberDaemonSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType remember_daemon__skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (RememberDaemonSkeleton, g_object_unref)
#endif

RememberDaemon *remember_daemon__skeleton_new (void);


G_END_DECLS

#endif /* __REMEMBERD_H__ */
