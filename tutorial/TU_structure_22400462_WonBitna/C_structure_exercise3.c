/*-------------------------------------------------------------------------------\
@ C-Tutorial by Young-Keun Kim - Handong Global University
Author           : SSS LAB
Created          : 19-08-2022
Modified         : 19-08-2022
Language/ver     : C in MSVS2022
Description      : C_structure_exercise3.c
-------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	int x;
	int y;
	int z;
} POSITION_TypeDef;

//
void addPos(POSITION_TypeDef pos1, POSITION_TypeDef pos2, POSITION_TypeDef *posOut);
void getDist(POSITION_TypeDef pos1, POSITION_TypeDef pos2, POSITION_TypeDef *posOut);
void printPos (POSITION_TypeDef Pos);

void main() 
{
	// Exercise 2 ***********************************************
	printf("\nExercise 2\n");
	POSITION_TypeDef Pos[2];
	POSITION_TypeDef PosOut = {0, };
	
	Pos[0].x = 2; Pos[0].y = 2; Pos[0].z = 2;
	Pos[1].x = 5; Pos[1].y = 5; Pos[1].z = 5;

	addPos(Pos[0], Pos[1], &PosOut);
	printPos(PosOut);
	getDist(Pos[0], Pos[1], &PosOut);
	printPos(PosOut);

	system("pause");
}

void addPos(POSITION_TypeDef pos1, POSITION_TypeDef pos2, POSITION_TypeDef *posOut){
	posOut->x = pos1.x + pos2.x;
	posOut->y = pos1.y + pos2.y;
	posOut->z = pos1.z + pos2.z;
	return;
}

void getDist(POSITION_TypeDef pos1, POSITION_TypeDef pos2, POSITION_TypeDef *posOut){
	posOut->x = abs(pos1.x - pos2.x);
	posOut->y = abs(pos1.y - pos2.y);
	posOut->z = abs(pos1.z - pos2.z);
	return;
}

void printPos (POSITION_TypeDef Pos){
	printf("PosOut result : (x, y, z) = (%d, %d, %d)\n", Pos.x, Pos.y, Pos.z);
	return;
}