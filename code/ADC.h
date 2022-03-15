/*
 * ADC.h
 *
 * Created: 14-03-2022 21:49:08
 *  Author: kunal Avghade
 */ 


#ifndef ADC_H_
#define ADC_H_

void acd_init()
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADSC);
}

unsigned int analogRead(uint8_t channel)
{
	ADMUX &= 0xF0;
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA & (1<<ADIF)) == 0);
	return ADCW;
}

unsigned int getMoisture(uint8_t channel)
{
	return (100-(analogRead(channel)*100.00)/1023.00);
}

unsigned int getTemp(uint8_t channel)
{
 return ((analogRead(channel)*4.88)/10.00);
}

#endif /* ADC_H_ */