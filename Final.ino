/* Reference:1.  https://blog.csdn.net/HouQi02/article/details/51712994
2.  https://zhuanlan.zhihu.com/p/65250414
3.  https://www.arducam.com/wp-content/uploads/2019/11/Arducam_ov7670_cmos_camera_module_revc_ds.pdf
4.  https://www.instructables.com/OV7670-Arduino-Camera-Sensor-Module-Framecapture-T/
*/
#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <Wire.h> 
#define OV7670_ADDRESS    0x21
#define VSYNC      2
#define D0         3
#define D1         4
#define D2         5
#define D3         6
#define D4         7
#define D5         8
#define D6         9
#define D7         10
#define RESET      12

#define FIFO_WRST  11
#define FIFO_WR    A2
#define FIFO_RRST  A3
#define FIFO_RCK   A0
#define FIFO_OE    A1


unsigned char WrCmos7670(unsigned char regID, unsigned char regDat);
unsigned char rdCmos7670Reg(unsigned char regID);
unsigned char Cmos7670_init(void);
void set_Cmos7670reg(void);
unsigned char ov7670_data(void);
void IO_Init(void);

unsigned char tmp;
uint16_t Vsync_Flag,i,j;
unsigned char t1,t2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(256000);
  Wire.begin();
  
  IO_Init();
  
  digitalWrite(RESET, LOW);
  delay(20);
  digitalWrite(RESET, HIGH);
  while(1!=Cmos7670_init());   
  tmp = rdCmos7670Reg(0x3A);
  if(tmp == 0x04)
  {
    }
    else
    {
      while(1);
      }
  attachInterrupt(digitalPinToInterrupt(VSYNC), OV7670, FALLING);
}

void loop() {
  

}

void IO_Init(void)
{
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  pinMode(RESET, OUTPUT);
  
  pinMode(FIFO_WRST, OUTPUT);
  pinMode(FIFO_WR, OUTPUT);
  pinMode(FIFO_RRST, OUTPUT);
  pinMode(FIFO_RCK, OUTPUT);
  pinMode(FIFO_OE, OUTPUT);

  pinMode(VSYNC, INPUT_PULLUP);
}

unsigned char WrCmos7670(unsigned char regID, unsigned char regDat)
{
  Wire.beginTransmission(OV7670_ADDRESS); 
  Wire.write(regID);
  Wire.write(regDat);
  Wire.endTransmission(); 
  return(1);
}   

unsigned char rdCmos7670Reg(unsigned char regID)
{
  unsigned char regDat;
  Wire.beginTransmission(OV7670_ADDRESS); 
  Wire.write(regID);
  Wire.endTransmission(); 
  Wire.requestFrom(OV7670_ADDRESS, 1);
  regDat = Wire.read();
  return regDat;
}

unsigned char Cmos7670_init(void)
{
  unsigned char mmm;  
  
  mmm=0x80;
  if(0==WrCmos7670(0x12, mmm)) 
  {
    return 0 ;
  }
  delay(10);

  set_Cmos7670reg();

  return 1; 
} 

