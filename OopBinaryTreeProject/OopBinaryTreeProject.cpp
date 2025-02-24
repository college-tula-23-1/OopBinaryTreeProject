#include <iostream>
#include <string>
#include "BinaryTree.h"

class User
{
    std::string name;
    int age;
public:
    User(std::string name, int age)
        : name{ name }, age{ age } {}
    User() : User("", 0) {}

    std::string& Name() { return name; }
    int& Age() { return age; }

    std::string ToString()
    {
        return "Name: " + name
            + ", Age: " + std::to_string(age);
    }

    friend std::ostream& operator<<(std::ostream& out, const User& user)
    {
        out << "Name: " << user.name << ", Age: " << user.age;
        return out;
    }
};

class UserAgeComparator : public IComparator<User>
{
public:
    int Compare(User user1, User user2) override
    {
        return user1.Age() - user2.Age();
    }

    int operator()(User user1, User user2) override
    {
        return user1.Age() - user2.Age();
    }
};

class UserNameComparator : public IComparator<User>
{
public:
    int Compare(User user1, User user2) override
    {
        return user1.Name().compare(user2.Name());
    }

    int operator()(User user1, User user2) override
    {
        return user1.Name().compare(user2.Name());
    }
};








int main()
{
    BinaryTree<User> tree(new UserNameComparator());

    tree.InsertReq(*(new User("Sammy", 29)));
    tree.InsertLoop(*(new User("Tommy", 19)));
    tree.InsertReq(*(new User("Jimmy", 25)));
    tree.InsertLoop(*(new User("Bobby", 30)));
    tree.Print();


}
