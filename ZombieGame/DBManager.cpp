

#include "../include/DBManager.h"

// Constructor - Open the database
DatabaseManager::DatabaseManager(const std::string& dbName) : db(nullptr), dbName(dbName) {
    int exit = sqlite3_open(dbName.c_str(), &db);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
    else {
        std::cout << "Database opened successfully!" << std::endl;
    }
}

// Destructor - Close the database
DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Database closed successfully!" << std::endl;
    }
}

// Create a table
bool DatabaseManager::createTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS players ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "NAME TEXT NOT NULL, "
        "SCORE INT NOT NULL);";

    return executeQuery(sql);
}

// Insert data into the table
bool DatabaseManager::insertData(const std::string& name, int score) {
    std::string sql = "INSERT INTO players (NAME, SCORE) VALUES ('" + name + "', " + std::to_string(score) + ");";

    return executeQuery(sql);
}

// Query data from the table
void DatabaseManager::queryData() {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM players;";

    int exit = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (exit == SQLITE_OK) {
        std::cout << "Querying data..." << std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int score = sqlite3_column_int(stmt, 2);

            std::cout << "ID: " << id << ", Name: " << name << ", Score: " << score << std::endl;
        }
    }
    else {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Internal method to execute a SQL command (CREATE, INSERT, etc.)
bool DatabaseManager::executeQuery(const std::string& query) {
    char* errMsg;
    int exit = sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg);

    if (exit != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}
