#include "naminjee.h"

//타이머
#define CCHAR 0
#ifdef CTIME
#undef CTIME
#endif
#define CTIME 1

// 게임 시작, 종료
#define GAME_START 0
#define GAME_END 1

// 방향키, 돌리기키
#define LFT 0
#define RHT 1
#define DOWN 2
#define ROTATE 3

// MINTET 블록 모양별 설정
#define BL_i 0
#define	BL_t 1
#define BL_s 2
#define BL_z 3
#define BL_l 4
#define BL_j 5
#define BL_o 6


char bl_i[4][4][4] =
	{
            1, 1, 1, 1,   0, 0, 0, 0,    0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 1,   0, 0, 0, 1,    0, 0, 0, 1,   0, 0, 0, 1,
            0, 0, 0, 0,   0, 0, 0, 0,    0, 0, 0, 0,   1, 1, 1, 1,
            1, 0, 0, 0,   1, 0, 0, 0,    1, 0, 0, 0,   1, 0, 0, 0
	};

char bl_t[4][4][4] =
	{
            1, 0, 0, 0,   1, 1, 0, 0,   1, 0, 0, 0,   0, 0, 0, 0,
            1, 1, 1, 0,   0, 1, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
			0, 0, 1, 0,   0, 1, 1, 0,   0, 0, 1, 0,   0, 0, 0, 0,
			0, 0, 0, 0,   0, 1, 0, 0,   1, 1, 1, 0,   0, 0, 0, 0
	};

char bl_s[4][4][4] =
	{
			1, 0, 0, 0,    1, 1, 0, 0,    0, 1, 0, 0,   0, 0, 0, 0,
			0, 1, 1, 0,    1, 1, 0, 0,    0, 0, 0, 0,   0, 0, 0, 0,
			0, 1, 0, 0,    0, 1, 1, 0,    0, 0, 1, 0,   0, 0, 0, 0,
            0, 0, 0, 0,    0, 1, 1, 0,    1, 1, 0, 0,   0, 0, 0, 0
	};

char bl_z[4][4][4] =
	{
            0, 1, 0, 0,    1, 1, 0, 0,   1, 0, 0, 0,    0, 0, 0, 0,
			1, 1, 0, 0,    0, 1, 1, 0,   0, 0, 0, 0,    0, 0, 0, 0,
			0, 0, 1, 0,    0, 1, 1, 0,   0, 1, 0, 0,    0, 0, 0, 0,
            0, 0, 0, 0,    1, 1, 0, 0,   0, 1, 1, 0,    0, 0, 0, 0
	};

char bl_l[4][4][4] =
	{
            1, 0, 0, 0,    1, 0, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0,
			1, 1, 1, 0,    1, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
			0, 1, 1, 0,    0, 0, 1, 0,    0, 0, 1, 0,    0, 0, 0, 0,
			0, 0, 0, 0,    0, 0, 1, 0,    1, 1, 1, 0,    0, 0, 0, 0
	};

char bl_j[4][4][4] =
	{
            0, 1, 0, 0,    0, 1, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0,
			1, 0, 0, 0,    1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0,
			1, 1, 0, 0,    1, 0, 0, 0,    1, 0, 0, 0,    0, 0, 0, 0,
			1, 1, 1, 0,    0, 0, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0
	};

char bl_o[4][4][4] =
	{
			1, 1, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
			1, 1, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
			1, 1, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
			1, 1, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
	};

/* 테트리스 테이블은 2차원 배열로 표현 하는데 양옆 2줄과 맨 아래 한줄은 벽을
 *표현 한다. 실제 테트블록들이 움직이고 놓이는 공간은 이를 고려해 계산*/

//2개의 테트리스 테이블
char mintris_table1[21][10];
char mintris_table2[21][17];

int speed = 5;
int saves = 5;
int width = 1;

int minlock_num = 0; //현재 블록
int after_minlock_num = 0; //다음 블록
int minlock_state = 0; //블록의 상태, 회전에 반응
int x = 4, y = 0; //블록의 위치
int game = GAME_END; //게임 상태 변수(시작과 종료)
int max_point = 0; //최고 점수
long pp = 0; //현재 점수

