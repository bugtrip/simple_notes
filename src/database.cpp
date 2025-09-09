#include "database.h"
#include <format>

int Database::table_count{0};

Database::Database(std::string_view db_name, sqlite3* _db){
	db = _db;
	int check_open = sqlite3_open(db_name.data(), &db);
	if(check_open != SQLITE_OK){
		std::cerr << sqlite3_errmsg(db) << std::endl;
	}
}

Database::~Database(){
	sqlite3_close(db);
}

int Database::database_init(){
	int check_create{-1};
	std::string table_name{"notes"};
	if(!check_table_exists(table_name)){
		check_create = create_basic_structure_notes();
	}

	return check_create;
}

bool Database::check_table_exists(const std::string& table_name){
	if(!is_valid_table_name(table_name)){ return false; }
	
	std::string table_exists{"select name from sqlite_master where type = 'table' and name =?1;"};
	sqlite3_stmt* stmt{nullptr};
	
	if(sqlite3_prepare_v2(db, table_exists.c_str(), -1, &stmt, nullptr) != SQLITE_OK) { 
		std::cerr << sqlite3_errmsg(db) << std::endl;
		return false; 
	}
	
	if(sqlite3_bind_text(stmt, 1, table_name.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK){
		std::cerr << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt); 
		return false; 
	}
	
	int check_step = sqlite3_step(stmt);
	if(check_step == SQLITE_ROW){
		sqlite3_finalize(stmt);
		return true;
	}
	//std::cerr << sqlite3_errmsg(db) << std::endl;
	sqlite3_finalize(stmt);
	
	return false;
}

int Database::create_basic_structure_notes(){
	char* err{0};
	//int check_create_notes{};
	//int check_create_others{};
	//int check_insert{};
	if(db != nullptr){
		const std::string create_table_notes{"create table if not exists notes(id integer primary key not null, name varchar check(length(name) <= 50), description varchar check(length(description) <= 50));"};
		sqlite3_exec(db, create_table_notes.c_str(), 0, 0, &err);
		++table_count;
		
		const std::string create_table_others{"create table if not exists others(others_id integer primary key not null, notes_id integer not null, title_note varchar check(length(title_note) <= 50), description varchar check(length(description) <= 3072), foreign key (notes_id) references notes(id))"};
		sqlite3_exec(db, create_table_others.c_str(), 0, 0, &err);
		++table_count;
		
		const std::string insert = std::format("insert into notes(name, description) values('others', 'Notes without sections');");
		sqlite3_exec(db, insert.c_str(), 0, 0, &err);
	}

	return 0;
}

bool Database::is_valid_table_name(const std::string& name){
	if(name.size() > max_size_table_name){ return false; }
	if(name.find(' ') != std::string::npos){ return false; }

	return true;
}
int& Database::get_table_count(){ return table_count; }
