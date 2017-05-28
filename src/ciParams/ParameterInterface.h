#pragma once

#include "cinder/app/App.h"


namespace params {
    template<class T>
    class ParameterInterface {
        public:
            
            ParameterInterface() : pParam(NULL){}
            ParameterInterface(T& param) : pParam(&param){}
            
            const T& get() const { return *pParam; }

            void set(const T& newValue){
                T previousValue = *pParam;
                
                *pParam = newValue;
                
                if(previousValue != newValue){
                    onChange.emit(newValue);
                }
            }

            const T* getVar() const { return pParam; }
            void setVar(T& param){ pParam = &param; }

        public:
            ci::signals::Signal<void(const T&)> onChange;
        
        private:
            T* pParam;
        
    };
}