//게임 끝날 때, 사용자 이름 현재 날짜 시간 얻은 점수 저장하는 구조체
static struct result
{
    char name[30];
    int rank;
    int year;
	int month;
	int day;
	int hour;
	int min;
    long point;
}save_inform;

int tetris(void)
{
	int menu = 1;

	while(menu)
	{
        menu = DP_menu1();

		if(menu == 1)
		{

            		speed = DP_menu2(); //speed에 리턴값을 넣음
            		saves =  speed; //saves는 속도값을 받음
            		width = DP_menu3(); //width에 리턴 값을 넣음
           	 	game = GAME_START; //game의 값을 바꿔줌
			menu = game_start();
		}
		else if(menu == 2)
		{
            		outcome_search();
		}
		else if(menu == 3)
		{
            		outcome_print();
		}
		else if(menu == 4)
		{
			return 4;
		}
	}

	
}

/* 메뉴를 보여줌 */
int DP_menu1(void)
{
	int menu = 0;

	while(1)
	{
		system("clear");
        printf("\n\n\t\t\t\tM i n t r i s");
        printf("\n\t\t\t----------------------------");
        printf("\n\n\t\t\t\t게 임 메 뉴\t\n");
        printf("\n\t\t\t✄---------------------------");
		printf("\n\t\t\t=\t1) 게임 시작\t   =");
		printf("\n\t\t\t=\t2) 기록 검색\t   =");
		printf("\n\t\t\t=\t3) 기록 출력\t   =");
		printf("\n\t\t\t=\t4) 종료\t\t   =");
		printf("\n\t\t\t============================");
		printf("\n\t\t\t\t\t 선택 : ");
		scanf("%d",&menu);
		if(menu < 1 || menu > 4)
		{
			continue;
		}
		else
		{
			return menu;
		}
	}
	return 0;
}

/* 메뉴를 보여줌 */
int DP_menu2(void)
{
	int menu = 0;

	while(1)
	{
		system("clear");
        	printf("\n\n\t\t\t\t M i n t r i s");
        	printf("\n\t\t\t----------------------------");
        	printf("\n\n\t\t\t\t   속도\t\n");
        	printf("\n\t\t\t=========✄------------------");
        	printf("\n\t\t\t=\t1) 신\t\t   =");
        	printf("\n\t\t\t=\t2) 영웅\t\t   =");
        	printf("\n\t\t\t=\t3) 상급자\t   =");
        	printf("\n\t\t\t=\t4) 중급자\t   =");
        	printf("\n\t\t\t=\t5) 초보자\t   =");
		printf("\n\t\t\t============================");
		printf("\n\t\t\t\t\t 선택 : ");
		scanf("%d",&menu);
		if(menu < 1 || menu > 5)
		{
			continue;
		}
		else
		{
			return menu;
		}
	}
	return 0;
}
int DP_menu3(void)
{
	int menu = 0;

	while(1)
	{
		system("clear");
        	printf("\n\n\t\t\t\t M i n t r i s");
        	printf("\n\t\t\t----------------------------");
        	printf("\n\n\t\t\t\t  너비\t\n");
        	printf("\n\t\t\t=====================✄------");
        	printf("\n\t\t\t=\t1) 8칸\t\t  =");
        	printf("\n\t\t\t=\t2) 15칸\t\t  =");
        	printf("\n\t\t\t============================");
		printf("\n\t\t\t\t\t 선택 : ");
		scanf("%d",&menu);
		if(menu < 1 || menu > 2)
		{
			continue;
		}
		else
		{
			return menu;
		}
	}
	return 0;
}

