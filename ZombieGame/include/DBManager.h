#ifndef DBManager_h
#define  DBManager_h

#include <string>
#include <iostream>
#include "sqlite3.h"

class DatabaseManager {
public:
    
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

 
    bool createTable();
    bool insertData(int posx, int posy, int health, int level, int exp);
    void queryData(int v[2]);

    int gethealthdb();


    bool updatePosition(int posX, int posY);  

    void updateHealthdb(int new_health);


private:
    sqlite3* db; 
    std::string dbName;  

    bool executeQuery(const std::string& query);  
};

#endif 