void set_Cmos7670reg(void)  
{    
  WrCmos7670(0x3a, 0x04);
  WrCmos7670(0x40, 0xd0);
  WrCmos7670(0x12, 0x14);
  WrCmos7670(0x32, 0x80);
  WrCmos7670(0x17, 0x16);
  WrCmos7670(0x18, 0x04);
  WrCmos7670(0x19, 0x02);
  WrCmos7670(0x1a, 0x7b);
  WrCmos7670(0x03, 0x06);
  WrCmos7670(0x0c, 0x00);
  WrCmos7670(0x3e, 0x00);
  WrCmos7670(0x70, 0x3a);
  WrCmos7670(0x71, 0x35);  
  WrCmos7670(0x72, 0x11);
  WrCmos7670(0x73, 0x00);
  WrCmos7670(0xa2, 0x02);
  WrCmos7670(0x11, 0x81);
  
  WrCmos7670(0x7a, 0x20);
  WrCmos7670(0x7b, 0x1c);
  WrCmos7670(0x7c, 0x28);
  WrCmos7670(0x7d, 0x3c);
  WrCmos7670(0x7e, 0x55);
  WrCmos7670(0x7f, 0x68);
  WrCmos7670(0x80, 0x76);
  WrCmos7670(0x81, 0x80);
  WrCmos7670(0x82, 0x88);
  WrCmos7670(0x83, 0x8f);
  WrCmos7670(0x84, 0x96);
  WrCmos7670(0x85, 0xa3);
  WrCmos7670(0x86, 0xaf);
  WrCmos7670(0x87, 0xc4);
  WrCmos7670(0x88, 0xd7);
  WrCmos7670(0x89, 0xe8);
  
  WrCmos7670(0x13, 0xe0);
  WrCmos7670(0x00, 0x00);
  
  WrCmos7670(0x10, 0x00);
  WrCmos7670(0x0d, 0x00);
  WrCmos7670(0x14, 0x28);
  WrCmos7670(0xa5, 0x05);
  WrCmos7670(0xab, 0x07);
  WrCmos7670(0x24, 0x75);
  WrCmos7670(0x25, 0x63);
  WrCmos7670(0x26, 0xA5);
  WrCmos7670(0x9f, 0x78);
  WrCmos7670(0xa0, 0x68);
  WrCmos7670(0xa1, 0x03);
  WrCmos7670(0xa6, 0xdf);
  WrCmos7670(0xa7, 0xdf);
  WrCmos7670(0xa8, 0xf0);
  WrCmos7670(0xa9, 0x90);
  WrCmos7670(0xaa, 0x94);
  WrCmos7670(0x13, 0xe5);

  WrCmos7670(0x0e, 0x61);
  WrCmos7670(0x0f, 0x4b);
  WrCmos7670(0x16, 0x02);
  WrCmos7670(0x1e, 0x37);
  WrCmos7670(0x21, 0x02);
  WrCmos7670(0x22, 0x91);
  WrCmos7670(0x29, 0x07);
  WrCmos7670(0x33, 0x0b);
  WrCmos7670(0x35, 0x0b);
  WrCmos7670(0x37, 0x1d);
  WrCmos7670(0x38, 0x71);
  WrCmos7670(0x39, 0x2a);
  WrCmos7670(0x3c, 0x78);
  WrCmos7670(0x4d, 0x40);
  WrCmos7670(0x4e, 0x20);
  WrCmos7670(0x69, 0x00);
  WrCmos7670(0x6b, 0x60);
  WrCmos7670(0x74, 0x19);
  WrCmos7670(0x8d, 0x4f);
  WrCmos7670(0x8e, 0x00);
  WrCmos7670(0x8f, 0x00);
  WrCmos7670(0x90, 0x00);
  WrCmos7670(0x91, 0x00);
  WrCmos7670(0x92, 0x00);
  WrCmos7670(0x96, 0x00);
  WrCmos7670(0x9a, 0x80);
  WrCmos7670(0xb0, 0x84);
  WrCmos7670(0xb1, 0x0c);
  WrCmos7670(0xb2, 0x0e);
  WrCmos7670(0xb3, 0x82);
  WrCmos7670(0xb8, 0x0a);



  WrCmos7670(0x43, 0x14);
  WrCmos7670(0x44, 0xf0);
  WrCmos7670(0x45, 0x34);
  WrCmos7670(0x46, 0x58);
  WrCmos7670(0x47, 0x28);
  WrCmos7670(0x48, 0x3a);
  WrCmos7670(0x59, 0x88);
  WrCmos7670(0x5a, 0x88);
  WrCmos7670(0x5b, 0x44);
  WrCmos7670(0x5c, 0x67);
  WrCmos7670(0x5d, 0x49);
  WrCmos7670(0x5e, 0x0e);
  WrCmos7670(0x64, 0x04);
  WrCmos7670(0x65, 0x20);
  WrCmos7670(0x66, 0x05);
  WrCmos7670(0x94, 0x04);
  WrCmos7670(0x95, 0x08);
  WrCmos7670(0x6c, 0x0a);
  WrCmos7670(0x6d, 0x55);
  WrCmos7670(0x6e, 0x11);
  WrCmos7670(0x6f, 0x9f);
  WrCmos7670(0x6a, 0x40);
  WrCmos7670(0x01, 0x40);
  WrCmos7670(0x02, 0x40);
  WrCmos7670(0x13, 0xe7);
  WrCmos7670(0x15, 0x00);  
  
  
  WrCmos7670(0x4f, 0x80);
  WrCmos7670(0x50, 0x80);
  WrCmos7670(0x51, 0x00);
  WrCmos7670(0x52, 0x22);
  WrCmos7670(0x53, 0x5e);
  WrCmos7670(0x54, 0x80);
  WrCmos7670(0x58, 0x9e);
  
  WrCmos7670(0x41, 0x08);
  WrCmos7670(0x3f, 0x00);
  WrCmos7670(0x75, 0x05);
  WrCmos7670(0x76, 0xe1);
  WrCmos7670(0x4c, 0x00);
  WrCmos7670(0x77, 0x01);
  WrCmos7670(0x3d, 0xc2); 
  WrCmos7670(0x4b, 0x09);
  WrCmos7670(0xc9, 0x60);
  WrCmos7670(0x41, 0x38);
  WrCmos7670(0x56, 0x40);
  
  WrCmos7670(0x34, 0x11);
  WrCmos7670(0x3b, 0x02); 
                
  WrCmos7670(0xa4, 0x89);
  WrCmos7670(0x96, 0x00);
  WrCmos7670(0x97, 0x30);
  WrCmos7670(0x98, 0x20);
  WrCmos7670(0x99, 0x30);
  WrCmos7670(0x9a, 0x84);
  WrCmos7670(0x9b, 0x29);
  WrCmos7670(0x9c, 0x03);
  WrCmos7670(0x9d, 0x4c);
  WrCmos7670(0x9e, 0x3f);
  WrCmos7670(0x78, 0x04);
  
  WrCmos7670(0x79, 0x01);
  WrCmos7670(0xc8, 0xf0);
  WrCmos7670(0x79, 0x0f);
  WrCmos7670(0xc8, 0x00);
  WrCmos7670(0x79, 0x10);
  WrCmos7670(0xc8, 0x7e);
  WrCmos7670(0x79, 0x0a);
  WrCmos7670(0xc8, 0x80);
  WrCmos7670(0x79, 0x0b);
  WrCmos7670(0xc8, 0x01);
  WrCmos7670(0x79, 0x0c);
  WrCmos7670(0xc8, 0x0f);
  WrCmos7670(0x79, 0x0d);
  WrCmos7670(0xc8, 0x20);
  WrCmos7670(0x79, 0x09);
  WrCmos7670(0xc8, 0x80);
  WrCmos7670(0x79, 0x02);
  WrCmos7670(0xc8, 0xc0);
  WrCmos7670(0x79, 0x03);
  WrCmos7670(0xc8, 0x40);
  WrCmos7670(0x79, 0x05);
  WrCmos7670(0xc8, 0x30);
  WrCmos7670(0x79, 0x26); 
  WrCmos7670(0x09, 0x00);  
}