int game_start(void)
{
	static struct sigaction sa;//sigaction: 시그널 처리를 다양하게 한다.
	static struct itimerval timer;//타이머 설정
    time_t time_p;
    struct tm *t;
    FILE *fp = NULL;// 파일 입출력 있을 예정

	if(game == GAME_START)
	{
        reset_separate_table();//테이블 분리해서 초기화

        //일정시간이 지나면 신호를 전달하게 하는 타이머
        //타이머 시그널 발생시에 불러주는 신호처리기 타이머 시그널 핸들러 설치
        memset(&sa, 0, sizeof (sa));
        sa.sa_handler = &renovate;// 시간단위 처리함수 핸들러에 등록(신호 핸들러를 시간단위 처리함수로 지정)
        sigaction(SIGVTALRM, &sa, NULL);// SIGVTALRM를 지정하면서 NULL에 이전 정보를 구함

        //250 밀리 초 후에 끝내기 타이머를 설정
        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 1;

        //모든 250 밀리 초 후!
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 1;

        //가상 타이머를 시작. 이 과정이 행해질 때마다 카운트 다운.
        setitimer(ITIMER_VIRTUAL, &timer, NULL);

		while(1)
		{
			if(game == GAME_END)
			{

				timer.it_value.tv_sec = 0;
				timer.it_value.tv_usec = 0;
				timer.it_interval.tv_sec = 0;
				timer.it_interval.tv_usec = 0;
				setitimer(ITIMER_VIRTUAL,&timer,NULL);


				// 기록 파일로 저장

                		printf("\n\n 최종 득점 : %ld ", pp);
				printf("\n\n 이름을 입력 하세요 : ");
                		scanf("%s%*c", save_inform.name);
                		save_inform.point = pp;
				//새로운 점수가 max보다 크면 max포인트 바꿔줌
               	 		if(save_inform.point >= max_point)
                    		max_point = save_inform.point;


                time_p = time(NULL); //초단위로 표현 (현재의 시간)
                t = localtime(&time_p); //초단위 시간 분리 t struct 에 삽입, time.h 참조 time_p입력 받아 유저의 time 존에 맞게 돌려줌 tm구조체에 이미 다있다.

                		save_inform.year = t->tm_year + 1900;//년
				save_inform.month = t->tm_mon + 1;//월은 0부터 시작한다. 그러므로 프로그램상에서 제대로 표현하려면 +1을 해주어야 한다.
				save_inform.day = t->tm_mday;
				save_inform.day = t->tm_mday;
				save_inform.hour = t->tm_hour;
				save_inform.min = t->tm_min;

				fp = fopen("result", "ab");//이진파일을 추가로 연다.
				fseek(fp, 1, SEEK_END);//연파일에서 파일 끝으로 부터 뒤로1바이트 이동.
                   		fwrite(&save_inform, sizeof(struct result), 1, fp);// 파일에 버퍼 내용을 쓴다.
				fclose(fp);

				x = 3, y =0;//블록의 위치 초기화
                		pp = 0;//현재 점수 초기화

				return 1;
			}
		}
	}

  return 0;
}

// 현재 테트리스테이블 보여줌
int display_present_table(void)
{
	int i, j;
    char (*minlock_pointer)[4][4][4] = NULL;

    switch(after_minlock_num)
	{
        case BL_i :	minlock_pointer = &bl_i;
								  	break;
        case BL_t :	minlock_pointer = &bl_t;
										break;
        case BL_s : minlock_pointer = &bl_s;
										break;
        case BL_z : minlock_pointer = &bl_z;
										break;
        case BL_l : minlock_pointer = &bl_l;
										break;
        case BL_j : minlock_pointer = &bl_j;
										break;
        case BL_o :	minlock_pointer = &bl_o;
										break;
	}

    system("clear");//유닉스 모드 clear


    printf("\n\n After minlock\n");

	for(i = 0 ; i < 4 ; i++)
	{
		printf("\n ");
		for(j = 0 ; j < 4 ; j++)
		{
            if((*minlock_pointer)[0][i][j] == 1)
                printf("▣");
            else if((*minlock_pointer)[0][i][j] == 0)
				printf(" ");
		}
	}

	if(width == 1)
	{
	for(i = 2 ; i < 21 ; i++)
	{
		printf("\t");
		for(j = 0 ; j < 10 ; j++)
		{
			if(j == 0 || j == 9|| (i == 20 && (j > 1 || j < 9)))
			{
                printf("▒");
			}
            else if(mintris_table1[i][j] == 1)
                printf("▣");
            else if(mintris_table1[i][j] == 0)
				printf(" ");
		}
		printf("\n");
	}
	}
	else if(width == 2)
	{
	for(i = 2 ; i < 21 ; i++)
	{
		printf("\t");
		for(j = 0 ; j < 17 ; j++)
		{
			if(j == 0 || j == 16|| (i == 20 && (j > 1 || j < 16)))
			{
                printf("▒");
			}
            else if(mintris_table2[i][j] == 1)
                printf("▣");
            else if(mintris_table2[i][j] == 0)
				printf(" ");
		}
		printf("\n");
	}
	}
	return 0;
}

