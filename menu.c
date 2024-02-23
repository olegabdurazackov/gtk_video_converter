#include "proc.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>

/********************************************/
/*									 datas 								  */
/********************************************/
char *infile_name, *infile_sub, *outfile_name;
char* outfile_type = ".mpg" ;
char* aspect="4:3", *resize="720x576";
char* map_sub="", *map_sub_add="";
char* h264_preset="slow";
char* h264_tune="film";
char video_filter[1023], outfile_title[511];
char* b_frame="1", *quality="6", *outfile_name;
char* acanal="2", *abitrate="192";
int  calfil[30];
int h264 = 0, file_info = 0;
char time_start[63]="0", time_end[63]="36000";
long int t_start, t_end;
char* inter_matrix = "16,17,18,19,20,21,22,23,"
                     "17,18,19,20,21,22,23,24,"
                     "18,19,20,21,22,23,24,25,"
                     "19,20,21,22,23,24,26,27,"
                     "20,21,22,23,25,26,27,28,"
                     "21,22,23,24,26,27,28,30,"
                     "22,23,24,26,27,28,30,31,"
                     "23,24,25,27,28,30,31,33" ;

#define FLT_NAME_1 "f::Нормализация изображения YUV=4:4:4"
#define FLT_1 ",format=yuv444p,normalize=blackpt=black:whitept=white:smoothing=50:independence=0"
#define FLT_AVC_1 ""
#define FLT_NAME_2 "YUV=4:2:0"
#define FLT_2 ",format=yuv420p"
#define FLT_AVC_2 ",format=yuv420p"
#define FLT_NAME_3 "f::Авто яркость,контраст,деблок"
#define FLT_3 ",pp=ac"
#define FLT_AVC_3 ""
#define FLT_NAME_4 "Временной--улучшение сжимаемости"
#define FLT_4 ",atadenoise"
#define FLT_AVC_4 ",hqdn3d"
#define FLT_NAME_5 "Увеличение резкости sharpen/яркость+цвет"
#define FLT_5 ",unsharp=5:5:2:5:5:1.5"
#define FLT_AVC_5 ",unsharp=5:5:2:5:5:1.5"
#define FLT_NAME_6 "Увеличение резкости sharpen/яркость"
#define FLT_6 ",unsharp=5:5:1.5"
#define FLT_AVC_6 ",unsharp=5:5:1.5"
#define FLT_NAME_7 "Деинтерлейс"
#define FLT_7 ",kerndeint=sharp=1:twoway=1"
#define FLT_AVC_7 ",yadif"
#define FLT_NAME_8 "Отражение/по горизонтали" 
#define FLT_8 ",hflip"
#define FLT_AVC_8 ",hflip"
#define FLT_NAME_9 "Отражение/по вертикали " 
#define FLT_9 ",vflip"
#define FLT_AVC_9 ",vflip"
#define FLT_NAME_11 "f::Устранение дрожания" 
#define FLT_11 ",deshake=rx=64:ry=64"
#define FLT_AVC_11 ""
#define FLT_NAME_12 "Преобразование аспекта/2.21:1 -> 16:9/HD"
#define FLT_12 ",scale=1588:720,crop=1280:720:154:0"
#define FLT_AVC_12 ",scale=1588:720,crop=1280:720:154:0"
#define FLT_NAME_13 "Преобразование аспекта/2.21:1 -> 16:9/MPEG"
#define FLT_13 ",scale=896:576,crop=720:576:88:0"
#define FLT_AVC_13 ",scale=896:576,crop=720:576:88:0"
#define FLT_NAME_14 "Преобразование аспекта/16:9 -> 4:3/HD"
#define FLT_14 ",scale=1706:960,crop=1280:960:213:0"
#define FLT_AVC_14 ",scale=1706:960,crop=1280:960:213:0"
#define FLT_NAME_15 "Преобразование аспекта/16:9 -> 4:3/MPEG"
#define FLT_15 ",scale=1024:576,crop=720:576:152:0"
#define FLT_AVC_15 ",scale=1024:576,crop=720:576:152:0"
#define FLT_NAME_16 "Преобразование аспекта/ 4:3 -> 3:4/HD"
#define FLT_16 ",scale=1280:960,crop=720:960:280:0"
#define FLT_AVC_16 ",scale=1280:960,crop=720:960:280:0"
#define FLT_NAME_17 "Преобразование аспекта/ 4:3 -> 3:4/MPEG"
#define FLT_17 ",scale=768:576,crop=720:576:168:0"
#define FLT_AVC_17 ",scale=768:576,crop=720:576:168:0"
#define FLT_NAME_18 "Изменение яркости/х0.5"
#define FLT_18 ",lutyuv=y=val*0.5"
#define FLT_AVC_18 ",lutyuv=y=val*0.5"
#define FLT_NAME_19 "Изменение яркости/х1.2"
#define FLT_19 ",lutyuv=y=val*1.2"
#define FLT_AVC_19 ",lutyuv=y=val*1.2"
#define FLT_NAME_21 "Изменение яркости/х1.5"
#define FLT_21 ",lutyuv=y=val*1.5"
#define FLT_AVC_21 ",lutyuv=y=val*1.5"
#define FLT_NAME_22 "Изменение яркости/х2.0"
#define FLT_22 ",lutyuv=y=val*2.0"
#define FLT_AVC_22 ",lutyuv=y=val*2.0"
#define FLT_NAME_23 "Поворот/по часовой"
#define FLT_23 ",transpose=1"
#define FLT_AVC_23 ",transpose=1"
#define FLT_NAME_24 "Поворот/против часовой"
#define FLT_24 ",transpose=2"
#define FLT_AVC_24 ",transpose=2"
/********************************************/
/*							 procedures 							  */
/********************************************/
static void add_filter(){
    video_filter[0]='\0';
  strcpy( video_filter,( 0 == h264 )? "atadenoise" : "hqdn3d" );
   if( 1 == calfil[1] ) strcat( video_filter, ( 0 == h264 )? FLT_1 : FLT_AVC_1 );
   if( 2 == calfil[2] ) strcat( video_filter, ( 0 == h264 )? FLT_2 : FLT_AVC_2 );
   if( 3 == calfil[3] ) strcat( video_filter, ( 0 == h264 )? FLT_3 : FLT_AVC_3 );
   /* Этот фильтр включен по умолчанию */
 /*  if( 4 == calfil[4] ) strcat( video_filter, ( 0 == h264 )? FLT_4 : FLT_AVC_4 );*/
   if( 5 == calfil[5] ) strcat( video_filter, ( 0 == h264 )? FLT_5 : FLT_AVC_5 );
   if( 6 == calfil[6] ) strcat( video_filter, ( 0 == h264 )? FLT_6 : FLT_AVC_6 );
   if( 7 == calfil[7] ) strcat( video_filter, ( 0 == h264 )? FLT_7 : FLT_AVC_7 );
   if( 8 == calfil[8] ) strcat( video_filter, ( 0 == h264 )? FLT_8 : FLT_AVC_8 );
   if( 9 == calfil[9] ) strcat( video_filter, ( 0 == h264 )? FLT_9 : FLT_AVC_8 );
   if( 11 == calfil[11] ) strcat( video_filter, ( 0 == h264 )? FLT_11 : FLT_AVC_11 );
   if( 12 == calfil[12] ) strcat( video_filter, ( 0 == h264 )? FLT_12 : FLT_AVC_12 );
   if( 13 == calfil[13] ) strcat( video_filter, ( 0 == h264 )? FLT_13 : FLT_AVC_13 );
   if( 14 == calfil[14] ) strcat( video_filter, ( 0 == h264 )? FLT_14 : FLT_AVC_14 );
   if( 15 == calfil[15] ) strcat( video_filter, ( 0 == h264 )? FLT_15 : FLT_AVC_15 );
   if( 16 == calfil[16] ) strcat( video_filter, ( 0 == h264 )? FLT_16 : FLT_AVC_16 );
   if( 17 == calfil[17] ) strcat( video_filter, ( 0 == h264 )? FLT_17 : FLT_AVC_17 );
   if( 18 == calfil[18] ) strcat( video_filter, ( 0 == h264 )? FLT_18 : FLT_AVC_18 );
   if( 19 == calfil[19] ) strcat( video_filter, ( 0 == h264 )? FLT_19 : FLT_AVC_19 );
   if( 21 == calfil[21] ) strcat( video_filter, ( 0 == h264 )? FLT_21 : FLT_AVC_21 );
   if( 22 == calfil[22] ) strcat( video_filter, ( 0 == h264 )? FLT_22 : FLT_AVC_22 );
   if( 23 == calfil[23] ) strcat( video_filter, ( 0 == h264 )? FLT_23 : FLT_AVC_23 );
   if( 24 == calfil[24] ) strcat( video_filter, ( 0 == h264 )? FLT_24 : FLT_AVC_24 );
}
/*******************************************
int a2a ( const gchar* in ){
    char t[255];
    strcpy ( t, in );
    char tm[] = strtok ( t, "0123456789:" );

}
*/
/********************************************/
int a2a ( const gchar* in ){
    g_message (" --= start a2a =--%s!\n", in);
    int out = 0;
    int i = strlen ( in ) -1 ;;
        for ( i; i >=0; i-- ){
//            g_message ("   in[%d]=%c=%d  \n", i, in[i], in[i] );
            if ( '0' > in[i] || ':' < in[i] ){
                out = 1;
//                g_message (" %s!\n", "not number");
                continue;
            }
        }

    return out;

}
/********************************************/
static void enter_callback_start( GtkWidget *widget,
                            GtkWidget *entry_start )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry_start));
  strcpy( time_start, entry_text );
  printf ("Entry contents: %s\n", time_start);
}
                     
