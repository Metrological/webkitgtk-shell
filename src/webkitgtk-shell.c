#include <gtk/gtk.h>
#include <stdlib.h>
#include <webkit2/webkit2.h>

static gboolean fullscreenWindow(GtkWidget* widget)
{
    gtk_window_fullscreen(GTK_WINDOW(widget));
    return FALSE;
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    const char* uri = getenv("WEBKITGTK_SHELL_URI");
    if (!uri && argc > 1)
        uri = argv[1];
    if (!uri)
        uri = "http://www.webkitgtk.org/";

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    WebKitWebView* webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    WebKitSettings* settings = webkit_web_view_get_settings(webView);
    webkit_settings_set_enable_write_console_messages_to_stdout(settings, TRUE);
    webkit_settings_set_enable_accelerated_2d_canvas(settings, TRUE);

    webkit_web_view_load_uri(webView, uri);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webView));
    gtk_widget_show_all(window);

    g_idle_add((GSourceFunc)fullscreenWindow, window);

    gtk_main();

    return 0;
}
