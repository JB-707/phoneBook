#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char number[15];
    int areaCode;
    char name[50];
}Contact;
const int MAX_CONTACT = 100;

int main() {
    int userInput = 0;
    int running = 1;

    void addContacts(Contact phoneBook[], int *count);
    void removeContacts(Contact phoneBook[], int *count);
    void editContacts(Contact phoneBook[], int *count);
    void printContacts(Contact phoneBook[], int count);

    Contact phoneBook[MAX_CONTACT];
    int contactCount = 0;
    int *pContactCount = &contactCount;

    printf("Welcome to your phone book.\n");
    while (running){
    printf("1: print phoneBook\n2: add contacts\n3: remove contacts\n4: edit contacts\n5: exit");
    scanf("%d", &userInput);

    switch(userInput){
        case 1:
            printContacts(phoneBook, contactCount);
            break;
        case 2:
            addContacts(phoneBook, pContactCount);
            break;
        case 3:
            removeContacts(phoneBook, pContactCount);
            break;
        case 4:
            editContacts(phoneBook, pContactCount);
            break;
        case 5:
            printf("Goodbye!");
            running = 0;
            break;
        default:
            printf("That is not a valid option. exiting");
            running = 0;
            break;
    }

  }
    return 0;
}

/*
BREIF: an array acts as a pointer to the first value in it's bounds, no matter if its defined or not.
NOTE: use this to add user input values to an array. It involves using a counter pointer to add variabels to a specific slot in the array, the incrimenting it. Like a suppply chain.
WARNING: this does require pointer use. But is reletivly simple, and very useful.
*/

void addContacts(Contact phoneBook[], int *count){
    if(*count == 100){
        printf("The phone book is full! remove some contacts.");
        return;
    }

    int userNumber = 0;
    int userArea = 0;
    char userName[50];
    printf("Enter the contact's phone number: ");
    getchar();
    fgets(phoneBook[*count].number, 15, stdin);

    printf("Please enter the contacts area code number: ");
    scanf("%d", &phoneBook[*count].areaCode);
    getchar();
    printf("Please enter the contacts name: ");
    fgets(phoneBook[*count].name, 50, stdin);

    (*count)++;
    printf("Contact successfully made.");
}

void printContacts(Contact phoneBook[], int count){
    printf("Here are your contacts\n");
    for(int i = 0; i < count; i++){
        printf("%s, %d, %s \n", phoneBook[i].name, phoneBook[i].areaCode, phoneBook[i].number);
    }
}

void removeContacts(Contact phoneBook[], int *count){
    int userIndex = 0;
    printContacts(phoneBook, *count);

    printf("\n which contact would you like to remove(please insert the array index number");
    scanf("%d", &userIndex);
    int arrayIndex = userIndex - 1;

    if(arrayIndex < 0 || arrayIndex >= *count){
        printf("Please enter a valid index");
        return;
    }

    for(int i = arrayIndex; i < *count - 1; i++){
        phoneBook[i] = phoneBook[i + 1];
    }

    memset(phoneBook[*count - 1].number, 0, sizeof(phoneBook[*count - 1].number));
    phoneBook[*count - 1].areaCode = 0;

    memset(phoneBook[*count -1].name, 0, sizeof(phoneBook[*count - 1].name)); //NOTE: memset overwrites the memroy data allocated to name with 0's.

    (*count)--;
}
//TODO: needs check on userIndex
void editContacts(Contact phoneBook[], int *count){
    char newNumber[15];
    int newAreaCode = 0;
    char newName[50];
    int userIndex = 0;

    
    printContacts(phoneBook, *count);

    printf("\n what contact would you like to edit?(please use the index number)");
    scanf("%d", &userIndex);

    if(userIndex > *count){
    printf("Phone Number doesn't exist. Exiting...");
    return;
  }

    printf("what is the new name for this Contact: ");
    getchar();
    fgets(newName, 50, stdin);

    printf("\n what is the new number for this Contact: ");
    fgets(newNumber, 15, stdin);

    printf("\n what is the new area code for this Contact: ");
    scanf("%d", &newAreaCode);

    strcpy(phoneBook[userIndex].name, newName);
    strcpy(phoneBook[userIndex].number, newNumber);
    phoneBook[userIndex].areaCode = newAreaCode;

    printf("Your contact has been edited");
}
