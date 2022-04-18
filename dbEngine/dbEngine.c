#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "./models/models.h"
#include "dbEngine.h"

#define dbListFileName "dbList.dat"
#define bufferLimit 255

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
  fwrite(this->dbContainer, sizeof(DatabaseDefinitionContainer), 1, this->dbList);
}

char **searchDatabases(void *self, char *dbName)
{
  char **res = NULL;
  if (dbName == NULL)
  {
    // Get all
  }
  else
  {
    // Find specific ones
  }
  return res;
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
  dbEngine->searchDatabases = &searchDatabases;
  return dbEngine;
}

void main()
{
  DBEngine *db = ConstructDBEngine();
  db->openConnection(db);
  db->createDb(db, "mainDb");
  db->closeConnection(db);
}