#define dbNameCharLimit 255
#define dbDefinitionListLimit 255

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