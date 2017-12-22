
#ifndef SMARTPTR_H
#define SMARTPTR_H

template <typename T>
class SmartPtr
{   
    public:
        SmartPtr( T *p) : mPtr(p) {}

        ~SmartPtr()
        {
            delete mPtr;
        }

        T *operator ->()
        {
            return mPtr;
        }

    private:
    T *mPtr;
};

#endif