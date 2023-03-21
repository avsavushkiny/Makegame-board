/*
  systems test



#include <Arduino.h>

double divide(int a, int b)
{
    if(!b)  // если b == 0
    {
        throw 0;
    }
    if(b > a) 
    {
        throw "The first number is greater than the second one";
    }
    return a / b;
}
 
void test(int a, int b)
{
    try
    {
        double result {divide(a, b)};
        Serial.println(result);
    }
    catch (int code)
    {
        Serial.println("Error code: ");
    }
    catch (const char* error_message)
    {
        Serial.println(error_message);
    }
}
  
int mainn()
{
    test(100, 20);      // 5
    test(100, 0);       // Error code: 0
    test(100, 1000);    // The first number is greater than the second one
}

*/