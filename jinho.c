#include "jinho.h" // 헤더 인클루드

/*이름과 점수를 저장할 구조체*/
static struct data
{
	char name[30];
	long point;
}temp_point;

 
 int arr[4][13]; // 카드를 저장할 배열 (4개문양,13개의숫자)
 int q=4; // 처음 기본 두장 이후, 플레이어가 추가로 받을 카드를 정하는 변수
 int w=5; // 처음 기본 두장 이후, 토깽이가 추가로 받을 카드를 정하는 변수
 int ap,bp,cp,dp; // 처음 기본 두장의 카드값 (ap,cp는 플레이어의것, bp,dp는 토깽이의 것)
  int adder = 0; // 처음 기본 두장 이후 추가로 받은 카드값
  int p1[2]={0,0}; // 플레이어의 카드값 총합과 카드갯수 저장시킬 배열
  int p2[2]={0,0}; // 토깽이의 카드값 총합과 카드갯수 저장시킬 배열
  long point = 0; // 플레이어의 현재 점수
  int maxpoint = 0; // highest point
 /* 블랙잭 메인 */
int blackjack()
{
  srand(time(NULL)); // 시간별로 다른 난수를 발생시킴
  char s; // 플레이어로부터 (y/n) 입력받는데 쓰임
 
 
system("clear");

character1();

printf("어서와! 블랙잭은 처음이지?\n");
printf("\n응 처음이야(y)\n해본적 있어(n)\n");

 scanf(" %c", &s);
 while(s != 'y' && s !='n')
   {
    printf("\n에러다. 다시 입력해.");
    scanf(" %c", &s);
   }
 if(s == 'y')
   {
   system("clear");
   character2();
   printf("\n그럼 블랙잭의 기본적인 룰을 설명해줄게!");
   
   sleep(2);
   system("clear");
   printf("\n블랙잭 게임은 카드의 합이 21에 가장 가까운 쪽이 이기게 되는 게임이야.\n");
   sleep(1);
   printf("\n너는 21이 될 때까지 몇 장의 카드라도 받을 수 있지만,\n대신 21을 초과하면 패배!\n");
   sleep(2);
   printf("\nJ,Q,K 카드는 모두 10으로 계산하고,\n에이스(1번)카드는 1 또는 11 중 너가 원하는 숫자로 계산할 수 있어.\n");
   sleep(3);
   printf("\n처음엔 두장의 카드를 받고 시작하는데, 만약 처음 받은 두장의 합이 21일 경우\n'블랙잭' 이라 하고, 점수가 두배로 올라.\n");
   sleep(3);
  printf("\n만약 카드를 더 받았는데 카드의 합이 21이 넘어버린다면 '버스트' 라 하고,\n바로 상대방의 승리가 되는거야. OK?\n");
   sleep(3);
   getchar();
   }
   else if(s == 'n'){}
  sleep(1);
  system("clear");
  character2();
  
  printf("\n그럼 바로 게임을 시작해보자구!\n\n");
  sleep(2);
  printf("\n\n 너의 이름을 등록해줘 : ");
  scanf("%s%*c", temp_point.name);
  
  save_id();

  load_id(); /* 파일입출력 */

  sleep(1);
  
  while(1) // 마지막 한번 더 할래?에서 n을 누를때까지 계속 반복
  {
  sort(); // 카드섞기 (이때 받을 카드가 정해짐)
  system("clear");
  printf("먼저 카드를 두장씩 받습니다.\n");
  sleep(1);
  getchar();
     
  printf("카드를 받으시려면 엔터 키를 눌러주세요.\n");
  getchar();
  printf("\n플레이어 님이 첫 번째 카드를 받고있습니다...\n");
  card(0,0);
  sleep(1);
  ap = arr[0][0] % 13;
  
  if(ap==0 || ap>10) //포인트는 13으로 나눈 나머지값으로 하되, 0,11,12,는 각각 K,J,Q로 인식되어 10으로 반환
  { ap=10; }
  if(ap==1)
  {ap = one_or_eleven1(p1, p2);} // 만약 에이스가 나오면 1과 11중 선택할수 있는 기회 제공
  

  sleep(1);
  printf("토깽이가 첫 번째 카드를 받습니다...\n");
  sleep(1);
  card(0,1); // 첫번째 카드 받기
  sleep(1);
  bp = arr[0][1] % 13;
  if(bp == 0 || bp>10)// 토깽이의 카드도 K,Q,J를 10으로 반환.
  { bp=10; }
  else if(bp==1)// 에이스를 뽑았다면
	{
         printf("토깽이가 에이스의 값을 선택중입니다...\n");
         sleep(2);
         if(p2[0]+11<22) // 현재까지의 카드값 + 11이 21을 넘지 않는다면 11선택.
            { 
              bp = 11;
              printf("11로 선택했습니다\n");
            }
         else {
              bp = 1;
              printf("1로 선택했습니다\n");
            }
        }

  sleep(1);
  printf("플레이어님, 두번째 카드를 받으시려면 엔터키를 누르세요.\n");
  getchar();
  system("clear");
  printf("\n두 번째 카드를 받고있습니다...\n");
  sleep(1);
  card(0,0); //첫번째 카드
  card(0,2); // 두번째 카드 받기
  cp = arr[0][2] % 13;
  if(cp == 1)
  {cp = one_or_eleven1(p1, p2);}
  else if(cp == 0 || cp>10)
  { cp=10; }
  
  
  sleep(1);
  printf("토깽이가 두 번째 카드를 받습니다...\n");
  sleep(1);
  card(0,1);// 토깽이의 첫번째 카드
  card(0,3);// 토깽이의 두번째 카드
  dp = arr[0][3] % 13;
  if(dp == 0 || dp>10)
  { dp=10; }
  
  else if(dp==1)
	{
         printf("토깽이가 에이스의 값을 선택중입니다...\n");
         sleep(2);
         if(p2[0]+11<22)
            { 
              bp = 11;
              printf("11로 선택했습니다\n");
            }
         else {
              bp = 1;
              printf("1로 선택했습니다\n");
            }
        }
  
  p1[0] = ap + cp; // 플레이어의 카드값
  p1[1] = 2; // 플레이어의 카드 수
  p2[0] = bp + dp; // 토끼의 카드값
  p2[1] = 2; // 토깽이 카드 수
  sleep(1);
  printscore(p1, p2); //점수 출력
  if(p1[0] == 21)
    { 
     system("clear");
     character3(); // 토깽이 우는 모습 출력
     printf("\nWinner Winner Chicken Dinner !!\n플레이어 님의 블랙잭 입니다. 축하합니다^^\n");
     point += 20;// 점수+ (블랙잭2배)
     printf("\n너의 점수는 %ld point!\n",point);
     save_id();// 점수 저장
     sleep(3);
     rank_print();//랭킹 출력
     printf("\n한판 더 할래?(y/n)");
   scanf(" %c", &s);
   if(s == 'n')
   {   
	
      break;
   }
     
   }
  else if (p2[0] == 21)
    {
     system("clear");
     printf("\n토깽이가 블랙잭을 달성했습니다.\n");
     character2();// 토깽이 웃는 모습 출력
     printf("Winner Winner Chicken Dinner !! 얏호! 내가 한턱 쏠게!");
     point -= 20;
     printf("\n너의 점수는 %ld point!\n",point);
     save_id();
     sleep(3);
     rank_print();
     printf("\n한판 더 할래?(y/n)");
   scanf(" %c", &s);
   if(s == 'n')
   {   
	
      break;
   }
     
  }
      
  
  
  
   addscore1(p1, p2);// 카드 더받기 함수(플레이어)
   addscore2(p1, p2);// 카드 더받기 함수(토깽이)
   game_set(p1, p2);// 승부, 결과 출력
   
   printf("\n너의 점수는 %ld point!\n",point);
   save_id();
   sleep(3);
   rank_print();
   printf("\n현재 이 게임내에서 최고점수는 %d점!\n나를 많이 이겨서 그사람의 점수를 넘어보라구!",maxpoint);

   printf("\n한판 더 할래?(y/n)");
   scanf(" %c", &s);
   if(s == 'n')
   {   
	
      break;
   }
  }

  getchar();
  return 0;
 }


