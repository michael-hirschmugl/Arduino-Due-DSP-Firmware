/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Band Pass
Filter model: Butterworth
Filter order: 1
Sampling Frequency: 44 KHz
Fc1 and Fc2 Frequencies: 1.000000 KHz and 2.000000 KHz
Coefficents Quantization: 8-bit

Z domain Zeros
z = -1.000000 + j 0.000000
z = 1.000000 + j 0.000000

Z domain Poles
z = 0.914062 + j -0.154482
z = 0.914062 + j 0.154482
***************************************************************/
#define NCoef 2
#define DCgain 16

__int8 iir(__int8 NewSample) {
    __int8 ACoef[NCoef+1] = {
          103,
            0,
         -103
    };

    __int8 BCoef[NCoef+1] = {
           64,
         -117,
           55
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
