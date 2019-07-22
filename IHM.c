#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"
#include "smartFunctions.h"



/**
 * Fonction qui permet de fermet une fenêtre pop-up
 * @param widget [description]
 * @param window [description]
 */
void closeWindow(GtkWidget *widget, gpointer window)
{
        gtk_widget_hide(GTK_WIDGET(window)); //Cache la fenêtre passée en paramêtre
}

/**
 * Fonction qui permet d'ouvrir une fenêtre en pop-up
 * @param widget [description]
 * @param window [description]
 */
void openWindow(GtkWidget *widget, gpointer window)
{
        gtk_widget_show_all(GTK_WIDGET(window)); //Permet d'afficher la fenêtre
}

static void get_combo_box_value(GtkWidget *widget, GtkComboBoxText *combo_box[2])
{
  gchar* return_text[2];
  for(int i=0; i<2; i++)
  {
    return_text[i] = gtk_combo_box_text_get_active_text(combo_box[i]);
    printf("%s\n", return_text[i]);
  }
}
/**
 * Fonction qui permet de récupérer les dates du calendrier lors de l'ajout
 * d'une nouvelle réservation
 *
 * @param widget widget sur lequel on clique
 * @param [calendar] un tableau de deux calendrier correspondant au début et a la fin de la réservation
 */
static void get_calendar_values(GtkWidget *widget, GtkCalendar *calendar[2])
{
        guint year[2]; //On crée un tableau de deux années permettant de stocker le résultat des deux calendriers
        guint month[2]; //On crée un tableau de deux mois permettant de stocker le résultat des deux calendriers
        guint day[2]; //On crée un tableau de deux jours permettant de stocker le résultat des deux calendriers
        printf("DATES DE RESERVATION \n");
        for(int i=0; i<2; i++) //On parcours le tableau de calendrier passé en paramêtre
        {
                gtk_calendar_get_date(calendar[i],&year[i],&month[i],&day[i]); //On récupère les valeurs qui sont stockées dans year, month, day
                printf("%d\n", year[i]);
                printf("%d\n", month[i]+1);
                printf("%d\n", day[i]);
                printf("------------\n");
        }
}

/**
 * Fonction qui gère le contenu de la liste de reservation
 * @param list [description]
 */
static void manage_list_reservation(GtkWidget *widget, GtkListStore *list)
{
  GtkTreeIter iter; //On crée un itérateur
  gtk_list_store_clear(list); //On vide la liste
  for(int i=0; i<10; i++)
  {
    gtk_list_store_append(list, &iter); //On crée une nouvelle ligne vide a notre liste
    gtk_list_store_set(list, &iter, 0, 256, 1, 696969,-1); //Et on l'initailise
  }
}

/**
 * Fonction qui gère le contenu de la liste de reservation
 * @param list [description]
 */
static void manage_list_revision(GtkListStore *list)
{
  GtkTreeIter iter; //On crée un itérateur
  gtk_list_store_clear(list); //On vide la liste
  for(int i=0; i<10; i++)
  {
    gtk_list_store_append(list, &iter); //On crée une nouvelle ligne vide a notre liste
    gtk_list_store_set(list, &iter, 0,"69/69/6969",-1); //Et on l'intialise
  }
}

/**
 * Fonction qui gère le contenu de la list d'historique
 * @param list [description]
 */
static void manage_list_history(GtkListStore *list)
{
  GtkTreeIter iter; //On crée un itérateur
  gtk_list_store_clear(list); //On vide la liste
  for(int i=0; i<10; i++)
  {
    gtk_list_store_append(list, &iter); //On crée une nouvelle ligne vide a notre liste
    gtk_list_store_set(list, &iter, 0,20,1,30,2,"fr-236-pd",3,360,4,"07/02/2020", -1); //Et on l'initialise

  }
}

/**
 * Fonction qui permet de récupérer la valeur des différents champs de formulaire
 * du pop-up "Add Reservation "
 * @param widget [description]
 * @param [name] [description]
 */
static void get_add_reservation_entry(GtkWidget *widget, GtkWidget *entry[3])
{
        const gchar *entry_text[3]; //On crée un tableau de 3 chaines dans lequel sera stocké les valeurs des champs
        printf("INFORMATION CLIENT \n");
        for(int i=0; i<3; i++) //On parcours le tableau d'entry passé en paramêtre
        {
                entry_text[i] = gtk_entry_get_text (GTK_ENTRY (entry[i])); //On récupère la valeur des différents champs
                printf ("Entry contents: %s\n", entry_text[i]);
        }
}

/**
 * Fonction qui permet de récupérer la valeur des différents champs de formulaire
 * du pop-up "Return Vehicule "
 * @param widget [description]
 * @param [name] [description]
 */