void sort()
 { 
  
   int i,j; 
   int m,n; 
   int cnt,t; 
   cnt=0; 
   for(i=0;i<4;i++){ 
      for(j=0;j<13;j++){ 
         arr[i][j]=++cnt; // 4*13 배열 선언, 숫자 넣기
      } 
   } 
   srand((unsigned int)time(NULL)); 
   for(cnt=0;cnt<10000;cnt++){ // 만번 반복
      i=rand()%4; 
      j=rand()%13; 
      m=rand()%4; 
      n=rand()%13; 
      t=arr[i][j]; 
      arr[i][j]=arr[m][n]; // 랜덤으로 섞기
      arr[m][n]=t; 
   } 
     
 }

void card(int a, int b)
{
 char i;
 

 switch(arr[a][b]%13)
 {
 case 0:
    
    i='K';
    break;
 case 1:
    i='A';
    break;
    
 case 2:
    i=2;
    break;
    
 case 3:
    
    i=3;
    break;
 case 4:
    
    i=4;
    break;
 case 5:
    
    i=5;
    break;
 case 6:
    
    i=6;
    break;
 case 7:
   
    i=7;
    break;
 case 8:
    
    i=8;
    break;
 case 9:
    
    i=9;
    break;
 case 10:
    
    i=10;
    break;
 case 11:
    
    i='J';
    break;
 case 12:
    
    i='Q';
    break;
 }

 if(arr[a][b]<14)
 {
  if(arr[a][b]%13 == 1 || arr[a][b]%13 == 0 || arr[a][b]%13 == 11 || arr[a][b]%13 == 12)
   { 
printf("┏━━━━━━━━┓\n");
printf("┃%c       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♥   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %c┃\n",i);
printf("┗━━━━━━━━┛\n");
   }
  else if(arr[a][b]%13 == 10)
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d      ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♥   ┃\n"); 
printf("┃        ┃\n");
printf("┃      %d┃\n",i);
printf("┗━━━━━━━━┛\n");
  }
  else
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♥   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %d┃\n",i);
printf("┗━━━━━━━━┛\n");
   }
  }
 else if(arr[a][b]>13 && arr[a][b]<27)
 { if(arr[a][b]%13 == 1 || arr[a][b]%13 == 0 || arr[a][b]%13 == 11 || arr[a][b]%13 == 12)
   { 
printf("┏━━━━━━━━┓\n");
printf("┃%c       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♠   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %c┃\n",i);
printf("┗━━━━━━━━┛\n");
   }
  else if(arr[a][b]%13 == 10)
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d      ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♠   ┃\n"); 
printf("┃        ┃\n");
printf("┃      %d┃\n",i);
printf("┗━━━━━━━━┛\n");
  }
  else
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♠   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %d┃\n",i);
printf("┗━━━━━━━━┛\n");
   }}
  else if(arr[a][b]>26 && arr[a][b]<40)
 { if(arr[a][b]%13 == 1 || arr[a][b]%13 == 0 || arr[a][b]%13 == 11 || arr[a][b]%13 == 12)
   { 
printf("┏━━━━━━━━┓\n");
printf("┃%c       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♣   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %c┃\n",i);
printf("┗━━━━━━━━┛\n");
   }
  else if(arr[a][b]%13 == 10)
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d      ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♣   ┃\n"); 
printf("┃        ┃\n");
printf("┃      %d┃\n",i);
printf("┗━━━━━━━━┛\n");
  }
  else
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ♣   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %d┃\n",i);
printf("┗━━━━━━━━┛\n");
   }}
  else if(arr[a][b]>39)
 { if(arr[a][b]%13 == 1 || arr[a][b]%13 == 0 || arr[a][b]%13 == 11 || arr[a][b]%13 == 12)
   { 
printf("┏━━━━━━━━┓\n");
printf("┃%c       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ◆   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %c┃\n",i);
printf("┗━━━━━━━━┛\n");
   }
  else if(arr[a][b]%13 == 10)
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d      ┃\n",i);
printf("┃        ┃\n");
printf("┃    ◆   ┃\n"); 
printf("┃        ┃\n");
printf("┃      %d┃\n",i);
printf("┗━━━━━━━━┛\n");
  }
  else
  {
printf("┏━━━━━━━━┓\n");
printf("┃%d       ┃\n",i);
printf("┃        ┃\n");
printf("┃    ◆   ┃\n"); 
printf("┃        ┃\n");
printf("┃       %d┃\n",i);
printf("┗━━━━━━━━┛\n");
   }
}
 
 
 
}






 /*점수출력*/
 void printscore(int *p1, int *p2)
 {
  printf("\n플레이어의 점수 : %d",p1[0]);
  sleep(1);
  printf("\n토깽이의 점수 : %d",p2[0]);
  sleep(1);
  printf("\n플레이어의 카드 수 : %d",p1[1]);
  printf("\n토깽이의 카드 수 : %d",p2[1]);
  sleep(1);
 }

