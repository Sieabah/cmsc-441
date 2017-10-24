## CMSC Project 1 Report

### Psudocode

#### 4-multiply

    let z1, z2, result be complex numbers
    r1 = z1.real * z2.real
    r2 = z1.imaginary * z2.imaginary
    
    i1 = z1.real * z2.imaginary
    i2 = z2.imaginary * z2.real
    
    result.real = r1 - r2
    result.imaginary = i1 + i2

#### 3-multiply

    let z1, z2, result be complex numbers
    t = (z1.real + z1.imaginary) * (z2.real + z2.imaginary)
    r = z1.real * z2.real
    s = z1.imaginary * z2.imaginary
    
    result.real = r - s
    result.imaginary = t - r - s
    
### Time Analysis

All lengths will be tried against 50 pairs of numbers

*50 8-bit*

Method | Trial, Time

- CMUL4
    
Mean: 0.0001851
Std Dev: 2.7449 E-5

- CMUL3 

    
Mean: 0.00020416
Std Dev: 4.8762 E-5

*50 8-bit*

cmul4 0.00013144 2.139616597354181e-06
cmul3 0.00013267999999999998 1.2845137251910088e-05

*50 10-bit*

cmul4 0.00013516 6.041894553525275e-06
cmul3 0.00013694 1.0116484829530585e-05

*50 20-bit*

cmul4 0.00016426 1.18989109431348e-05
cmul3 0.00015854 1.293344028288763e-05

*50 30-bit*

cmul4 0.00019176 8.828432731226758e-06
cmul3 0.00017888 6.258512570238776e-06

*50 40-bit*

cmul4 0.00020176 1.2011151281290262e-05
cmul3 0.00019098 2.0468482491630987e-05

*50 100-bit*

cmul4 0.0005741 0.00016098539038797075
cmul3 0.00050008 0.00011840639806210142

*50 200-bit*

cmul4 0.00143554 0.0001250397830569886
cmul3 0.00115614 0.00011236311581617148






