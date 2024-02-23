
C = gcc
LDLIBS = `pkg-config gtk+-2.0 --libs`
CFLAGS = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED

CFLAGSMENU = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED 

N = gtk_video_conv

$N: menu.o infile.o insub.o outfile.o about.o
	$C $^ -o $@ $(LDLIBS)

menu.o: menu.c
	$C -c $^   $(CFLAGSMENU) `pkg-config gtk+-2.0 --cflags --libs` 

about.o: about.c
	$C -c $^   $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` 

infile.o: infile.c 
	$C -c $^ $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs`

insub.o: insub.c 
	$C -c $^ $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs`

outfile.o: outfile.c 
	$C -c $^ $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs`

clear: 
	rm -f *.o 