/*플레이어가 카드를 더 받는 경우*/
 void addscore1(int *p1, int *p2)
 {
 
  int adder; // 추가로 받은 카드의 카드값
  char yn;
  for( ; ; )
  {
   sleep(2);
   printf("\n\n플레이어님, 카드를 더 받으시겠습니까?(y/n)");
   scanf(" %c", &yn);
  
   while(yn != 'y' && yn !='n')
   {
    printf("\n에러입니다. 다시 입력해주세요.");
    scanf(" %c", &yn);
   }
  
   if(yn == 'y')
   { 
    printf("\n카드를 받고있습니다...\n");
    card(0,q);
    adder = arr[0][q] % 13;
    if(adder == 1)
     adder = one_or_eleven1(p1, p2);
    else if(adder == 0 || adder > 10)
     adder = 10;
    printf("\n계속 진행하려면 엔터키를 누르세요.");
    getchar();
    p1[0] += adder;
    p1[1] += 1;
    printscore(p1, p2);
    check_die(p1, p2);// 21을 넘어서 Burst 됐는지 확인
    q+=2;
   }
   else if(yn == 'n')
     break;
  }
  
 }
 
/*토깽이가 카드를 더 받는 경우*/
 void addscore2(int *p1, int *p2)
 {
  int adder;
  char yn;
  printf("\n토깽이가 카드를 더 받을지 선택중입니다...\n");
  for( ;p2[0]<17; )
  {    
   sleep(2);
   
  
   if(p2[0] <= 16)
   {
    printf("\n토깽이가 카드를 한장 더 받습니다.\n");
    card(0,w);
    
    adder = arr[0][w] % 13;
     w+=2;
    if(adder == 1)
	{
         printf("\n토깽이가 에이스의 값을 선택중입니다...\n");
         sleep(2);
         if(p2[0]+11<22)
            { 
              adder = 11;
              printf("11로 선택했습니다\n");
            }
         else 
            {
              adder = 1;
              printf("1로 선택했습니다\n");
            }
        }
    else if(adder == 0 || adder > 10)
     {
     adder = 10; 
     }
   
    p2[0] += adder;
    p2[1] += 1;
    
   }
  else {}
    
    printscore(p1, p2);
    check_die(p1, p2);// 21을 넘어서 Burst 됐는지 확인
   
  }
 }
 
