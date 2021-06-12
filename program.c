//made by 21800763 탁준혁, 소스코드 파일

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


//팀만드는 함수
int Maketeam(int *team_number, int *people_number);
//기타 함수 나열
int Menu(void);
//점수 관련 함수
void Score(int team_number);
void ScorePrint(int team_number);
//승자 출력 함수
void Winner(int team_number);
//게임함수들 나열
void GuessNumber(int team_number);
void RockSP(int team_number);
void StopWatch(int team_number);
void GuessWord(int team_number);
void SpeakBody(int teamnumber);
//행운권뽑기 함수
void Random(int people_number);


int sum[10]={0}; //각 팀의 누적 점수

int main(){
    int gamenumber=0; //메뉴에서 리턴받는 메뉴의 번호
    int team_number=0; //총 팀의 갯수
    int people_number=0; //전체사람의 수

    //팀을 나눈다
    Maketeam(&team_number,&people_number);

    printf("\n");

    //팀을 확인하면 아무키나 누른다 + 화면이 지워진다
    printf("gather with your team! (If you gather, input enter)");
    getchar();
    getc(stdin);
    system("clear");

    printf("\n\n");

    //무한 반복을 통해 게임이 끝날 때마다 메뉴를 출력하고 각 게임이 끝날 때 점수를 입력받고 누적한다
    while(1){
        gamenumber=Menu();

        system("clear");

        //gamenumber가 0일 경우 레크레이션을 끝낸다
        if(gamenumber==0){
            printf("\n\nrecreation finish!\n"); 
            break;
        }
        else if(gamenumber==7) Random(people_number); // special menu라 팀별 점수 입력 안받음
        else{
            // gamenumber에 따라서 각 함수를 실행한다 
            switch(gamenumber){
                case 1: GuessNumber(team_number); break;
                case 2: RockSP(team_number); break;
                case 3: StopWatch(team_number); break;
                case 4: GuessWord(team_number); break;
                case 5: SpeakBody(team_number); break;
                case 6: Random(people_number); break;
                case 999: break;
            }
            //각 게임이 실행되고 게임별 점수를 입력하고 누적점수를 출력한다
            Score(team_number);
            printf("\n");
            ScorePrint(team_number);
        }
    }
    //레크레이션이 끝난후 누적점수와 승자를 출력
    ScorePrint(team_number);
    Winner(team_number);
    return 0;
}
  

//팀 만드는 함수
int Maketeam(int *team_number, int *people_number){
    //변수선언
    int i=0, j=0; //loop variable
    int random[100]={0}; //random수
    
    //도입부분 말 실행
    printf("\nHello everyone! Welcome to HGU recreation!\nLet's start game!\nNow we make some team!\n\n");

    sleep(2);

    //팀 갯수를 입력받음
    printf("Please input less than \'10\' teams\n");
    // 10이하의 팀을 입력할때까지 다시 입력받음
    while(1){
        printf("Input the number of team: ");
        scanf("%d",&*team_number);
        if(*team_number<=0 || *team_number>10) printf("wrong input! try again\n\n");
        else break;
    }
   
    //전체 사람의 수를 입력받음
    printf("Input the number of people: ");
    scanf("%d",&*people_number);

    //만일 팀 수와 사람 수가 같으면 개인전이므로 아래 팀을 만드는 과정을 무시한다
    if(*team_number==*people_number){
        printf("It's individual game.\n Team number is your individual number\n");
    }
    
    //만일 그렇지 않으면
    else if(*team_number!=*people_number){
        //random seed를 줌
        srand(time(NULL));

        //random수를 만듬
        for(i=0;i<*people_number;i++){
            random[i]=rand()%*people_number+1;
            //누적된 랜덤수를 제거한다
            for(j=0;j<i;j++){
                if(random[i]==random[j]) i--;
            }
        }

        printf("\n");

        //팀 번호를 위에 쓰고 아래에 각 사람들의 번호들을 나열한다
        for(i=0;i<*team_number;i++){
            printf("%5d",i+1);
        }
        printf("  ---[team number]");

        printf("\n\n");
        
        //1~people_number까지의 랜덤수를 팀의 갯수로 나누어서 출력한다
        for(i=0;i<*people_number;i++){
            //random을 설정(반복되는 수 방지)
            printf("%5d",random[i]);

            //만약 팀 갯수의 수 만큼 랜덤이 출력되면 줄을 띄워 다시 실행
            if((i+1)%*team_number==0){
                printf("\n");
            }
        }
    }
    return *team_number, *people_number;
}


