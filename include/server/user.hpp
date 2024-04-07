#ifndef USER_H
#define USER_H

#include <string>
enum STATE {
    online,
    offline
};
class User{
public:
    User(int id = -1, std::string name = "", std::string password = " ", std::string state = "offline");

    void setid(int id);
    void setName(std::string name);
    void setPassword(std::string password);
    void setState(std::string state);

    int getId();
    std::string getName();
    std::string getPassword();
    std::string getState();
private:
    int id;
    std::string name;
    std::string password;
    std::string state;
};

#endif