/* 동의할 경우 게임을 끝내고 결과를 출력*/
 void game_set(int *p1, int *p2)
 {
  char yn1;
  printf("\n토깽이가 더이상의 카드를 받지 않기로 했습니다.\n");
  printf("\n플레이어님, 카드를 더이상 받지 않으시겠습니까?(y/n)");
  scanf(" %c" , &yn1);
  while(yn1 != 'y' && yn1 != 'n')
  {
   printf("\n에러입니다. 다시 입력해주세요.");
   scanf(" %c", &yn1);
  }
  
  if(yn1 == 'y')
  {
   printscore(p1, p2);
   if(p1[0] > p2[0]){
    printf("\n플레이어님이 이겼습니다!\n");
    character3();
    point +=10;
    
    }
   else if(p1[0] < p2[0]){
    printf("\n토깽이가 이겼습니다!\n");
    character2();
    point -=10;
        
    }
   else
   {
    if(p1[1] > p2[1]){
     printf("\n토깽이가 이겼습니다!\n");
     character2();
     point -=10;
          
     }
    else if(p1[1] < p2[1]){
     printf("\n플레이어님이 이겼습니다!\n");
     character3();
     point +=10;
     
     }
    else
     printf("\n비겼습니다.\n");
     
   }
   
  }
  else
   printf("\n게임을 계속 진행합니다.");
 }
 
