/*
 CONTACT.C
  -> This file contains the implementation of functions related to contact management in the address book application.   
  ->It includes functions for loading contacts from a file, adding new contacts with validation and duplicate checks, 
    searching for contacts, editing existing contacts, deleting contacts, listing all contacts in a sorted manner, 
    and saving contacts back to the file.
 
*/
#include "contact.h"
#include"validate.h"
#include"ui.h"
#include"animation.h"
#include<string.h>
#include<stdio.h>

void load_contacts(struct AddressBook *addressBook) //loading contacts from file to structure
{
    int i=0;
    addressBook->contactCount = 0;
    FILE *fp;
    fp=fopen("contact.csv","r"); //opening the file
    while(fscanf(fp,"%[^,],%[^,],%[^\n]\n ",addressBook->contacts[i].name,
                                            addressBook->contacts[i].mobno,
                                            addressBook->contacts[i].email)!= EOF)//read from user
    {
        addressBook->contactCount++; //incrementing count
        i++;
    }
    fclose(fp); //closing file
}

void add_contact(struct AddressBook *addressBook) //function for creating contact
{
    char name[50],mobno[11],email[40];
    int res1,res2,res3;
    do
    {
        printf("Enter your name:");
        scanf("%[^\n]", name);
        getchar();// Consume newline character left by scanf
        res1=validate_name(name);  //validating name
        if(res1 == 0)
        {
            printf(RED"Invalid tryagain!!...😒\n"RESET);
        }
        else
        {
            break;//valid name
        }
    }while( res1 == 0);//if fails iterate again
    printf("Contact name:%s\n",name);
    do
    {
        printf("Enter mobileno:");
        scanf("%s",mobno);
        getchar();// Consume newline character left by scanf
        res2=validate_num(mobno); //validating mobile number
        if(res2 == 1 && (!checkDuplicatnum(mobno,addressBook)))//checking for duplicate
        {
            printf(YELLOW"Number already exists!!Tryagain!\n"RESET);
            res2=0;
        }
        else if(res2 == 0)
        {
             printf(RED"Invalid tryagain!!...😒\n"RESET);
        }
        else
        {
            break; //valid number
        }
    }while(res2 == 0);//if fails iterate again
    printf("Mobile number:%s\n",mobno);
    do
    {
        printf("Enter Email: \n[eg., abc123@gmail.com]\n");
        scanf(" %s",email);
        getchar();// Consume newline character left by scanf
        res3=validate_email(email); //validating email
            if(res3 == 1 && (!checkDuplicatemail(email,addressBook))) //checking for duplicate
            {
                printf(YELLOW"Email already exists!!Tryagain!\n"RESET);
                res3=0;
            }
            else if(res3 == 0)
            {
                printf(RED"Invalid tryagain!!...😒\n"RESET);
            }
            else
            {
                break;//valid email
            }
    }while(res3 == 0); //if fails iterate again
    printf("Email:%s\n",email);

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);//storing name to structure
    strcpy(addressBook->contacts[addressBook->contactCount].mobno,mobno);//storing mobno to structure
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);//storing email to structure
    addressBook->contactCount++; //incementing the contact count
    printf("Total Contacts : %d\n",addressBook->contactCount);
}

