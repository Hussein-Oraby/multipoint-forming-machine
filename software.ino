#include<ArduinoSTL.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 int senddata=1;
int minimum=300;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
float positions[16]={
150,200,100,100,200,100,200,100,100,200,100,100,200,100,200,100 
};
int button1; 
int button2; 
int button3; 
int button4; 
int button5;
int back; 
int next; 
float input;
int state=0;
int page=1; // page variables to show acruators posotion 
int test=0;// variable to show warning message
int show=0; // variable to show positions manual entry state
int menue=1;
float Rnomaximum;
int res; // reset button
int speeD; // speed button
int index = 25; // no of actuators at the trejectory array
#define index 16 // no of actuators at the trejectory array
#define PITCH  1 
#define START_THREAD  4
int L= PITCH * START_THREAD ;// thread lead which mean one screw revolution equal to 8 mmm linear distance  but for 2 microstep mode we get 4 mm linear distance for one revolution
float speedDelay = 500; // delay time in microsecond between each pulse
const int stepPin1 = 3; 
const int dirPin1 = 4; 
const int stepPin2 = 5; 
const int dirPin2 = 6; 
const int stepPin3 = 7; 
const int dirPin3 = 8; 
const int stepPin4 = 9; 
const int dirPin4 = 10;
const int stepPin5 = 11; 
const int dirPin5 = 12;
const int stepPin6 = 22; 
const int dirPin6 = 23;
const int stepPin7 = 24; 
const int dirPin7 = 25;
const int stepPin8 = 26; 
const int dirPin8 = 27;
const int stepPin9 = 28; 
const int dirPin9 = 29;
const int stepPin10 = 30; 
const int dirPin10 = 31;
const int stepPin11 = 32; 
const int dirPin11 = 33;
const int stepPin12 = 34; 
const int dirPin12 = 35;
const int stepPin13 = 36; 
const int dirPin13 = 37;
const int stepPin14 = 38; 
const int dirPin14 = 39;
const int stepPin15 = 40; 
const int dirPin15 = 41;
const int stepPin16 = 42; 
const int dirPin16 = 43;
/*String dataIn = "";
String dataInS1 = "";
String dataInS2 = "";*/
float stepper1pos,stepper2pos,stepper3pos,stepper4pos,stepper5pos, stepper6pos, stepper7pos,stepper8pos,stepper9pos,stepper10pos,stepper11pos,stepper12pos,stepper13pos,stepper14pos,
stepper15pos ,stepper16pos;// current linear position for each actuator
float stepper1ppos,stepper2ppos,stepper3ppos,
stepper4ppos ,stepper5ppos,stepper6ppos,stepper7ppos,stepper8ppos ,stepper9ppos,stepper10ppos,stepper11ppos,stepper12ppos, stepper13ppos,stepper14ppos,stepper15ppos ,stepper16ppos;// previouse linear position for each actuator
float Rno1;
float Rno2;
float Rno3;
float Rno4;
float Rno5;
float Rno6;
float Rno7;
float Rno8;
float Rno9;
float Rno10;
float Rno11;
float Rno12;
float Rno13;
float Rno14;
float Rno15;
float Rno16;
float res1;
float res2;
float res3;
float res4;
float res5;
float res6;
float res7;
float res8;
float res9;
float res10;
float res11;
float res12;
float res13;
float res14;
float res15;
float res16;
void Home(){// home screen
  lcd.clear();
      lcd.setCursor(2,0);
  lcd.print("choose operation");
  lcd.setCursor(0,1);
  lcd.print("[1] Go position");
  lcd.setCursor(0,2);
  lcd.print("[2] Home position");
  lcd.setCursor(0,3);
  lcd.print("[3]Manual data entry"); 
  delay(3000);
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("[4] S.M data entry"); 
  lcd.setCursor(0,3);
  lcd.print("press Home to Repeat"); 
  }
