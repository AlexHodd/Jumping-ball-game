#ifndef ENTITY_H
#define ENTITY_H

#include "ComponentManager.h"
#include "Sprite.h"

class Entity : public Component
{
    public:
        Entity(const Sprite &, float2, float);
        virtual ~Entity();

        virtual void draw();
        virtual void update();

        float2 getPosition() const { return position; }
        void setPosition(const float2 &p) { position = p; }

        template <class EntityType> EntityType* collisionWith(Entity* = NULL);
        float2 collisionSeparate(Entity *e);
    protected:
        Sprite sprite;
        float2 position;
        float orientation;
        float2 velocity;
        float radius;
        int hp;
    private:
};

template <class EntityType> EntityType* Entity::collisionWith(Entity* except)
{
    ComponentManager::find<EntityType>();
    EntityType *r, *t = NULL;
    float maxLen = 0.f;
    while( (r=ComponentManager::next<EntityType>()) != NULL )
    {
        float len = r->radius + radius - (r->position-position).len();
        if ( len>0 && except!=r && len>maxLen)
        {
            maxLen = len;
            t = r;
        }
    }
    return t;
}

#endif // ENTITY_H
