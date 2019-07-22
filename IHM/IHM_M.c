#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#define DIM 100


typedef struct variable {
  char***voiture_det;
  GtkWidget*label1[11];
  int i;
}variable;

void InitVar(variable*var) {
  var->i = 0;
  var->voiture_det = (char***) malloc(sizeof(char**)*DIM); // Nombre de voiture + 1 (car le nombre de voiture commence a 1)
  for(int j = 0; j<DIM;j++) {
    var->voiture_det[j] = (char**) malloc(sizeof(char*)*11); // Nombre d'attribut
    for(int i = 0; i<11; i++) {
      var->voiture_det[j][i] = (char*) malloc(sizeof(char)*20); // Nombre de caractère
    }
  }
  for(int i=0; i<=11; i++)
  var->label1[i] = NULL;
}


static void cb_ok (GtkWidget * p_wid, gpointer p_data)
{
  GtkWidget   * p_dialog  = NULL;
  const char  * p_text    = p_data;


  if (p_text != NULL)
  {
    p_dialog = gtk_message_dialog_new (
      NULL,
      GTK_DIALOG_MODAL,
      GTK_MESSAGE_INFO,
      GTK_BUTTONS_OK,
      p_text
    );


    gtk_dialog_run (GTK_DIALOG (p_dialog));
    gtk_widget_destroy (p_dialog);
  }
}


static void cb_quit (GtkWidget * p_wid, gpointer p_data)
{
  gtk_main_quit ();
}


void print_hello(GtkWidget*widget, gpointer data) {

  variable*var = data;
  var->i = atoi(gtk_widget_get_tooltip_text(widget)); // pour récuperer la voiture sur laquelle on clique
}



void edit_label(GtkWidget*widget, gpointer data) {

  variable*var = data;

  var->i = atoi(gtk_widget_get_tooltip_text(widget)); // pour récuperer la voiture sur laquelle on clique

  // Contient les attributs

  var->voiture_det[var->i][0] = "88-MFL-88"; //plate number
  var->voiture_det[var->i][1] = "A";  //category
  var->voiture_det[var->i][2] = "175862"; //km
  var->voiture_det[var->i][3] = "Citröen"; //brand
  var->voiture_det[var->i][4] = "C5"; // model
  var->voiture_det[var->i][5] = "Manuel"; // gearbox
  var->voiture_det[var->i][6] = "2016"; // years
  var->voiture_det[var->i][7] = "plate"; // revision
  var->voiture_det[var->i][8] = "30€"; // daily price
  var->voiture_det[var->i][9] = "11999€"; // selling price
  var->voiture_det[var->i][10] = "20999€"; // purchase price


  // Change le contenu du label

  gtk_label_set_text(GTK_LABEL(var->label1[0]), var->voiture_det[var->i][0]); // Remplace le label plate number
  gtk_label_set_text(GTK_LABEL(var->label1[1]), var->voiture_det[var->i][1]); // Remplace le label category
  gtk_label_set_text(GTK_LABEL(var->label1[2]), var->voiture_det[var->i][2]); // Remplace le label km
  gtk_label_set_text(GTK_LABEL(var->label1[3]), var->voiture_det[var->i][3]); // Remplace le label brand
  gtk_label_set_text(GTK_LABEL(var->label1[4]), var->voiture_det[var->i][4]); // Remplace le label model
  gtk_label_set_text(GTK_LABEL(var->label1[5]), var->voiture_det[var->i][5]); // Remplace le label gearbox
  gtk_label_set_text(GTK_LABEL(var->label1[6]), var->voiture_det[var->i][6]); // Remplace le label years
  //gtk_label_set_text(GTK_LABEL(var->label1[7]), "Revision"); // Remplace le label revision
  gtk_label_set_text(GTK_LABEL(var->label1[8]), var->voiture_det[var->i][8]); // Remplace le label daily
  gtk_label_set_text(GTK_LABEL(var->label1[9]), var->voiture_det[var->i][9]); // Remplace le label selling
  gtk_label_set_text(GTK_LABEL(var->label1[10]), var->voiture_det[var->i][10]); // Remplace le label purchase

}

