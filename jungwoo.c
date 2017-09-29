#include "jungwoo.h"

int puzzle()
{
	
	
	ranking_first_make();

	menu();	
	
	return 0;
}



int menu()
{
	int menu_select=0;
	int remenu=1;
	int file_err_state=0;
	int result;		//성공했는지의 여부를 넣을 변수.

	int num[16];	//숫자16개 생성.
	int move_count = 0;		//몇번 만에 성공

	 
	do{
		system("clear");
	     	printf("\n\n\t\t\t\tP u z z l e.CHOI.kW");
        	printf("\n\t\t\t✄--------------------------");
        	printf("\n\t\t\t=\t 1) 게임 시작\t  =");        	
		printf("\n\t\t\t=\t 2) 불러 오기\t  =");
		printf("\n\t\t\t=\t 3) 기록 검색\t  =");
		printf("\n\t\t\t=\t 4) 종  료\t  =");
		printf("\n\t\t\t============================");
		printf("\n\t\t\t\t\t 선택 : ");
		
		menu_select = input();		

		switch(menu_select){
		case 1:	//새게임시작
			//printf("1번실행\n");	//새게임을 초기화하고, 게임함수를 부름.
			
			do{
				rand_make(num);		//num에 1~16까지 랜덤하고 숫자 생성.
				result = success(num);	
				//성공했는지 확인하는 함수 호출  : 완성시 0반환  :미완성시 1반환
			}while(result!=1);	//1~16정렬이 완벽하게 나오면 다시 생성.
			
			file_err_state = game_(num, move_count);

			remenu=1;			
			
			break;		
		case 2:	
			file_err_state = load(num, move_count);//불러오기
			remenu=1;
			
			break;	
		case 3:	
			file_err_state = ranking_read();//랭킹확인
			remenu=1;
			
			break;
		case 4:	
			remenu=1;  //종료
			
			break;
		default: 
			//printf("다시 입력 하세요!!\n\n"); 
			remenu = 0;
			
			continue;
		}
	}while(remenu==0);
	return file_err_state;
}


void rand_make(int* num)	//1~16까지의 숫자를 섞는 함수.
{
	int i;	//for문에 사용.
	int r;	//랜덤에 사용할 변수.
	int empty_space=15;	//빈칸의 초기값은 4행4열에 위치한다.
		 		//(배열은 0부터시작함으로16이 아니라 15이다.)
	
	for(i=1; i<= 16; i++){	//1~16까지 생성.
		num[i-1]=i;		
	}
	srand(time(0));		
	//이함수를 씀으로써 랜덤에서 유사한 숫자가 나오는것을 예방한다.
	
	
	for(i=0; i<=600 ; i++){
		r = rand()%15;	//0~15까지중의 숫자를 생성.
		empty_space = empty_and_select_relation(num, empty_space, r);
	}
}

int success(int* num){		//각 배열에 해당 숫자가 있으면 완성!(빈칸포함)
	if(num[0]==1 && num[1]==2 && num[2]==3 && num[3]==4 && num[4]==5 && 
		num[5]== 6 && num[6]==7 && num[7]==8 && num[8]==9 && num[9] ==10
		&& num[10]==11 && num[11]==12 && num[12]==13 && num[13]==14 &&
		num[14]==15 && num[15]==16)	
	{
		
		return 0;	//종료(성공)
	}else{
		return 1;	//계속
	}
}




int input(void)		//사용자로 부터 숫자를 입력받는 함수.
{
     int num;	 
     char ch[100];	

     
     gets(ch);//사용자로 부터 문자열을 입력 받습니다.
	 
     num = atoi(ch); //문자열을 정수로 바꾸어주는 함수 입니다.
	
     while(1)
     {
          if(num == 0) // atoi 함수는 문자열을 정수로 반환할때 입력값이 옳지 않으면 0을 반환
          {
                //printf("please enter the integer!! : ");
                gets(ch);
                num = atoi(ch);
          }
         else	//옳게 입력되었으므로
         {
                 break;
         }
    }
    return num;	//사용자 숫자를 반환.

}