//메뉴 출력 함수
int Menu(){
    int gamenumber=0; //메뉴에서 선택한 것을 저장하는 변수

    //메뉴를 출력
    printf("[ GAME MENU ]\n\n1. GUESS NUMBER\n2. ROCK SCISSOR PAPER\n3. HUMAN STOPWATCH\n4. GUESS THE RIGHT WORD\n5. SPEAK WITH YOUR BODY\n6. RANDOM PICK\n999. SCORE INPUT\n0. EXIT\n\n");

    // 유효한 숫자 입력값만 받음
    while(1){
        printf("select the game number: ");
        scanf("%d",&gamenumber);
        if(gamenumber>6 && gamenumber!=999) printf("wrong input! try again\n\n");
        else break;
    }
    return gamenumber;
}


//점수 계산함수
void Score(int team_number){

    int i=0; //loop variable
    int jumsu[10]={0}; //게임마다 얻은 팀별 점수

    //팀별로 점수를 입력함
    for(i=0;i<team_number;i++){
        printf("Input score of team \'%d\' : ",i+1);
        scanf("%d",&jumsu[i]);

        //각 팀별 점수를 누적함
        sum[i]+=jumsu[i];
    }
}


//점수 출력함수
void ScorePrint(int team_number){
    int i=0; //loop variable

    //각 팀들의 누적점수를 출력
    for(i=0;i<team_number;i++){
        printf("team %d cumulative score : %d\n",i+1,sum[i]);
    }

    printf("\n");

    printf("\nIf you check all, press enter.\n");
    getchar();
    getc(stdin);
    system("clear");
}


//승자 출력 함수
void Winner(int team_number){
    int max=0; //가장 큰 점수
    int max_team=0; //점수가 가장 높은 팀
    int i=0; //loop variable

    //점수 제일 높은 팀 구함
    //max를 계산
    for(i=0;i<team_number;i++){
        if(max==0) max=sum[i];
        else if(max<sum[i]) {
            max=sum[i];
            max_team=i;
        }
    }

    // 카운트 다운 3초 후
    printf("WINNER IS...\n");
    for(i=0;i<3;i++){
        sleep(1);
        printf("%d\n",3-i);
    }
    sleep(1);
    // 화면 지우고 승자 팀 알려줌
    system("clear");
    printf("TEAM \'%d\'!!!!!!!!!!!!!\n",max_team+1);
    printf("\n\n");

    //날짜를 입력받고, 승리한 팀을 파일에 저장함
    FILE* fp = fopen("winner.txt","a");
    int year = 0;
    int month = 0;
    int day = 0;
    printf("Today's year (ex. 2021): ");
    scanf("%d", &year);
    printf("Today's month (ex. 06): ");
    scanf("%d", &month);
    printf("Today's day (ex. 11): ");
    scanf("%d", &day);

    fprintf(fp, "<%d %d %d> Winner team: %d.\n", year, month, day, max_team+1);
    fclose(fp);

    //함수 종료
    printf("press enter to finish");
    getchar();
    getc(stdin);
}