void search_contact(struct AddressBook *addressBook)//function for searching contact 
{
    int choice;
    char name[40], mobno[11],email[40];
    addressBook->ir_size=0;//reset everytime
    do
    {
    printf("1.Search by name\n2.Search by mobno\n3.Search by email\n4.Exit\n"); //prompt 
    printf("Enter your choice:\n");
    scanf("%d",&choice);
    getchar();// Consume newline character left by scanf
    switch(choice)
    {
    case 1:
        printf("Enter name:");
        scanf(" %[^\n]",name);
            for(int i=0;i < addressBook->contactCount;i++)
            {
                addressBook->index_record[addressBook->ir_size] = i;
                if(strcmp(name,addressBook->contacts[i].name) == 0)//compare name whether available or not
                {
                    search_animation(); //calling animation function
                    printf(BLUE"\n%d Contacts Matches...😍\n"RESET,addressBook->ir_size+1);
                    printf("Name : \t\t%s\nMobNo : \t%s\nEmail : \t%s\n",
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].mobno,
                                addressBook->contacts[i].email);
                    addressBook->ir_size++;
                }     
            }
            if(addressBook->ir_size == 0) //checking if no contact
            {
            printf("Contact not found😒...try again!!!!\n");
            }
        break;
    case 2:
            printf("Enter mobno:");
            scanf(" %s",mobno);
            for(int i=0;i < addressBook->contactCount;i++)
            {
                addressBook->index_record[addressBook->ir_size] = i;
                if(strcmp(mobno,addressBook->contacts[i].mobno) == 0) //compare mobno
                {
                    search_animation();//calling animation function
                    printf("\n%d Contacts Matches...😍\n",addressBook->ir_size+1);
                    printf("Name : \t\t%s\nMobNo : \t%s\nEmail : \t%s\n",
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].mobno,
                                addressBook->contacts[i].email);
                    addressBook->ir_size++;
                }
            }
            if(addressBook->ir_size == 0) //checking if no contact
            {
            printf("Contact not found😒...try again!!!!\n");
            }
        break;
    case 3:
        printf("Enter email:");
        scanf(" %s",email);
        for(int i=0;i < addressBook->contactCount;i++)
            {
                addressBook->index_record[addressBook->ir_size] = i;
                if(strcmp(email,addressBook->contacts[i].email) == 0) //compare email
                {
                    search_animation(); //calling animation function
                    printf("\n%d Contacts Matches...😍\n",addressBook->ir_size+1);
                    printf("Name : \t\t%s\nMobNo : \t%s\nEmail : \t%s\n",
                                    addressBook->contacts[i].name,
                                    addressBook->contacts[i].mobno,
                                    addressBook->contacts[i].email);
                    addressBook->ir_size++;
                }
            }
            if(addressBook->ir_size == 0) //checking if no contact
        {
        printf("Contact not found😒...try again!!!!\n");
        }
        break;
        case 4:
           exiting_animation();
        break;
    default:
        printf(RED"Invalid choice!!!!😒\n"RESET);
        return;
    }
    
    }while(choice!=4);
    
}

void edit_contact(struct AddressBook *addressBook) //function definition for editing the contact
{
    int select,choice,index,n,m,e;
    char name[50],mobno[11],email[40];
    //list_contacts(addressBook);
    //search for contact u want to edit
    search_contact(addressBook);
    if(addressBook->ir_size == 0)
    {
        return;//nothing to edit because contact not found
    }
    //selecting which contact to edit
    printf("Select contact 1 to %d : ",addressBook->ir_size);  
    scanf("%d",&select);
    if(select < 1 || select > addressBook->ir_size) //checking if selected within available contacts or not
     {
        printf(RED"Invalid selection..😒\n"RESET);
        return;
     }
    index = addressBook->index_record[select-1];
    printf("Edit by:\n1.Name\n2.Mobile\n3.Email\n4.Exit\n");
    printf("Enter your choice: "); //choosing what to edit
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        do{
                printf("Enter new name: ");
                scanf(" %[^\n]", name); //read into local var
                getchar();
                n = validate_name(name); //validating new name
                if(n == 0)
                {
                    printf(RED"Invalid name....😒tryagain!!!\n"RESET);
                }
                else
                {
                    editing_animation(); //calling for edit animation fn
                    strcpy(addressBook->contacts[index].name,name);//storing name to structure
                    printf(GREEN"\nName modified successfully🫡\n"RESET);
                }
        }while(n == 0); //if fail iterate again
        break;
        case 2:
        do
        {
            printf("Enter new mobile: ");
            scanf("%s",mobno);
            m = validate_num(mobno);  //validating new mobile
            if(m == 1 && (!checkDuplicatnum(mobno,addressBook))) //checking for duplicate
            {
                printf(YELLOW"Number already exists!!Tryagain!😶\n"RESET);
                m=0;
            }
            else if(m == 0)
            {
                printf(RED"Invalid number....😒tryagain!!!\n"RESET);
            }
            else
            {
                editing_animation();//calling edit animation fn
                strcpy(addressBook->contacts[index].mobno,mobno);//storing mobno to structure
                printf(GREEN"\nMobile number modified successfully🫡\n"RESET);
            }
        }while(m == 0);//if fail iterate again
        break;
        case 3:
        do
        {
            printf("Enter new email: ");
            scanf("%s", email);
            e = validate_email(email);  //validating the new email
            if(e == 1 && (!checkDuplicatemail(email,addressBook)))//checking for duplicate
            {
                printf(YELLOW"Email already exists!!Tryagain!😶\n"RESET);
                e=0;
            }
            else if(e == 0)
            {
                printf(RED"Invalid email....😒tryagain!!!\n"RESET);
            }
            else
            {
                editing_animation(); //calling edit animation fn
                strcpy(addressBook->contacts[index].email,email);//storing email to structure
                printf(GREEN"\nEmail modified successfully🫡\n"RESET);
            }
        }while(e == 0);//if fail iterate again
        break;
        case 4:
        printf(YELLOW"Exiting...👋\n"RESET);
        break;
        default:
            printf(RED"Invalid choice😒\n"RESET);
    }
}

