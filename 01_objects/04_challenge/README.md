```cpp

#include <iostream>
#include <string>
#include <vector>

class Person {
public:
    Person(const std::string& name) : name(name) {}

    std::string get_name() const {
        return name;
    }

private:
    std::string name;
};

class Team {
public:
    void add_member(const Person& member) {
        members.push_back(member);
    }

    void print_members() const {
        for (const Person& member : members) {
            std::cout << member.get_name() << std::endl;
        }
    }

private:
    std::vector<Person> members;
};

class Project {
public:
    Project() : team() {}

    void add_team_member(const Person& member) {
        team.add_member(member);
    }

    void print_team_members() const {
        team.print_members();
    }

private:
    Team team;
};

int main() {
    Project project;
    project.add_team_member(Person("Alice"));
    project.add_team_member(Person("Bob"));
    project.add_team_member(Person("Charlie"));

    std::cout << "Project team members:" << std::endl;
    project.print_team_members();

    return 0;
}

```