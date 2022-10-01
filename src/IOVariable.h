#ifndef _IOVariable_h
#define _IOVariable_h

#include <LinkedList.h>


#if defined(ESP8266) || defined(ESP32)
#include <functional>
#define IOVAR_CALLBACK_SIGNATURE std::function<void(T)>
#define IOVAR_ONCHANGE_SIGNATURE std::function<void(T)> __func
#else
#define IOVAR_CALLBACK_SIGNATURE void (*)(T)
#define IOVAR_ONCHANGE_SIGNATURE void (*__func)(T __value)
#endif


template <typename T>
class IOVariable {
	public:
		IOVariable();
		IOVariable(T initializeValue, bool __callbackSameValue = false);
		T get();
		void set(T __value);
		void forceSet(T __value);
		void onChange(IOVAR_ONCHANGE_SIGNATURE);
	private:
		T value;
		bool callbackSameValue;
		LinkedList<IOVAR_CALLBACK_SIGNATURE> callbacks;
};


template <typename T>
IOVariable<T>::IOVariable() {
	value = (T)0;
}

template <typename T>
IOVariable<T>::IOVariable(T initializeValue, bool __callbackSameValue) {
	value = initializeValue;
	callbackSameValue = __callbackSameValue;
}

template <typename T>
T IOVariable<T>::get() {
	return (T)value;
}

template <typename T>
void IOVariable<T>::set(T __value) {

	if(!callbackSameValue) {
		if(value == __value) {
			return;
		}
	}

	value = __value;

	for( int i=0 ; i<callbacks.size(); i ++) {
		callbacks.get(i)(value);
	}
}

template <typename T>
void IOVariable<T>::forceSet(T __value) {

	value = __value;

	for( int i=0 ; i<callbacks.size(); i ++) {
		callbacks.get(i)(value);
	}
}

template <typename T>
void IOVariable<T>::onChange(IOVAR_ONCHANGE_SIGNATURE) {
	callbacks.add(__func);
}


#endif