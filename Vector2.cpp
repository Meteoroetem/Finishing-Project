#include<math.h>
#include<Arduino.h>
#include "Vector2.h"

double Vector2::GetMagnitude(){
    return sqrt(x*x + y*y);
}
double Vector2::GetSignedAngle(){
    return atan2(y, x);
}
double Vector2::GetUnsignedAngle(){
    double angle = atan2(y, x);
    return angle < 0 ? (2*M_PI)+angle : angle;
}