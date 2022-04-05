#include <stdio.h>
#include <stdlib.h>

#define dbListFileName "dbList.dat"
#define bufferLimit 255

int fileExists(char *fileName)
{
  FILE *file;
  if ((file = fopen(fileName, "rb")) != NULL)
  {
    fclose(file);
    return 1;
  }
  else
  {
    return 0;
  }
}

typedef struct DatabaseDefinition
{
  char *name;
  char **tableNames;
  int tableCount;
} DatabaseDefinition;

typedef struct DBEngine
{
  void (*createDb)(DBEngine *self, char *dbName);
  void (*createTable)(DBEngine *self, char *dbName, char *tableName);
  int (*isDbListEmpty)();
  void (*createDbList)();
  int (*dbExists)(char *dbName);
} DBEngine;

void createDb(DBEngine *self, char *dbName)
{
  if (self->isDbListEmpty())
  {
    self->createDbList();
  }

  FILE *fp = fopen(dbListFileName, "rb");

  if (!(self->dbExists(dbName)))
  {
    DatabaseDefinition databaseDefinition;
    fread(&databaseDefinition, sizeof(DatabaseDefinition), 1, fp);
    printf("%s", databaseDefinition.name);
  }
  else
  {
    DatabaseDefinition databaseDefinition;
    databaseDefinition.name = dbName;
    databaseDefinition.tableCount = 1;
    databaseDefinition.tableNames = malloc(sizeof(char *));
    databaseDefinition.tableNames[0] = malloc(5 * sizeof(char));
    fwrite(&databaseDefinition, sizeof(databaseDefinition), 1, fp);
  }

  fclose(fp);
}

void createTable(DBEngine *self, char *dbName, char *tableName)
{
  // Check if db exists
  // Check if table name exists
  // Create
}

void createDbList()
{
  FILE *fp = fopen(dbListFileName, "wb");
  fclose(fp);
}

int dbExists(char *dbName)
{
  FILE *fp = fopen(dbListFileName, "wb");
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
  dbEngine.createDbList = &createDbList;
  dbEngine.dbExists = &dbExists;
  return dbEngine;
}

void main()
{
  DBEngine db = ConstructDBEngine();
  db.createDb(&db, "mainDb");
}