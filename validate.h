//validation function declarations takes place here
#ifndef VALIDATE_H
#define VALIDATE_H
#include"contact.h"
int validate_name(char name[]);
int validate_num(char mobno[]);
int validate_email(char email[]);
int checkDuplicatname(char name[],struct AddressBook *addressBook);
int checkDuplicatnum(char mobno[],struct AddressBook *addressBook);
int checkDuplicatemail(char email[],struct AddressBook *addressBook);
#endif