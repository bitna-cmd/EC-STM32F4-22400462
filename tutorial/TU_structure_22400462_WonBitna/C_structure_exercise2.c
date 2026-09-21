/*-------------------------------------------------------------------------------\
@ C-Tutorial by Young-Keun Kim - Handong Global University
Author           : SSS LAB
Created          : 19-08-2022
Modified         : 19-08-2022
Language/ver     : C in MSVS2022
Description      : C_structure_exercise2.c
-------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char building_name[100];
	int room_number;
	char room_name[100];
} Handong;


int main()
{
    // Create structure type (Handong)  variable  room1
    Handong room1;
    
    // Create structure type (Handong)  variable  room2, room3
    // Your code goes here
	Handong room2, room3;
	
    // Create structure type (Handong)  Pointer , roomPt
    Handong *room1Pt = &room1;
    
    // Assign room3 address to roomPt
    // Your code goes here
	Handong *room3Pt = &room3;
	

    // Define structure variable  memeber values: room1
	strcpy(room1.building_name, "Newton");
	room1.room_number = 109;
	strcpy(room1.room_name, "iiLAB");

    // Define structure variable  memeber values: room2
	// Your code goes here
	// Your code goes here
	// Your code goes here
	strcpy(room2.building_name, "Newton");
	room2.room_number = 118;
	strcpy(room2.room_name, "Control-Lab");

    // Define structure variable  memeber values: room3
	// Your code goes here
	// Your code goes here
	// Your code goes here
	strcpy(room3.building_name, "Newton");
	room3.room_number = 119;
	strcpy(room3.room_name, "SW-Lab");
    
    // Print each member values  : room1, room2, room3
	printf("%s building, room  %d  is %s\n", room1.building_name, room1.room_number, room1.room_name);
	// Your code goes here
	// Your code goes here
	printf("%s building, room  %d  is %s\n", room2.building_name, room2.room_number, room2.room_name);
	printf("%s building, room  %d  is %s\n", room3.building_name, room3.room_number, room3.room_name);	

	// Print each member values by  pointer variable: room1Pt
	// Your code goes here
	printf("%s building, room  %d  is %s\n", room1Pt->building_name, room1Pt->room_number, room1Pt->room_name);

	
	// Print address of   room1  and value of room1Pt and compare. 
	printf("\n room1 address=%x ,  roomPt = %x  \n", &room1, room1Pt);
		

}