/********************************************/
static void enter_callback_stop( GtkWidget *widget,
                            GtkWidget *entry_stop )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry_stop));
  strcpy( time_end, entry_text );
  printf ("Entry contents: %s\n", time_end);
}
                     
/********************************************/
static void enter_callback_title_file( GtkWidget *widget,
                            GtkWidget *entry_title_file )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry_title_file));
  strcpy(outfile_title, entry_text );
  printf ("Entry contents: %s\n", outfile_title);
}
                     
/********************************************/
/* Obligatory basic callback */
static void f_open_sub( GtkWidget *w,
                    gpointer   data ) {
  insub();
//  file_info = 0;
  g_message ("new %s!\n", infile_sub);
}
/********************************************/
static void h_about( GtkWidget *w,
                    gpointer   data ) {
  about();

  g_message ("open %s!\n", "about");
}
/********************************************/
static void f_open( GtkWidget *w,
                    gpointer   data ) {
  infile();
  file_info = 0;

  g_message ("open %s!\n", infile_name);
}
/********************************************/
static void f_info( GtkWidget *w,
                    gpointer   data ) {
  infile();
  file_info = 1;
  g_message ("info %s!\n", infile_name);
}
/********************************************/
static void f_save_mpg( GtkWidget *w,
                        gpointer   data ) {
  outfile_type = ".mpg"; 
  outfile();
//  file_info = 0;
  h264 = 0;
  g_message ("%s\n", outfile_name);
}
/**********************************************/
static void f_save_mkv( GtkWidget *w,
                        gpointer   data ) {
  outfile_type = ".mkv" ;
  outfile();
//  file_info = 0;
  h264 = 0;
  g_message ("%s\n", outfile_name);
}
/**********************************************/
static void f_save_mkv_h264( GtkWidget *w,
                        gpointer   data ) {
  outfile_type = ".mkv" ;
  outfile();
  h264 = 1;
  g_message ("%s\n", outfile_name);
}
/**********************************************/
static void f_save_mp4( GtkWidget *w,
                        gpointer   data ) {
  outfile_type = ".mp4" ;
  outfile();
  h264 = 1;
  g_message ("%s\n", outfile_name);
}
/**********************************************/
static void f_save_avi( GtkWidget *w,
                        gpointer   data ) {
  outfile_type = ".avi" ;
  outfile();
  h264 = 0;
  g_message ("%s\n", outfile_name);
}
/*******************************************/
static int selected_time( GtkWidget *widget, GtkWidget *entry_lin) {
  /* timer()*/

  g_message ("%s\n", " Start timer" );
  if ( 0 != a2a ( time_start ) || 0 != a2a ( time_end )  ){
    g_message ("%s\n", " Время и длительность должны быть числами" );
    return 1;
  }
  if ( NULL == infile_name ){
    g_message ("%s\n", " не задан входной файл" );
    return 1;
  }
  if ( NULL == outfile_name ){
    g_message ("%s\n", " не задан выходной файл" );
    return 1;
  }
  g_message ("%s\n", " File names -- OK" );
  add_filter();
  g_message ("%s : %s : %s\n", " :278", outfile_name, outfile_type );
	strcat( outfile_name, outfile_type );
  g_message ("%s\n", " :280" );
  char mtitle[400]="title=";
	strcat( mtitle, outfile_title );
	strcat( mtitle, ":software=gtk_video_converter-" );
	strcat( mtitle, PROGRAMM_VERSION );
  g_message ("%s\n", " :283" );
	char* ffmpeg_xvid_args[] = {
			"ffmpeg","-y","-ss",time_start,"-t",time_end,"-i",infile_name,
			"-map","0:v","-c:v","libxvid","-vtag","XVID","-qmin","0",
			"-qmax",quality,"-bufsize","4096","-mbd","rd","-flags","+qpel",
			"-coder","1","-subq","6","-psy-rd","1.0:0.8","-bf",b_frame,
			"-trellis","1","-cmp","satd","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-inter_matrix",inter_matrix,"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,
      outfile_name,
			NULL };
  g_message ("%s\n", " :295" );
	char* ffmpeg_xvid_args_sub[] = {
			"ffmpeg","-y","-ss",time_start,"-t",time_end,"-i",infile_name,
			"-map","0:v","-c:v","libxvid","-vtag","XVID","-qmin","0",
			"-qmax",quality,"-bufsize","4096","-mbd","rd","-flags","+qpel",
			"-coder","1","-subq","6","-psy-rd","1.0:0.8","-bf",b_frame,
			"-trellis","1","-cmp","satd","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-inter_matrix",inter_matrix,"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,"-map","0:s",
			outfile_name,
			NULL };
	char* ffmpeg_xvid_args_sub_add[] = {
			"ffmpeg","-y","-ss",time_start,"-t",time_end,"-i",
      infile_name, "-i", infile_sub,
			"-map","0:v","-c:v","libxvid","-vtag","XVID","-qmin","0",
			"-qmax",quality,"-bufsize","4096","-mbd","rd","-flags","+qpel",
			"-coder","1","-subq","6","-psy-rd","1.0:0.8","-bf",b_frame,
			"-trellis","1","-cmp","satd","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-inter_matrix",inter_matrix,"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,"-map","0:s","-map","1",
			outfile_name,
			NULL };
	char* ffmpeg_xvid_args_add[] = {
			"ffmpeg","-y","-ss",time_start,"-t",time_end,"-i",
      infile_name, "-i", infile_sub,
			"-map","0:v","-c:v","libxvid","-vtag","XVID","-qmin","0",
			"-qmax",quality,"-bufsize","4096","-mbd","rd","-flags","+qpel",
			"-coder","1","-subq","6","-psy-rd","1.0:0.8","-bf",b_frame,
			"-trellis","1","-cmp","satd","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-inter_matrix",inter_matrix,"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,/*"-map","0:s",*/"-map","1",
			outfile_name,
			NULL };
  g_message ("%s\n", " :307" );
	char* ffmpeg_mpg_args[] = {
			"ffmpeg","-y","-ss",time_start,"-t",time_end,"-i",infile_name,
      "-target","pal-dvd",
			"-map","0:v","-c:v","mpeg2video","-vf",video_filter,"-mbd","rd",
      "-trellis","1","-cmp","2",
      "-subcmp","2","-b_strategy","1","-mpv_flags","+skip_rd+qp_rd+cbp_rd",
			"-qscale",quality, "-s",resize, "-aspect",aspect,"-metadata", mtitle,
			"-inter_matrix",inter_matrix,"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate, 
			outfile_name,
			NULL };
  g_message ("%s\n", " :319" );
	char* avconv_mp4_args[] = {
			"avconv","-y","-ss",time_start,"-t",time_end,"-i",infile_name,
			"-map","0:v","-c:v","libx264","-preset",h264_preset,
			"-tune",h264_tune,"-crf","20","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-map","0:a","-ar","44100",
			"-ac","2","-ab",abitrate,
      outfile_name,
			NULL };
  g_message ("%s\n", " :329" );
	char* avconv_mkv_args[] = {
			"avconv","-y","-ss",time_start,"-t",time_end,"-i",infile_name,
			"-map","0:v","-c:v","libx264","-preset",h264_preset,
			"-tune",h264_tune,"-crf","20","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,
      outfile_name,
			NULL };
  g_message ("%s\n", " :339" );
	char* avconv_mkv_args_sub[] = {
			"avconv","-y","-ss",time_start,"-t",time_end,"-i",infile_name,
			"-map","0:v","-c:v","libx264","-preset",h264_preset,
			"-tune",h264_tune,"-crf","20","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,"-map","0:s",
      outfile_name,
			NULL };
	char* avconv_mkv_args_sub_add[] = {
			"avconv","-y","-ss",time_start,"-t",time_end,"-i",
      infile_name, "-i", infile_sub,
			"-map","0:v","-c:v","libx264","-preset",h264_preset,
			"-tune",h264_tune,"-crf","20","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,"-map","0:s","-map","1",
      outfile_name,
			NULL };
	char* avconv_mkv_args_add[] = {
			"avconv","-y","-ss",time_start,"-t",time_end,"-i",
      infile_name, "-i", infile_sub,
			"-map","0:v","-c:v","libx264","-preset",h264_preset,
			"-tune",h264_tune,"-crf","20","-r","24","-s",resize,
			"-aspect",aspect,"-vf",video_filter,"-metadata", mtitle,
			"-map","0:a","-c:a","ac3","-ar","48000",
			"-ac",acanal,"-ab",abitrate,/*"-map","0:s",*/"-map","1",
      outfile_name,
			NULL };

	pid_t result;
  g_message ("%s\n", "start timer");
	result = fork ();
	if( -1 == result ){
			g_message( "fork error\n" );
			return 1;
	}
  g_message ("%d\n", file_info);
	if ( result == 0 ){
      if ( 1 == file_info ) {
          g_message ("%s\n", "start file_info-play:353");
          file_info = 0;
          execlp ("avplay","avplay",infile_name, NULL );
          g_message( "execve error\n" );
          return 1;
      }
      if ( 0 == h264 ) {
          g_message ("%s\n", "start ffmpeg:360");
			    execvp ("ffmpeg",
              (".mpg" == outfile_type )?ffmpeg_mpg_args:
              ("1" == map_sub && "2" == map_sub_add)?ffmpeg_xvid_args_sub_add:
              ("1" == map_sub)?ffmpeg_xvid_args_sub:
              ("2" == map_sub_add)?ffmpeg_xvid_args_add: ffmpeg_xvid_args);
			    g_message( "execve error\n" );
			    return 1;
      }
      if ( 1 == h264 ) {
          g_message ("%s\n", "start h264:368");
			    execvp ("avconv",
              (".mp4" == outfile_type )? avconv_mp4_args:
              ("1" == map_sub && "2" == map_sub)?avconv_mkv_args_sub_add:
              ("1" == map_sub)?avconv_mkv_args_sub:
              ("2" == map_sub)?avconv_mkv_args_add: avconv_mkv_args );
			    g_message( "execve error\n" );
			    return 1;
      }
      g_message ("%s\n", "start avconv:375");
      execlp ( "avconv","avconv","-i", infile_name,NULL );
 //      execlp ("ffmpeg","ffmpeg","-i",infile_name, NULL );
	} else {
			g_message( "I'm parent with PID=%d\n", getpid() ) ;
	}
	g_message ("else %s\n", "done");

  
	return 0;
}

