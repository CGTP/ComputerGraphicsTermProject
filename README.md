Computer Graphics TermProject
===================

마인크래프트처럼 사각형 블록을 이용한 FPS 게임 
![Image01](http://techholic.co.kr/wp-content/uploads/2013/11/minecraft_logo.jpg)
![Image02](https://i.ytimg.com/vi/fMXCCRCXCFo/maxresdefault.jpg)
![Image03](https://camo.githubusercontent.com/2e6c068912cdd758350b95e64c3f6863c90ce3d2/687474703a2f2f692e6779617a6f2e636f6d2f63316664613764396563333239666237363931633462356461346133343539662e706e67)
![Image04](http://i.ytimg.com/vi/MC_NePjnuSk/maxresdefault.jpg)

모든 캐릭터, 무기, 건물들이 다 사각형으로 이루어 져있으며,
수업시간에 배운 좌표계시스템(변환 등), 객체 그리기, 입력 컨트롤, 타이머, 쉐이딩 및 조명,
앞으로 배울 매핑과 애니메이션 등을 활용하여 만들 계획입니다.

----------
개발자
-------------

+ 2012180004 / 권창현
+ 2012181029 / 이인호

----------
개발 환경
-------------

+ Visual Studio 2013 -> Visual Studio 2015
+ OpenGL
+ C/C++

----------

구현내용
-------------

 1. 기본 프레임워크
 2. 무기, 캐릭터, 맵 모델링
 3. 충돌체크
 4. UI

----------

추가 구현
-------------

 1. 미니맵
 2. 조명
 3. 점프, 앉기
 4. ...

----------

팀원의 역할 분담표
-------------------

+ **권창현 :**
 2. 캐릭터 애니메이션
	- 캐릭터의 이동 모션
	- 캐릭터의 좌,우 움직임
	- 캐릭터의 앞,뒤 움직임
 3. 캐릭터 모델링
	- 캐릭터에 맞춰서 텍스쳐 맵핑

+ **이인호 :**
 4. 무기 모델링
	- 무기에 종류에 따라서 텍스쳐 맵핑
 5. 맵 모델링
	- 전체적인 맵 구현
	- 맵에 대한 장애물 구현
 6. UI 제작
	- 처음 시작시 UI 화면
	- 게임 진행중 HP, 총알 남은 개수 구현

+ **공동 구현 :**
 1. 프레임워크 구현
 2. 캐릭터 충돌 구현
	- 캐릭터 와 캐릭터 간의 충돌체크
	- 캐릭터 와 맵 간의 충돌체크
	- 캐릭터 와 총알 간의 충돌체크
	- 캐릭터 와 장애물 간의 충돌체크

----------


스케줄표
-------------------

####1주차 :

 1. 게임을 진행하기 위한 프레임 워크를 구현한다.
	 +  입력 컨트롤을 사용하여 화면의 움직임, 캐릭터 움직임을 구현
	 +  각자 분담된 업무에 대한 작업 시작

####2주차 :

 1. 각자 분담된 업무개발 마무리 및 테스트
 2. 조명 구현 및 1차 테스트 후 문제점 수정

####3주차 :

 1. “충돌 체크” 작업 시작.

####4주차 :

 1. “충돌 체크” 마무리 및 2차 테스트 후 문제점 수정
 2. 최종 발표를 위한 작업 내용 정리 및 릴리즈 파일 준비.

----------


완성된 이미지 & 동영상
--------------------
+ [유튜브 시연 영상 (36초) - 촬영을 위하여 FPS를 30으로 조정하였습니다.](https://www.youtube.com/watch?v=55W6j0bYiPQ)
+ 기본적인 조명을 활용한 시점
![Image05](http://i.imgur.com/cVUgaWY.png)

+ 줌을 한뒤 하이라이트 조명을 사용한 시점
![Image06](http://i.imgur.com/ZBUe298.png)

+ 3인칭 시점
![Image07](http://i.imgur.com/q1C4g8x.png)

+ 1인칭 시점에서의 좀비 캐릭터 확인
![Image08](http://i.imgur.com/Tuxp8Gh.png)

+ 1번 이미지와 같은 일반적인 시점
![Image09](http://i.imgur.com/cVUgaWY.png)
