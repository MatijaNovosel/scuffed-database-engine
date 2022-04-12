#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dbListFileName "dbList.dat"
#define bufferLimit 255
#define dbNameCharLimit 255
#define dbDefinitionListLimit 255

int fileEmpty(FILE *fp)
{
  if (NULL != fp)
  {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    if (size == 0)
    {
      return 1;
    }
    return 0;
  }
}

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
  DatabaseDefinition databases[dbDefinitionListLimit];
  int databaseCount;
} DatabaseDefinitionContainer;

typedef struct
{
  FILE *dbList;
  DatabaseDefinitionContainer *dbContainer;
  void (*createDb)(void *self, char *dbName);
  void (*createTable)(void *self, char *dbName, char *tableName);
  void (*createDbList)();
  void (*applyDbChanges)(void *self);
  int (*dbExists)(void *self, char *dbName);
  void (*openConnection)(void *self);
  void (*closeConnection)(void *self);
} DBEngine;

void createDb(void *self, char *dbName)
{
  DBEngine *this = (DBEngine *)self;

  DatabaseDefinition databaseDefinition;
  databaseDefinition.tableCount = 1;
  strcpy(databaseDefinition.name, dbName);

  this->dbContainer->databases[this->dbContainer->databaseCount] = databaseDefinition;

  this->applyDbChanges(this);
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

  int exists = 0;

  // Make a better algorithm ...
  for (int i = 0; i < this->dbContainer->databaseCount; i++)
  {
    if (!strcmp(this->dbContainer->databases[i].name, dbName))
    {
      exists = 1;
      break;
    }
  }

  return exists;
}

void openConnection(void *self)
{
  DBEngine *this = (DBEngine *)self;
  if (!(fileExists(dbListFileName)))
  {
    this->createDbList();
  }
  this->dbList = fopen(dbListFileName, "wb+");

  if (fileEmpty(this->dbList))
  {
    DatabaseDefinitionContainer *container = malloc(sizeof(DatabaseDefinitionContainer));
    container->databaseCount = 0;
    fwrite(container, sizeof(DatabaseDefinitionContainer), 1, this->dbList);
  }

  DatabaseDefinitionContainer *container = malloc(sizeof(DatabaseDefinitionContainer));
  fread(container, sizeof(DatabaseDefinitionContainer), 1, this->dbList);

  this->dbContainer = container;
}

void closeConnection(void *self)
{
  DBEngine *this = (DBEngine *)self;
  fclose(this->dbList);
}

void applyDbChanges(void *self)
{
  DBEngine *this = (DBEngine *)self;
  // Write to file
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
  dbEngine->applyDbChanges = &applyDbChanges;
  return dbEngine;
}

void main()
{
  DBEngine *db = ConstructDBEngine();
  db->openConnection(db);
  db->createDb(db, "mainDb");
  db->closeConnection(db);
}