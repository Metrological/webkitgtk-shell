#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static gboolean fullscreenWindow(GtkWidget* widget)
{
    gtk_window_fullscreen(GTK_WINDOW(widget));
    return FALSE;
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    WebKitWebView* webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
    webkit_web_view_load_uri(webView, argc > 1 ? argv[1] : "http://www.webkitgtk.org/");

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webView));
    gtk_widget_show_all(window);

    g_idle_add((GSourceFunc)fullscreenWindow, window);

    gtk_main();

    return 0;
}