// 1번 게임 함수
void GuessNumber(int team_number) {

    int answer; // 컴퓨터가 만들어 낸 1부터 100사이의 임의의 숫자 
    int number_try; // 사용자가 제시한 숫자 
    int count[10]={0}; // 사용자가 맞추려고 시도한 횟수
    int jumsu[10]={0}; //각 팀별 게임 점수
    int i=0; //loop variable

    printf("\n[1. GUESS NUMBER]\n\n");
    sleep(1);
    //게임의 규칙 설명
    printf("<RULES>\n\n");
    printf("1. Each team have to guess the number which the computer makes.\n");
    printf("2. Computer makes number between 1 and 100.\n");
    printf("3. If you input number which is smaller than the computer number -> print \"bigger than you've tried\".\n");
    printf("4. If you input number which is bigger than the computer number -> print \"smaller than you've tried\"\n");
    printf("5. The score: 1) start score is 150. 2) each count increases -> -10 point\n");
    
    //아무키나 누르면 다음으로 넘어감
    printf("\nIf you read all, press enter.\n");
    getchar();
    getc(stdin);

    printf("Let's start GUESS NUMBER game!\n\n");
    sleep(2);

    system("clear");

    //random seed 제공
    srand(time(NULL));

    //아래 과정을 팀 갯수 만큼 진행
    for(i=0;i<team_number;i++){
        //1~100까지의 수를 랜덤으로 answer에 지정
        answer=rand()%100+1;

        //한줄 띄우기
        printf("\n");

        //지금 플레이 하는 팀을 알려줌
        printf("Now, team %d's turn.\n\n",i+1);

        // 답 맞을 때까지 루프 돌림
        while(answer!=number_try){
            printf("guess the number between 1 to 100: ");
            scanf("%d",&number_try);

            // 정답보다 작은거 입력했을 경우-너가 시도한 것보다 더 크다고 알려줌
            if(answer>number_try){
                printf("bigger than you've tried\n\n");
            }

            // 정답보다 큰 거 입력했을 경우-너가 시도한 것보다 더 작다고 알려줌
            else if(answer<number_try){
                printf("smaller than you've tried\n\n");
            }

            //답이 맞으면 반복문을 나옴
            else if(answer==number_try) break;

            //시도 횟수 계산해서 나중에 점수 계산
            count[i]++;
        }

        printf("\n");

        //각팀별 점수 계산
        jumsu[i]=150-10*(count[i]+1);

        //결과출력
        printf("You %d times try to win.\n",count[i]+1);
        printf("%d team's score is %d.\n\n",i+1,jumsu[i]);

        //3초쉬고 화면지움
        sleep(3);
        system("clear");
    }
    
    //최종 게임 점수를 팀별로 다 띄워줌
    for(i=0;i<team_number;i++){
        printf("%d team's score is %d.\n",i+1,jumsu[i]);
    }

    printf("\n");
}


