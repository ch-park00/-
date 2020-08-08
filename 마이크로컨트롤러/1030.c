/*
   ���ͷ�Ʈ 
  ���α׷� ���� �߿� CPU �� ���� ó�� ������ �ߴܽ�Ű�� �ٸ� ������ �����ϵ��� �ϴ� ��

  AVR ������ ���ͷ�Ʈ ó��

  1. ����� ���ͷ�Ʈ ���(����)
  2. ���ͷ�Ʈ ��� ����
  3. �ش� ���ͷ�Ʈ�� ISR �ڵ�(CPU�� call ����)
  4. Global Interrupt Enalbe


  CPU INT0/INT1 > ���ͷ�Ʈ �޴� ��

  INT1 
  ISC10,11 �� control

  ISR(INT0_vect)  //  �ܺ����ͷ�Ʈ 0���� ISR
  {				  //  
  cli();
  EIFR |=0x01;
  sei();
  }
*/


#include<avr/interrupt.h>

#include<avr/io.h>			// �⺻
#define F_CPU 16000000UL	// ������ ���� ����
#include<util/delay.h>



unsigned char seg_tbl16[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
unsigned char seg_tblD[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
void disp_seg (int in);
void LED_shift_dec(int num);


int main()
{

	DDRD = 0xF3;
	DDRB = 0xFF;
	DDRC = 0xFF;
	PORTC = 0xFF;

	unsigned char inc;
	unsigned char shift;
	int num = 0x00;

	while(1){						// ���� ���(��� Ȯ��), main �� Ŀ����(���).

		inc = ((PIND & 0X04)>>2);
		shift = ((PIND & 0X08)>>3);		
		num = num + inc;
		
		while(PIND & 0X04){
			if(num==16){
				num = 0x00;
			}
		}
		if(shift == 0X01){
			if(num != 0){
				LED_shift_dec(num);
				num = 0;
			}
		}
		disp_seg(num);
		_delay_ms(100);
	}
}


void disp_seg (int in)
{
	PORTD = (seg_tblD[in]<<4);
	PORTB = (seg_tblD[in]>>4 | 0XF0);
}

void LED_shift_dec(int num)
{
	int max = num;
	for(int i = 0 ; i < max ; i++){
		for(int j = 0 ; j < 8 ; j++){
			PORTD = (seg_tblD[num]<<4);
			PORTB = ~(0x01<<j)<<4 | (seg_tblD[num] >> 4);
			PORTC = ~(0x01<<j)>>2;
			_delay_ms(50);
		}
		for(int j = 0 ; j < 8 ; j++){
			PORTD = (seg_tblD[num]<<4);
			PORTB = ~(0x80>>j)<<4 | (seg_tblD[num] >> 4);
			PORTC = ~(0x80>>j)>>2;
			_delay_ms(50);
		}
		num--;
	}
}
