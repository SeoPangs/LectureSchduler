﻿//"교과목.txt에 있는 2022년 2학기 수업 1341개를 세팅 및 추천하는 프로그램.
// 주의 : 메모장 저장 시 인코딩을 ANSI로 해야 한글이 안깨집니다.

#include "schedule.h"
#include "lecture.h"
#include "Algorithm.h"


int main()
{
	FILE* data = fopen("교과목.txt", "r");
	Schedule sche = { {0,}, {0,}, {0,}, {0,}, {0,} };
	Lecture lec;
	LecArray lec_array[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호랑 가중치 있는 array,
	LecArray major_insert[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호랑 가중치 있는 array,
	LecArray basic_insert[MAX_LECTURE] = { 0, }; //교양 삽입에 필요한 어레이
	Preference* user_preference;
	UserInfo user_info;
	int idx = 0;
	
	char string[MAX_LEN] = "";
	int input = 0;
	
	//질문 입력받아 user_info에 저장
	user_info = ask_major();

	//질문 입력받아 user_preference에 저장
	user_preference = ask_basic();
	
	//모든 인덱스를 탐색하면서 모든 강의의 가중치를 계산
	for (int i = 0; i < MAX_LECTURE; i++)
	{
		lec = lec_search(i); //원하는 인덱스를 삽입

		printf("%5d ", i); //실행중인지 확인

		if (strstr(lec.cmp_clf, "전") != NULL)	//전공일 경우,
			lec_array[idx] = weight_setting_major(lec, user_info);
		else									//교양일 경우,
			lec_array[idx] = weight_setting_basic(lec, user_preference);
		idx++;
	}
	printf("\n%d개를 탐색\n\n", idx);


	//(수정필요) 가중치 계산하는 부분
	for (int i = 0, j = 0; i < idx; i++)
	{
		if (lec_array[i].weight > 8)
		{
			basic_insert[j].index = lec_array[i].index; //원하는 인덱스를 삽입
			
			lec = lec_search(lec_array[i].index);
			lec_print(lec);

			j++;
		}
	}

	//교양 수업을 삽입하기 위해 LecArray에서 가져온 index에 삽입
	for (int i = 0; i < 5; i++)
	{
		lec = lec_search(basic_insert[i].index);
		sche = push_lec(lec, sche);
	}

	sche_print(sche);

	printf("\n\n");
	return 0;
}


//나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
