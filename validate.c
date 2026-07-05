/* This validation file is for validating contacts and 
   checking duplicates 
*/

#include "contact.h"
#include "validate.h"
#include<stdio.h>
#include<string.h>
          /*NAME*/
int validate_name(char *name) //function definition for validating name
{
    int i=0;
    //check if name is empty or name starts with digits
    if((name[0] == '\0')||(name[0] == ' ')||(name[0] >= '0' && name[0] <= '9'))
        {
          return 0;//fail
        }
    while(name[i] != '\0')
    {
        //check next char
         if(name[i+1] != '\0')
          {
            //check if consecutive spaces or dots present
            if((name[i] == ' ' && name[i+1] == ' ')||
                (name[i] == '.' && name[i+1] == '.'))
            {
              return 0; //fail
            }
         }
          //checking for invalid characters
          if(!((name[i]>='A'&&name[i]<='Z') || 
               (name[i]>='a'&&name[i]<='z') || 
               (name[i] == ' ') || (name[i] == '.')))
          {
            return 0; //fail   
          }
          
        i++;
    }
    
    //last char should not be space or dot
          if(i > 0 &&((name[i-1] == ' ') || (name[i-1] == '.')))
          {
            return 0; //fail
          }
    return 1; //success
}
              /*NUMBER*/
int validate_num(char *mobno)//function definition for validating number
{
  int i=0;
  int len=strlen(mobno);
  //check if length is 10 or not
  if(len != 10) 
  {
    return 0; //fail
  }
  //check if num starts with digits 6,7,8,9
  if(!(mobno[0] >= '6' && mobno[0] <= '9'))
  {
    return 0; //fail
  }
  while(mobno[i] != '\0') //going through each digit until reaches null
  {
    if(!(mobno[i] >= '0'  && mobno[i] <= '9'))//checking for non numeric
    {
      return 0; //fail
    }
    i++;
  }
  return 1; //success
}
               /*EMAIL*/
int validate_email(char *email) //function definition for validating email
{
  int i=0,count=0;
  int len=strlen(email);
  if(len < 10) //should be lengthy than @gmail.com
  {
    return 0; //fail
  }
  //first char should not be digit or '@'
  if((email[0] >= '0' && email[0] <= '9')||(email[0] == '@'))
  {
     return 0;//fail
  }
  //count '@'
  for(i = 0;i < len; i++)
  {
  if(email[i] == '@')
    count++;
  }
  if(count != 1)
  {
    return 0;//fail
  }
  //must end with "@gmail.com"
  if(strcmp(email+len-10,"@gmail.com") != 0)
  {
    return 0; //fail
  }
  //reset of i with 0 because i becomes len in the above loop
  i=0; 
  //checking valid characters
  while(i < len) //checking len times
  {
    //validating 
    if(!((email[i] >= 'a' && email[i] <= 'z') ||
         (email[i] >= '0' && email[i] <= '9') || 
         email[i] == '@' || email[i] == '.' || email[i] == '_'))
    {
      return 0; //fail
    }
    i++;                                    
  }
  
  return 1;//success
}

//funtion definition for checking duplicate name
int checkDuplicatname(char name[],struct AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(name,addressBook->contacts[i].name)==0) //comparing name
        return 0;//fail
    }
    return 1;//success
}

//function definition for checking duplicate number
int checkDuplicatnum(char mobno[],struct AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(mobno,addressBook->contacts[i].mobno) == 0) //comparing number
        return 0;//fail
    }
    return 1;//success
}

//funtion definition for checking duplicate email
int checkDuplicatemail(char email[],struct AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email) == 0)  //comparing email
        return 0;//fail
    }
    return 1;//success
}