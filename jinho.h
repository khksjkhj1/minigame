#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <termios.h>

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>


 void printscore(int *p1, int *p2);
 void addscore1(int *p1, int *p2);
 void addscore2(int *p1, int *p2);
 int one_or_eleven1(int *p1, int *p2);
 int one_or_eleven2(int *p1, int *p2);
 void game_set(int *p1, int *p2);
 void check_die(int *p1, int *p2);
 void sort();
 void card(int a, int b);
 int load_id();
 int save_id();
 int rank_print();
 void character1();
 void character2();
 void character3();