/************************/
/* For the check button */
static void print_toggle( gpointer   callback_data,
                          guint      callback_action,
                          GtkWidget *menu_item )
{
   g_message ("Check button state - %d\n",
              GTK_CHECK_MENU_ITEM (menu_item)->active);
}
/***************************************/
static void filter_toggle( gpointer   callback_data,
                          guint      callback_action,
                          GtkWidget *menu_item ) {
   if( 1 == callback_action ){
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[1]=1;
       }else{
          calfil[1]=0;
       }
   }
   if( 2 == callback_action ){
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[2]=2;
       }else{
          calfil[2]=0;
       }
   }
   /* Этот фильтр включен по умолчанию */
 /*  if( 3 == callback_action ) strcat( video_filter, FLT_3 );*/
   if( 4 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[4]=4;
       }else{
          calfil[4]=0;
       }
   }

   if( 5 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[5]=5;
       }else{
          calfil[5]=0;
       }
   }

   if( 6 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[6]=6;
       }else{
          calfil[6]=0;
       }
   }

   if( 7 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[7]=7;
       }else{
          calfil[7]=0;
       }
   }

   if( 8 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[8]=8;
       }else{
          calfil[8]=0;
       }
   }

   if( 9 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[9]=9;
       }else{
          calfil[9]=0;
       }
   }

   if( 11 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[11]=11;
       }else{
          calfil[11]=0;
       }
   }

   if( 12 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[12]=12;
       }else{
          calfil[12]=0;
       }
   }

   if( 13 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[13]=13;
       }else{
          calfil[13]=0;
       }
   }

   if( 14 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[14]=14;
       }else{
          calfil[14]=0;
       }
   }

   if( 15 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[15]=15;
       }else{
          calfil[15]=0;
       }
   }
   if( 15 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[15]=15;
       }else{
          calfil[15]=0;
       }
   }
   if( 16 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[16]=16;
       }else{
          calfil[16]=0;
       }
   }
   if( 17 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[17]=17;
       }else{
          calfil[17]=0;
       }
   }
   if( 18 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[18]=18;
       }else{
          calfil[18]=0;
       }
   }
   if( 19 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[19]=19;
       }else{
          calfil[19]=0;
       }
   }
   if( 21 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[21]=21;
       }else{
          calfil[21]=0;
       }
   }
   if( 22 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[22]=22;
       }else{
          calfil[22]=0;
       }
   }
   if( 23 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[23]=23;
       }else{
          calfil[23]=0;
       }
   }
   if( 24 == callback_action ) {
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           calfil[24]=24;
       }else{
          calfil[24]=0;
       }
   }

   g_message ("Check button state - %d\ callbackn+action=%d video_filter=%s\n",
              GTK_CHECK_MENU_ITEM (menu_item)->active,
              callback_action,
							video_filter );
}
/*************************/
/* For the radio buttons */
static void print_selected( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item )
{
   if(GTK_CHECK_MENU_ITEM(menu_item)->active)
     g_message ("Radio button %d selected\n", callback_action);
}
/***************************************************/
static void selected_audio( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item ) {
   if(GTK_CHECK_MENU_ITEM(menu_item)->active){
     if( 1 == callback_action ){
				acanal = "2";
				abitrate ="192k";
		 }
     if( 2 == callback_action ){
				acanal = "2";
				abitrate ="64k";
		 }
     if( 3 == callback_action ){
				acanal = "2";
				abitrate ="192k";
		 }
     if( 4 == callback_action ){
				acanal = "6";
				abitrate ="384k";
		 }
     if( 5 == callback_action ){
				acanal = "6";
				abitrate ="448k";
		 }
     g_message ("aspect Radio button %d selected\n", callback_action);
     g_message ("acanal Radio button %s selected\n", acanal);
     g_message ("abitrate Radio button %s selected\n", abitrate);
   }
}
/****************************************************/
static void selected_razmer( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item ) {
   if(GTK_CHECK_MENU_ITEM(menu_item)->active){
     if( 1 == callback_action ) resize = "720x576" ;
     if( 2 == callback_action ) resize = "1280x960" ;
     if( 3 == callback_action ) resize = "1280x720" ;
     if( 13 == callback_action ) resize = "960x720" ;
     if( 4 == callback_action ) resize = "1024x576" ;
     if( 5 == callback_action ) resize = "720x576" ;
     if( 6 == callback_action ) resize = "352x576" ;
     if( 7 == callback_action ) resize = "852x480" ;
     if( 8 == callback_action ) resize = "640x480" ;
     if( 9 == callback_action ) resize = "480x480" ;
     if( 10 == callback_action ) resize = "640x360" ;
     if( 11 == callback_action ) resize = "480x360" ;
     if( 12 == callback_action ) resize = "352x288" ;
     if( 13 == callback_action ) resize = "960x720" ;
     if( 14 == callback_action ) resize = "1920x1080" ;
     g_message ("resize Radio button %d selected\n", callback_action);
     g_message ("razmer Radio button %s selected\n", resize);
   }
}
/******************************************************/
static void selected_aspect( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item ) {
   if(GTK_CHECK_MENU_ITEM(menu_item)->active){
     if( 2 == callback_action ) aspect = "4:3" ;
     if( 3 == callback_action ) aspect = "16:9" ;
     if( 4 == callback_action ) aspect = "221:100" ;
     g_message ("aspect Radio button %d selected\n", callback_action);
     g_message ("aspect Radio button %s selected\n", aspect);
   }
}
/******************************************************/
static void selected_qual( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item ) {
   if(GTK_CHECK_MENU_ITEM(menu_item)->active){
     if( 2 == callback_action ){
         quality = "1" ;
         h264_preset = "placebo";
     }
     if( 3 == callback_action ){
         quality = "2" ;
         h264_preset = "veryslow";
     }
     if( 4 == callback_action ){
         quality = "3" ;
         h264_preset = "slower";
     }
     if( 5 == callback_action ){
         quality = "4" ;
         h264_preset = "slow";
     }
     if( 6 == callback_action ){
         quality = "5" ;
         h264_preset = "medium";
     }
     if( 7 == callback_action ){
         quality = "6" ;
         h264_preset = "fast";
     }
     if( 8 == callback_action ){
         quality = "7" ;
         h264_preset = "faster";
     }
     if( 9 == callback_action ){
         quality = "8" ;
         h264_preset = "veryfast";
     }
     if( 10 == callback_action ){
         quality = "9" ;
         h264_preset = "superfast";
     }
     if( 11 == callback_action ){
         quality = "10" ;
         h264_preset = "ultrafast";
     }
     if( 12 == callback_action ) quality = "11" ;
     if( 13 == callback_action ) quality = "12" ;
     g_message ("quality Radio button %d selected\n", callback_action);
     g_message ("quality Radio button %s selected\n", quality);
   }
}
/******************************************************/
static void selected_b_frame( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item ) {
   if(GTK_CHECK_MENU_ITEM(menu_item)->active){
     if( 1 == callback_action ){
         b_frame = "1" ;
         h264_tune    = "grain";
     }
     if( 2 == callback_action ){
         b_frame = "2" ;
         h264_tune    = "film";
     }
     if( 3 == callback_action ){
         b_frame = "2" ;
         h264_tune    = "animation";
     }
     if( 4 == callback_action ){
         b_frame = "3" ;
         h264_tune    = "stillimage";
     }
     g_message ("b_frame Radio button %d selected\n", callback_action);
     g_message ("b_frame Radio button %s selected\n", b_frame);
   }
}
/***********************************************************/
static void selected_subtitle( gpointer   callback_data,
                            guint      callback_action,
                            GtkWidget *menu_item ) {
   if( 1 == callback_action ){
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           map_sub="1";
       }else{
          map_sub="0";
       }
   }
   if( 2 == callback_action ){
       if( 1 == GTK_CHECK_MENU_ITEM (menu_item)->active){
           map_sub_add="2";
       }else{
          map_sub_add="0";
       }
   }
     g_message ("map_sub Radio button %d selected\n", callback_action);
     g_message ("map_sub = %s selected\n", map_sub);
     g_message ("map_sub_add = %s selected\n", map_sub_add);
   
}