void OV7670(void)
{
  uint16_t cnt;
  detachInterrupt(digitalPinToInterrupt(VSYNC)); 
        
  Vsync_Flag++;
  if(Vsync_Flag==1)    
  {
    digitalWrite(FIFO_WRST, HIGH);
    digitalWrite(FIFO_WRST, LOW);
    for(i=0;i<100;i++);
    digitalWrite(FIFO_WRST, HIGH); 
    digitalWrite(FIFO_WR, HIGH);    
    
  }
  if(Vsync_Flag==2)
  {
    
    digitalWrite(FIFO_WR, LOW);
    detachInterrupt(digitalPinToInterrupt(VSYNC));
    //EXTI->EMR&=~(1<<4);


    digitalWrite(FIFO_RRST, LOW);
    digitalWrite(FIFO_RCK, LOW);             
    digitalWrite(FIFO_RCK, HIGH);
    digitalWrite(FIFO_RCK, LOW);
    digitalWrite(FIFO_RCK, HIGH);
    digitalWrite(FIFO_RRST, HIGH);

    digitalWrite(FIFO_OE, LOW);
    Serial.write(0x01);
    Serial.write(0xFE);
    for(i = 0; i < 9600; i ++)  
     {  
      for(j = 0; j < 8; j ++)
      {                   
        digitalWrite(FIFO_RCK, LOW);   
        digitalWrite(FIFO_RCK, HIGH);          
        t1 = ov7670_data();       
        digitalWrite(FIFO_RCK, LOW);          
        digitalWrite(FIFO_RCK, HIGH);          
        t2 = ov7670_data();  
        Serial.write(t2); 
        Serial.write(t1);                         
      }
    }
    digitalWrite(FIFO_OE, HIGH);       
  }  
    if(Vsync_Flag >= 2)
    {
        Serial.write(0xFE);
        Serial.write(0x01);
        pinMode(VSYNC, INPUT_PULLUP);
        detachInterrupt(digitalPinToInterrupt(VSYNC));     
      }
     else
     {
        pinMode(VSYNC, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(VSYNC), OV7670, FALLING);
      } 
  }

  unsigned char ov7670_data(void)
  {
    unsigned char tmp;
    unsigned char DATA7 = 0;
    unsigned char DATA6 = 0;
    unsigned char DATA5 = 0;
    unsigned char DATA4 = 0;
    unsigned char DATA3 = 0;
    unsigned char DATA2 = 0;
    unsigned char DATA1 = 0;
    unsigned char DATA0 = 0;
    tmp = 0;

    DATA7 = (unsigned char)digitalRead(D7);
    DATA6 = (unsigned char)digitalRead(D6);
    DATA5 = (unsigned char)digitalRead(D5);
    DATA4 = (unsigned char)digitalRead(D4);
    DATA3 = (unsigned char)digitalRead(D3);
    DATA2 = (unsigned char)digitalRead(D2);
    DATA1 = (unsigned char)digitalRead(D1);
    DATA0 = (unsigned char)digitalRead(D0);
    tmp = (DATA7 << 7) | (DATA6 << 6) | (DATA5 << 5) | (DATA4 << 4)\
         |(DATA3 << 3) | (DATA2 << 2) | (DATA1 << 1) | (DATA0 << 0);

    return tmp;
  }
  
