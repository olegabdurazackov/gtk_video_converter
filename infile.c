#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
 
extern char* infile_name;
int infile( ){
 /* int argc;
  char** argv; */
  GtkWidget *dialog;
  /*gtk_init( &argc, &argv );*/
   
  dialog = gtk_file_chooser_dialog_new ("Open File",
                   /* parent_window */  NULL,
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                        GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                        NULL);
// char* namef;  
  if( gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT ) {
//      char *filename;
          
      infile_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
      g_print/* open_file*/("%s\n",infile_name) ;
//      strcpy( namef, filename );
//      strcpy( infile_name, filename );
//      g_free (filename);
  }
    
  gtk_widget_destroy(dialog);
//	return namef;
}
