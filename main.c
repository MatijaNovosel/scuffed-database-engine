#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./dbEngine/dbEngine.h"

void main()
{
  DBEngine *db = ConstructDBEngine();
  db->openConnection(db);
  db->createDb(db, "mainDb");
  db->closeConnection(db);
}