int empty_and_select_relation(int* num, int empty_space, int select_space)
{
	//사용자가 관계없는 숫자를 입력했을때는 빈공간의 위치가 안바뀌므로.. 
	int new_empty_space = empty_space;	
	
	if(empty_space == 0){	//빈공간이 0자리 일경우
		if(num[empty_space+1] == num[select_space]){//오른쪽 
			//오른쪽과 빈공간(16)을 자리바꿀예정
			//빈공간과 사용자숫자를 바꾼다.
			two_num_change(&num[empty_space], &num[select_space]);
			//빈공간의 위치가 바뀐다.
			new_empty_space = empty_space+1;
			//새로운 빈공간의 위치를 리턴.
			return new_empty_space;
		}else if(num[empty_space+4] == num[select_space]){	//아래
			//아래와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+4;
			return new_empty_space;
		}
	}else if(empty_space == 1 || empty_space == 2){	//1,2자리 일경우
		if(num[empty_space-1] == num[select_space]){	//왼쪽
			//왼쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-1;
			return new_empty_space;
		}else if(num[empty_space+1] == num[select_space]){//오른쪽
			//오른쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+1;
			return new_empty_space;
		}else if(num[empty_space+4] == num[select_space]){//아래
			//아래와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+4;
			return new_empty_space;
		}
	}else if(empty_space == 3){	//3자리 일경우
		if(num[empty_space-1] == num[select_space]){	//왼쪽
			//왼쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-1;
			return new_empty_space;
		}else if(num[empty_space+4] == num[select_space]){//아래
			//아래와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+4;
			return new_empty_space;
		}
	}else if(empty_space == 4 || empty_space == 8){	//4,8자리 일경우
		if(num[empty_space-4] == num[select_space]){		//위
			//위와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-4;
			return new_empty_space;
		}else if(num[empty_space+1] == num[select_space]){	//오른쪽
			//오른쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+1;
			return new_empty_space;
		}else if(num[empty_space+4] == num[select_space]){	//아래
			//아래와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+4;
			return new_empty_space;
		}
	}else if(empty_space == 7 || empty_space == 11){	//7,11자리 일경우
		if(num[empty_space-4] == num[select_space]){	//위
			//위와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-4;
			return new_empty_space;
		}else if(num[empty_space-1] == num[select_space]){	//왼쪽
			//왼쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-1;
			return new_empty_space;
		}else if(num[empty_space+4] == num[select_space]){	//아래
			//아래와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+4;
			return new_empty_space;
		}
	}else if(empty_space == 5 || empty_space == 6 ||
	  empty_space == 9 || empty_space == 10){	//5,6,9,10자리 일경우
		if(num[empty_space-4] == num[select_space]){	//위
			//위와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-4;
			return new_empty_space;
		}else if(num[empty_space-1] == num[select_space]){	//왼쪽
			//왼쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-1;
			return new_empty_space;
		}else if(num[empty_space+1] == num[select_space]){	//오른쪽
			//오른쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+1;
			return new_empty_space;
		}else if(num[empty_space+4] == num[select_space]){	//아래
			//아래와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+4;
			return new_empty_space;
		}
	}else if(empty_space == 12){	//12자리 일경우
		if(num[empty_space-4] == num[select_space]){	//위
			//위와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-4;
			return new_empty_space;
		}else if(num[empty_space+1] == num[select_space]){	//오른쪽
			//오른쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+1;
			return new_empty_space;
		}
	}else if(empty_space == 13 || empty_space == 14){	//13,14자리 일경우
		if(num[empty_space-4] == num[select_space]){	//위
			//위와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-4;
			return new_empty_space;
		}else if(num[empty_space-1] == num[select_space]){	//왼쪽
			//왼쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-1;
			return new_empty_space;
		}else if(num[empty_space+1] == num[select_space]){	//오른쪽
			//오른쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space+1;
			return new_empty_space;
		}
	}else if(empty_space == 15){	//15자리 일경우
		if(num[empty_space-1] == num[select_space]){	//왼쪽
			//왼쪽과 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-1;
			return new_empty_space;
		}else if(num[empty_space-4] == num[select_space]){	//위
			//위와 빈공간(16)을 자리바꿀예정
			two_num_change(&num[empty_space], &num[select_space]);
			new_empty_space = empty_space-4;
			return new_empty_space;
		}
	}
	
	return new_empty_space;
}