// 2번 게임 함수
void RockSP(int team_number){
    int com_finger=0; //컴퓨터가 낸 바위(1), 가위(2), 보(3) 
    int my_finger=0; //사용자가 낸 바위(1), 가위(2), 보(3) 
    int score[3]={0}; //이긴 것, 진 것, 비긴 것에 대한 횟수
    int jumsu[10]={0}; //게임 결과에 따른 점수
    int i=0; //loop variable
    int j=0; //loop variable

    //random seed
    srand(time(NULL));
    
    //무슨게임인지 출력
    printf("\n[2. ROCK SCISSOR PAPER]\n\n");
    sleep(1);

    //게임의 규칙 설명
    printf("<RULES>\n\n");
    printf("1. Each team plays rock scissor paper game 10 times with the computer.\n");
    printf("2. Team leaders say \"Rock\" or \"SICSSOR\" or \"PAPER\"\n");
    printf("3. The score: 1) win point: +10 2) draw point: +5 3) lose point: -3\n");
    
    //아무키나 누르면 게임이 진행됌
    printf("\nIf you read all, press enter.\n");
    getchar();
    getc(stdin);

    printf("Let's start ROCK SCISSOR PAPER game!\n\n");
    sleep(2);

    system("clear");

    //전체를 팀 수만큼 돌림
    for(i=0;i<team_number;i++){
        //지금 플레이 하는 팀을 알려줌
        printf("Now, team %d's turn.\n\n",i+1);
        sleep(1);

        //score[1,2,3]초기화
        score[0]=0;
        score[1]=0;
        score[2]=0;

        for(j=0;j<10;j++){
            // 10번의 게임중 현재 횟수 표시
            printf("[play %d]\n",j+1);

            //컴퓨터가 낼거 랜덤 지정
            com_finger=rand()%3+1;

            // 사용자의 가위바위보 입력받기
            while(1){
                printf("input ROCK(1), SICSSOR(2), PAPER(3). ");
                scanf("%d",&my_finger);
                
                // 1,2,3 아닌거 입력받으면 제대로 입력할 때까지 다시 입력받음
                if(my_finger<0 || my_finger>3) printf("wrong input! try again\n\n");
                else break;
            }

            // 컴퓨터가 낸거 알려줌
            switch(com_finger){
                case 1: printf("computer's choice is ROCK"); break;
                case 2: printf("computer's choice is SCISSOR"); break;
                case 3: printf("computer's choice is PAPER"); break;
            }

            // 승 패 무승부 결과 알려줌 + 각 경우의 횟수를 계산
            printf(" -----> ");
            //사용자 패배
            if((com_finger==2 && my_finger==3)||(com_finger==1 && my_finger==2)||(com_finger==3 && my_finger==1)){
                printf("COMPUTER win");
                score[0]++;
            }

            //사용자 승리
            else if((my_finger==2 && com_finger==3)||(my_finger==1 && com_finger==2)||(my_finger==3 && com_finger==1)){
                printf("YOU win!!");
                score[1]++;
            }

            //비겼을 경우
            else {
                printf("draw~");
                score[2]++;
            }

            printf("\n\n");
        }

        // 승 패 무승부 총 합산 결과 알려줌
        printf("\n");
        printf("You win %d times, lose %d times, draw %d times.\n\n\n",score[1],score[2],score[0]);

        //팀별 점수계산
        jumsu[i]= 10*score[1] + 5*score[2] -3*score[0];

        sleep(2);
        system("clear");
    }

    //각 팀별 점수를 띄운다
    for(i=0;i<team_number;i++){
        printf("%d team's score is %d.\n",i+1,jumsu[i]);
    }

    printf("\n");
}