/*둘 중 한명의 점수가 21을 초과할 경우 게임을 종료*/
 void check_die(int *p1, int *p2)
 {
  if(p1[0] > 21)
  {
   printf("\n플레이어님의 점수가 21을 초과하여 게임이 끝났습니다.");
   printf("\n토깽이가 이겼습니다!\n");
   character2();
   point -=10;
   
   getchar();
   
   getchar();
   
  }
  else if(p2[0] > 21)
  {
   printf("\n딜러의 점수가 21을 초과하여 게임이 끝났습니다.");
   printf("\n플레이어님이 이겼습니다!\n");
   character3();
   point +=10;
   
   getchar();
   getchar();
   
  }
 }
 
/*플레이어가 받은 카드가 ACE일 경우 그 값을 정함*/
 int one_or_eleven1(int *p1, int *p2)
 {
  int a;
  char oe;
  printf("\n\n플레이어님이 에이스를 받았습니다.");
  printf("\n에이스의 값을 1로 하려면 o를 누르고,");
  printf("\n11로 하려면 e를 눌러주세요.\n ");
  scanf(" %c", &oe);
  while(oe != 'o' && oe != 'e')
  {
   printf("\n에러입니다. 다시 입력해주세요.");
   scanf(" %c", &oe);
  }
  if(oe =='o')
   a = 1;
  else if(oe =='e')
   a = 11;
  return a;
 }


/* 파일입출력 */
int load_id(void)
{	
  FILE *fp = NULL;
  char name[30];//찾을 이름 저장
  int find = 0;// 찾기 성공실패 확인값
  char yn;

  fp = fopen("data", "rb"); // 읽기전용 

	if(fp == NULL)
		return 0;

	
  system("clear");


  printf("\n 너의 이름을 입력하면 저장된 점수를 불러올 수 있어 : ");
  scanf("%s%*c", name);
  
  while(1)
	{
        fread(&temp_point, sizeof(struct data), 1, fp); //파일 통해 데이터 읽기 
		if(!feof(fp)) //파일의 끝 확인 함수 feof :끝이 아니면
		{
             		if(!strcmp(temp_point.name, name)) //문자열 비교 :문자열이 같으면
			{
				find = 1;
				
                			printf("\n\n어서와 %s. 블랙잭에 온걸 환영해!\n너의 현재 점수는 %ld point. \n나를 이겨서 점수를 높여보라구!\n", temp_point.name, temp_point.point);
			}
		}
		else //파일의 끝이면
		{
			break;
		}
	}
        
        
	if(find == 0) //찾지 못했다면
            printf("\n존재하지 않는 이름입니다\n");
         sleep(2);
 
        return 0;
} 

int save_id()
{
  FILE *fp = NULL;
  
  temp_point.point = point;//현재 점수 저장
  if(temp_point.point >= maxpoint)                     			
	maxpoint = temp_point.point;//현재점수가 최고점수이면 최고점수로 등록
  fp = fopen("data", "ab");//이어쓰기
  fseek(fp, 1, SEEK_END);// 가장 뒤에
  fwrite(&temp_point, sizeof(struct data), 1, fp);
  fclose(fp);
  point = 0;
  
  return 0;
}

int rank_print(void)
{
	FILE *fp = NULL;
	char ch = 1 ;

	fp = fopen("data", "rb"); // 읽기 전용

	if(fp == NULL)
		return 0;

	system("clear");

    	printf("\n\t\t\t\tB L A C K J A C K");
	printf("\n\t\t\t\t\n\n");
	printf("\n\t\t\t이름\t\t\t\t점수\t");

    	while(1)
    	{
            	fread(&temp_point, sizeof(struct data), 1, fp);
            	if(!feof(fp)) //끝이 아니라면 실행
            	{
                		printf("\n\t=======================================");
                		printf("\n\t\t\t%s\t\t\t\t%ld\t\n", temp_point.name, temp_point.point);

            	}
            	else
            	{
                		break;
           	 }
    	}

	fclose(fp);

	printf("\n\n\t게임 메뉴로 이동 : y");
	while(1)
	{
		scanf("%s",&ch);
                
		if(ch == 'y' || ch == 'Y') 
		break;
	}
	return 0;
}


