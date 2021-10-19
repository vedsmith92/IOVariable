# IOVariable

Lightweight callbackable variable for Arduino, ESPx


# Example

```cpp
#include <IOVariable.h>

void onChange(int __value) {
	Serial.print("Value change to: ");
	Serial.println(__value);
}

IOVariable<int> v(0);
int i = 0;

void setup() {
	Serial.begin(9600);
	v.onChange(&onChange);
}

void loop() {
	i++;
	v.set(i);
	delay(1000);
}
```