//테트리스테이블 초기화 한다. 벽과 공간 구분
int reset_separate_table(void)
{
    int i = 0, j = 0;

    //높은 난이도 맵 초기화
	for(i = 0 ; i < 20 ; i++)
		for(j = 1 ; j < 9 ; j++)
            mintris_table1[i][j] = 0;

	for(i = 0 ; i < 21 ; i++)
	{
        mintris_table1[i][0] = 1;
        mintris_table1[i][9] = 1;
	}

	for(j = 1 ; j < 9 ; j++)
        mintris_table1[20][j]= 1;

    //낮은 난이도 맵 초기화
	for(i = 0 ; i < 20 ; i++)
		for(j = 1 ; j < 16 ; j++)
            mintris_table2[i][j] = 0;

	for(i = 0 ; i < 21 ; i++)
	{
        mintris_table2[i][0] = 1;
        mintris_table2[i][16] = 1;
	}

	for(j = 1 ; j < 16 ; j++)
        mintris_table2[20][j]= 1;

	return 0;
}

//문자를 바로 입력 받을 수 있는 함수
int getch(void)
{
             char   chr;
             int   err;
             static struct termios Oty, Nty;

             fflush(stdout);
             tcgetattr(0, &Oty);
             Nty = Oty;
             Nty.c_iflag  =  0;
             Nty.c_oflag  =  0;
             Nty.c_lflag &= ~ICANON;
#if 1
            Nty.c_lflag &= ~ECHO;
#else
            Nty.c_lflag |=  ECHO;
#endif
            Nty.c_cc[VMIN]  = CCHAR;
            Nty.c_cc[VTIME] = CTIME;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

            if (0 == (err = tcsetattr(0, FLAG, &Nty)))
            {
                err  = read(0, &chr, 1 );
                err += tcsetattr(0, FLAG, &Oty);
            }

            return (err == 1 ? (int) chr : -1 );
}

//계속 호출되는 새로고침 함수
//타이머에 콜백 함수로 등록되어 계속 새로고침 하며 호출되는 함수. 키입력 확인, 화면 새로고침, 한줄 완성 확인
int renovate(int signum)
{
    static int d_count = 0; //0-(speed-1)
    static int s_count = 0; //0-9
    static long sp_count = 0; //0-499
    static int first_start = 0;

    char chr;

    srand((unsigned)time(NULL));//랜덤함수 위해 있다.

    if(first_start == 0)
	{
        minlock_num= rand()%7;// 0-6중에 랜덤을 돌린다.
        if(first_start == 0)
            first_start++;
	}

    printf("\n 득점 : %ld | 속도 : %d | 최고점수  : %d", pp,  speed, max_point);// 상태 표시줄
    display_present_table();//현제 테트리스 상태
    line1_completion();//1라인 완성되었는가 확인

    printf("\n 게임 멈추려면? : P");

    if(d_count ==  speed-1)
	{
        pp += 1; // 1점 상승
        m_minlock(DOWN);//블록 내려옴
    }

    if(sp_count == 499)
	{
        if( speed != 1)
             speed--;//블록 속도 빨라짐
	}

    d_count++;
    d_count %=  speed;
    sp_count++;
    sp_count %= 500;

    if(x == 4 && y == 0) //딱 처음 블록이 나왔는데
	{
        if(bump_check(LFT) || bump_check(RHT) || bump_check(DOWN) || bump_check(ROTATE)) //충돌이 일어남
		{
			printf("\n Game End! \n");
            		d_count = 0;
            		s_count = 0;
            		sp_count = 0;
            		speed = saves;
            		first_start = 0;
			game = GAME_END;
		}
	}

    if(bump_check(DOWN))
	{
        if(s_count == 9)
		{
            minlock_num= after_minlock_num; //다음블록을 현재블록으로 설정
            after_minlock_num = rand()%7; //새로운블록 랜덤
            minlock_state = 0;
            x = 4;
			y = 0;
		}
        s_count++;
        s_count %= 10;
	}

    chr = getch(); //키를 받음

    //키받고 블록 움직이거나 끝내기
    switch(chr)
	{
		case 74	 :
        	case 106 :	m_minlock(LFT);
					  		break;
		case 76	 :
        	case 108 :	m_minlock(RHT);
						  	break;
		case 75	 :
        	case 107 :	m_minlock(DOWN);
								break;
		case 73	 :
        	case 105 :	m_minlock(ROTATE);
								break;
		case 65  :
        	case 97  :	land();
								break;
 		case 80  :
        	case 112 :	d_count = 0;
                                s_count = 0;
                                sp_count = 0;
                                speed = saves;
                                first_start = 0;
                                game = GAME_END;
 								break;
 		default : 	break;
	}
	return 0;
}

