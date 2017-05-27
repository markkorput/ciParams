#include "cinder/app/App.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace params {
    template<class T>
    class ParameterInterface {
    public:
        ParameterInterface() : pParam(NULL){}
        ParameterInterface(T& param) : pParam(&param){}
        
        const T& get() const { return *pParam; }
        void set(const T& newValue){ *pParam = newValue; }

        const T* getParameter() const { return pParam; }
        void setParameter(T& param){ pParam = &param; }
    private:
        T* pParam;
    };
}