//두 수의 값을 바꾸는 함수.
void two_num_change(int *first_num, int *second_num)
{
	int temp;
	
	temp = *first_num;
	*first_num = *second_num;
	*second_num = temp;
}

//형변환
void strreverse(char* begin, char* end)
{
	char aux;

	while(end>begin)
		aux=*end, *end-- = *begin, *begin++ = aux;
}
void itoas(int value, char* str,int base)
{
	static char num[] = "0123456789abcdefghijklmnoprstuvwxyz";
	char * wstr = str;
	int sign;
	div_t res;

	if(base<2 || base>35) { *wstr = '\0'; return;}
	if((sign = value) < 0) value = -value;

	do{
			res = div(value,base);
			*wstr++ = num[res.rem];
	}while(value=res.quot);

	if(sign<0) *wstr++='-';
	*wstr ='\0';

	strreverse(str,wstr-1);

}

void output(int* num)	//화면 출력 함수.
{
	int i;
	char ch_num[16][100];
	int empty_space;

	//빈공간이 몇번째 있는지 찾자.
	for(i=0; i<16; i++){
		if(num[i] == 16){//빈공간(16)을 찾으면
			empty_space = i;	//i번째 빈공간(16)이 들어있다.empty_space에 i를 넣음.
			break;
		}
	}
	
	//형변환
	for(i=0 ; i<16 ; i++){
		itoas(num[i], ch_num[i],10);
	}
	

	//출력
	for(i=0 ; i< 16 ; i++){
		if(i%4==0){
			printf("\n\t\t\t ");
		}
		if(i!=empty_space){
			printf("%3s", ch_num[i]);
		}else{	//16이면
			printf("   ");
		}
	
		
	}
	printf("\n");
	
   	
	
	
}

