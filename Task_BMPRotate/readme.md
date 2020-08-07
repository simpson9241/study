Bitmap_Rotation
=====

코드 설명
-----

이 코드는
<br>
http://blog.naver.com/PostView.nhn?blogId=virapasas&logNo=130162830476&parentCategoryNo=20&categoryNo=&viewDate=&isShowPopularPosts=true&from=search
<br>에서 참조하며 작성한 코드입니다.
<br><br>
샘플 파일은 Annick.bmp이고, 코드가 돌아간 후 생성되는 파일은 Annick_result.bmp입니다.
<br>
샘플 파일은 코드 내에서 경로를 변경하여 바꿔서 테스트하실 수 있습니다.
<br>
기본적으로 파일은 24비트 bmp 파일이어야 합니다.
<br>
Makefile 파일을 만들어놨기 때문에, 해당 경로로 가셔서 아래의 명령어를 순차적으로 실행하시면 됩니다.
<br><br>
1.make test
<br>
2../test
<br>
3.(.o 파일 및 생성된 테스트 파일 삭제)make clean
<br><br>
실제로 돌아가는 코드는 총 3개의 cpp 파일로 구성되어 있고, main 함수는 main.cpp에, 그리고 필요한 함수들은 BMPreading.cpp 와 ImageRead.cpp 에 구현되어있습니다.
<br><br>
기본적으로 bmp 파일을 열어서 헤더로부터 파일 정보를 받아오고, 각 RGB 값을 받아온 다음 3개의 매트릭스에 RGB 값을 나누어 담았습니다. 이후 각 매트릭스를 rotation 함수를 통해 오른쪽으로 90도씩 회전시켜 저장한 다음, Output으로 저장할 파일에 다시 순차적으로 RGB 값을 넣어주었습니다.
