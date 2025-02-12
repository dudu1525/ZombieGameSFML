

#ifndef DBManager_h
#define  DBManager_h
#include "/proiecte/ZombieGame/ZombieGame/sqlite/sqlite3.h"
#include <string>
#include <iostream>

class DatabaseManager {
public:
    
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    // Public Methods
    bool createTable();
    bool insertData(int posx, int posy, int health, int level, int exp);
    void queryData(int v[2]);

    int gethealthdb();


    bool updatePosition(int posX, int posY);  // New method to update player position

    void updateHealthdb(int new_health);


private:
    sqlite3* db; 
    std::string dbName;  

    bool executeQuery(const std::string& query);  
};

#endif 