//충돌검사후 블록 이동
int m_minlock(int command)
{
    int i, j;
    int freshx, freshy;
    int before_x, before_y;
    int before__minlock_state;
    char (*minlock_pointer)[4][4][4] = NULL;

    freshx = x;
    freshy = y;

    before__minlock_state = minlock_state;

    if(bump_check(command) == 0)
	{
		switch(command)
		{
            case	LFT :	freshx--;
										break;
            case	RHT :	freshx++;
										break;
            case	DOWN :	freshy++;
										break;
            case ROTATE :	minlock_state++;
                                        minlock_state %= 4;
										break;
		}
	}
	else
	{
		return 1;
	}

    switch(minlock_num)
    {
        case BL_i :	minlock_pointer = &bl_i;
                                    break;
        case BL_t :	minlock_pointer = &bl_t;
                                        break;
        case BL_s : minlock_pointer = &bl_s;
                                        break;
        case BL_z : minlock_pointer = &bl_z;
                                        break;
        case BL_l : minlock_pointer = &bl_l;
                                        break;
        case BL_j : minlock_pointer = &bl_j;
                                        break;
        case BL_o : minlock_pointer = &bl_o;
                                        break;
    }


	if(width == 1)
	{
    for(i = 0, before_y = y ; i < 4 ; i++, before_y++)
	{
        for(j = 0, before_x = x ; j < 4 ; j++, before_x++)
		{
            if(before_x > 0 && before_x < 9 && before_y < 20 && before_y > 0)
                if((*minlock_pointer)[before__minlock_state][i][j] == 1)
                        mintris_table1[before_y][before_x] = 0;

		}
	}

    x = freshx;
    y = freshy;

    for(i = 0, freshy = y ; i < 4 ; i++, freshy++)
	{
        for(j = 0, freshx = x ; j < 4 ; j++, freshx++)
		{
            if(freshx > 0 && freshx < 9 && freshy < 20 && freshy > 0)
                if((*minlock_pointer)[minlock_state][i][j] == 1)
                    mintris_table1[freshy][freshx] = (*minlock_pointer)[minlock_state][i][j];
		}
	}
	}
	else if(width == 2)
	{
    for(i = 0, before_y = y ; i < 4 ; i++, before_y++)
	{
        for(j = 0, before_x = x ; j < 4 ; j++, before_x++)
		{
            if(before_x > 0 && before_x < 16 && before_y < 20 && before_y > 0)
                if((*minlock_pointer)[before__minlock_state][i][j] == 1)
                        mintris_table2[before_y][before_x] = 0;

		}
	}

    x = freshx;
    y = freshy;

    for(i = 0, freshy = y ; i < 4 ; i++, freshy++)
	{
        for(j = 0, freshx = x ; j < 4 ; j++, freshx++)
		{
            if(freshx > 0 && freshx < 16 && freshy < 20 && freshy > 0)
                if((*minlock_pointer)[minlock_state][i][j] == 1)
                    mintris_table2[freshy][freshx] = (*minlock_pointer)[minlock_state][i][j];
		}
	}
	}

	return 0;
}