int game_(int* num, int move_count)//랜덤의 숫자가 들어간 배열과 , 움직인 횟수가 들어감
{
	
	//char char_num[16][10];
	int result;		//성공했는지의 여부를 넣을 변수.
	int select;		//사용자의 입력을 받을 변수.
	int empty_space;	//빈공간이 몇번째에 있는지(임시로 16이 빈공간이다!!!)
	int new_empty_space;	//빈공간과 어느숫자와 자리를 바꾸면 빈공간이 몇번째 있는지바뀐다.
	int select_space=-1;		//사용자가 입력한 숫자가 몇번째 있는지
	int i;					//반복에 사용할 변수
	
	int file_err_state=0;



	//새게임이면
	
	//로드게임이면
	//로드해서 num에 넣고, move_count도 넣고시작함.



	output(num);	//화면 출력.
	

	//빈공간이 몇번째 있는지 찾자.
	for(i=0; i<16; i++){
		if(num[i] == 16){//빈공간(16)을 찾으면
			empty_space = i;	//i번째 빈공간(16)이 들어있다.empty_space에 i를 넣음.
			break;
		}
	}
	
	
	
	do{
		printf("                                          나가기:\"100\"\n");
		printf("                                    움직인 횟수 : %d", move_count);
		printf("\n움직일 숫자를 입력하시오 :  ");
		select = input();		//사용자 입력
		
		//저장하기를 입력했다면 save()를 불러서 파일입출력을 열어서 정보를 저장.
		if(select ==100){
			file_err_state = save(num, move_count);
			if(file_err_state ==1) return 1;

			else printf("저장 완료!\n");
			printf("Bye bye.\n");
			break;//return 0;
		}

		move_count++;		//입력할때 마다 카운트 함.
		
		//사용자가 선택입력한 select가 몇번째 자리에 있는지 찾자.
		for(i=0; i<16; i++){
			if(num[i] == select){//찾으면
				select_space = i;	//i번째 사용자숫자가 들어있다.select에 i를 넣음.
				break;
			}
		}
		
		
		//빈공간과 사용자가 입력한 숫자가 (위, 아래, 양옆)등에 위치하는가
		//확인후 관계가 있다면 "입력한 두 수의 값을 바꾸는 함수"를 
		//호출하여 그 숫자와 빈공간(16)의 위치를 바꾼다.
		new_empty_space = empty_and_select_relation(num, empty_space, select_space);
		if(new_empty_space !=empty_space)//PlaySound("put.wav", NULL, SND_SYNC );

		empty_space = new_empty_space; //빈공간의 위치가 바뀐다.
		system("clear");
		output(num);	//화면 출력.
		
		result = success(num);	//완성했는지 확인하는 함수 호출.
		if(result == 0){		//완성했다면
			printf("당신은%d회 움직여서 퍼즐을 맞추었습니다. \n", move_count); //종료
			file_err_state = ranking_write(move_count);
			if(file_err_state ==1) return 1;
			
			break;
		}//완성했으면 게임종료.
	}while(1);
	return file_err_state;
}

int save(int* num, int move_count)
{
	int state;               // error 체크 변수
    	char name[30];		//save할 사용자이름.
	int i;

	FILE * file;

	printf("저장할 이름을 입력해주세요 : ");
	gets(name);//scanf("%s", name);

	strcat(name,".txt");

	/* 쓰기 전용 파일 개방 */
    file=fopen(name,"wt");
    if(file==NULL){
        printf("file open error!\n");
        return 1;
    }
	
	/* fprintf 함수의 활용 */
	fprintf(file,"%d\n",move_count);
	for(i=0 ; i<16; i++){
		fprintf(file,"%d ", num[i]);
	}
	
	/* 파일의 종결 */
	state=fclose(file);
    if(state!=0){
        printf("file close error!\n");
        return 1;
    }
	return 0;
}

