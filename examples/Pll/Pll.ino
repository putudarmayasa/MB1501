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

	uint32_t xtal = 10240000;
	uint32_t freq = 108500000;
	uint16_t ref_divider = 1024;

	uint16_t pll_div;
	uint8_t  pll_swallow;

	// freq = ((prescaler * plldivider)+ swallow) * ( xtal / pll_rev_divider)

	pll_div = freq / ((xtal/ref_divider) * 64) ;
  pll_swallow = (freq / (xtal / ref_divider) ) - ( 64 * pll_div) ) ;

	Serial.print("Sending value ref value: ");
	Serial.print(ref_divider, DEC);
	Serial.print(" -- Transfer ref -- ");
	myPLL.transfer_ref(ref_divider,0);
	Serial.print(" -- Transfer End Ref -- ");

	delay(1000);


	Serial.print(" --- Transfer div -- ");
	Serial.print("Sending value div value: ");
	Serial.print(pll_div, DEC);
	Serial.print("Sending value swallow value: ");
	Serial.print(pll_swallow, DEC);


	Serial.print(" ---Transfer div---- ");
	myPLL.transfer_div(pll_div,pll_swallow);
	Serial.print(" Transfer End Div ");



	delay(2000);

}
