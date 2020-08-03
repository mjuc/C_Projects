#ifndef DB_LIB
#define DB_LIB
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "DB.h"


pthread_mutex_t lock;
struct DataBase local_db;
void *read_db(void)
{
    FILE *db_file;
    db_file = *fopen("data_base","rb");
    if (db_file == NULL)
    {
        printf("Cannot access data base \n");
    }
    else
    {
        for(int i=0;i<150;i++)
        {
            gets(local_db.record[i],30,db_file);
        }
    }
    fclose(db_file);
}
void *save_db(void)
{
    FILE *db_file;
    pthread_mutex_lock(&lock);
    db_file = *fopen("data_base","wb");
    if (db_file == NULL)
    {
        printf("Cannot access data base \n");
    }
    else
    {
        for(int i=0;i<150;i++)
        {
            fprintf(db_file,local_db.record[i]);
        }
    }
    fclose(db_file);
    pthread_mutex_unlock(&lock);
    pthread_create(&thread_id, NULL, read_db, NULL); 
    pthread_join(thread_id, NULL);
}
void* replace_record(void)
{
    int record_number;
    char new_record[30];
    printf("%s","Choose record to replace:\n");
    scanf("%d",record_number);
    if(record_number < 150)
    {
        printf("%s","New record:\n");
        new_record = getline(stdin);
        int limit = strlen(local_db.record[record_number]);
        for (int i=0;i<limit;i++)
        {
            local_db.record[record_number][i]=new_record[i];
        }
    }
}
void database_menu(void)
{
    int choice;
    pthread_t thread_id; 
    printf("%s","Menu\n");
    printf("%s","1:Read data base.\n");
    printf("%s","2:Save local copy of data base.\n");
    printf("%s","3:Change record in local copy of data base.\n")
    printf("%s","4:Exit\n");
    scanf("%d",choice);
    while (true)
    {
        switch (choice)
        {
        case 1:
            pthread_create(&thread_id, NULL, read_db, NULL); 
            pthread_join(thread_id, NULL); 
            break;
        case 2:
            pthread_create(&thread_id, NULL, save_db, NULL); 
            pthread_join(thread_id, NULL); 
            break;
        case 3:
            pthread_create(&thread_id, NULL, replace_record, NULL); 
            pthread_join(thread_id, NULL); 
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
}
#endif
