### micrograd in C++

I try to implement karpathy's micrograd in C++ for practice!


###### Example run of 2 layer 16-16-1 MLP with batch_size = 16 and regularization

Step: 0 loss: 0.998631, accuracy: 50% <br>
Step: 1 loss: 1.42631, accuracy: 62.5% <br>
Step: 2 loss: 0.523121, accuracy: 81.25% <br>
Step: 3 loss: 0.437246, accuracy: 81.25% <br>
Step: 4 loss: 0.581027, accuracy: 68.75% <br>
Step: 5 loss: 0.672871, accuracy: 68.75% <br>
Step: 6 loss: 0.237222, accuracy: 87.5% <br>
Step: 7 loss: 0.275604, accuracy: 87.5% <br>
Step: 8 loss: 0.035695, accuracy: 100% <br>
Step: 9 loss: 0.289272, accuracy: 93.75% <br>
Step: 10 loss: 0.229946, accuracy: 87.5% <br>
Step: 11 loss: 0.320241, accuracy: 81.25% <br>
Step: 12 loss: 0.226493, accuracy: 87.5% <br>
Step: 13 loss: 0.34053, accuracy: 87.5% <br>
Step: 14 loss: 0.309344, accuracy: 87.5% <br>
Step: 15 loss: 0.119552, accuracy: 93.75% <br>
Step: 16 loss: 0.144316, accuracy: 93.75% <br>
Step: 17 loss: 0.0698922, accuracy: 100% <br>
Step: 18 loss: 0.157142, accuracy: 87.5% <br>
Step: 19 loss: 0.33435, accuracy: 87.5% <br>
Step: 20 loss: 0.565561, accuracy: 81.25% <br>
Step: 21 loss: 0.262006, accuracy: 87.5% <br>
Step: 22 loss: 0.173924, accuracy: 93.75% <br>
Step: 23 loss: 0.39842, accuracy: 87.5% <br>
Step: 24 loss: 0.415999, accuracy: 81.25% <br>
Step: 25 loss: 0.277124, accuracy: 81.25% <br>
Step: 26 loss: 0.0793746, accuracy: 100% <br>
Step: 27 loss: 0.261445, accuracy: 93.75% <br>
Step: 28 loss: 0.0789688, accuracy: 93.75% <br>
Step: 29 loss: 0.089331, accuracy: 93.75% <br>
Step: 30 loss: 0.236404, accuracy: 87.5% <br>
Step: 31 loss: 0.209752, accuracy: 87.5% <br>
Step: 32 loss: 0.0173908, accuracy: 100% <br>
Step: 33 loss: 0.0729736, accuracy: 100% <br>
Step: 34 loss: 0.0993274, accuracy: 93.75% <br>
Step: 35 loss: 0.11403, accuracy: 93.75% <br>
Step: 36 loss: 0.154407, accuracy: 93.75% <br>
Step: 37 loss: 0.132819, accuracy: 93.75% <br>
Step: 38 loss: 0.11246, accuracy: 93.75% <br>
Step: 39 loss: 0.0114788, accuracy: 100% <br>
Step: 40 loss: 0.141832, accuracy: 93.75% <br>
Step: 41 loss: 0.0198907, accuracy: 100% <br>
Step: 42 loss: 0.170058, accuracy: 93.75% <br>
Step: 43 loss: 0.0266963, accuracy: 100% <br>
Step: 44 loss: 0.161301, accuracy: 93.75% <br>
Step: 45 loss: 0.0129771, accuracy: 100% <br>
Step: 46 loss: 0.0926244, accuracy: 93.75% <br>
Step: 47 loss: 0.154573, accuracy: 93.75% <br>
Step: 48 loss: 0.156265, accuracy: 100% <br>
Step: 49 loss: 0.0117459, accuracy: 100% <br>
Step: 50 loss: 0.0117433, accuracy: 100% <br>
Step: 51 loss: 0.0117407, accuracy: 100% <br>
Step: 52 loss: 0.142946, accuracy: 93.75% <br>
Step: 53 loss: 0.0918816, accuracy: 93.75% <br>
Step: 54 loss: 0.0230755, accuracy: 100% <br>
Step: 55 loss: 0.223324, accuracy: 87.5% <br>
Step: 56 loss: 0.0803141, accuracy: 93.75% <br>
Step: 57 loss: 0.127496, accuracy: 93.75% <br>
Step: 58 loss: 0.0643294, accuracy: 100% <br>
Step: 59 loss: 0.0118767, accuracy: 100% <br>
Step: 60 loss: 0.0118744, accuracy: 100% <br>
Step: 61 loss: 0.121067, accuracy: 93.75% <br>
Step: 62 loss: 0.127865, accuracy: 93.75% <br>
Step: 63 loss: 0.0140429, accuracy: 100% <br>
Step: 64 loss: 0.0118784, accuracy: 100% <br>
Step: 65 loss: 0.0297555, accuracy: 100% <br>
Step: 66 loss: 0.143731, accuracy: 100% <br>
Step: 67 loss: 0.0242111, accuracy: 100% <br>
Step: 68 loss: 0.064397, accuracy: 100% <br>
Step: 69 loss: 0.113047, accuracy: 93.75% <br>
Step: 70 loss: 0.175621, accuracy: 93.75% <br>
Step: 71 loss: 0.0310848, accuracy: 100% <br>
Step: 72 loss: 0.0119908, accuracy: 100% <br>
Step: 73 loss: 0.0119891, accuracy: 100% <br>
Step: 74 loss: 0.0944525, accuracy: 100% <br>
Step: 75 loss: 0.0381775, accuracy: 100% <br>
Step: 76 loss: 0.0570863, accuracy: 100% <br>
Step: 77 loss: 0.168127, accuracy: 93.75% <br>
Step: 78 loss: 0.042405, accuracy: 100% <br>
Step: 79 loss: 0.012034, accuracy: 100% <br>
Step: 80 loss: 0.0176918, accuracy: 100% <br>
Step: 81 loss: 0.0455499, accuracy: 100% <br>
Step: 82 loss: 0.0235499, accuracy: 100% <br>
Step: 83 loss: 0.0120331, accuracy: 100% <br>
Step: 84 loss: 0.0120319, accuracy: 100% <br>
Step: 85 loss: 0.0120307, accuracy: 100% <br>
Step: 86 loss: 0.0340633, accuracy: 100% <br>
Step: 87 loss: 0.0120384, accuracy: 100% <br>
Step: 88 loss: 0.0353821, accuracy: 100% <br>
Step: 89 loss: 0.0120451, accuracy: 100% <br>
Step: 90 loss: 0.0120441, accuracy: 100% <br>
Step: 91 loss: 0.0120432, accuracy: 100% <br>
Step: 92 loss: 0.0120423, accuracy: 100% <br>
Step: 93 loss: 0.0120415, accuracy: 100% <br>
Step: 94 loss: 0.0602868, accuracy: 100% <br>
Step: 95 loss: 0.0120507, accuracy: 100% <br>
Step: 96 loss: 0.0426617, accuracy: 100% <br>
Step: 97 loss: 0.0120495, accuracy: 100% <br>
Step: 98 loss: 0.0378732, accuracy: 100% <br>
Step: 99 loss: 0.0150766, accuracy: 100% <br>

#### TODO:
- add functionality in "dunder methods" like in the original implementation
 if isistance(other, value):
	 Maybe use templates in every operator overloading?? so that i have a single function for every operation! 

- I HAVE TO IMPLEMENT +=, *+ !!!

 