//3번 게임 함수 (인간스톱워치)
void StopWatch(int team_number){
    int second=0; //스톱워치에서 얼만큼 초를 세는지 나타내는 변수 (random으로 만들어진 세야하는 시간)
    int i=0; //loop variable
    int j=0; //loop variable
    int timespent=0; //사용자가 센 초
    int jumsu[10]={0}; //팀별 점수
    clock_t start,end; //시간재는 함수 선언
    
    srand(time(NULL));
    
    printf("\n[ 3. HUMAN STOPWATCH ]\n\n");
    sleep(1);

    //게임의 규칙 설명
    printf("<RULES>\n\n");
    printf("1. Each team has 1 time to play. (the game will repeat \'%d\' times)\n", team_number);
    printf("2. Each team is given a random seconds to count. (between 20 and 29 seconds)\n");
    printf("3. When you think you're close to a set seconds, raise your hand and say your team name.\n");
    printf("4. The score:\n 1) +-1: get +300 \n 2) +-2: get +200 \n 3) +-3: get +150 \n 4) +-4: get +100 \n 5) +-5: get +50 \n 6) Else: lose -50.\n");
    
    //아무키나 누르면 게임을 실행
    printf("\nIf you read all, press enter.\n");
    getchar();
    getc(stdin);

    printf("Let's start HUMAN STOPWATCH game!\n\n");
    sleep(2);

    system("clear");

    //게임에 참여하는 팀의 번호를 출력
    for(i=0;i<team_number;i++){
        //초기화 설정
        timespent=0;
        start=0;
        end=0;

        //게임을 플레이 할 팀을 알려준다
        printf("Now, team %d's turn.\n",i+1);
        sleep(1);

        //시간을 정한다
        second=rand()%10+20; //20~29초 사이에서 랜덤으로 시간을 정함
        printf("You have to count '%d'seconds.\n",second);
        sleep(1);

        //게임할 준비가 되면 클릭하라고 한다.
        printf("If your team is ready, please press enter.\n");
        getchar();
        getc(stdin);

        //시작한다
        printf("Game will start in 3 seconds\n");
        //카운트 다운
        for(j=0;j<3;j++){
            sleep(1);
            printf("%d\n",3-j);
        }

        printf("Count start!\n");
        
        //아무키나 누르면 시간재기 시작
        printf("If you think the time is up, just press enter.\n");
        start=clock();

        //아무 키나 눌렀을 경우 초를 세는 것을 멈추고, 몇초가 지났는지 출력해준다.
        getchar();
        if(getc(stdin)!=-1) end=clock();

        //지금까지 센 시간을 계산
        timespent=(int)(end-start)/1000; // 초로 나타냄
        printf("you count %d second!!\n\n",timespent);

        //점수를 계산함
        //뺏을때의 절댓값에 따라서 점수를 나눈다
        if(abs(second-timespent)<=1){
            jumsu[i]=300;
        }
        
        else if(abs(second-timespent)<=2){
            jumsu[i]=200;
        }
        
        else if(abs(second-timespent)<=3){
            jumsu[i]=150;
        }
        
        else if(abs(second-timespent)<=4){
            jumsu[i]=100;
        }
        
        else if(abs(second-timespent)<=5){
            jumsu[i]=50;
        }
        
        else jumsu[i]=-50;

        //팀의 점수를 알려줌
        printf("Team %d's score: %d\n\n",i+1,jumsu[i]);
        sleep(2);

        //콘솔창을 지움
        system("clear");
    }

    //반복문 종료 후 각 팀들의 점수를 보여줌
    for(i=0;i<team_number;i++){
        printf("%d team's score is %d.\n",i+1,jumsu[i]);
    }

    printf("\n");
}


