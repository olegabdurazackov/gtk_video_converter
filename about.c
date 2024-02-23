#include "proc.h"
#include <gtk/gtk.h>

  static GtkWidget *window = NULL;
  GtkWidget *hbox;
  GtkWidget *vbox;
  GtkWidget *frame;
  GtkWidget *label;

  GdkBitmap *mask;
  GdkPixmap *pixmap;
  GtkStyle *style;
  GtkWidget *pixmapwid;
 
  GtkWidget *hbox_pixmap;
  GtkWidget *button;

void free_this(){
  
  gtk_widget_destroy(window);
}
void about(){
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (free_this),
		    NULL);

  gtk_window_set_title (GTK_WINDOW (window), "About");
  vbox = gtk_vbox_new (FALSE, 5);
  hbox = gtk_hbox_new (FALSE, 5);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  
  
  frame = gtk_frame_new (PROGRAMM_NAME);
  label = gtk_label_new (PROGRAMM_VERSION \
          "\n"\
			 PROGRAMM_DESCRIPTION\
			 );
  gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_FILL);
  gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (vbox), hbox_pixmap, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 0);
  
  
  gtk_widget_show_all (window);

} 