/* 블록이 이동, 회전하기 전에 충돌되는 블록이나 벽이 없는지 확인하는 함수*/
int bump_check(int command)
{
	int i, j;
	int tempx, tempy;
    int before_x, before_y;
    int temp_minlock_state;
    char (*minlock_pointer)[4][4][4];
    char temp_mintris_table1[21][10];
    char temp_mintris_table2[21][17];

    before_x = tempx = x;
    before_y = tempy = y;
    temp_minlock_state = minlock_state;

	switch(command)
	{
        case	LFT :	tempx--;
									break;
        case	RHT :	tempx++;
									break;
		case	DOWN :	tempy++;
									break;
        case ROTATE : temp_minlock_state++;
                                    temp_minlock_state %=  4;
									break;
	}
    switch(minlock_num)
    {
        case BL_i :	minlock_pointer = &bl_i;
                                    break;
        case BL_t :	minlock_pointer = &bl_t;
                                        break;
        case BL_s : minlock_pointer = &bl_s;
                                        break;
        case BL_z : minlock_pointer = &bl_z;
                                        break;
        case BL_l : minlock_pointer = &bl_l;
                                        break;
        case BL_j : minlock_pointer = &bl_j;
                                        break;
        case BL_o :	minlock_pointer = &bl_o;
                                        break;
    }

	if(width == 1)
	{
	for(i = 0 ; i < 21 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
            temp_mintris_table1[i][j] = mintris_table1[i][j];
		}
	}

    for(i = 0, before_y = y ; i < 4 ; i++, before_y++)
	{
        for(j = 0, before_x = x ; j < 4 ; j++, before_x++)
		{
            if(before_x > 0 && before_x < 9 && before_y < 20 && before_y > 0)
			{
                if((*minlock_pointer)[minlock_state][i][j] == 1)
                        temp_mintris_table1[before_y][before_x] = 0;
			}
		}
	}

	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j < 4 ; j++)
		{

            if(temp_mintris_table1[tempy+i][tempx+j] == 1 && (*minlock_pointer)[temp_minlock_state][i][j] == 1)
					return 1;
		}
	}
	}

	else if(width == 2)
	{
	for(i = 0 ; i < 21 ; i++)
	{
		for(j = 0 ; j < 17 ; j++)
		{
            temp_mintris_table2[i][j] = mintris_table2[i][j];
		}
	}

    for(i = 0, before_y = y ; i < 4 ; i++, before_y++)
	{
        for(j = 0, before_x = x ; j < 4 ; j++, before_x++)
		{
            if(before_x > 0 && before_x < 16 && before_y < 20 && before_y > 0)
			{
                if((*minlock_pointer)[minlock_state][i][j] == 1)
                        temp_mintris_table2[before_y][before_x] = 0;
			}
		}
	}

	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j < 4 ; j++)
		{

            if(temp_mintris_table2[tempy+i][tempx+j] == 1 && (*minlock_pointer)[temp_minlock_state][i][j] == 1)
					return 1;
		}
	}
	}

	return 0;
}

//충돌있기 전까지 블록을 내림.
int land(void)
{
    while(!bump_check(DOWN))//충돌안하면
        m_minlock(DOWN);//계속내림

	return 0;
}

