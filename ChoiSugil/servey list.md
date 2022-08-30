# 자료 조사:
- - -
## Linux server.
구름 IDE 를 이용한 클라우드 서버   
[구름IDE]:(https://help.goorm.io/ko/goormide/17.various-features/ssh-port-forwarding, "구름")   
[웹서버]:(https://pascucu.tistory.com/10, "웹서버")   

* 구름 IDE 계정 생성
* 포드포워드 생성 : 생성된 아이피와 포트 저장
* 서버 코드 업로드 

## Linux client.
* 리눅스에서 접속
* 테스트 용으로 접속 함.




## Server get character massages   
* "X---------" : 관리자.   
* "0---------" : 0번 아두이노 IOT   
* "1---------" : 1번 아두이노 IOT
* ...


# 서버 변경점
* 파일 로그 저장 추가
* 명령어 저장 : "1personIn"
* 명령어 저장 : "1personOut"
- - - 
* 인원수 저장용 struct person 만듬.
<code>
typedef struct roomPerson{
	int room1;
	int room2;
	int room3;
	int room4;
} Person;
</code>

* 1personIn 신호 받을 때 room1 증가.

# 문제점 
* 서버와 클라이언트 파일이 c 언어로 되어 있음 c++ 로 바꿀려고 했지만, thread 사용 하는 방법이 너무 달라서 C 로 진행 하기로 함.
* 아두이노에서 서버로 명령어를 보낼 때, 5초 정도의 delay 가 생김. 
* 서버를 안정적으로 종료 되는 코드가 없음.