// 4번 게임 함수
void GuessWord(int team_number){
    
    char word[110][25]={"pig","cow","sheep","rabbit","giraffe","hippo","leopard","zebra","squirrel","rhino","turtle","deer","kangaroo","tiger","fox","chicken","snake","camel","monkey","elephant","horse","mouse","bear","wolf","skunk","lion","whale","seal","dolphin","koala","kangaroo","frog","penguin","peacock","parrot","pigeon","owl","spider","octopus","happy","cold","upset","anxious","sad","nervous","angry","dizzy","awkward","shy","ashamed","thankful","greedy","calm","relaxed","passionate","jealous","confident","golf","tennis","soccer","tabletennis","ski","taekwondo","volleyball","hockey","wrestling","judo","swim","dodgeball","basketball","handball","toothbrush","kettle","soap","eraser","pencil","lipstick","laptop","coat","spoon","chopstick","cup","toliet","sauna","karaoke","waterpark","laboratory","classroom","mountain","beach","airport","valley","subway","waterfall","restaurant","hotel","kitchen","theater","hospital","library","museum","church","bank","temple","gym","zoo","office","school","cafe","military"}; //뒤섞이기 전의 원래 단어들에 대한 배열
    char user[25]=""; //user가 입력한 답
    int i=0,j=0,k=0; //loop variable
    int index[5]={0}; //문제 10개의 index를 배열에 저장한다.
    int place[25]={0}; //랜덤한 단어 배열을 위한 변수
    int count =0,countr=0; //중복처리를 위함
    int correct=0; //맞은 개수 계산하기
    int timespent=0; ///게임을 진행하는데 걸린 시간
    int jumsu[10]={0}; //각 팀별 점수
    clock_t start,end; //시간재는 변수 선언, long clock과 같은 형태

    // 뒤섞인 단어 알아맞추기
    printf("\n[4. GUESS THE RIGHT WORD]\n\n");
    sleep(1);

    //게임의 규칙 설명
    printf("<RULES>\n\n");
    printf("1. One of team member will solve 5 question.\n");
    printf("2. Look at the random alphabet and type the right word.\n");
    printf("3. The score: The more answers you get, the faster you get, you will get the higher score.\n");
    
    //아무키나 누르면 게임 시작
    printf("\nIf you read all, press enter.\n");
    getchar();
    getc(stdin);

    printf("Let's start GUESS THE RIGHT WORD game!\n\n");
    sleep(2);

    system("clear");

    // 랜덤 씨드 지정
    srand(time(NULL));

    // team number 만큼 반복
    for(j=0;j<team_number;j++){   
        // 값들 초기화
        start=0;
        end=0;
        timespent=0;
        correct=0;

        //지금 플레이 하는 팀을 알려줌
        printf("Now, team %d's turn.\n",j+1);
        printf("If team %d gets ready than press enter\n",j+1);
        getchar();
        getc(stdin);

        // 문제 5개의 번호를 인덱스 배열에 저장해놓기-중복처리하기
        for(i=0;i<5;i++){
            index[i]=rand()%110;
            for(count=0;count<i;count++){
                if(index[i]==index[count]){
                    i--;
                    break;
                }
            }
        }

        // 5초 카운트 다운 후에 게임 시작 및 시간 재기 시작
        printf("Game will start in 5 seconds\n");
        for(i=0;i<5;i++){
            sleep(1);
            printf("%d\n",5-i);
        }

        // 5문제 출력- 5문제 푸는 시간 계산하기
        start=clock(); // 시간 재기 시작

        // 단어 뒤섞어서 내보내기
        //5문제를 냄
        for(i=0;i<5;i++){
            printf("\n[ question %d ]\n\n",i+1);

            // 25개 정렬하는데 자리 랜덤 배정해주는 거임 - 중복처리
            for(k=0;k<25;k++){
                place[k]=rand()%25;
                for(countr=0;countr<k;countr++){
                    if(place[k]==place[countr]){
                        k--;
                        break;
                    }
                }
            }

            // 단어 무작위로 프린트 해줌 5x5배열
            for(k=0;k<25;k++){
                printf("%c ",word[index[i]][place[k]]);
                if(k%5==1) printf("\n");
            }

            printf("\n\nanswer is : ");
            scanf(" %s",user);

            //strcmp 함수를 써서 입력한 정답이랑 원래 답이랑 같으면 correct 수 올려줌
            if(strcmp(word[index[i]],user)==0) correct++;
            printf("the right answer is \"%s\"\n",word[index[i]]);
        }

        end=clock(); // 시간 재기 끝
        timespent=(int)(end-start)/1000; //문제를 풀기까지 걸린 시간 계산 + 초로 나타내기

        // 팀별 시간에 따른 점수와 맞은 개수에 따라서 점수를 합산해서 저장
        jumsu[j]=(200-timespent)+(correct*50);

        //게임 결과를 알려줌
        printf("\n\nYou got \'%d\' questions right, and it took \'%d\' seconds.\n\n\n",correct,timespent);
        sleep(3);
        system("clear");
    }

    //각 팀별 점수를 띄운다
    for(i=0;i<team_number;i++){
        printf("%d team's score is %d.\n",i+1,jumsu[i]);
    }
    printf("\n");
}


