#include <Mb1501.h>

//  3 Wire port :
// Pin 2 = DATA,
// Pin 3 = LE,
// Pin 4 = SCK

Mb1501 MyPLL(2, 3, 4);

void setup() {
	MyPLL.begin();
	Serial.begin(9600);
}

void loop() {

	float freq = 108500000;
	uint16_t ref_divider = 1024;

	uint16_t pll_div;
	uint8_t  pll_swallow;

	// freq = ((prescaler * plldivider)+ swallow) * ( xtal / pll_rev_divider)

	pll_div = (freq / 5000) / 64 ;
  pll_swallow = (freq / 5000) - ( 64 * pll_div)  ;


  

	Serial.print("Sending value ref value: ");
	Serial.print(ref_divider, DEC);
  Serial.print("\n");

	MyPLL.transferRef(ref_divider,1);  // 1 : Prescaler 64 , 0 : Prescaler 128
	

	delay(1000);



	Serial.print("Sending value div value: ");
	Serial.print(pll_div, DEC);
	Serial.print(" Sending value swallow value:  ");
	Serial.print(pll_swallow, DEC);
  Serial.print("\n");


	MyPLL.transferDiv(pll_div,pll_swallow);



	delay(2000);
  

}