/*********************************************************************/
/* Our menu, an array of GtkItemFactoryEntry structures that defines each menu item */
static GtkItemFactoryEntry menu_items[] = {
  { "/_File",         NULL,         NULL,          0, "<Branch>" },
  { "/File/Open_Sub", "<control>S", f_open_sub,    0, "<StockItem>", GTK_STOCK_NEW },
  { "/File/_Open",    "<control>O", f_open,        0, "<StockItem>", GTK_STOCK_OPEN },
  { "/File/_Info-Play","<control>I", f_info,        0, "<StockItem>", GTK_STOCK_MEDIA_PLAY },
  { "/File/sep1",     NULL,         NULL,          0, "<Separator>" },
  { "/File/Save _MPEG","<control>M",f_save_mpg,   0, "<StockItem>", GTK_STOCK_SAVE_AS },
  { "/File/Save MKV _h264","<control>H",f_save_mkv_h264,0,"<StockItem>",GTK_STOCK_SAVE },
  { "/File/Save M_P4 h264","<control>P",f_save_mp4,0, "<StockItem>", GTK_STOCK_SAVE },
  { "/File/Save MKV _xvid","<control>X",f_save_mkv,0,"<StockItem>", GTK_STOCK_SAVE_AS },
  { "/File/Save _AVI xvid","<CTRL>A",    f_save_avi,   0, "<StockItem>", GTK_STOCK_SAVE_AS },
  { "/File/sep1",     NULL,         NULL,          0, "<Separator>" },
  { "/File/_Quit",    "<CTRL>Q", gtk_main_quit,    0, "<StockItem>", GTK_STOCK_QUIT },
  { "/_Timer",             NULL,NULL,         0, "<Branch>" },
  { "/Timer/start process",NULL,selected_time,0,"<StockItem>",GTK_STOCK_MEDIA_RECORD },
  { "/_Video",              NULL,  NULL,           0, "<Branch>" },
  { "/Video/tear",          NULL,  NULL,           0, "<Tearoff>" },
  { "/Video/аспект/   4:3", NULL, selected_aspect, 2, "<RadioItem>" },
  { "/Video/аспект/  16:9", NULL, selected_aspect, 3, "/Video/аспект/   4:3" },
  { "/Video/аспект/2.21:1", NULL, selected_aspect, 4, "/Video/аспект/   4:3" },
  { "/Video/sep",           NULL,      NULL,       0, "<Separator>" },
  { "/Video/размер/Off",       NULL, selected_razmer, 1, "<RadioItem>" },
  { "/Video/размер/1920x1080", NULL, selected_razmer, 14, "/Video/размер/Off" },
  { "/Video/размер/1280x960",   NULL, selected_razmer, 2, "/Video/размер/Off" },
  { "/Video/размер/1280x720",   NULL, selected_razmer, 3, "/Video/размер/Off" },
  { "/Video/размер/960x720",   NULL, selected_razmer, 13, "/Video/размер/Off" },
  { "/Video/размер/1024x576",   NULL, selected_razmer, 4, "/Video/размер/Off" },
  { "/Video/размер/ 720x576",   NULL, selected_razmer, 5, "/Video/размер/Off" },
  { "/Video/размер/ 352x576",   NULL, selected_razmer, 6, "/Video/размер/Off" },
  { "/Video/размер/ 852x480",   NULL, selected_razmer, 7, "/Video/размер/Off" },
  { "/Video/размер/ 640x480",   NULL, selected_razmer, 8, "/Video/размер/Off" },
  { "/Video/размер/ 480x480",   NULL, selected_razmer, 9, "/Video/размер/Off" },
  { "/Video/размер/ 640x360",   NULL, selected_razmer, 10, "/Video/размер/Off" },
  { "/Video/размер/ 480x360",   NULL, selected_razmer, 11, "/Video/размер/Off" },
  { "/Video/размер/ 352x288",   NULL, selected_razmer, 12, "/Video/размер/Off" },
  { "/Video/sep",           NULL,      NULL,       0, "<Separator>" },
  { "/Video/фильтр/"FLT_NAME_1,  NULL,  filter_toggle,   1, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_2,  NULL,  filter_toggle,   2, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_3,  NULL,  filter_toggle,   3, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_4,  NULL,  filter_toggle,   4, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_5,  NULL,  filter_toggle,   5, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_6,  NULL,  filter_toggle,   6, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_7,  NULL,  filter_toggle,   7, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_8,  NULL,  filter_toggle,   8, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_9,  NULL,  filter_toggle,   9, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_11, NULL,  filter_toggle,  11, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_12, NULL,  filter_toggle,  12, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_13, NULL,  filter_toggle,  13, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_14, NULL,  filter_toggle,  14, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_15, NULL,  filter_toggle,  15, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_16, NULL,  filter_toggle,  16, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_17, NULL,  filter_toggle,  17, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_18, NULL,  filter_toggle,  18, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_19, NULL,  filter_toggle,  19, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_21, NULL,  filter_toggle,  21, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_22, NULL,  filter_toggle,  22, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_23, NULL,  filter_toggle,  23, "<CheckItem>" },
  { "/Video/фильтр/"FLT_NAME_24, NULL,  filter_toggle,  24, "<CheckItem>" },
  { "/Video/sep",           NULL,      NULL,       0, "<Separator>" },
  { "/Video/качество/Off", NULL, selected_qual, 1, "<RadioItem>" },
  { "/Video/качество/1 placebo", "<CTRL>1", selected_qual, 2, "/Video/качество/Off" },
  { "/Video/качество/2 veryslow", "<CTRL>2", selected_qual, 3, "/Video/качество/Off" },
  { "/Video/качество/3 slower", "<CTRL>3", selected_qual, 4, "/Video/качество/Off" },
  { "/Video/качество/4 slow", "<CTRL>4", selected_qual, 5, "/Video/качество/Off" },
  { "/Video/качество/5 medium", "<CTRL>5", selected_qual, 6, "/Video/качество/Off" },
  { "/Video/качество/6 fast", "<CTRL>6", selected_qual, 7, "/Video/качество/Off" },
  { "/Video/качество/7 faster", "<CTRL>7", selected_qual, 8, "/Video/качество/Off" },
  { "/Video/качество/8 veryfast", "<CTRL>8", selected_qual, 9, "/Video/качество/Off" },
  { "/Video/качество/9 superfast", "<CTRL>9", selected_qual, 10, "/Video/качество/Off" },
  { "/Video/качество/10 ultrafast",   NULL, selected_qual, 11, "/Video/качество/Off" },
  { "/Video/качество/11",   NULL, selected_qual, 12, "/Video/качество/Off" },
  { "/Video/качество/12",   NULL, selected_qual, 13, "/Video/качество/Off" },
  { "/Video/sep",        NULL,      NULL,       0, "<Separator>" },
  { "/Video/b-кадр/1 grain",     NULL, selected_b_frame, 1, "<RadioItem>" },
  { "/Video/b-кадр/2 film",      NULL, selected_b_frame, 2, "/Video/b-кадр/1 grain" },
  { "/Video/b-кадр/2 animation",  NULL,selected_b_frame, 3, "/Video/b-кадр/1 grain" },
  { "/Video/b-кадр/3 stillimage", NULL,selected_b_frame, 4, "/Video/b-кадр/1 grain" },
  { "/_Audio",           NULL,  NULL,           0, "<Branch>" },
  { "/Audio/tear",       NULL,  NULL,           0, "<Tearoff>" },
  { "/Audio/ac3",        NULL,  selected_audio, 1, "<RadioItem>" },
  { "/Audio/ac3-2c-64k", NULL,  selected_audio, 2, "/Audio/ac3" },
  { "/Audio/ac3-2c-192k",NULL,  selected_audio, 3, "/Audio/ac3" },
  { "/Audio/ac3-6c-384k",NULL,  selected_audio, 4, "/Audio/ac3" },
  { "/Audio/ac3-6c-448k",NULL,  selected_audio, 5, "/Audio/ac3" },
  { "/_Subtitle",      NULL,  NULL,           0, "<Branch>" },
  { "/Subtitle/tear",  NULL,  NULL,           0, "<Tearoff>" },
  { "/Subtitle/On",    NULL,  selected_subtitle, 1, "<CheckItem>" },
  { "/Subtitle/add",   NULL,  selected_subtitle, 2, "<CheckItem>" },
  { "/Help",        NULL,   NULL,      0, "<LastBranch>" },
  { "/Help/Help",   "<F1>", h_about,      0, "<StockItem>",  GTK_STOCK_HELP },
  { "/Help/About",  NULL,   h_about,   0, "<StockItem>",  GTK_STOCK_ABOUT },
};
/**********************************************************************/
static gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

