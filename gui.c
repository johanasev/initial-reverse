#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para mostrar un diálogo emergente
void show_message(GtkWindow *parent, const char *message, GtkMessageType type) {
    GtkWidget *dialog = gtk_message_dialog_new(parent,
        GTK_DIALOG_MODAL,
        type,
        GTK_BUTTONS_OK,
        "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Verifica si el archivo está vacío
int is_file_empty(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    return size == 0;
}

// Invierte las líneas del archivo y las retorna como un string único
char *invert_file(const char *filename, GtkWindow *parent) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        show_message(parent, "✘ Error: No se pudo abrir el archivo.", GTK_MESSAGE_ERROR);
        return NULL;
    }

    if (is_file_empty(file)) {
        fclose(file);
        show_message(parent, "⚠️  Advertencia: El archivo está vacío.", GTK_MESSAGE_WARNING);
        return NULL;
    }

    char **lines = NULL;
    int capacity = 10, count = 0;
    lines = malloc(capacity * sizeof(char *));
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (count >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char *));
        }
        lines[count++] = strdup(line);
    }

    fclose(file);
    free(line);

    size_t total_size = 0;
    for (int i = 0; i < count; i++)
        total_size += strlen(lines[i]);

    char *result = malloc(total_size + 1);
    result[0] = '\0';

    for (int i = count - 1; i >= 0; i--) {
        strcat(result, lines[i]);
        free(lines[i]);
    }

    free(lines);
    return result;
}

// Callback del botón
void on_open_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *text_view = GTK_WIDGET(user_data);
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));

    GtkWidget *dialog = gtk_file_chooser_dialog_new("Seleccionar archivo",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancelar", GTK_RESPONSE_CANCEL,
        "_Abrir", GTK_RESPONSE_ACCEPT,
        NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        char *content = invert_file(filename, GTK_WINDOW(window));

        if (content) {
            GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buffer, content, -1);
            free(content);
        }

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Initial Reverse");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *button = gtk_button_new_with_label("📂 Abrir archivo");
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(button, "clicked", G_CALLBACK(on_open_clicked), text_view);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