//한줄이 완성되었는지 확인하는 함수. 완성되면 한줄을 지우고, 점수에 1000점을 더한다
int line1_completion(void)
{
	int i, j;
    int temp_i, temp_j;
	int line_hole;

	if(width ==1)
	{
	for(i = 19 ; i > 0 ; i--)
	{
		line_hole = 0;
		for(j = 1 ; j < 9 ; j++)
		{
            if(mintris_table1[i][j] == 0) //한개라도 빈칸 있으면 다음 줄로 감.
			{
				line_hole = 1;
			}
		}
        //한줄 모두 차있을 때 1줄 지원짐
		if(line_hole == 0)
		{
            pp += 1000;
            for(temp_i = i ; temp_i > 0 ; temp_i--)
			{
                for(temp_j = 0 ; temp_j < 9 ; temp_j++)
				{
                    mintris_table1[temp_i][temp_j] = mintris_table1[temp_i-1][temp_j];
				}
			}
		}
	}
	}
	else if(width ==2)
	{
	for(i = 19 ; i > 0 ; i--)
	{
		line_hole = 0;
		for(j = 1 ; j < 16 ; j++)
		{
            if(mintris_table2[i][j] == 0)
			{
				line_hole = 1;
			}
		}

		if(line_hole == 0)
		{
            pp += 1000;
            for(temp_i = i ; temp_i > 0 ; temp_i--)
			{
                for(temp_j = 0 ; temp_j < 16 ; temp_j++)
				{
                    mintris_table2[temp_i][temp_j] = mintris_table2[temp_i-1][temp_j];
				}
			}
		}
	}
	}

	return 0;
}

/*메뉴에서 기록검색시 호출되어 기러고을 검색하는 함수*/
int outcome_search(void)
{
	FILE *fp = NULL;
	char name[30];
	char ch;
	int find = 0;

	fp = fopen("result", "rb");

	if(fp == NULL)
		return 0;

	system("clear");

	printf("\n\n\t\t검색할 이름을 입력하세요.  : ");
	scanf("%s%*c", name);

    	printf("\n\t\t\t\tM i n t r i s");
    	printf("\n\t\t\t\t 게임 기록\n\n");
	printf("\n\t\t이름\t\t점수\t   날짜\t\t 시간");

	while(1)
	{
        	fread(&save_inform, sizeof(struct result), 1, fp);//파일 통해 데이터 읽기
        	if(!feof(fp))//파일의 끝 확인 함수 feof :끝이 아니면
		{
            		if(!strcmp(save_inform.name, name))//문자열 비교 :문자열이 같으면
			{			
				find = 1;
				printf("\n\t========================================================");
                		printf("\n\t\t%s\n\t\t\t\t%ld\t%d. %d. %d.  |  %d : %d\n", save_inform.name, save_inform.point, save_inform.year, save_inform.month, save_inform.day, save_inform.hour, save_inform.min);
			}
		}
	
        	else//파일의 끝이면
		{
			break;
		}
	}

	if(find == 0)
		printf("\n\n\n\t\t검색된 이름이 없습니다.");

    	printf("\n\n\n\t\t게임 메뉴로 돌아가려면? : M");
	while(1)
	{
        	ch = getch();//문자값을 입력받음
        	if(ch == 77 || ch == 109)//m,M이 입력되었을 때
			break;
	}

	return 0;
}

//메뉴에서 기록 출력 (검색 부에서 문자열 비교만 빠짐)
//메뉴에서 기록출력시 호출되어 기록을 출력하는 함수
int outcome_print(void)
{
	FILE *fp = NULL;
	char ch = 1 ;

    fp = fopen("result", "rb");//이진파일을 읽기 전용으로 염

	if(fp == NULL)
		return 0;

	system("clear");

    printf("\n\t\t\t\tM i n t r i s");
	printf("\n\t\t\t\t 게임 기록\n\n");
	printf("\n\t\t이름\t\t점수\t   날짜\t\t 시간");

    while(1)
    {
            fread(&save_inform, sizeof(struct result), 1, fp);
            if(!feof(fp))
            {
                printf("\n\t========================================================");
                printf("\n\t\t%s\n\t\t\t\t%ld\t%d. %d. %d.  |  %d : %d\n", save_inform.name, save_inform.point, save_inform.year, save_inform.month, save_inform.day, save_inform.hour, save_inform.min);

            }
            else
            {
                break;
            }
    }

	fclose(fp);

    printf("\n\n\t게임 메뉴로 돌아가려면? : M");
	while(1)
	{
        ch = getch();//문자값을 입력받음
        if(ch == 77 || ch == 109)//m,M이 입력되었을 때
			break;
	}
	return 0;

}