void setup() {
Serial.begin(9600);
Serial1.begin(9600);
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT); 
  pinMode(dirPin3,OUTPUT);
  pinMode(stepPin4,OUTPUT); 
  pinMode(dirPin4,OUTPUT);
  pinMode(stepPin5,OUTPUT); 
  pinMode(dirPin5,OUTPUT);
  pinMode(stepPin6,OUTPUT); 
  pinMode(dirPin6,OUTPUT);
  pinMode(stepPin7,OUTPUT); 
  pinMode(dirPin7,OUTPUT);
  pinMode(stepPin8,OUTPUT); 
  pinMode(dirPin8,OUTPUT);   
  pinMode(stepPin9,OUTPUT); 
  pinMode(dirPin9,OUTPUT);
  pinMode(stepPin10,OUTPUT); 
  pinMode(dirPin10,OUTPUT);
  pinMode(stepPin11,OUTPUT); 
  pinMode(dirPin11,OUTPUT);
  pinMode(stepPin12,OUTPUT); 
  pinMode(dirPin12,OUTPUT);
  pinMode(stepPin13,OUTPUT); 
  pinMode(dirPin13,OUTPUT);
  pinMode(stepPin14,OUTPUT); 
  pinMode(dirPin14,OUTPUT);
  pinMode(stepPin15,OUTPUT); 
  pinMode(dirPin15,OUTPUT); 
    pinMode(stepPin16,OUTPUT); 
  pinMode(dirPin16,OUTPUT); 
  stepper1ppos=0;
  stepper2ppos=0;
  stepper3ppos=0;
  stepper4ppos=0;
  stepper5ppos=0;
  stepper6ppos=0;
  stepper7ppos=0;
  stepper8ppos=0;
  stepper9ppos=0;
  stepper10ppos=0;
  stepper11ppos=0;
  stepper12ppos=0;
  stepper13ppos=0;
  stepper14ppos=0;
  stepper15ppos=0;
  stepper16ppos=0;
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("System Loading...");
  lcd.setCursor(11,1);
  lcd.print("%");
   lcd.setCursor(1,2);
  lcd.print("<Please open S.M>");
  for ( int i=0;i<=100;i+=5){
     lcd.setCursor(9,1);
  lcd.print(i);
  delay(400);
  }
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("welcome to");
  lcd.setCursor(1,2);
  lcd.print("multipoint forming");
   lcd.setCursor(3,3);
  lcd.print("machine system.");
  delay(4000);
   Home();         
}
float stepsanddirectioncalculator(float x,float y,int dirPin){ /* fuction calculates required revolutions for each motor and direction shouid takes>>> takes stepper[i]pos ,  
  stepper[i]ppos and stepper direction pin  returns Rno[i] and gives stepper direction pin high or low */
         if(x<=500){
      if (y >= x) {      // If previous position is bigger then current position
        float lineardistance=y-x;
        // note that one revolution for screw equal 8 mm linear distance of stepper
        float revolution=lineardistance/L;
         float Rno=200*revolution; // Rno is number of pulses needed to rotate stepper to required no of revolutions
         digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction 
        return Rno;
      }
      if (y < x) {
        float lineardistance=x-y;
        // note that one revolution for screw equal 8 mm linear distance of stepper
        float revolution=lineardistance/L;
         float Rno =200*revolution; // Rno is number of pulses needed to rotate stepper to required no of revolutions
         digitalWrite(dirPin,LOW); //Changes the rotations direction
        return Rno;
      } 
      }
        else if (x>500){
       // Serial.println("actuator1 Distance is out of permitted range");
        float Rno=0;
         return Rno;
      }
      }
 float stepscalculator(float x,float y){ // fuction calculates required revolutions for each motor takes stepper[i]pos and  stepper[i]ppos and returns Rno[i]
         if(x<=500){
      if (y >= x) {      // If previous position is bigger then current position
        float lineardistance=y-x;
        // note that one revolution for screw equal 8 mm linear distance of stepper
        float revolution=lineardistance/L;
         float Rno=200*revolution; // Rno is number of pulses needed to rotate stepper to required no of revolutions
        return Rno;
      }
      if (y < x) {
        float lineardistance=x-y;
        // note that one revolution for screw equal 8 mm linear distance of stepper
        float revolution=lineardistance/L;
         float Rno =200*revolution; // Rno is number of pulses needed to rotate stepper to required no of revolutions
        return Rno;
      } 
      }
      }

      
      float homeposition(float res){//function returns steppers to Home position(zero position) takes res return Rno(no of revolutions)
      float lineardistance=res;
        // note that one revolution for screw equal 8 mm linear distance of stepper
        float revolution=lineardistance/L;
      float  Rno =200*revolution; // Rno is number of pulses needed to rotate stepper to required no of revolutions
        return Rno;
      }
