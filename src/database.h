#ifndef	_DATABASE_
#define	_DARABASE_

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <string_view>

enum{max_size_table_name = 20};

class Database{
private:
	sqlite3* db{nullptr};
	sqlite3_stmt* stmt{nullptr};
	static int table_count;
public:
	Database(std::string_view db_name, sqlite3* _db);
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;
	sqlite3* get_db();
	int database_init();
	int create_basic_structure_notes();
	//int add_section(const std::string& section_name);
	//int insert_note(const std::string& section_name, const std::string& title_name, const std::string& description);
	int& get_table_count();
	//int find_section_id(const std::string& section_name);
	//bool find_section(const std::string& section_name);
	//std::string find_note();
	bool check_table_exists(const std::string& table_name);
	bool is_valid_table_name(const std::string& name);
	//std::string retrieve_note();
	~Database();
};
#endif
