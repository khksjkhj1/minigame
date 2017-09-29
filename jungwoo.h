#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int puzzle();
int menu();
void rand_make(int* num);	//1~16까지의 숫자를 섞는 함수.
int success(int* num);		//완성했는지 확인하는 함수.
void output(int* num);		//현재상태의 숫자들을 출력하는 함수.
int input(void);	//사용자로 부터 숫자를 입력받는 함수.

//빈공간(16)과 사용자가 어떤숫자(사용자가입력한 숫자,혹은 처음에 
//퍼즐을섞을때 랜덤숫자) 와의 관계(위, 아래, 양옆)를 따져, 어느
//부분(위, 아래, 양옆)과 바꿀것인지를 결정하는 함수.
int empty_and_select_relation(int* num, int empty_space, int select_space);
void itoas(int value, char* str,int base); //형변환
void strreverse(char* begin, char* end);   //형변환

//입력한 두 수의 값을 바꾸는 함수.
void two_num_change(int *first_num, int *second_num);
int game_(int* num, int move_count);
int save(int* num, int move_count);	
int load(int* num, int move_count);
int ranking_write(int move_count);
int ranking_read();

int ranking_first_make();

