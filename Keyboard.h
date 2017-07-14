#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
    public:
        static Keyboard &get(void)
        {
            static Keyboard instance;
            return instance;
        }
        static void keyb(unsigned char, bool);
        static bool pressed(unsigned char);
    protected:
        static bool keys[128];
    private:
        Keyboard();
        Keyboard(Keyboard const &);
        void operator=(Keyboard const &);
};

#endif // KEYBOARD_H
