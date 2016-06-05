String testStr = "G00 X123.1651 Z345.14";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.println(parsenum2('Y', -1));
  Serial.println(round(3.4));
  Serial.println(round(3.49));
  Serial.println(round(3.50));
  Serial.println(round(3.51));
  Serial.println(round(3.6));
}

void loop() {
  // put your main code here, to run repeatedly:

}

float parsenum2(char code, float val)
{
  int i = 0;
  byte start = testStr.indexOf(code);
  if(start == 255)
  {
    return val;
  }
  Serial.println(start);
  byte ende = testStr.substring(start).indexOf(" ");
  Serial.println(ende);
  String result = testStr.substring(start+1,start+ende);
  Serial.println(result);
  float resFloat = result.toFloat();
  Serial.println(resFloat);
  //Serial.println(buf.substring(buf.indexOf(code), buf.indexOf(" ")));
  return resFloat;
}