/* Returns a menubar widget made from the above menu */
static GtkWidget *get_menubar_menu( GtkWidget  *window )
{
  GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;

  /* Make an accelerator group (shortcut keys) */
  accel_group = gtk_accel_group_new ();

  /* Make an ItemFactory (that makes a menubar) */
  item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>",
                                       accel_group);

  /* This function generates the menu items. Pass the item factory,
     the number of items in the array, the array itself, and any
     callback data for the the menu items. */
  gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);

  /* Attach the new accelerator group to the window. */
  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

  /* Finally, return the actual menu bar created by the item factory. */
  return gtk_item_factory_get_widget (item_factory, "<main>");
}

/* Popup the menu when the popup button is pressed */
static gboolean popup_cb( GtkWidget *widget,
                          GdkEvent *event,
                          GtkWidget *menu )
{
   GdkEventButton *bevent = (GdkEventButton *)event;
  
   /* Only take button presses */
   if (event->type != GDK_BUTTON_PRESS)
     return FALSE;
  
   /* Show the menu */
   gtk_menu_popup (GTK_MENU(menu), NULL, NULL,
                   NULL, NULL, bevent->button, bevent->time);
  
   return TRUE;
}

/* Same as with get_menubar_menu() but just return a button with a signal to
   call a popup menu */
