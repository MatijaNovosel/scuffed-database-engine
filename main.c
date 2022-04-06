#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dbListFileName "dbList.dat"
#define bufferLimit 255
#define dbNameCharLimit 255

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

typedef struct
{
  char name[dbNameCharLimit];
  int tableCount;
} DatabaseDefinition;

typedef struct
{
  FILE *dbList;
  void (*createDb)(void *self, char *dbName);
  void (*createTable)(void *self, char *dbName, char *tableName);
  void (*createDbList)();
  int (*dbExists)(void *self, char *dbName);
  void (*openConnection)(void *self);
  void (*closeConnection)(void *self);
} DBEngine;

void createDb(void *self, char *dbName)
{
  DBEngine *this = (DBEngine *)self;

  if (this->dbExists(self, dbName))
  {
    DatabaseDefinition databaseDefinition;
    fread(&databaseDefinition, sizeof(DatabaseDefinition), 1, this->dbList);
    printf("%s", databaseDefinition.name);
  }
  else
  {
    DatabaseDefinition *databaseDefinition = malloc(sizeof(DatabaseDefinition));
    databaseDefinition->tableCount = 1;

    strcpy(databaseDefinition->name, dbName);
    printf("%s\n", databaseDefinition->name);

    fwrite(databaseDefinition, sizeof(databaseDefinition), 1, this->dbList);

    DatabaseDefinition dd;

    rewind(this->dbList);
    fread(&dd, sizeof(DatabaseDefinition), 1, this->dbList);
    printf("%s", dd.name);
  }
}

void createTable(void *self, char *dbName, char *tableName)
{
  // Check if db exists
  // Check if table name exists
  // Create
}

void createDbList()
{
  FILE *fp = fopen(dbListFileName, "wb+");
  fclose(fp);
}

int dbExists(void *self, char *dbName)
{
  DBEngine *this = (DBEngine *)self;
  return 0;
}

void openConnection(void *self)
{
  DBEngine *this = (DBEngine *)self;
  if (!(fileExists(dbListFileName)))
  {
    this->createDbList();
  }
  this->dbList = fopen(dbListFileName, "wb+");
}

void closeConnection(void *self)
{
  DBEngine *this = (DBEngine *)self;
  fclose(this->dbList);
}

DBEngine *ConstructDBEngine()
{
  DBEngine *dbEngine = malloc(sizeof(DBEngine));
  dbEngine->createDb = &createDb;
  dbEngine->createTable = &createTable;
  dbEngine->createDbList = &createDbList;
  dbEngine->dbExists = &dbExists;
  dbEngine->openConnection = &openConnection;
  dbEngine->closeConnection = &closeConnection;
  return dbEngine;
}

void main()
{
  DBEngine *db = ConstructDBEngine();
  db->openConnection(db);
  db->createDb(db, "mainDb");
  db->closeConnection(db);
}