// 5번 게임 함수
void SpeakBody(int team_number)
{
    char category[5][10]={"animal","emotion","sport","thing","place"}; //텍스트의 카테고리를 나타내는 변수

    char animal[50][20]={"pig","cow","sheep","rabbit","giraffe","hippopotamus","crocodile","leopard","zebra","ostrich","squirrel","rhinoceros","hedgehog","turtle","deer","kangaroo","tiger","fox","chicken","racoon","snake","anteater","camel","monkey","elephant","horse","meerkat","mouse","bear","wolf","skunk","lion","whale","seal","dolphin","hamster","beaver","koala","kangaroo","frog","penguin","peacock","parrot","pigeon","owl","seagull","crow","woodpecker","spider","octopus"}; //동물
    char emotion[38][20]={"happy","cold","upset","anxious","sad","annoyed","relieved","nervous","angry","excited","confused","frustrated","depressed","tired","pain","bored","sleepy","disappointed","exhausted","loving","touched","satisfied","shocked","dizzy","scared","hopeful","wonderful","awkward","respectful","shy","ashamed","thankful","greedy","calm","relaxed","passionate","jealous","confident"}; //감정
    char sport[27][20]={"golf","tennis","soccer","tabletennis","ski","boiling","taekwondo","fencing","volleyball","hockey","wrestling","judo","kendon","archery","weight lifting","swim","dodgeball","basketball","handball","cycling","boxing","climbing","bobsleigh","ski jumping","curling","speed skating","figure skating"}; //운동
    char thing[12][25]={"toothbrush","toothpick","kettle","soap","eraser","pencil","lipstick","laptop","coat","spoon","chopstick","cup"}; //사물
    char place[31][25]={"amusement park","toliet","sauna","karaoke","waterpark","laboratory","classroom","mountain","beach","airport","valley","subway","waterfall","restaurant","hotel","kitchen","theater","hospital","library","museum","church","bank","temple","pc room","gym","zoo","police office","office","school","cafe","military"}; //장소

    int i=0,j=0; // loop variable
    int cat=0; // 카테고리 결정
    int number=0; // 해당 카테고리 안에 있는 문제 후보 개수
    int index[10]={0}; //문제 10개의 index를 배열에 저장한다.
    int count =0; // 중복처리를 위함
    int correct=0; // 맞은 개수 입력받기
    int correctcount=0; // 10개 중에 맞은 개수
    int timespent=0; //게임하는 시간을 재는 변수
    int jumsu[10]={0}; //각 팀별 점수

    clock_t start,end; //시간을 재기위해 필요한 변수, long clock과 같은 형태

    // 몸으로 말해요 게임
    printf("\n[5. SPEAK WITH YOUR BODY]\n\n");
    sleep(1);

    //게임의 규칙 설명
    printf("1. one of team member will explain the word with body.(Don't speak)\n");
    printf("2. Each team solves\'10\' questions.\n");
    printf("3. category is randomized.\n");
    printf("4. You can pass the questions.\n");
    printf("5. category : animal, emotion, sport, thing, place\n");
    printf("6. The score: The more answers you get, the faster you get, you will get the higher score.\n");
    
    //아무키나 누르면 게임 시작
    printf("\nIf you read all, press enter.\n");
    getchar();
    getc(stdin);
    printf("Let's start SPEAK WITH YOUR BODY game!\n\n");
    sleep(2);

    system("clear");

    // 랜덤 씨드 지정
    srand(time(NULL));

    // team number 만큼 반복
    for(j=0;j<team_number;j++)
    {   
        // 값들 초기화
        start=0;
        end=0;
        timespent=0;
        correctcount=0;

        //지금 플레이 하는 팀을 알려줌
        printf("Now, team %d's turn.\n",j+1);
        sleep(1);

        // 카테고리 5개 중에 랜덤 지정해서 무슨 카테고리인지 알려줌
        cat=rand()%5;
        printf("%d team's category is \"%s\"\n\n",j+1,category[cat]);
        printf("If team %d gets ready than press enter\n",j+1);
        getchar();
        getc(stdin);

        // 카테고리 별로 문제를 냄
        switch(cat){
            case 0: number=50; break; //animal
            case 1: number=38; break; //emotion
            case 2: number=27; break; //sport
            case 3: number=12; break; //thing
            case 4: number=31; break; //place
        }

        // 각 문제 10개의 번호를 인덱스 배열에 저장해놓음
        for(i=0;i<10;i++){
            index[i]=rand()%number;
            for(count=0;count<i;count++){
                if(index[i]==index[count]){
                    i--;
                    break;
                }
            }
        }

        // 5초 카운트 다운 후에 게임 시작 및 시간 재기 시작
        printf("Game will start in 5 seconds\n");
        for(i=0;i<5;i++){
            sleep(1);
            printf("%d\n",5-i);
        }

        // 10문제 출력- 10문제 푸는 시간 계산하기
        start=clock(); // 시간 재기 시작

        //10문제 내기
        for(i=0;i<10;i++){
            //문제 번호출력
            printf("\n[ question %d ]\n\n",i+1);

            //카테고리에 따라 내는 문제를 다르게 설정함
            switch(cat){
            case 0: printf("\"%s\"\n\n\n",animal[index[i]]); break; //animal
            case 1: printf("\"%s\"\n\n\n",emotion[index[i]]); break; //emotion
            case 2: printf("\"%s\"\n\n\n",sport[index[i]]); break; //sport
            case 3: printf("\"%s\"\n\n\n",thing[index[i]]); break; //thing
            case 4: printf("\"%s\"\n\n\n",place[index[i]]); break; //place
            }

            //문제를 맞춘것인지 pass한 것인지 입력
            printf("Press key (1 : CORRECT!! , else number : PASS ) : ");
            scanf(" %d",&correct);

            //1 입력할 경우 맞은 횟수 더함
            if(correct==1) correctcount++;
        }

        end=clock(); // 시간 재기 끝
        timespent=(int)(end-start)/1000; // 초로 나타내기

        // 팀별 시간에 따른 점수 맞은 개수에 따른 점수 합산해서 저장
        jumsu[j]=(1000-timespent)+(correctcount*70);
        
        //결과 출력
        printf("\n\nYou got \'%d\' questions right, and it took \'%d\' seconds.\n\n\n",correctcount,timespent);
        sleep(4);
        system("clear");

    }

    //각 팀별 점수를 띄운다
    for(i=0;i<team_number;i++){
        printf("%d team's score is %d.\n",i+1,jumsu[i]);
    }

    printf("\n");
}