void delete_contact(struct AddressBook *addressBook)  //function for deleting contact
{
    int select,index,choice;
    char name[50],mobno[11],email[40],confirm;
    //list_contacts(addressBook);
    search_contact(addressBook); //calling search fn for searching to delete
     if(addressBook->ir_size == 0)
    {
        return;//nothing to delete because contact not found
    }
    printf("Select contact 1 to %d : ",addressBook->ir_size); //selecting which contact to edit 
    scanf("%d",&select);
    if(select < 1 || select > addressBook->ir_size) //check if selected within available contact or not
     {
        printf(RED"Invalid selection..😒\n"RESET);
        return;
     }
     index = addressBook->index_record[select-1];
        printf(ORANGE"DELETE MENU:\n"RESET);
        printf(BLUE"*************\n"RESET);
        printf("1.Delete by Name\n2.Delete by Mobilenumber\n3.Delete by Email\n4.Exit\n");
        scanf("%d",&choice);
        getchar();
        switch(choice)
        {
            case 1:
            do
            {
                printf("Enter the name to delete contact : ");
                scanf(" %[^\n]",name);//read name from user
                getchar();// Consume newline character left by scanf
            }while(!validate_name(name));//if fails iterate again
            break;
            case 2:
            do
            {
                printf("Enter the mobile number to delete contact:");
                scanf("%s",mobno); //read from user
                getchar();// Consume newline character left by scanf
            }while(!validate_num(mobno)); //if fails iterate again
            break;
            case 3:
            do
            {
                printf("Enter the emailid to delete contact:");
                scanf("%s",email);
                getchar();// Consume newline character left by scanf
            }while(!validate_email(email)); //if fails iterate again
            break;
            case 4:
            printf(YELLOW"Exiting delete contact....\n"RESET);
            break;
            default:
            printf(RED"Invalid choice...tryagain!!!!\n"RESET);       
        }  
    printf(PINK"Do you want to delete....Y/N:\n"RESET);
    scanf(" %c",&confirm);
       if((confirm == 'Y') || (confirm == 'y'))
       {
            for(int i=index;i<addressBook->contactCount-1;i++)
            {
                strcpy(addressBook->contacts[i].name,  addressBook->contacts[i + 1].name); //shift name
                strcpy(addressBook->contacts[i].mobno, addressBook->contacts[i + 1].mobno);//shift phone
                strcpy(addressBook->contacts[i].email,  addressBook->contacts[i + 1].email);//shift email
            }
            addressBook->contactCount--;
            deleting_animation();
        }
       else
       {
        printf(PINK"\nDeletion cancelled....\n"RESET);
        //   return;
       }
}

void list_contacts(struct AddressBook *addressBook)  //function for displaying contacts
{
    if(addressBook->contactCount == 0) //condition to check if no contacts
    {
        printf(RED"No Contacts found....\n"RESET);
        return;
    }
    {
        for (int i = 0; i < addressBook->contactCount - 1; i++) // Bubble sort to sort contacts by name
        {
            for (int j = 0; j < addressBook->contactCount - 1 - i; j++) //checking inner loop
            {
                if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) //case insensitive comparison
                {
                    //swap contacts
                    struct Contact temp = addressBook->contacts[j]; 
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
    }
    printf("\n");
   int c=32; //ascii value for space
   printf("%30c"ORANGE"LIST OF CONTACTS....\n"RESET,c);//displaying the title
   printf("%30c"BLUE"********************\n"RESET,c);
   //storing line to string
   char *strline = "|-------------------------------------------------------------------------------------------------|";
   printf("%s\n",strline);//printing line
   printf("|%-27s|%-27s|%-27s|%-27s",YELLOW"S.No"RESET, YELLOW "Name"RESET,  YELLOW" Mobno"RESET,YELLOW"Email"RESET);
   printf("\n%s\n",strline);
   for(int i=0;i<addressBook->contactCount;i++)
   {
        printf(PINK"|%-18d|"RESET GREEN"%-18s|"RESET BLUE"%-18s|"RESET ORANGE"%-18s"RESET,i+1,addressBook->contacts[i].name,
                                        addressBook->contacts[i].mobno,
                                        addressBook->contacts[i].email);
    
     printf("\n%s\n",strline);
    }        
    printf("|Total Contacts:%d" "%s\n",addressBook->contactCount,"|");//to display tot contacts in number
    printf("%s\n",strline);
}

void save_contacts(struct AddressBook *addressBook)  //saving contatcts from structure to file
{
    FILE *fp;
    fp=fopen("contact.csv","w"); //opening file in write mode
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    saving_animation(); //animation before writing
    for(int i=0;i < addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,
                                addressBook->contacts[i].mobno,
                                addressBook->contacts[i].email);
    }
    fclose(fp);
    printf(GREEN"\nContact saved successfully....😍\n"RESET);
    
}


