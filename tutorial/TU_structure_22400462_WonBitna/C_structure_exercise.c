/*-------------------------------------------------------------------------------\
@ C-Tutorial by Young-Keun Kim - Handong Global University
Author           : 코딩 도장
Created          : 19-08-2022
Modified         : 19-08-2022
Language/ver     : C in MSVS2022
Description      : C_structure_exercise.c
-------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[20];
    int grade;
    int class;
    float average;
};

int main()
{
    struct Student *s1 = malloc(sizeof(struct Student));

    strcpy(s1->name, "고길동");
    s1->grade = 1;
    s1->class = 3;
    s1->average = 65.389999;

    printf("이름: %s\n", s1->name);
    printf("학년: %d\n", s1->grade);
    printf("반: %d\n", s1->class);
    printf("평균점수: %f\n", s1->average);

    free(s1);

    return 0;
}