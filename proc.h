#ifndef PROC_H
#define PROC_H

#define PROGRAMM_VERSION "version 1.1.9"
#define PROGRAMM_NAME		 " Графическая оболочка ffmpeg и avconv "
#define PROGRAMM_DESCRIPTION	 "\n  Конвертирование "\
      "видеофайлов в форматы 'mpeg-2' и 'mpeg-4' "\
      "с помощью ffmpeg кодеками mpeg2video и xvid "\
      "и avconv кодеком h264.\n"\
      "   Для запуска процесса конвертирования нажмите"\
      " Timer/start process."

#define FI 1.618
#define HIGHT_MAIN 440
#define WIDTH_MAIN 808
#define HIGHT_POPUP 320
#define WIDTH_POPUP 678

int infile();
int insub();
int outfile();
void about();

#endif
