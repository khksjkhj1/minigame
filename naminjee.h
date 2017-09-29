#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

/* 메뉴를 보여줌 */
int DP_menu1(void); 
int DP_menu2(void); 
int DP_menu3(void);

int reset_separate_table(void); 
int display_present_table(void); 
int game_start(void); 
int renovate(int);
int m_minlock(int);
int land(void);
int bump_check(int);
int line1_completion(void);
int outcome_print(void);
int outcome_search(void); 
int getch(void);