void character1(void)
{
printf("\n\n.........███...............██");
printf("\n........█...█.............█▒▒█");
printf("\n.......█..▓▓.█...........█.▓▓▒█");
printf("\n......█..▓▓▓..█. .......█..▓▓▓▒█");
printf("\n.....█...▓▓▓....███████....▓▓▓.▒█");
printf("\n....█..........................▒▒█");
printf("\n...█............................▒▒█");
printf("\n. ███████...................████████");
printf("\n █...............................▒▒█");
printf("\n█......██......................██.▒▒█");  
printf("\n█......██......................██.▒▒█");
printf("\n█.................................▒▒█");
printf("\n█........▓▓▓....█...█...█....▓▓▓..▒▒█");
printf("\n.█......▓▓▓▓▓....███.███....▓▓▓▓▓▒▒█");
printf("\n..█......▓▓▓.................▓▓▓▒▒█");
printf("\n...███......................▒▒▒███");
printf("\n......█████...............█████");
printf("\n............██▓▓▓▓▓▓▓▓███");
printf("\n..........██.........▒▒▓▓██");
printf("\n.........█▒█..........▒▒▓█▓█");
printf("\n........█▒██..........▒▒▓██▓█");
printf("\n.......█.█.█..........▒▒▓█ █▒█\n");
}

void character2(void)
{
printf("\n\n.........███...............██");
printf("\n........█...█.............█▒▒█");
printf("\n.......█..▓▓.█...........█.▓▓▒█");
printf("\n......█..▓▓▓..█. .......█..▓▓▓▒█");
printf("\n.....█...▓▓▓....███████....▓▓▓.▒█");
printf("\n....█..........................▒▒█");
printf("\n...█............................▒▒█");
printf("\n. ███████...................████████");
printf("\n █...............................▒▒█");
printf("\n█......██......................██.▒▒█");  
printf("\n█.....█..█....................█..█▒▒█");
printf("\n█.................................▒▒█");
printf("\n█........▓▓▓....█...█...█....▓▓▓..▒▒█");
printf("\n.█......▓▓▓▓▓....███.███....▓▓▓▓▓▒▒█");
printf("\n..█......▓▓▓.................▓▓▓▒▒█");
printf("\n...███......................▒▒▒███");
printf("\n......█████...............█████");
printf("\n............██▓▓▓▓▓▓▓▓███");
printf("\n..........██.........▒▒▓▓██");
printf("\n.........█▒█..........▒▒▓█▓█");
printf("\n........█▒██..........▒▒▓██▓█");
printf("\n.......█.█.█..........▒▒▓█ █▒█\n");
}

void character3(void)
{
printf("\n\n.........███...............██");
printf("\n........█...█.............█▒▒█");
printf("\n.......█..▓▓.█...........█.▓▓▒█");
printf("\n......█..▓▓▓..█. .......█..▓▓▓▒█");
printf("\n.....█...▓▓▓....███████....▓▓▓.▒█");
printf("\n....█..........................▒▒█");
printf("\n...█............................▒▒█");
printf("\n. ███████...................████████");
printf("\n █...............................▒▒█");
printf("\n█.....█████..................█████▒▒█");  
printf("\n█......█.█....................█.█.▒▒█");
printf("\n█.................................▒▒█");
printf("\n█........▓▓▓.......████.....▓▓▓..▒▒█");
printf("\n.█......▓▓▓▓▓....██....██...▓▓▓▓▓▒▒█");
printf("\n..█......▓▓▓.................▓▓▓▒▒█");
printf("\n...███......................▒▒▒███");
printf("\n......█████...............█████");
printf("\n............██▓▓▓▓▓▓▓▓███");
printf("\n..........██.........▒▒▓▓██");
printf("\n.........█▒█..........▒▒▓█▓█");
printf("\n........█▒██..........▒▒▓██▓█");
printf("\n.......█.█.█..........▒▒▓█ █▒█\n");
}

