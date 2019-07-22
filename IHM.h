#include <gtk/gtk.h>

void closeWindow(GtkWidget *widget, gpointer window);
void openWindow(GtkWidget *widget, gpointer window);
static void get_combo_box_value(GtkWidget *widget, GtkComboBoxText *combo_box[2]);
static void get_calendar_values(GtkWidget *widget, GtkCalendar *calendar[2]);
static void manage_list_reservation(GtkWidget *widget, GtkListStore *list);
static void manage_list_revision(GtkListStore *list);
static void manage_list_history(GtkListStore *list);
static void get_add_reservation_entry(GtkWidget *widget, GtkWidget *entry[3]);
static void get_return_form_values( GtkWidget *widget, GtkWidget *entry[2]);
static void get_search_client_form_values( GtkWidget *widget, GtkWidget *entry[2]);
int main_ihm (int argc, char ** argv);