static void get_return_form_values( GtkWidget *widget, GtkWidget *entry[2] )
{
        const gchar *entry_text[2]; //On crée un tableau de 2 chaines dans lequel sera stocké les valeurs des champs
        for(int i=0; i<2; i++) //On parcours le tableau d'entry passé en paramètre
        {
                entry_text[i] = gtk_entry_get_text (GTK_ENTRY (entry[i])); //On récupère la valeur des différents champs parcourus
                printf ("Entry contents: %s\n", entry_text[i]);
        }
}

/**
 * Fonction qui permet de récupérer la valeur des différents champs de formulaire
 * de notre pop-up "Search Client"
 * @param widget [description]
 * @param [name] [description]
 */
static void get_search_client_form_values( GtkWidget *widget, GtkWidget *entry[2] )
{
        const gchar *entry_text[2]; //On crée un tableau de 2 chaines dans lequel sera stocké les valeurs des champs
        for(int i=0; i<2; i++) //On parcours le tableau d'entry passé en parmètre
        {
                entry_text[i] = gtk_entry_get_text (GTK_ENTRY (entry[i]));
                printf ("Entry contents: %s\n", entry_text[i]);
        }
}



int main (int argc, char ** argv)
{
        GtkBuilder  *  p_builder   = NULL;
        GError      *  p_err       = NULL;

        GObject *button_sell_car;

        //initialisation des maillon
        maillon *car, *customers, *reservation, *resultcar;
        customers = initializeClients("files/clients.csv");
        reservation = initializeReservation("files/booking.csv", customers);
        car = initializeCar("files/vehicules.csv", reservation);

        //test console
        int prediction;
        date d,e;
        d.day = 3;
        d.year = 2019;
        d.month = 10;
        d.hour = 9;

        e.day = 23;
        e.year = 2019;
        e.month = 10;
        e.hour = 9;
        prediction = milePrediction(&reservation , d, e);
        int h;
        h = calculusDate(d,e);
        printf("Prediction %d pour %d jours \n", prediction ,h);

        /* Variables pour la fenetre de retour vehicule */
        char returnFormEntry[20];
        GtkEntry *return_form[2];
        GObject *button_return_vehicule;
        GObject *button_validate_return_vehicule;
        GObject *button_cancel_return_vehicule;
        GObject *reservation_list_return_button;
        GtkComboBoxText *reservation_dropdown[2];
        char comboBox_id[30];

        /* Variables pour l'ajout de réservation */
        char addReservationFormEntry[30];
        GtkEntry *addReservation_form[3];
        GObject *button_validate_add_reservation;
        GObject *button_cancel_add_reservation;
        GObject *button_add_reservation;
        GObject *button_search_reservation;


        /* Variables pour la recherche de client */
        char searchFormEntry[20];
        GtkEntry *search_form[2];
        GObject *button_validate_search_client;
        GObject *button_search_stop;

        /* Variables pour le calendrier principal */
        GObject *calendar[31];
        char joursCalendrier[20];
        GtkComboBoxText *date_changer[2];
        char char_date_changer[20];
        GObject *button_validate_date_changer;


        /* Variables pour le calendrier de réservation*/
        GtkCalendar *calendar_reservation[2];
        char calendar_reservation_name[25];

        char compteur[20];



        /* Initialisation de GTK+ */
        gtk_init (&argc, &argv);

        /* Creation d'un nouveau GtkBuilder */
        p_builder = gtk_builder_new ();

        if (p_builder != NULL)
        {
                /* Chargement du XML dans p_builder */
                gtk_builder_add_from_file (p_builder, "IHM.glade", &p_err);

                if (p_err == NULL)
                {
                        /* Permet d'intialiser le pop_up d'ajout de réservation */
                        GtkWidget * pop_up_reservation_add = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "reservation-add"
                                );
                        /* Permet d'initailiser le pop_up de recherche client*/
                        GtkWidget * pop_up_client_search = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "client_search"
                                );

                        /* Permet d'initailiser la fenêtre principale du projet */
                        GtkWidget * main_win = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "PROJET"
                                );

                        /* Permet d'initailiser la fenetre d'affichage des réservation pour les différents jours */
                        GtkWidget * reservation_list_window = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "reservation_list_window"
                                );

                        /* Permet d'initailiser la fenetre de retour vehicule */
                        GtkWidget * return_vehicule = (GtkWidget * ) gtk_builder_get_object (
                                p_builder, "return_vehicule"
                                );


                        /* Permet d'initialiser les différents entryForm de notre fenetre
                           de retour vehicule, d'intialiser le bouton de validation et de faire
                           appel a la fonction correspondante */
                        for(int j=0; j<2; j++)
                        {
                                sprintf(compteur, "%d",j); //on crée une chaine de caractère contenant le compteur
                                strcpy(returnFormEntry, "return_form"); //on concatène les deux chaines
                                strcat(returnFormEntry, compteur); //on concatène les deux chaines
                                return_form[j]=(GtkEntry*)gtk_builder_get_object(p_builder, returnFormEntry); //on récupère les entryform de Glade
                        }
                        button_validate_return_vehicule = gtk_builder_get_object(p_builder, "return_validate_button"); //On initialise le boutton de validation
                        g_signal_connect(button_validate_return_vehicule, "clicked", G_CALLBACK(get_return_form_values), return_form); //on appelle la fonction au clic


                        /* Permet d'initialiser les différents entryForm de notre fenetre
                           de retour de réservation ainsi que les calendriers de réservation,
                           d'intialiser le bouton de validation et de faire appel a la fonction
                           correspondante */
                        for(int x=0; x<3; x++)
                        {
                                sprintf(compteur, "%d", x); //on crée une chaine de caractère contenant le compteur
                                strcpy(addReservationFormEntry, "add_reserv_entry"); //on concatène les deux chaines
                                strcat(addReservationFormEntry, compteur); //on concatène les deux chaines
                                addReservation_form[x] = (GtkEntry*)gtk_builder_get_object(p_builder, addReservationFormEntry); //on récupère les entryform de Glade
                        }
                        for(int w=0; w<2; w++)
                        {
                                sprintf(compteur, "%d",w); //on crée une chaine de caractère contenant le compteur
                                strcpy(calendar_reservation_name, "calendar_reservation"); //on concatène les deux chaines
                                strcat(calendar_reservation_name, compteur); //on concatène les deux chaines
                                calendar_reservation[w]=(GtkCalendar*)gtk_builder_get_object(p_builder, calendar_reservation_name); //on récupère les entryform de Glade

                                strcpy(comboBox_id, "reservation_add_dropdown"); //On crée une chaine de caractère contenant le compteur
                                strcat(comboBox_id, compteur); //On concatène la chaine avec le compteur
                                reservation_dropdown[w]=(GtkComboBoxText*)gtk_builder_get_object(p_builder, comboBox_id); //on récupère le combo_box

                                strcpy(char_date_changer, "date_changer"); //On crée une chane de caractère contenant le compteur
                                strcat(char_date_changer, compteur); //On concatène la chaine avec le compteur
                                date_changer[w] = (GtkComboBoxText*)gtk_builder_get_object(p_builder, char_date_changer); //on récupère le combo_box
                        }

                        button_validate_add_reservation = gtk_builder_get_object(p_builder, "add_reservation_validate_button"); //On initialise le boutton de validation
                        g_signal_connect (button_validate_add_reservation, "clicked", G_CALLBACK(get_add_reservation_entry), addReservation_form); //on appelle la fonction des entryForm au clic
                        g_signal_connect (button_validate_add_reservation, "clicked", G_CALLBACK (get_combo_box_value),reservation_dropdown); //on appelle la fonction de calendrier au clic
                        g_signal_connect (button_validate_add_reservation, "clicked", G_CALLBACK (get_calendar_values),calendar_reservation); //on appelle la fonction de calendrier au clic


                        button_validate_date_changer = gtk_builder_get_object(p_builder, "validate_date_changer"); //On initialise le boutton de validation
                        g_signal_connect(button_validate_date_changer, "clicked", G_CALLBACK(get_combo_box_value), date_changer); //On appelle la fonction de récupération de combo_box lors du clic souris


                        /* Permet d'initialiser les différents entryForm de notre fenetre
                           de recherche client d'intialiser le bouton de validation et de faire
                           appel a la fonction correspondante */
                        for(int z=0; z<2; z++)
                        {
                                sprintf(compteur, "%d", z); //on crée une chaine de caractère contenant le compteur
                                strcpy(searchFormEntry, "search_entry"); //on concatène les deux chaines
                                strcat(searchFormEntry, compteur); //on concatène les deux chaines
                                search_form[z] = (GtkEntry*)gtk_builder_get_object(p_builder, searchFormEntry); //on récupère les entryform de Glade
                        }
                        button_validate_search_client = gtk_builder_get_object(p_builder, "search_client_validate_button"); //On intialise le bouton de validation
                        g_signal_connect(button_validate_search_client, "clicked", G_CALLBACK(get_search_client_form_values), search_form); //On appelle la fonction au clic sur le bouton


                        /* Gestion des boutons */
                        button_cancel_add_reservation = gtk_builder_get_object(p_builder, "add_reservation_cancel_butto"); //Récupération du bouton d'annulation d'ajout de réservation
                        g_signal_connect (button_cancel_add_reservation, "clicked", G_CALLBACK (closeWindow), G_OBJECT(pop_up_reservation_add)); //On y associe la fonction de fermeture de fenetre

                        button_search_stop = gtk_builder_get_object(p_builder, "search_client_cancel_button"); //Récupération du bouton d'anulation de la recherche client
                        g_signal_connect(button_search_stop, "clicked", G_CALLBACK(closeWindow), G_OBJECT(pop_up_client_search)); //On y associe la fonction de fermeture de fenetre

                        button_sell_car = gtk_builder_get_object(p_builder, "sell_car_button");
                        g_signal_connect(button_sell_car, "clicked", G_CALLBACK(closeWindow), G_OBJECT(button_sell_car));

                        button_cancel_return_vehicule = gtk_builder_get_object(p_builder, "return_cancel_button"); //Récupération du bouton d'annulation de retour véhicule
                        g_signal_connect(button_cancel_return_vehicule, "clicked", G_CALLBACK(closeWindow), G_OBJECT(return_vehicule)); //On y associe la fonction de fermeture de fenêtre

                        g_signal_connect(main_win, "delete_event", gtk_main_quit, NULL); //Ferme le programme lorsqu'on clique la croix en haut à droite

                        button_add_reservation = gtk_builder_get_object(p_builder, "add_reservation_button"); //Récupération du bouton d'ajout de résérvation
                        g_signal_connect(button_add_reservation, "clicked", G_CALLBACK(openWindow), G_OBJECT(pop_up_reservation_add)); //On y associe la fonction d'ouverture du pop-up d'ajout de réservation

                        button_search_reservation = gtk_builder_get_object(p_builder, "search_reservation_button"); //Récupération du bouton de recherche client
                        g_signal_connect(button_search_reservation, "clicked", G_CALLBACK(openWindow), G_OBJECT(pop_up_client_search)); //On y associe la fonction d'ouverture de la pop-up de recherche client

                        button_return_vehicule = gtk_builder_get_object(p_builder, "return_vehicule_button"); //Récupération du bouton de renvoi de véhicule
                        g_signal_connect(button_return_vehicule, "clicked", G_CALLBACK(openWindow), G_OBJECT(return_vehicule)); //On y associe la fonction d'ouverture de la pop-up de retour véhicule

                        reservation_list_return_button = gtk_builder_get_object(p_builder, "reservation_list_return_button"); //Récupération du bouton de retour dans pop_up de liste reservation
                        g_signal_connect(reservation_list_return_button, "clicked", G_CALLBACK(closeWindow), G_OBJECT(reservation_list_window)); //On y associe la fonction de fermeture fenetre lors du clic



                        /* Gestion de la liste de reservation */
                        GtkListStore *list_reservation = (GtkListStore *) gtk_builder_get_object(p_builder, "reservation_lists"); //On récupère la liste reservation_lists

                        /* Gestion de la liste d'historique des reservations */
                        GtkListStore *list_price_history = (GtkListStore *) gtk_builder_get_object(p_builder, "price_history"); //On récupère la liste d'historique
                        manage_list_history(list_price_history);

                        /* Gestion de la liste de révision */
                        GtkListStore *list_revision = (GtkListStore * ) gtk_builder_get_object(p_builder, "Revision"); //On récup-re la liste de revision
                        manage_list_revision(list_revision);




                        /* Boucle for qui permet d'intialiser des boutons clicables pour chaque case de notre
                        calendrier */
                        for(int i=1; i<=31; i++)
                        {
                                sprintf(compteur, "%d",i); //on crée une chaine de caractère contenant le compteur
                                strcpy(joursCalendrier, "day"); //on concatène les deux chaines
                                strcat(joursCalendrier, compteur); //on concatène les deux chaines
                                calendar[i]=gtk_builder_get_object(p_builder, joursCalendrier); //Pour chaque case, on récupère le bouton glade correspondant
                                g_signal_connect(calendar[i], "clicked", G_CALLBACK(openWindow), G_OBJECT(reservation_list_window)); //On y associe la fonction d'ouverture
                                g_signal_connect(calendar[i], "clicked", G_CALLBACK(manage_list_reservation), list_reservation);
                        }


                        /* Affichage des fenêtres */
                        gtk_widget_show_all(main_win);

                        gtk_main ();
                }
                else
                {
                        /* Affichage du message d'erreur de GTK+ */
                        g_error ("%s", p_err->message);
                        g_error_free (p_err);
                }
        }


        return EXIT_SUCCESS;
}