// 6번 게임 함수
void Random(int people_number){
    int lucky=0; //행운에 당첨될 사람 수
    int count=0; //중복처리
    int i=0; //loop variable
    int number[1000]={0}; //게임하는 사람의 수

    printf("It's RANDOM time~~\n");
    printf("give some special present for lucky guys!\n\n");

    //몇명을 추첨할지 입력함
    while(1){
        printf("How many people will you give a good luck? : ");
        scanf("%d",&lucky);
        if(lucky>people_number) printf("wrong input! try again\n\n");
        else break;
    }

    //추첨을 할 인원만큼 랜덤을 돌려 사람들을 뽑음 (lucky만큼)
    for(i=0;i<lucky;i++){
        number[i]=rand()%people_number+1;
        
        //중복이 없게 만듬
        for(count=0;count<i;count++){
            if(number[i]==number[count]){
                i--;
                break;
            }
        }
    }

    //결과 출력하기전 카운트 다운 3초
    printf("the LUCKY number is...\n");
    for(i=0;i<3;i++){
        sleep(1);
        printf("%d\n",3-i);
    }
    sleep(1);
    system("clear");

    //추첨된 사람 출력
    printf("\n");
    printf("This is people's number\n\n");
    for(i=0;i<lucky;i++){
        printf("<%d>\n",number[i]);
    }

    sleep(1);
    printf("\n");
    
    //아무키나 누르면 행운권 추첨 함수 종료
    printf("press enter\n");
    getchar();
    getc(stdin);
    system("clear");
}
