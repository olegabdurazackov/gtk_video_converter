#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

extern char* outfile_name;
int  outfile(){
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new( "Save File",
									/* parent_window */ NULL,
									GTK_FILE_CHOOSER_ACTION_SAVE,
									GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
									GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
									NULL );
	gtk_file_chooser_set_do_overwrite_confirmation(
																			GTK_FILE_CHOOSER( dialog ), TRUE );

	/* < зона конкретных переменных > */
	gboolean user_edited_a_new_document = TRUE;
	char* default_folder_for_saving = "/home/o/video";
	char* filename_for_existing_document = "rm_my.txt";
	/*</>*/

	if( user_edited_a_new_document ) {
		gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( dialog ),
																						 default_folder_for_saving );
		gtk_file_chooser_set_current_name( GTK_FILE_CHOOSER( dialog ),
																					"default_gtk_video_saved" );
	}else{
			 gtk_file_chooser_set_filename( GTK_FILE_CHOOSER( dialog ),
																	 filename_for_existing_document );
	}
	if( gtk_dialog_run(GTK_DIALOG( dialog )) == GTK_RESPONSE_ACCEPT ) {

			 outfile_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
			 g_print/*save_to_file*/( "%s\n", outfile_name );
  }

	gtk_widget_destroy(dialog);
	      

		return 0;
}
