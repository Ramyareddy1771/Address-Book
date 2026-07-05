//Animations for user interface
#include"animation.h"
#include<stdio.h>
#include<unistd.h>
#include"ui.h"

void search_animation()
{
    char str[]="Searching..";
    for(int i=0;str[i] != '\0';i++)
    {
        printf(" %c",str[i]);
        fflush(stdout);
        usleep(100000); //1.0 sec delay
    }
}
void editing_animation()
{
    printf("Modifying\n");
    char str[]="....";
    for(int i = 0;str[i] != '\0';i++)
    {
        printf(" %c",str[i]);
        fflush(stdout);
        sleep(1); //1 sec
    }
}
void saving_animation()
{
    printf("Saving");
    char str[]="....";
    for(int i=0;str[i] != '\0';i++)
    {
        printf(" %c",str[i]);
        fflush(stdout);
        sleep(1); //1 sec
    }   
}
void deleting_animation()
{
    char str[]="Deleting...!!!";
    for(int i = 0; str[i] != '\0'; i++)
    {
        printf(" %c",str[i]);
        fflush(stdout);
        usleep(100000); // 0.1 sec
    }

    printf(GREEN"Contact deleted successfully....🫡\n"RESET);
}
void exiting_animation()
{
    char str[]="Exiting....";
    for(int i=0;str[i] != '\0';i++ )
    {
        printf(" %c",str[i]);
        fflush(stdout);
        usleep(100000);//0.1sec delay
    }
    printf("\n");
}