int load(int* num, int move_count)
{
	int state;               // error 체크 변수
    	char name[30];		//load할 사용자이름.
	int i;

	FILE * file;

	
	printf("이름을 입력해주세요 : ");
	gets(name);//scanf("%s", name);


	fflush(stdin); 
	strcat(name,".txt");

	/* 읽기 전용 파일 개방 */
    file=fopen(name,"rt");
    if(file==NULL){
        printf("file open error!\n");
        return 1;
    }

	/* fscanf 함수의 활용 */
	fscanf(file,"%d",&move_count);
	//printf("%d\n", move_count);
	for(i=0 ; i<16; i++){
		fscanf(file,"%d ", &num[i]);
		//printf("%d ", num[i]);
	}
	//fscanf(file,"%d %c %d %c %d",&a,&c1,&b,&c2,&c);

	/* 파일의 종결 */
    state=fclose(file);
    if(state!=0){
        printf("file close error!\n");
        return 1;
    }
	game_(num, move_count);
    return 0;

}
int ranking_first_make()
{
	/* 읽기 전용 파일 개방 */
	FILE * file;
	int state;

	file=fopen("ranking.txt","rt"); //
	if(file==NULL){
		printf("\n랭킹파일을 만들었습니다");
		sleep(1);
		printf("\n다시 시작해주세요.\n");
		file=fopen("ranking.txt","wt"); //
		if(file==NULL){
			printf("file open error!\n");
			return 1;
		}
		/* 파일의 종결 */
		state=fclose(file);//  스트림을 닫을때 사용  성공시 0반환 : 오류시  eof 반환
		if(state!=0){
			printf("file close error!\n");
			return 1;
		}
        return 1;
    }
	/* 파일의 종결 */
	
	state=fclose(file);
    if(state!=0){
        printf("file close error!\n");
        return 1;
    }
	return 0;
}
int ranking_write(int move_count)
{	//char buffer[256];
	char name[30];
	int state;
	int before_move_count[4] ={0};
	char before_name[4][30];
	int i,j;
	int temp;
	int temp_name[30];
	

	
	FILE * file;
	
	strcpy(before_name[0], ""); 
	strcpy(before_name[1], ""); 
	strcpy(before_name[2], "");
	strcpy(before_name[3], ""); 

	printf("랭킹에 올릴 이름을 입력해주세요 : ");
	gets(name);//scanf("%s", name);

	/* 읽기 전용 파일 개방 */
	file=fopen("ranking.txt","rt");
	if(file==NULL){
        printf("file open error!\n");
        return 1;
    }

	/* fscanf 함수의 활용 */
	i =0;
	for(  ; fscanf(file,"%d ", &before_move_count[i]) != EOF || i<3 ; i++){
		
		fscanf(file,"%s", before_name[i]);
		if(before_move_count[i]==0){
			before_move_count[i] = move_count;
			strcpy(before_name[i], name); 
			break;
		}
	}
	
	if(i==4){i=3;}
	before_move_count[i] = move_count;
	strcpy(before_name[i], name); 
	i =0;
	//확인후
	
	/* 파일의 종결 */
    state=fclose(file);
    if(state!=0){
        printf("file close error!\n");
        return 1;
    }
	
	//작은 순위로 정렬
	for(i=0; i<=2; i++){
		for(j=i+1; j<=3; j++){
			if(before_move_count[i] > before_move_count[j]){

				if(before_move_count[j] != 0){

					temp = before_move_count[i];
					strcpy(temp_name, before_name[i]); 
					before_move_count[i] = before_move_count[j];
					strcpy(before_name[i], before_name[j]); 
					before_move_count[j] = temp;
					strcpy(before_name[j], temp_name); 
				}
			}
		}
	}

	//확인후
	
	printf("\n\n\n\t\t\t======Now, Ranking======\n");
	for(i=0;i<3; i++){
		printf("%dth: %d ", i+1,before_move_count[i]);
		printf("%s\n", before_name[i]);
	}
	printf("\t\t\t========================\n");
	
	/* 쓰기 전용 파일 개방 */
	
	file=fopen("ranking.txt","wt");
	if(file==NULL){
        printf("file open error!\n");
        return 1;
    }
	
	


	
	
	for(i=0 ; i<=3 ; i++){
		fprintf(file,"%d ",before_move_count[i]);
		fprintf(file,"%s\n", before_name[i]);
	}
	
	

	/* 파일의 종결 */
	
	state=fclose(file);
    if(state!=0){
        printf("file close error!\n");
        return 1;
    }
	return 0;
	
}

int ranking_read()
{		
	int state;
	int move_count;
	char name[30];
	int i;

	system("clear");
	/* 읽기 전용 파일 개방 */
	FILE * file=fopen("ranking.txt","rt");
	if(file==NULL){
        printf("file open error!\n");
        return 1;
    }
	printf("\n\n\n\n=========RANKING=========\n");
	for(i=0; fscanf(file,"%d ", &move_count) != EOF && i<3; i++){
		fscanf(file,"%s", name);
		printf("%dth: %d ", i+1,move_count);
		printf("%s\n", name);
	}
	printf("==========================\n\n");
	/* 파일의 종결 */
    state=fclose(file);
    if(state!=0){
        printf("file close error!\n");
        return 1;
    }
	
    return 0;
}
