#include <stdlib.h>

struct DataBase{
    char record[150][30];
};

void *read_db(void);
void *save_db(void);
void* replace_record(void);
void database_menu(void);
