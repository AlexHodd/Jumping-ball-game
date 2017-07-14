#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <iostream>
#include <list>

using std::list;

class Component
{
    public:
        Component(): deleted(false), active(true), visible(true) {}
        virtual ~Component () {}
        virtual void draw() = 0;
        virtual void update() = 0;
        bool isDeleted() { return deleted; }
        bool isActive() { return active; }
        bool isVisible() { return visible; }
        virtual void kill() { deleted = true; }
        void activate() { active=true; }
        void deactivate() { active=false; }
        void show() { visible=true; }
        void hide() { visible=false; }
    protected:
        bool deleted:1, active:1, visible:1;
    friend class ComponentManager;
};

class ComponentManager
{
    public:
        static void add(Component*);
        template <class ComponentType> static void find();
        template <class ComponentType> static ComponentType* next();
        template <class ComponentType> static int count();
        static void update();
        static void draw();
        static void clear();
    protected:
        list<Component*> components;
        list<Component*>::iterator foundIter;
    private:
        static ComponentManager &get(void)
        {
            static ComponentManager instance;
            return instance;
        }
        ComponentManager() { };
        ComponentManager(ComponentManager const &);
        void operator=(ComponentManager const &);
        ~ComponentManager() { clear(); }
};

template <class ComponentType> void ComponentManager::find()
{
    get().foundIter = get().components.begin();
}

template <class ComponentType> ComponentType* ComponentManager::next()
{
    while ( get().foundIter != get().components.end() )
    {
        ComponentType *et=dynamic_cast<ComponentType*>(*get().foundIter);
        ++get().foundIter;
        if (et != NULL)
            return et;
    }
    return NULL;
}

template <class ComponentType> int ComponentManager::count()
{
    int idx = 0;
    for (list<Component*>::iterator i = get().components.begin(); i != get().components.end(); ++i)
        if ( dynamic_cast<ComponentType*>(*i) != NULL )
            ++idx;
    return idx;
}

#endif // COMPONENTMANAGER_H
