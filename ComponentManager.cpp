#include "ComponentManager.h"

void ComponentManager::add(Component* e)
{
//    cout<<"ComponentManager::add( "<<typeid(*e).name()<<" )"<<endl;
    get().components.push_front(e);
}

void ComponentManager::update()
{
    for (list<Component*>::iterator i = get().components.begin();
        i != get().components.end(); ++i)
            if ((*i)->active)
                (*i)->update();
    for (list<Component*>::iterator i = get().components.begin();
        i != get().components.end();)
            if ( (*i)->deleted )
            {
                delete *i;
                i=get().components.erase(i);
            }
            else
                ++i;
}

void ComponentManager::draw()
{
    for (list<Component*>::reverse_iterator i = get().components.rbegin();
        i != get().components.rend(); ++i)
        if ((*i)->visible)
            (*i)->draw();
}

void ComponentManager::clear()
{
    for (list<Component*>::iterator i = get().components.begin();
        i != get().components.end(); ++i)
            delete *i;
    get().components.clear();
}
