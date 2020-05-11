#include <iostream>
#include <string>

class Entity
{
private:
    int x;
public:
    void Print() const {
        std::cout << "Hello!" << std::endl;
    }
};

class ScopedPtr
{
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity* entity)
        : m_Obj(entity) {}
    
    ~ScopedPtr()
    {
        delete m_Obj;
    }

    const Entity* operator->() const 
    {
        return m_Obj;
    }
};

struct Vector3
{
    float x, y, z;
};

int main(int argc, char const *argv[])
{
    ScopedPtr entity = new Entity();
    entity->Print();

    int xoffset = (int)&(((Vector3*)nullptr)->x);
    std::cout << xoffset << std::endl;
    std::cout << (int)&((Vector3*)nullptr)->y << std::endl;
    std::cout << (int)&((Vector3*)nullptr)->z << std::endl;

    return 0;
}
