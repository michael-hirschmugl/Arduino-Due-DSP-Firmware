/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 2
Sampling Frequency: 44 KHz
Cut Frequency: 1.000000 KHz
Coefficents Quantization: 8-bit

Z domain Zeros
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000

Z domain Poles
z = 0.898437 + j -0.072870
z = 0.898437 + j 0.072870
***************************************************************/
#define NCoef 2
#define DCgain 128

__int8 iir(__int8 NewSample) {
    __int8 ACoef[NCoef+1] = {
           37,
           75,
           37
    };

    __int8 BCoef[NCoef+1] = {
           64,
         -115,
           52
    };

    static __int16 y[NCoef+1]; //output samples
    //Warning!!!!!! This variable should be signed (input sample width + Coefs width + 2 )-bit width to avoid saturation.

    static __int8 x[NCoef+1]; //input samples
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];

    y[0] /= BCoef[0];
    
    return y[0] / DCgain;
}
