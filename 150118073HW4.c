#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct student_list {
    char *name;
    char *surname;
    int ID;
    struct student_list* name_next;
    struct student_list* surname_next;
    struct student_list* id_next;
   
}student_list;

typedef student_list * student_listPtr;

void printList(student_listPtr currNamePtr,student_listPtr currSurnamePtr,student_listPtr currIdPtr);
void insert(student_listPtr *name_rootPtr,student_listPtr *surname_rootPtr,student_listPtr * id_rootPtr,char *name,char*surname,int id);
void instructions();
void delete(student_listPtr *name_rootPtr,student_listPtr *surname_rootPtr,student_listPtr * id_rootPtr,char *name,char*surname,int id);
void printListToFile(student_listPtr currNamePtr,student_listPtr currSurnamePtr,student_listPtr currIdPtr);

int main(int argc,char *argv[])
{
    
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("Can not opened file.");
        return(-1);
    }
    char studentName[50];
    char studentSurname[50];
    char *ptrName = studentName;
    char *ptrSurname = studentSurname;
    int studentId;
    char line[128];
    
    student_listPtr root_namePtr = NULL;
    student_listPtr root_surnamePtr = NULL;
    student_listPtr root_idPtr = NULL;

    while(fgets(line,sizeof(line),fp)){
        sscanf(line,"%s %[^\t]%d",studentName,studentSurname,&studentId);
        insert(&root_namePtr,&root_surnamePtr,&root_idPtr,ptrName,ptrSurname,studentId);
        
    }
    fclose(fp);
    
    printList(root_namePtr,root_surnamePtr,root_idPtr);
    instructions();
    printf("%s","? ");
    unsigned int choice;
    scanf("%u",&choice);
    while (choice != 5)
   {
       switch (choice)
       {
       case 1:
        printf("%s","Enter a student name ,surname and ID:");
        scanf("\n%s %s %d",studentName,studentSurname,&studentId);
        insert(&root_namePtr,&root_surnamePtr,&root_idPtr,ptrName,ptrSurname,studentId);
                break;

       case 2:
        printf("%s","Enter a student name, surname and ID:");
        scanf("\n%s %s %d",studentName,studentSurname,&studentId);
        delete(&root_namePtr,&root_surnamePtr,&root_idPtr,ptrName,ptrSurname,studentId);
        printf("\nThe student \"%s %s %d\" is deleted from the list.\n",ptrName,ptrSurname,studentId);
       break;

       case 3:
       printList(root_namePtr,root_surnamePtr,root_idPtr);
            break;

       case 4:
       printListToFile(root_namePtr,root_surnamePtr,root_idPtr);
            break;
       
       default:
       puts("Invalid choice.");
            break;
       }
       printf("\n");
       instructions();
       printf("%s","? ");
       scanf("%u",&choice);
       
   }
   puts("THE END");
   puts("--------------------------------");
   
    return 0;
}
void insert(student_listPtr *name_rootPtr,student_listPtr *surname_rootPtr,student_listPtr * id_rootPtr,char *name,char*surname,int id){
    
    student_listPtr newPtr = malloc(sizeof(student_list));
    
    if(newPtr != NULL){
        newPtr->ID=id;
        newPtr->name = strdup(name);
        newPtr->surname = strdup(surname);
        newPtr->id_next = NULL;
        newPtr->name_next=NULL;
        newPtr->surname_next=NULL;

        student_listPtr preNamePtr = NULL;
        student_listPtr currtNamePtr = *name_rootPtr;
        student_listPtr preSurnamePtr = NULL;
        student_listPtr currSurnamePtr = *surname_rootPtr;
        student_listPtr preIdPtr = NULL;
        student_listPtr currIdPtr = *id_rootPtr;

        while(currtNamePtr != NULL && strcmp(currtNamePtr->name,name)<0){
            preNamePtr = currtNamePtr;
            currtNamePtr = currtNamePtr->name_next;
        }

        while(currSurnamePtr != NULL && strcmp(currSurnamePtr->surname,surname)<0){
            preSurnamePtr = currSurnamePtr;
            currSurnamePtr = currSurnamePtr->surname_next;
        }

        while(currIdPtr != NULL && id > currIdPtr->ID){
            preIdPtr = currIdPtr;
            currIdPtr = currIdPtr->id_next;
        }

        if(preNamePtr == NULL){
            newPtr->name_next = *name_rootPtr;
            *name_rootPtr = newPtr;
        }else
        {
            preNamePtr->name_next = newPtr;
            newPtr->name_next = currtNamePtr;
        }
        
        if(preSurnamePtr == NULL){
            newPtr->surname_next = *surname_rootPtr;
            *surname_rootPtr = newPtr;
        }
        else
        {
            preSurnamePtr->surname_next = newPtr;
            newPtr->surname_next = currSurnamePtr;
        }

        if(preIdPtr ==NULL){
            newPtr->id_next = *id_rootPtr;
            *id_rootPtr = newPtr;
        }else
        {
            preIdPtr->id_next=newPtr;
            newPtr->id_next=currIdPtr;
        }
    }
    else
    {
        printf("Student is not inserted.No memory available.\n");
    }
}
void printList(student_listPtr currNamePtr,student_listPtr currSurnamePtr,student_listPtr currIdPtr){
        puts("The list in name-alphabetical order:");
        int i = 1;
        while (currNamePtr != NULL){
            printf("%d. %s %s\t%d\n",i,currNamePtr->name,currNamePtr->surname,currNamePtr->ID);
            currNamePtr = currNamePtr->name_next;
            i++;
        }
        i=1;
        printf("\n");
        puts("The list in surname-alphabetical order:");
        while (currSurnamePtr != NULL){
            printf("%d. %s %s\t%d\n",i,currSurnamePtr->name,currSurnamePtr->surname,currSurnamePtr->ID);
            currSurnamePtr = currSurnamePtr->surname_next;
            i++;
        }
        i=1;
        printf("\n");
        puts("The list in ID sorted order:");
        while (currIdPtr != NULL){
            printf("%d. %s %s\t%d\n",i,currIdPtr->name,currIdPtr->surname,currIdPtr->ID);
            currIdPtr = currIdPtr->id_next;
            i++;
        }
        printf("\n");
}
void instructions(){
    puts("Enter your choice:\n"
    "1 to insert  a student  into the list.\n"
    "2 to  delete a student  from the list.\n"
    "3 to print the students in the list.\n"
    "4 to print the students to an output file.\n"
    "5 to end.");
}
void delete(student_listPtr *name_rootPtr,student_listPtr *surname_rootPtr,student_listPtr * id_rootPtr,char *name,char*surname,int id){
    if(strcmp((*name_rootPtr)->name,name)== 0 && strcmp((*surname_rootPtr)->surname,surname)==0 && (*id_rootPtr)->ID == id){ //if all is root
        student_listPtr tempPtr = *name_rootPtr;
        *name_rootPtr = (*name_rootPtr)->name_next;
        *surname_rootPtr = (*surname_rootPtr)->surname_next;
        *id_rootPtr = (*id_rootPtr)->id_next;
        free(tempPtr);
    }else if(strcmp((*name_rootPtr)->name,name)== 0 && strcmp((*surname_rootPtr)->surname,surname)==0 && (*id_rootPtr)->ID != id ){ //only name and surname is root 
        *name_rootPtr = (*name_rootPtr)->name_next;
        *surname_rootPtr = (*surname_rootPtr)->surname_next;
        student_listPtr previousPtr2 = *id_rootPtr;
        student_listPtr currentPtr2 = (*id_rootPtr)->id_next;
        while(currentPtr2 != NULL && currentPtr2->ID != id){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->id_next;
        }
        if(currentPtr2 != NULL){
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->id_next = currentPtr2->id_next;
            free(tempPtr2);
        }
    }else if(strcmp((*name_rootPtr)->name,name)== 0 && strcmp((*surname_rootPtr)->surname,surname)!=0 && (*id_rootPtr)->ID == id){ //only name and id is root
        *name_rootPtr = (*name_rootPtr)->name_next;
        *id_rootPtr = (*id_rootPtr)->id_next;
        student_listPtr previousPtr2 = *surname_rootPtr;
        student_listPtr currentPtr2 = (*surname_rootPtr)->surname_next;
        while(currentPtr2 != NULL && strcmp(currentPtr2->surname,surname)!=0){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->surname_next;
        }
        if(currentPtr2 != NULL){
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->surname_next = currentPtr2->surname_next;
            free(tempPtr2);
        }
    }else if(strcmp((*name_rootPtr)->name,name)!= 0 && strcmp((*surname_rootPtr)->surname,surname)==0 && (*id_rootPtr)->ID == id){ // only surname and id root
        *surname_rootPtr = (*surname_rootPtr)->surname_next;
        *id_rootPtr = (*id_rootPtr)->id_next;
        student_listPtr previousPtr2 = *name_rootPtr;
        student_listPtr currentPtr2 = (*name_rootPtr)->name_next;
        while(currentPtr2 != NULL && strcmp(currentPtr2->name,name)!=0){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->name_next;
        }
        if(currentPtr2 != NULL){
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->name_next = currentPtr2->name_next;
            free(tempPtr2);
        }
    }else if(strcmp((*surname_rootPtr)->surname,surname)==0 && strcmp((*name_rootPtr)->name,name) != 0 && (*id_rootPtr)->ID != id ){ //if only surname is root
        student_listPtr tempPtr = *surname_rootPtr;
        *surname_rootPtr = (*surname_rootPtr)->surname_next;
        student_listPtr previousPtr1 = *name_rootPtr;
        student_listPtr currentPtr1 = (*name_rootPtr)->name_next;
        student_listPtr previousPtr2 = *id_rootPtr;
        student_listPtr currentPtr2 = (*id_rootPtr)->id_next;
        while(currentPtr1 != NULL && strcmp(currentPtr1->name,name)!=0){
            previousPtr1 = currentPtr1;
            currentPtr1 = currentPtr1->name_next;
        }
        while(currentPtr2 != NULL && currentPtr2->ID != id){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->id_next;
        }
        if(currentPtr1 != NULL && currentPtr2 != NULL){
            student_listPtr tempPtr1 = currentPtr1;
            previousPtr1->name_next = currentPtr1->name_next;
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->id_next = currentPtr2->id_next;
            free(tempPtr1);
        } 
    }else if((*id_rootPtr)->ID == id && strcmp((*surname_rootPtr)->surname,surname)!=0 && strcmp((*surname_rootPtr)->surname,surname) != 0){ // if only id is root
        student_listPtr tempPtr = *id_rootPtr;
        *id_rootPtr = (*id_rootPtr)->id_next;
        student_listPtr previousPtr1 = *name_rootPtr;
        student_listPtr currentPtr1 = (*name_rootPtr)->name_next;
        student_listPtr previousPtr2 = *surname_rootPtr;
        student_listPtr currentPtr2 = (*surname_rootPtr)->surname_next;
        while(currentPtr1 != NULL && strcmp(currentPtr1->name,name)!=0){
            previousPtr1 = currentPtr1;
            currentPtr1 = currentPtr1->name_next;
        }
        while(currentPtr2 != NULL && strcmp(currentPtr2->surname,surname)!=0){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->surname_next;
        }
        if(currentPtr1 != NULL && currentPtr2 != NULL){
            student_listPtr tempPtr1 = currentPtr1;
            previousPtr1->name_next = currentPtr1->name_next;
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->surname_next = currentPtr2->surname_next;
            free(tempPtr1);
        } 

    }else if(strcmp((*name_rootPtr)->name,name)==0 && strcmp((*surname_rootPtr)->surname,surname) != 0 && (*id_rootPtr)->ID != id){ // if only name is root
        student_listPtr tempPtr = *name_rootPtr;
        *name_rootPtr = (*name_rootPtr)->name_next;
        student_listPtr previousPtr1 = *surname_rootPtr;
        student_listPtr currentPtr1 = (*surname_rootPtr)->surname_next;
        student_listPtr previousPtr2 = *id_rootPtr;
        student_listPtr currentPtr2 = (*id_rootPtr)->id_next;
        while(currentPtr1 != NULL && strcmp(currentPtr1->surname,surname)!=0){
            previousPtr1 = currentPtr1;
            currentPtr1 = currentPtr1->surname_next;
        }
        while(currentPtr2 != NULL && currentPtr2->ID != id){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->id_next;
        }
        if(currentPtr1 != NULL && currentPtr2 != NULL){
            student_listPtr tempPtr1 = currentPtr1;
            previousPtr1->surname_next = currentPtr1->surname_next;
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->id_next = currentPtr2->id_next;
            free(tempPtr1);
        } 
    }else if(strcmp((*name_rootPtr)->name,name)!=0 && strcmp((*surname_rootPtr)->surname,surname) != 0 && (*id_rootPtr)->ID != id){ // no root
        student_listPtr previousPtr = *name_rootPtr;
        student_listPtr currentPtr = (*name_rootPtr)->name_next;
        student_listPtr previousPtr1 = *surname_rootPtr;
        student_listPtr currentPtr1 = (*surname_rootPtr)->surname_next;
        student_listPtr previousPtr2 = *id_rootPtr;
        student_listPtr currentPtr2 = (*id_rootPtr)->id_next;

        while(currentPtr != NULL && strcmp(currentPtr->name,name)!=0){
            previousPtr = currentPtr;
            currentPtr = currentPtr->name_next;
        }
        while(currentPtr1 != NULL && strcmp(currentPtr1->surname,surname)!=0){
            previousPtr1 = currentPtr1;
            currentPtr1 = currentPtr1->surname_next;
        }
        while(currentPtr2 != NULL && currentPtr2->ID != id){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->id_next;
        }
        if(currentPtr !=NULL && currentPtr1 != NULL && currentPtr1 != NULL){
            student_listPtr tempPtr = currentPtr;
            previousPtr->name_next = currentPtr->name_next;
            student_listPtr tempPtr1 = currentPtr1;
            previousPtr1->surname_next = currentPtr1->surname_next;
            student_listPtr tempPtr2 = currentPtr2;
            previousPtr2->id_next = currentPtr2->id_next;
            free(tempPtr);
        }
    }
}
void printListToFile(student_listPtr currNamePtr,student_listPtr currSurnamePtr,student_listPtr currIdPtr){
    printf("%s","Enter a file name:");
       char fileName[50];
       char *fileNamePtr = fileName;
       scanf("\n%s",fileName);
       FILE *filePtr;
       filePtr = fopen(fileNamePtr,"w");
    fprintf(filePtr,"The list in name-alphabetical order:\n");
        int i = 1;
        while (currNamePtr != NULL){
            fprintf(filePtr,"%d. %s %s\t%d\n",i,currNamePtr->name,currNamePtr->surname,currNamePtr->ID);
            currNamePtr = currNamePtr->name_next;
            i++;
        }
        i=1;
        fprintf(filePtr,"\n");
        fprintf(filePtr,"The list in surname-alphabetical order:\n");
        while (currSurnamePtr != NULL){
            fprintf(filePtr,"%d. %s %s\t%d\n",i,currSurnamePtr->name,currSurnamePtr->surname,currSurnamePtr->ID);
            currSurnamePtr = currSurnamePtr->surname_next;
            i++;
        }
        i=1;
        fprintf(filePtr,"\n");
        fprintf(filePtr,"The list in ID sorted order:\n");
        while (currIdPtr != NULL){
            fprintf(filePtr,"%d. %s %s\t%d\n",i,currIdPtr->name,currIdPtr->surname,currIdPtr->ID);
            currIdPtr = currIdPtr->id_next;
            i++;
        }
        fprintf(filePtr,"\n");
}
