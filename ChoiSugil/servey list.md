- - -
## Linux server.
- - - 
구름 IDE 를 이용한 클라우드 서버   
[구름IDE]:(https://help.goorm.io/ko/goormide/17.various-features/ssh-port-forwarding, "구름")   
[웹서버]:(https://pascucu.tistory.com/10, "웹서버")   

* 구름 IDE 계정 생성
* 포트포워드 생성 : 생성된 아이피와 포트 저장
* 서버 코드 업로드 

## Linux client.
* 리눅스에서 접속
* 테스트 용으로 접속 함.




## Server get massages   
* "X---------" : 관리자.   
* "0---------" : 0번 아두이노 IOT   
* "1---------" : 1번 아두이노 IOT
* "1personIn" : 1번 룸 인원 추가.
* "2personIn" : 2번 룸 인원 추가.
* "3personIn" : 3번 룸 인원 추가.
* "4personIn" : 4번 룸 인원 추가.
* "1personOut" : 1번 룸 인원 감소.
* "2personOut" : 2번 룸 인원 감소.
* "3personOut" : 3번 룸 인원 감소.
* "4personOut" : 4번 룸 인원 감소.

## Server out massages 
* "1turnoff" : 1번 방 전등 꺼짐.
* "2turnoff" : 2번 방 전등 꺼짐.
* "3turnoff" : 3번 방 전등 꺼짐.
* "4turnoff" : 4번 방 전등 꺼짐.

# 서버 변경점
* 파일 로그 저장 추가
* 명령어 저장 : "1personIn"
* 명령어 저장 : "1personOut"
- - - 
* 인원수 저장용 struct person 만듬.
```
typedef struct roomPerson{   
	int room1;   
	int room2;   
	int room3;   
	int room4;   
} Person;   
```

* 1personIn 신호 받을 때 room1 증가.
* 1personOut 신호 받을 때 room2 감소.
* person.dat 파일을 만들어서 4개의 int 값 저장room1, room2, room3, room4
- - - 
* 로그파일에 월 일 시분초 추가.
* 사람이 0이 될 때 turn off 추가. 
* room2 room3 room4 추가. 

# 문제점 
* 서버와 클라이언트 파일이 c 언어로 되어 있음 c++ 로 바꿀려고 했지만, thread 사용 하는 방법이 너무 달라서 C 로 진행 하기로 함.
* 아두이노에서 서버로 명령어를 보낼 때, 5초 정도의 delay 가 생김. ---- 해결
* 서버를 안정적으로 종료 되는 코드가 없음.
* 각 방에 서버에서 나가는 코드가 모든 방에 나가게 됨. 특정 메세지가 특정 방에만 보내게 변경 해야 함.
* Wifi module 이 간혹가다가 정상 작동 됨. 

# 제목
### 소제목
* 첫번째
* 두버째
	*들여쓰기
	
