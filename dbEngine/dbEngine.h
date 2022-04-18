#include "../models/models.h"
#include <stdio.h>

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
  char **(*searchDatabases)(void *self, char *dbName);
} DBEngine;

DBEngine *ConstructDBEngine();
void createDb(void *self, char *dbName);
void createTable(void *self, char *dbName, char *tableName);
void createDbList();
int dbExists(void *self, char *dbName);
void openConnection(void *self);
void closeConnection(void *self);
void applyDbChanges(void *self);
char **searchDatabases(void *self, char *dbName);