void attributVehicule(variable*var, GtkBuilder*p_builder) {

  // Attribut le label a son identifiant

  var->label1[0] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_plate_number")); // Initialisation du label plate number dans véhicule
  var->label1[1] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_category")); // Initialisation du label plate number dans véhicule
  var->label1[2] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_km")); // Initialisation du label plate number dans véhicule
  var->label1[3] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_bran")); // Initialisation du label plate number dans véhicule
  var->label1[4] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_mode")); // Initialisation du label plate number dans véhicule
  var->label1[5] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_gearbox")); // Initialisation du label plate number dans véhicule
  var->label1[6] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_years")); // Initialisation du label plate number dans véhicule
  var->label1[7] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_revision")); // Initialisation du label plate number dans véhicule
  var->label1[8] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_daily")); // Initialisation du label plate number dans véhicule
  var->label1[9] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_selling")); // Initialisation du label plate number dans véhicule
  var->label1[10] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_purchase")); // Initialisation du label plate number dans véhicule

}



void GenerateVehicule(variable*var, GtkBuilder*p_builder ) {
    GtkWidget*box_car = NULL; // La GtkBox contenant toute les voitures
    GtkWidget*car[DIM]; // Correspond au voiture a afficher, elle est ajouté dans box_car
    GtkWidget*tab[2];// Contient le contenu de GtkBox  de véhicule
    char number[4]; // Recupere le nombre de voiture pour le concaténer

  box_car = GTK_WIDGET(gtk_builder_get_object(p_builder, "box_car")); // Permet de définir la GtkBox de véhicule

  for(int i=1; i<100; i++) { // Boucle selon le nombre de voiture

    sprintf(number,"%d",i);

    car[i] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Param 1 : orientation, param 2 : nb de pixel qui separe les elements

    tab[0] =gtk_image_new_from_file ("Citroen.png"); // Initialise le logo de la marque
    tab[1] = gtk_label_new("C5"); // Initialise le modele de voiture
    tab[2] =  gtk_button_new_with_label ("Show"); // Initialise le bouton

    gtk_widget_set_tooltip_text(tab[2], number);

    gtk_box_pack_start (GTK_BOX(car[i]),tab[0],TRUE,TRUE,1); // ajoute a la gtkBox le logo
    gtk_box_pack_start (GTK_BOX(car[i]),tab[1],TRUE,TRUE,1); // ajoute a la gtkBox le modele
    gtk_box_pack_start (GTK_BOX(car[i]),tab[2],TRUE,TRUE,1); // ajoute a la gtkBox le bouton

    gtk_container_add(GTK_CONTAINER(box_car), car[i]); // Ajoute toutes les voitures a afficher dans la GtkBox scrollable

    g_signal_connect(G_OBJECT (tab[2]), "clicked", G_CALLBACK(print_hello), var); // vérifie que le clic sur le bouton show fonctionne
    g_signal_connect(G_OBJECT (tab[2]), "clicked", G_CALLBACK(edit_label), var); // vérifie que le clic sur le bouton show fonctionne
  }

}


int main (int argc, char ** argv)
{
  GtkBuilder  *  p_builder   = NULL;
  GError      *  p_err       = NULL;

  variable*var; // Structure affichant les details de chaque voiture

  /* Initialisation de GTK+ */
  gtk_init (& argc, & argv);

  /* Creation d'un nouveau GtkBuilder */
  p_builder = gtk_builder_new ();


  if (p_builder != NULL)
  {

    /* Chargement du XML dans p_builder */
    gtk_builder_add_from_file (p_builder, "IHM.glade", & p_err);

    var = (variable*) malloc(sizeof(variable));
    InitVar(var);

    GenerateVehicule(var,p_builder);

    attributVehicule(var,p_builder);


    if (p_err == NULL)
    {
      /* 1.- Recuparation d'un pointeur sur la fenetre. */
      GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
        p_builder, "PROJET"
      );


      gtk_widget_show_all (p_win);
      gtk_main ();

    }
    else
    {
      /* Affichage du message d'erreur de GTK+ */
      g_error ("%s", p_err->message);
      g_error_free (p_err);
    }
  }

  printf("Fermeture de la fenetre.\n");
  gtk_main_quit();
  return EXIT_SUCCESS;
}
