#include <iostream>
#include "database.h"

int main(){
	sqlite3* db{nullptr};
	Database test("notesDb.db", db);
	test.database_init();





	return 0;
}
