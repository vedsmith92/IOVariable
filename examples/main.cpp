#include <Arduino.h>
#include <IOVariable.h>


void onChange1(int __value) {
	Serial.print("[Callback 1] Value change to: ");
	Serial.println(__value);
}

void onChange2(int __value) {
	Serial.print("[Callback 2] Value change to: ");
	Serial.println(__value);
}

IOVariable<int> v(0);

int i = 0;


void setup() {

	Serial.begin(9600);

	v.onChange(&onChange1);
	v.onChange(&onChange2);

	Serial.print("Initialize value: ");
	Serial.println(v.get());

	Serial.print("Get value(0): ");
	Serial.println(v.get());

	v.set(-1);
	
	Serial.print("Get value(-1): ");
	Serial.println(v.get());

	v.set(-2);
	
	Serial.print("Get value(-2): ");
	Serial.println(v.get());

}


void loop() {
	i++;
	v.set(i);
	delay(1000);
}