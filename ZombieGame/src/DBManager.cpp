

#include "../include/DBManager.h"

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

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Database closed successfully!" << std::endl;
    }
}

// Create a table
bool DatabaseManager::createTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS player ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "POSX INT NOT NULL, "
        "POSY INT NOT NULL, "
        "HEALTH INT NOT NULL,"
        "LEVEL INT NOT NULL,"
        "EXP INT NOT NULL);";

    return executeQuery(sql);
}

// Insert data into the table
bool DatabaseManager::insertData(int posx, int posy,int health,int level,int exp) {
    std::string sql = "INSERT INTO player (POSX, POSY, HEALTH, LEVEL, EXP) VALUES ("
        + std::to_string(posx) + ", "
        + std::to_string(posy) + ", "
        + std::to_string(health) + ", "
        + std::to_string(level) + ", "
        + std::to_string(exp) + ");";

    return executeQuery(sql);
}

// Query data from the table
void DatabaseManager::queryData(int v[2]) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM player;";

    int exit = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (exit == SQLITE_OK) {
        std::cout << "Querying data..." << std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            float posx= sqlite3_column_int(stmt, 1);
            float posy = sqlite3_column_int(stmt, 2);
            v[0] = posx;
            v[1] = posy;
            std::cout << "ID: " << id << ", Name: " << posx << ", Score: " << posy << std::endl;
        }
    }
    else {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

int DatabaseManager::gethealthdb()
{
    int health=0;
    sqlite3_stmt* stmt;
    std::string query = "SELECT HEALTH  FROM player;";
    int exit = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (exit == SQLITE_OK) {
        std::cout << "Querying data..." << std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
             health = sqlite3_column_int(stmt, 0);
            
        }
    }
    else {
        std::cerr << "Failed to execute query health: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return health;
}

bool DatabaseManager::updatePosition(int posX, int posY)
{
    std::string sql = "UPDATE player SET POSX = " + std::to_string(posX) +
        ", POSY = " + std::to_string(posY) + ";";

    // Execute the query
    return executeQuery(sql);
    return false;
}
void DatabaseManager::updateHealthdb(int new_health)
{
    std::string sql = "UPDATE player SET HEALTH = " + std::to_string(new_health) + ";";
    
  executeQuery(sql);
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
