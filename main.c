/*
	NAME          : RAMYA AMBATI
	DATE          : 28-03-2026
	PROJECT TITLE : ADDRESS BOOK
	DESCRIPTION   : Main file to run the Address structure 
					and provides a menu-driven interface for user interaction.
					It repeatedly prompts the user to select operations such as
					adding,searching,editing,deleting,listing,saving and exiting contacts.

   OPERTIONS USED   :   1. Add/Create contact
						2. Search contact
						3. Edit contact
						4. Delete contact
						5. List all contacts
						6. Save And Exit

    OBJECTIVE     : * To implement an address book application in C that allows users to manage their contacts efficiently. 
		`			* The application provides functionalities to add, search, edit, delete, list and save contacts,
					   ensuring data integrity through validation and duplicate checks. 

	CONCEPTS USED  : Structures, File Handling, String Manipulation, Functions, Arrays, User Input Validation.

	COMPILER      : GCC (GNU Compiler Collection)
	
	CODE STRUCTURE  : 1. contact.h - Contains structure definitions and function declarations related to contact management.
					2. contact.c - Implements functions for loading, adding, searching, editing, deleting, listing, and saving contacts.
					3. validate.h - Contains function declarations for validating contact details and checking duplicates.
					4. validate.c - Implements validation functions for names, mobile numbers, and email addresses, as well as duplicate checks.
					5. animation.h - Contains function declarations for user interface animations.
					6. animation.c - Implements animations for searching, editing, saving, and deleting contacts.
					7. ui.h - Contains function declarations for user interface elements (if any).
					8. main.c - The entry point of the application that provides a menu-driven interface for user interaction.

    COMMANDS`	  : To compile: gcc *.c
					To run: ./a.out
*/
#include "contact.h"
#include "validate.h"
#include "ui.h"
#include "animation.h"
#include<stdio.h>
int main() 
{
    int choice;
    struct AddressBook addressBook;
    addressBook.contactCount = 0;
    addressBook.ir_size = 0;
	load_contacts(&addressBook);
    printf("size of addressbook is:%zu\n", sizeof(addressBook));
    do 
    {
	printf(PINK"\nADDRESSBOOK MENU:\n"RESET);
	printf(BLUE"1. Add/Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Save\n");
	printf("7. Exit\n"RESET);
	printf("Enter your choice: ");
	scanf("%d", &choice);
    getchar(); // Consume newline character left by scanf
	switch (choice) 
	{
	    case 1:
		add_contact(&addressBook);
		break;
	    case 2:
		search_contact(&addressBook);
		break;
	    case 3:
		edit_contact(&addressBook);
		break;
	    case 4:
		delete_contact(&addressBook);
		break;
	    case 5:
		list_contacts(&addressBook);
		break;
	    case 6:
		save_contacts(&addressBook);
		break;
	    case 7:
		exiting_animation();
		break;
	    default:
		printf(RED"Invalid choice. Please try again.\n"RESET);
	}
    }while (choice != 7);
    return 0;
}
