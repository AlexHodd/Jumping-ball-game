#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <map>

using std::map;

#include "Texture2D.h"

class ResourceFactory
{
    public:
        static ResourceFactory &get(void)
        {
            static ResourceFactory instance;
            return instance;
        }
        static Texture2D* load(const char *);
    protected:
        map<const char*, Texture2D*> textures;
        virtual ~ResourceFactory();
    private:
        ResourceFactory();
        ResourceFactory(ResourceFactory const &);
        void operator=(ResourceFactory const &);
};

#endif // RESOURCEFACTORY_H