void loop() {
  if ( state==5) {
    int x[16];
  /* 
   ملاحظات هامة عند استخدام مود ادخال البيانات بالكومبيوتر
    1: ممنوع ادخل ارقام عشرية زي 200.45 لازم يكون رقم صحيح زي 200 او 100 او 150 وهكذلا ولو دخلت هيقبل عادي وهيحولها لرقم صحيح يعني هيهمل الكسر ولكن مش هيرضي يدخل علي مزد الادخال بالكومبيوتر تاني غير 
   لما ارستر الاردوينوا
   2: ممنوع اسيب مسافات بين كل عنصر ولفصلة لو عملت كدا هيقبل عادي لكن مش هيرضي يشغل مود الادخال بالكومبيوتر تاني غير لو عمت ريستارت للاردوينو
   3: لازم اشغل السريال مونيتور قبل ما اعمل اي حاجة بالجهاز علشان لما بشغل السريال الاردوينو بيعمل ريسيت اجباري ف لو انا كنت واقف عند بوزشن معين هيعتبره انه واقف ف الصفر وبالتالي المحركات هتطلع 
   بره الريينج وهتتكسر
   */
  printf("enter new positions arry: \n");
   lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("Enter new positions");
  lcd.setCursor(1,1);
  lcd.print("array in S.M then");
  lcd.setCursor(4,2);
  lcd.print("press Enter.");
  scanf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&x[0],&x[1],&x[2],&x[3],&x[4],&x[5],&x[6],&x[7],&x[8],&x[9],
     &x[10],&x[11],&x[12],&x[13],&x[14],&x[15]);
     for(int i =0 ;i<=15 ;i++){
      if(x[i]<=500 && x[i]>=0){
        positions[i]=x[i];
      }
     }
  printf(" new actuator  positions are : \n");
  for (int i=0;i<=15;i++){
    Serial.print("actutor :  ");
    Serial.print(i+1);
     Serial.println(" : ");
   Serial.println(positions[i]);
  }
  for(int i =0 ;i<=15 ;i++){
       if (x[i]>500){
        Serial.print("actutor :  ");
        Serial.print(i+1);
        Serial.println(" is out of permitted range position is set to zero relative to current position");
      }
     }
  lcd.clear();
      lcd.setCursor(6,0);
  lcd.print("Entering");
  lcd.setCursor(0,1);
  lcd.print("new positions array");
  lcd.setCursor(4,2);
  lcd.print("is completed.");
delay(5000);
     senddata=1;
      state=1;
  }
  
    button1 = analogRead(A0);
    button2 = analogRead(A1);
    button3 = analogRead(A2);
    button4 = analogRead(A3);
    button5 = analogRead(A8);
    next = analogRead(A4);
    back = analogRead(A5);
    speeD=analogRead(A6);
    if ( button1>=600){
      state=1;
    }
    else if ( button2>=600){
      state=2;
       menue=1;
    }
    else if ( button3>=600){
      state=3;
      test=0;
      menue=1;
      Serial1.println("2");
    }
    else if ( button4>=600){
      state=4;
      menue=1;
     
    }
     else if ( button5>=600){
      state=5;
      test=0;
      menue=1;
    }
    else if ( next>=600){
      page--;
      menue=1;
      if(page<=1){
        page=1;
      }
      //page=1;
    }
    else if (back>=600){
      page++;
      menue=1;
        if(page>=4){
        page=4;
      }
      //page=2  ;
    }
    if (state==1){
 Home();
  state=0;
    }
    if(button4>=500){
      page=0;
      test=0;
      lcd.clear();
      lcd.setCursor(2,0);
  lcd.print("Enter Actuator");
   lcd.setCursor(2,1);
  lcd.print("Position :");
  lcd.setCursor(18,1);
  lcd.print("mm");
  lcd.setCursor(0,3);
  lcd.print("Next");
  lcd.setCursor(4,3);
  lcd.print(">");
  lcd.setCursor(18,3);
       lcd.print("Ok");
      int i =0;
      while (i<15){
        show=0;
        lcd.setCursor(12,1);
  lcd.print("   ");
       input= map(analogRead(A7),0,1023,0,500);  // change pulses delay time which change rotation speed
  lcd.setCursor(17,0);
  lcd.print(i+1);
   lcd.setCursor(12,1);
  lcd.print(input);
    next = analogRead(A4);
    back = analogRead(A5);
      if ( next>=600){
      page=1;
    }
    else if (back>=600){
      page=2;
    }  
      if( page==1){
      i++;
      page=0;
      delay(300);
    }
     if( page==2){
      positions[i]=input;
      i++;
      page=0;
      delay(300);
    }
    button1 = analogRead(A0);
    if(button1>=500){
      show=1;
      break;
      
    }
    delay(100);
   
    }
    if (show==0){
       lcd.clear();
      lcd.setCursor(1,0);
  lcd.print("Entering Actuators");
   lcd.setCursor(3,1);
  lcd.print(" new Positions ");
  lcd.setCursor(5,2);
  lcd.print(" completed.");
  delay(5000);
  Home(); 
    }
    if (show==1){
       lcd.clear();
      lcd.setCursor(1,0);
  lcd.print("Entering Actuators");
   lcd.setCursor(3,1);
  lcd.print(" new Positions ");
  lcd.setCursor(4,2);
  lcd.print("is canseled.");
  delay(5000);
Home();
    }
    senddata=1;
     page=1;
    } 
  if (state==2) {
    // Stepper 1 input position***************************************************************
      stepper1pos = positions[0];
      Rno1=stepsanddirectioncalculator(stepper1pos,stepper1ppos,dirPin1); 
       // Stepper 2 input position***************************************************************
      stepper2pos = positions[1];
      Rno2=stepsanddirectioncalculator(stepper2pos,stepper2ppos,dirPin2);      
      // Stepper 3 input position***************************************************************
      stepper3pos = positions[2];  
       Rno3=stepsanddirectioncalculator(stepper3pos,stepper3ppos,dirPin3); 
      // Stepper 4 input position***************************************************************
      stepper4pos = positions[3];  
       Rno4=stepsanddirectioncalculator(stepper4pos,stepper4ppos,dirPin4); 
      // Stepper 5 input position***************************************************************
      stepper5pos = positions[4];
      Rno5=stepsanddirectioncalculator(stepper5pos,stepper5ppos,dirPin5); 
      // Stepper 6 input position***************************************************************
      stepper6pos = positions[5];
       Rno6=stepsanddirectioncalculator(stepper6pos,stepper6ppos,dirPin6); 
      // Stepper 7 input position***************************************************************
      stepper7pos = positions[6];
       Rno7=stepsanddirectioncalculator(stepper7pos,stepper7ppos,dirPin7); 
      // Stepper 8 input position***************************************************************
      stepper8pos = positions[7];
      Rno8=stepsanddirectioncalculator(stepper8pos,stepper8ppos,dirPin8); 
      // Stepper 9 input position***************************************************************
      stepper9pos = positions[8];
       Rno9=stepsanddirectioncalculator(stepper9pos,stepper9ppos,dirPin9); 
      // Stepper 10 input position***************************************************************
      stepper10pos = positions[9];
       Rno10=stepsanddirectioncalculator(stepper10pos,stepper10ppos,dirPin10); 
      // Stepper 11 input position***************************************************************
      stepper11pos = positions[10];
      Rno11=stepsanddirectioncalculator(stepper11pos,stepper11ppos,dirPin11); 
      // Stepper 12 input position***************************************************************
      stepper12pos = positions[11];
       Rno12=stepsanddirectioncalculator(stepper12pos,stepper12ppos,dirPin12); 
      // Stepper 13 input position***************************************************************
      stepper13pos = positions[12];
       Rno13=stepsanddirectioncalculator(stepper13pos,stepper13ppos,dirPin13); 
       // Stepper 14 input position***************************************************************
      stepper14pos = positions[13];
      Rno14=stepsanddirectioncalculator(stepper14pos,stepper14ppos,dirPin14); 
      // Stepper 15 input position***************************************************************
      stepper15pos = positions[14];
       Rno15=stepsanddirectioncalculator(stepper15pos,stepper15ppos,dirPin15); 
       //*********************************************************************************************************************  
      stepper16pos = positions[15];
      Rno16=stepscalculator(stepper16pos,stepper16ppos);
       //*********************************************************************************************************************
     if (test==0){
      page=1;
    if (positions[0]>500){
      lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator1");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno1=0;
        stepper1pos=stepper1ppos;
        delay(3500);
              lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator1 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }
    if (positions[1]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator2");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno2=0;
        stepper2pos=stepper2ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator2 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }
     if (positions[2]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator3");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno3=0;
        stepper3pos=stepper3ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator3 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
 if (positions[3]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator4");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno4=0;
        stepper4pos=stepper4ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator4 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[4]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator5");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno5=0;
        stepper5pos=stepper5ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator5 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[5]>500){
       lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator6");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno6=0;
        stepper6pos=stepper6ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator6 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[6]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator7");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno7=0;
        stepper7pos=stepper7ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator7 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      } 
     if (positions[7]>500){
     lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator8");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno8=0;
        stepper8pos=stepper8ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator8 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[8]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator9");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno9=0;
        stepper9pos=stepper9ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator9 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[9]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator10");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno10=0;
        stepper10pos=stepper10ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator10 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[10]>500){
       lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator11");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno11=0;
        stepper11pos=stepper11ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator11 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }  
    if (positions[11]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator12");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno12=0;
        stepper12pos=stepper12ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator12 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      } 
    if (positions[12]>500){
       lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator13");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno13=0;
        stepper13pos=stepper13ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator13 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      } 
   if (positions[13]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator14");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno14=0;
        stepper14pos=stepper14ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator14 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }
     if (positions[14]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator15");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno15=0;
        stepper15pos=stepper15ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator15 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      } 
      if (positions[15]>500){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("warning!! actuator16");
  lcd.setCursor(5,1);
  lcd.print("is out of");
  lcd.setCursor(2,2);
  lcd.print(" permitted range");
        Rno16=0;
        stepper16pos=stepper16ppos;
        delay(3500);
         lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuator16 position");
  lcd.setCursor(3,1);
  lcd.print("is set to zero");
  delay(2500);
      }
    lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuators are now");
  lcd.setCursor(3,1);
  lcd.print("set to desired");
  lcd.setCursor(3,2);
  lcd.print("positions.....");
      }  
     Rnomaximum=Rno1;
   if (Rno2>=Rnomaximum){
     Rnomaximum=Rno2;
   }
   if (Rno3>=Rnomaximum){
     Rnomaximum=Rno3;
   }
    if (Rno4>=Rnomaximum){
     Rnomaximum=Rno4;
   }
   if (Rno5>=Rnomaximum){
     Rnomaximum=Rno5;
   }
   if (Rno6>=Rnomaximum){
     Rnomaximum=Rno6;
   }
   if (Rno7>=Rnomaximum){
     Rnomaximum=Rno7;
   }
   if (Rno8>=Rnomaximum){
     Rnomaximum=Rno8;
   }
   if (Rno9>=Rnomaximum){
     Rnomaximum=Rno9;
   }
   if (Rno10>=Rnomaximum){
     Rnomaximum=Rno10;
   }
   if (Rno11>=Rnomaximum){
     Rnomaximum=Rno11;
   }
   if (Rno12>=Rnomaximum){
     Rnomaximum=Rno12;
   }
   if (Rno13>=Rnomaximum){
     Rnomaximum=Rno13;
   }
   if (Rno14>=Rnomaximum){
     Rnomaximum=Rno14;
   }
   if (Rno15>=Rnomaximum){
     Rnomaximum=Rno15;
   }
   if (Rno16>=Rnomaximum){
     Rnomaximum=Rno16;
   }
   if(Rnomaximum>0){
  for(float x = 0; x < Rnomaximum; x++) {
    if(x<=Rno1){
    digitalWrite(stepPin1,HIGH); 
    }
    else{
      digitalWrite(stepPin1,LOW); 
    }   
    //**********************************
    if(x<=Rno2){
    digitalWrite(stepPin2,HIGH); 
     }
     else{
      digitalWrite(stepPin2,LOW); 
    }
     //**********************************
    if(x<=Rno3){
    digitalWrite(stepPin3,HIGH); 
     }
     else{
      digitalWrite(stepPin3,LOW); 
    }
     //**********************************
    if(x<=Rno4){
    digitalWrite(stepPin4,HIGH); 
     }
     else{
      digitalWrite(stepPin4,LOW); 
    }
    //**********************************
    if(x<=Rno5){
    digitalWrite(stepPin5,HIGH); 
     }
     else{
      digitalWrite(stepPin5,LOW); 
    }
    //**********************************
    if(x<=Rno6){
    digitalWrite(stepPin6,HIGH); 
     }
     else{
      digitalWrite(stepPin6,LOW); 
    }
    //**********************************
    if(x<=Rno7){
    digitalWrite(stepPin7,HIGH); 
     }
     else{
      digitalWrite(stepPin7,LOW); 
    }
    //**********************************
    if(x<=Rno4){
    digitalWrite(stepPin8,HIGH); 
     }
     else{
      digitalWrite(stepPin8,LOW); 
    }
    //**********************************
    if(x<=Rno9){
    digitalWrite(stepPin9,HIGH); 
     }
     else{
      digitalWrite(stepPin9,LOW); 
    }
    //**********************************
    if(x<=Rno10){
    digitalWrite(stepPin10,HIGH); 
     }
     else{
      digitalWrite(stepPin10,LOW); 
    }
    //**********************************
    if(x<=Rno11){
    digitalWrite(stepPin11,HIGH); 
     }
     else{
      digitalWrite(stepPin11,LOW); 
    }
    //**********************************
    if(x<=Rno12){
    digitalWrite(stepPin12,HIGH); 
     }
     else{
      digitalWrite(stepPin12,LOW); 
    }
    //**********************************
    if(x<=Rno13){
    digitalWrite(stepPin13,HIGH); 
     }
     else{
      digitalWrite(stepPin13,LOW); 
    }
    //**********************************
    if(x<=Rno14){
    digitalWrite(stepPin14,HIGH); 
     }
     else{
      digitalWrite(stepPin14,LOW); 
    }
    //**********************************
    if(x<=Rno15){
    digitalWrite(stepPin15,HIGH); 
     }
     else{
      digitalWrite(stepPin15,LOW); 
    }
    //**********************************
        if(x<=Rno16){
    digitalWrite(stepPin16,HIGH); 
     }
     else{
      digitalWrite(stepPin16,LOW); 
    }
    //**********************************
    delayMicroseconds( speedDelay);
    digitalWrite(stepPin1,LOW);  
    digitalWrite(stepPin2,LOW); 
    digitalWrite(stepPin3,LOW); 
    digitalWrite(stepPin4,LOW); 
    digitalWrite(stepPin5,LOW); 
    digitalWrite(stepPin6,LOW); 
    digitalWrite(stepPin7,LOW); 
    digitalWrite(stepPin8,LOW); 
    digitalWrite(stepPin9,LOW); 
    digitalWrite(stepPin10,LOW); 
    digitalWrite(stepPin11,LOW); 
    digitalWrite(stepPin12,LOW); 
    digitalWrite(stepPin13,LOW); 
    digitalWrite(stepPin14,LOW); 
    digitalWrite(stepPin15,LOW); 
    digitalWrite(stepPin16,LOW);
    delayMicroseconds( speedDelay); 
     speeD=analogRead(A6);    
      speedDelay= map(speeD,0,1023,minimum,1000);  // change pulses delay time which change rotation speed
      
    }
   }
   if (test==0){
   lcd.clear();
      lcd.setCursor(1,1);
  lcd.print("Positions install");
  lcd.setCursor(5,2);
  lcd.print("Complete.");
  delay(2000);
  test=1;
   }
      stepper1ppos = stepper1pos  ; // set current position as previous position
      res1=stepper1ppos;
      stepper2ppos = stepper2pos  ; // set current position as previous position
      res2=stepper2ppos;
      stepper3ppos = stepper3pos  ; // set current position as previous position
      res3=stepper3ppos;
      stepper4ppos = stepper4pos  ; // set current position as previous position
      res4=stepper4ppos;
        stepper5ppos = stepper5pos  ; // set current position as previous position
      res5=stepper5ppos;
      stepper6ppos = stepper6pos  ; // set current position as previous position
      res6=stepper6ppos;
      stepper7ppos = stepper7pos  ; // set current position as previous position
      res7=stepper7ppos;
      stepper8ppos = stepper8pos  ; // set current position as previous position
      res8=stepper8ppos;
       stepper9ppos = stepper9pos  ; // set current position as previous position
      res9=stepper9ppos;
      stepper10ppos = stepper10pos  ; // set current position as previous position
      res10=stepper10ppos;
      stepper11ppos = stepper11pos  ; // set current position as previous position
      res11=stepper11ppos;
        stepper12ppos = stepper12pos  ; // set current position as previous position
      res12=stepper12ppos;
      stepper13ppos = stepper13pos  ; // set current position as previous position
      res13=stepper13ppos;
      stepper14ppos = stepper14pos  ; // set current position as previous position
      res14=stepper14ppos;
      stepper15ppos = stepper15pos  ; // set current position as previous position
      res15=stepper15ppos;
      stepper16ppos = stepper16pos  ; // set current position as previous position
      res16=stepper16ppos;
      
      Rno1=0;
      Rno2=0;
      Rno3=0;
      Rno4=0;
      Rno5=0;
      Rno6=0;
      Rno7=0;
      Rno8=0;
      Rno9=0;
      Rno10=0;
      Rno11=0;
      Rno12=0;
      Rno13=0;
      Rno14=0;
      Rno15=0;
      Rno16=0;
     
       if(menue==1){
      if (page==1){
        lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("S1:");
      lcd.setCursor(3,0);
  lcd.print(stepper1ppos);
  lcd.setCursor(9,0);
  lcd.print(",");
  lcd.setCursor(10,0);
  lcd.print("S2:"); 
  lcd.setCursor(13,0);
  lcd.print(stepper2ppos);
     lcd.setCursor(0,1);
      lcd.print("S3:");
      lcd.setCursor(3,1);
  lcd.print(stepper3ppos);
  lcd.setCursor(9,1);
  lcd.print(",");
  lcd.setCursor(10,1);
  lcd.print("S4:"); 
  lcd.setCursor(13,1);
  lcd.print(stepper4ppos);
     lcd.setCursor(0,2);
      lcd.print("S5:");
      lcd.setCursor(3,2);
  lcd.print(stepper5ppos);
  lcd.setCursor(9,2);
  lcd.print(",");
  lcd.setCursor(10,2);
  lcd.print("S6:");
  lcd.setCursor(13,2);
  lcd.print(stepper6ppos);
      lcd.setCursor(0,3);
      lcd.print("S7:");
      lcd.setCursor(3,3);
  lcd.print(stepper7ppos);
   lcd.setCursor(15,3);
  lcd.print("Next");
  lcd.setCursor(19,3);
  lcd.print(">");
  menue=0;
      }
       if (page==2){
           lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("S8:");
      lcd.setCursor(3,0);
  lcd.print(stepper8ppos);
  lcd.setCursor(9,0);
  lcd.print(",");
  lcd.setCursor(10,0);
  lcd.print("S9:"); 
  lcd.setCursor(13,0);
  lcd.print(stepper9ppos);
     lcd.setCursor(0,1);
      lcd.print("S10:");
      lcd.setCursor(4,1);
  lcd.print(stepper10ppos);
  lcd.setCursor(10,1);
  lcd.print("S11:"); 
  lcd.setCursor(14,1);
  lcd.print(stepper11ppos);
     lcd.setCursor(0,2);
      lcd.print("S12:");
      lcd.setCursor(4,2);
  lcd.print(stepper12ppos);
  lcd.setCursor(10,2);
  lcd.print("S13:");
  lcd.setCursor(14,2);
  lcd.print(stepper13ppos);
       lcd.setCursor(0,3);
       lcd.print("<Back");
       lcd.setCursor(5,3);
      lcd.print("S14:");
      lcd.setCursor(9,3);
  lcd.print(stepper14ppos);
   lcd.setCursor(15,3);
  lcd.print("Next");
  lcd.setCursor(19,3);
  lcd.print(">");
  //page=0;
  menue=0;
      }
      if (page==3){
              lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("S15:");
      lcd.setCursor(4,0);
  lcd.print(stepper15ppos);
  lcd.setCursor(10,0);
  lcd.print("S16:"); 
  lcd.setCursor(14,0);
  lcd.print(stepper16ppos);
    lcd.setCursor(0,3);
       lcd.print("<Back");
   lcd.setCursor(17,3);
  lcd.print("End");
  //page=0;
  menue=0;         
      }
      }
      
      }
      
    
    
    // If button "RESET" is pressed
   if ( state==3) {
     digitalWrite(dirPin1,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin2,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin3,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin4,HIGH); // Enables the motor to move in a particular direction
     digitalWrite(dirPin5,HIGH); // Enables the motor to move in a particular direction 
      digitalWrite(dirPin6,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin7,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin8,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin9,HIGH); // Enables the motor to move in a particular direction
     digitalWrite(dirPin10,HIGH); // Enables the motor to move in a particular direction 
      digitalWrite(dirPin11,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin12,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin13,HIGH); // Enables the motor to move in a particular direction 
     digitalWrite(dirPin14,HIGH); // Enables the motor to move in a particular direction
     digitalWrite(dirPin15,HIGH); // Enables the motor to move in a particular direction 
      digitalWrite(dirPin16,HIGH); // Enables the motor to move in a particular direction 
     //*******************************************************************************************************************
      
        Rno1=homeposition(res1);
        //**********************************************************************************************************************
        Rno2=homeposition(res2);
        //**********************************************************************************************************************
        Rno3=homeposition(res3);    
        //**********************************************************************************************************************
        Rno4=homeposition(res4);
        //********************************************************************************************************************** 
        Rno5=homeposition(res5);
        //**********************************************************************************************************************  
        Rno6=homeposition(res6);
        //********************************************************************************************************************** 
        Rno7=homeposition(res7);
        //********************************************************************************************************************** 
        Rno8=homeposition(res8);
        //**********************************************************************************************************************   
         Rno9=homeposition(res9);
        //**********************************************************************************************************************  
         Rno10=homeposition(res10);
        //**********************************************************************************************************************    
         Rno11=homeposition(res11);
        //********************************************************************************************************************** 
         Rno12=homeposition(res12);
        //**********************************************************************************************************************   
         Rno13=homeposition(res13);
        //**********************************************************************************************************************   
         Rno14=homeposition(res14);
        //********************************************************************************************************************** 
         Rno15=homeposition(res15);
        //********************************************************************************************************************** 
         Rno16=homeposition(res16);
          //********************************************************************************************************************** 
  // return each stepper to zero position
    Rnomaximum=Rno1;
   if (Rno2>=Rnomaximum){
     Rnomaximum=Rno2;
   }
    if (Rno3>=Rnomaximum){
     Rnomaximum=Rno3;
   }
    if (Rno4>=Rnomaximum){
     Rnomaximum=Rno4;
   }
   if (Rno5>=Rnomaximum){
     Rnomaximum=Rno5;
   }
   if (Rno6>=Rnomaximum){
     Rnomaximum=Rno6;
   }
   if (Rno7>=Rnomaximum){
     Rnomaximum=Rno7;
   }
   if (Rno8>=Rnomaximum){
     Rnomaximum=Rno8;
   }
   if (Rno9>=Rnomaximum){
     Rnomaximum=Rno9;
   }
   if (Rno10>=Rnomaximum){
     Rnomaximum=Rno10;
   }
   if (Rno11>=Rnomaximum){
     Rnomaximum=Rno11;
   }
   if (Rno12>=Rnomaximum){
     Rnomaximum=Rno12;
   }
   if (Rno13>=Rnomaximum){
     Rnomaximum=Rno13;
   }
   if (Rno14>=Rnomaximum){
     Rnomaximum=Rno14;
   }
   if (Rno15>=Rnomaximum){
     Rnomaximum=Rno15;
   }
   if (Rno16>=Rnomaximum){
     Rnomaximum=Rno16;
   }
   if(Rnomaximum>0){
    lcd.clear();
      lcd.setCursor(0,0);
  lcd.print("actuators are now");
  lcd.setCursor(3,1);
  lcd.print("set to Home");
  lcd.setCursor(3,2);
  lcd.print("position.....");
   }
  for(float x = 0; x < Rnomaximum; x++) {
    if(x<=Rno1){
    digitalWrite(stepPin1,HIGH); 
    }
    else{
      digitalWrite(stepPin1,LOW); 
    }  
    //**********************************
    if(x<=Rno2){
    digitalWrite(stepPin2,HIGH); 
     }
     else{
      digitalWrite(stepPin2,LOW); 
    }
    //**********************************
    if(x<=Rno3){
    digitalWrite(stepPin3,HIGH); 
     }
     else{
      digitalWrite(stepPin3,LOW); 
    }
    //**********************************
    if(x<=Rno4){
    digitalWrite(stepPin4,HIGH); 
     }
     else{
      digitalWrite(stepPin4,LOW); 
    }
    //**********************************
    if(x<=Rno5){
    digitalWrite(stepPin5,HIGH); 
     }
     else{
      digitalWrite(stepPin5,LOW); 
    }
    //**********************************
    if(x<=Rno6){
    digitalWrite(stepPin6,HIGH); 
     }
     else{
      digitalWrite(stepPin6,LOW); 
    }
    //**********************************
    if(x<=Rno7){
    digitalWrite(stepPin7,HIGH); 
     }
     else{
      digitalWrite(stepPin7,LOW); 
    }
    //**********************************
    if(x<=Rno8){
    digitalWrite(stepPin8,HIGH); 
     }
     else{
      digitalWrite(stepPin8,LOW); 
    }
    //**********************************
    if(x<=Rno9){
    digitalWrite(stepPin9,HIGH); 
     }
     else{
      digitalWrite(stepPin9,LOW); 
    }
    //**********************************
    if(x<=Rno10){
    digitalWrite(stepPin10,HIGH); 
     }
     else{
      digitalWrite(stepPin10,LOW); 
    }
    //**********************************
    if(x<=Rno11){
    digitalWrite(stepPin11,HIGH); 
     }
     else{
      digitalWrite(stepPin11,LOW); 
    }
    //**********************************
    if(x<=Rno12){
    digitalWrite(stepPin12,HIGH); 
     }
     else{
      digitalWrite(stepPin12,LOW); 
    }
    //**********************************
    if(x<=Rno13){
    digitalWrite(stepPin13,HIGH); 
     }
     else{
      digitalWrite(stepPin13,LOW); 
    }
    //**********************************
    if(x<=Rno14){
    digitalWrite(stepPin14,HIGH); 
     }
     else{
      digitalWrite(stepPin14,LOW); 
    }
    //**********************************
    if(x<=Rno15){
    digitalWrite(stepPin15,HIGH); 
     }
     else{
      digitalWrite(stepPin15,LOW); 
    }
        //**********************************
    if(x<=Rno16){
    digitalWrite(stepPin16,HIGH); 
     }
     else{
      digitalWrite(stepPin16,LOW); 
    }
    delayMicroseconds( speedDelay); 
    digitalWrite(stepPin1,LOW); 
    digitalWrite(stepPin2,LOW); 
    digitalWrite(stepPin3,LOW); 
    digitalWrite(stepPin4,LOW); 
    digitalWrite(stepPin5,LOW); 
    digitalWrite(stepPin6,LOW); 
    digitalWrite(stepPin7,LOW); 
    digitalWrite(stepPin8,LOW); 
    digitalWrite(stepPin9,LOW); 
    digitalWrite(stepPin10,LOW); 
    digitalWrite(stepPin11,LOW); 
    digitalWrite(stepPin12,LOW); 
    digitalWrite(stepPin13,LOW); 
    digitalWrite(stepPin14,LOW); 
    digitalWrite(stepPin15,LOW); 
      digitalWrite(stepPin16,LOW);
    delayMicroseconds( speedDelay); 
      speeD=analogRead(A6);    
      speedDelay= map(speeD,0,1023,minimum,1000);  // change pulses delay time which change rotation speed
    }
    if(Rnomaximum>0){
      lcd.clear();
      lcd.setCursor(1,1);
  lcd.print("Positions install");
  lcd.setCursor(5,2);
  lcd.print("Complete.");
  delay(2000);
   page=1;
   }
      res1 = 0  ; // set current position as previous position
      stepper1ppos =0;
      stepper1pos =0;
      res2 = 0  ; // set current position as previous position
      stepper2ppos =0;
      stepper2pos =0;
      res3 = 0  ; // set current position as previous position
      stepper3ppos =0;
      stepper3pos =0;
      res4 = 0  ; // set current position as previous position
      stepper4ppos =0;
      stepper4pos =0;
       res5 = 0  ; // set current position as previous position
      stepper5ppos =0;
      stepper5pos =0;
      res6 = 0  ; // set current position as previous position
      stepper6ppos =0;
      stepper6pos =0;
      res7 = 0  ; // set current position as previous position
      stepper7ppos =0;
      stepper7pos =0;
      res8 = 0  ; // set current position as previous position
      stepper8ppos =0;
      stepper8pos =0;
       res9 = 0  ; // set current position as previous position
      stepper9ppos =0;
      stepper9pos =0;
      res10 = 0  ; // set current position as previous position
      stepper10ppos =0;
      stepper10pos =0;
      res11 = 0  ; // set current position as previous position
      stepper11ppos =0;
      stepper11pos =0;
       res12 = 0  ; // set current position as previous position
      stepper12ppos =0;
      stepper12pos =0;
      res13 = 0  ; // set current position as previous position
      stepper13ppos =0;
      stepper13pos =0;
      res14 = 0  ; // set current position as previous position
      stepper14ppos =0;
      stepper14pos =0;
      res15 = 0  ; // set current position as previous position
      stepper15ppos =0;
      stepper15pos =0;
      res16 = 0  ; // set current position as previous position
      stepper16ppos =0;
      stepper16pos =0;
      Rno1=0;
      Rno2=0;
      Rno3=0;
      Rno4=0;
      Rno5=0;
      Rno6=0;
      Rno7=0;
      Rno8=0;
      Rno9=0;
      Rno10=0;
      Rno11=0;
      Rno12=0;
      Rno13=0;
      Rno14=0;
      Rno15=0;
      Rno16=0;
      if(menue==1){
      if (page==1){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print(stepper1ppos);
  lcd.setCursor(6,0);
  lcd.print(",");
  lcd.setCursor(7,0);
  lcd.print(stepper2ppos);
  lcd.setCursor(13,0);
  lcd.print(",");
  lcd.setCursor(14,0);
  lcd.print(stepper3ppos);
       lcd.setCursor(0,1);
  lcd.print(stepper4ppos);
  lcd.setCursor(6,1);
  lcd.print(",");
  lcd.setCursor(7,1);
  lcd.print(stepper5ppos);
  lcd.setCursor(13,1);
  lcd.print(",");
  lcd.setCursor(14,1);
  lcd.print(stepper6ppos);
       lcd.setCursor(0,2);
  lcd.print(stepper7ppos);
  lcd.setCursor(6,2);
  lcd.print(",");
  lcd.setCursor(7,2);
  lcd.print(stepper8ppos);
  lcd.setCursor(13,2);
  lcd.print(",");
  lcd.setCursor(14,2);
  lcd.print(stepper9ppos);
       lcd.setCursor(0,3);
  lcd.print(stepper10ppos);
  lcd.setCursor(6,3);
  lcd.print(",");
  lcd.setCursor(7,3);
  lcd.print(stepper11ppos);
  lcd.setCursor(15,3);
  lcd.print("Next");
  lcd.setCursor(19,3);
  lcd.print(">");
  //page=0;
  menue=0;
      }
       if (page==2){
        lcd.clear();
      lcd.setCursor(0,0);
  lcd.print(stepper12ppos);
  lcd.setCursor(6,0);
  lcd.print(",");
  lcd.setCursor(7,0);
  lcd.print(stepper13ppos);
  lcd.setCursor(13,0);
  lcd.print(",");
  lcd.setCursor(14,0);
  lcd.print(stepper14ppos);
       lcd.setCursor(0,1);
  lcd.print(stepper15ppos);
  lcd.setCursor(6,1);
  lcd.print(",");
  lcd.setCursor(7,1);
  lcd.print(stepper16ppos);
   lcd.setCursor(0,3);
       lcd.print("<Back");
   lcd.setCursor(17,3);
  lcd.print("End");
 
  //page=0;
  menue=0;
      }
      }
     
  }
  // change steppers speed
  delay(100);
  }
