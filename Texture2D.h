#ifndef TEXTURE2D_H
#define TEXTURE2D_H

class Texture2D
{
    public:
        Texture2D(const char *);
        ~Texture2D();

        void bind();
    protected:
        const char *fname;
        unsigned int id;

        void die(int);
    private:
};

#endif // TEXTURE2D_H
