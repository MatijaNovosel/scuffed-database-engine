#include <stdio.h>
#include <memory.h>

#define dbListFileName "dbList.txt"

int fileExists(char *fileName)
{
  FILE *file;
  if ((file = fopen(fileName, "r")) != NULL)
  {
    fclose(file);
    return 1;
  }
  else
  {
    return 0;
  }
}

typedef struct DBEngine
{
  void (*createDb)(DBEngine *self, char *dbName);
  void (*createTable)(DBEngine *self, char *dbName, char *tableName);
  int (*isDbListEmpty)();
  void (*createDbList)();
} DBEngine;

void createDb(DBEngine *self, char *dbName)
{
  if (self->isDbListEmpty())
  {
    self->createDbList();
  }
  else
  {
    //
  }
}

void createTable(DBEngine *self, char *dbName, char *tableName)
{
  // Check if db exists
  // Check if table name exists
  // Create
}

void createDbList()
{
  FILE *fp;
  fp = fopen(dbListFileName, "w");
  fclose(fp);
}

int isDbListEmpty()
{
  if (fileExists(dbListFileName))
  {
    printf("File exists!");
  }
  else
  {
    return 0;
  }
}

DBEngine ConstructDBEngine()
{
  DBEngine dbEngine;
  dbEngine.createDb = &createDb;
  dbEngine.isDbListEmpty = &isDbListEmpty;
  dbEngine.createTable = &createTable;
  return dbEngine;
}

void main()
{
  DBEngine db = ConstructDBEngine();
  db.createDb(&db, "mainDb");
  db.isDbListEmpty();
}