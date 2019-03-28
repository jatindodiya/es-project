int scl;
int sda;

void i2c_clock_jd()
{
  delay(1);
  digitalWrite(scl, HIGH);
  delay(1);
  digitalWrite(scl, LOW);
}
/*
start condition high to low pulse when the clock is high
*/
void i2c_start_jd()
{
  digitalWrite(scl, LOW);
  digitalWrite(sda, HIGH);
  delay(1);
  
  digitalWrite(scl, HIGH);
  delay(1);
  
  digitalWrite(sda, LOW);
  delay(1);

  scl = 0;
}
/*
stop codition   low to high pulse when the clock is high
*/
void i2c_stop_jd()
{
  digitalWrite(scl, LOW);
  delay(1);
  digitalWrite(sda, HIGH);
  delay(1);
  digitalWrite(scl, HIGH);
  delay(1);
  digitalWrite(sda, HIGH);
}

/*
it takes 8 bit for MSB
*/
void i2c_write_jd(unsigned char data)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    sda = data & '0x80';
    i2c_clock_jd();
    data = data<<1;
  }
  sda=1;
 }
 
 
 unsigned char i2c_read_jd()
 {
  unsigned char i,data = 0x00;

    digitalWrite(sda, HIGH);;
  for(i=0;i<8;i++)
  {
    delay(1);
    
    digitalWrite(scl, HIGH);;
    delay(1);
    data== data<<1;
    data = data | sda;
    digitalWrite(scl, LOW);
  }
  return data;
  }
  /*when clock is high and pull the data line low will give positive ack
  */
  void i2c_ack_jd()
  {
   digitalWrite(sda, LOW);
    i2c_clock_jd();
    digitalWrite(sda, HIGH);
  }
  void i2c_noack_jd()
  {
    digitalWrite(sda, HIGH);
    i2c_clock_jd();
    digitalWrite(sda, HIGH);
  }


  /*
  GY 906 functions
  */
  #define gy906_id 0x5A
  #define t01address 0x00
  #define t02address 0x01
  #define control 0x05);
  void gy906start()
  {
    i2c_start_jd();
    gy906write(gy906_id);
    gy906write(control);

    gy906write(0x00);

    i2c_stop_jd();
  }
  
  int gy906write(void)
  {
    i2c_write_jd(data);
    i2c_clock_jd();
  }
  unsigned char gy906read()
  {
    unsigned char data;
    data = i2c_read_jd();
    return(data);
  }
  void gy906gettemp(unsigned char *to1,unsigned *to2)
  {
    i2c_start_jd();
    gy906write(gy906_id);
    gy906write(0x00);
    i2c_stop_jd();
    
    i2c_start_jd();
    gy906write(B4h);   // 5A leftshift 1 to get read enable
    
    *to1 = gy906read();
    i2c_ack_jd();
    *to2 = gy906read();
    i2c_noack_jd();
  }




void setup() 
{

gy906start();
  
}

void loop() 
{
  
  double tempData = 0x0000;
  double tempFactor = 0.02;
  int frac,to1,to2;
  gy906gettemp(unsigned char &tmax , unsigned char &tmin);
  //calculation
  to1= *tmax;
  to2= *tmin;
  tempData = (double)(((to1 & 0x007F) << 8) + to2);
  tempData = (tempData * tempFactor)-0.01;
  float celcius = tempData - 273.15;
  float fahrenheit = (celcius*1.8) + 32;
  Serial.print("celcous : ");
  Serial.println(celcius);
}