GtkWidget *get_popup_menu( void )
{
   GtkItemFactory *item_factory;
   GtkWidget *button, *menu;
  
   /* Same as before but don't bother with the accelerators */
   item_factory = gtk_item_factory_new (GTK_TYPE_MENU, "<main>",
                                        NULL);
   gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
   menu = gtk_item_factory_get_widget (item_factory, "<main>");
  
   /* Make a button to activate the popup menu */
   button = gtk_button_new_with_label (".");
   /* Make the menu popup when clicked */
   g_signal_connect (G_OBJECT(button),
                     "event",
                     G_CALLBACK(popup_cb),
                     (gpointer) menu);

   return button;
}

/* Same again but return an option menu */
GtkWidget *get_option_menu( void )
{
   GtkItemFactory *item_factory;
   GtkWidget *option_menu;
  
   /* Same again, not bothering with the accelerators */
   item_factory = gtk_item_factory_new (GTK_TYPE_OPTION_MENU, "<main>",
                                        NULL);
   gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
   option_menu = gtk_item_factory_get_widget (item_factory, "<main>");

   return option_menu;
}

/********************************************/
/*									 main 								  */
/********************************************/
int main( int argc, char *argv[] ) {

  GtkWidget *window;
  GtkWidget *frame, *frame1, *frame2;
  GtkWidget *main_vbox, *hbox1,*hbox2,*hbox,*hbox_2;
  GtkWidget *entry_start, *entry_stop,*entry_title_file;
  GtkWidget *menubar, *option_menu, *popup_button;

  /* Initialize GTK */
  gtk_init (&argc, &argv);
 
  /* Make a window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);
  gtk_window_set_title (GTK_WINDOW(window), PROGRAMM_NAME);
  gtk_widget_set_size_request (GTK_WIDGET(window),
                              WIDTH_MAIN, HIGHT_MAIN);
 
  /* Make a vbox to put the three menus in */
  main_vbox = gtk_vbox_new (FALSE, 1);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);
  gtk_container_add (GTK_CONTAINER (window), main_vbox);
 
  /* Get the three types of menu */
  /* Note: all three menus are separately created, so they are not the
     same menu */

  hbox = gtk_hbox_new (FALSE, 5);
  hbox1= gtk_hbox_new (FALSE, 5);
  hbox2= gtk_hbox_new (FALSE, 5);
  hbox_2= gtk_hbox_new (FALSE, 5);
  gtk_widget_set_size_request (GTK_WIDGET(hbox_2),
                                330, 20);
  frame = gtk_frame_new ("Время старта:");
  frame1= gtk_frame_new ("Длительность:");
  frame2= gtk_frame_new ( "Название фильма:");
  gtk_container_add (GTK_CONTAINER (hbox), frame);
  gtk_container_add (GTK_CONTAINER (hbox1), frame1);
  gtk_container_add (GTK_CONTAINER (hbox_2), frame2);
  gtk_box_pack_start (GTK_BOX (hbox2), hbox, FALSE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox2), hbox1, FALSE, TRUE, 0);
  gtk_box_pack_end (GTK_BOX (hbox2), hbox_2, FALSE, TRUE, 0);

  menubar = get_menubar_menu (window);
  popup_button = get_popup_menu ();
  gtk_widget_set_size_request (GTK_WIDGET(popup_button),
                              WIDTH_POPUP, HIGHT_POPUP);
  option_menu = get_option_menu ();
  /*------------------------*/
  /* entry ******************/
    entry_start = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_start), 12);
    g_signal_connect (entry_start, "changed",
		      G_CALLBACK (enter_callback_start),
		      (gpointer) entry_start);
    gtk_entry_set_text (GTK_ENTRY (entry_start), "1");

    entry_stop = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_stop), 12);
    g_signal_connect (entry_stop, "changed",
		      G_CALLBACK (enter_callback_stop),
		      (gpointer) entry_stop);
    gtk_entry_set_text (GTK_ENTRY (entry_stop), "6:00:00");

    entry_title_file = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_title_file), 255);
    g_signal_connect (entry_title_file, "changed",
		      G_CALLBACK (enter_callback_title_file),
		      (gpointer) entry_title_file);
    gtk_entry_set_text (GTK_ENTRY (entry_title_file), "title video");

  /*------------------------*/


  /* Pack it all together */
  gtk_box_pack_start (GTK_BOX (main_vbox), menubar, FALSE, TRUE, 0);
  gtk_box_pack_end (GTK_BOX (main_vbox), option_menu, FALSE, TRUE, 0);
  gtk_box_pack_end (GTK_BOX (main_vbox), hbox2, FALSE, FALSE, 0);
  gtk_box_pack_end (GTK_BOX (main_vbox), popup_button, FALSE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (frame1), entry_stop);
  gtk_container_add (GTK_CONTAINER (frame), entry_start);
  gtk_container_add (GTK_CONTAINER (frame2), entry_title_file);

  /* Show the widgets */
  gtk_widget_show_all (window);
  
  /* Finished! */
  gtk_main ();
 
  return 0;
}
