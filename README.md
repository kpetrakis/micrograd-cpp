### micrograd in C++

I try to implement karpathy's micrograd in C++ for practice!


###### Example run of 2 layer 8-8-1 MLP
Step: 0 loss: 1.69494, accuracy: 20% <br>
Step: 1 loss: 1.00028, accuracy: 31% <br>
Step: 2 loss: 0.949358, accuracy: 50% <br>
Step: 3 loss: 0.851974, accuracy: 50% <br>
Step: 4 loss: 0.706048, accuracy: 50% <br>
Step: 5 loss: 0.639069, accuracy: 83% <br>
Step: 6 loss: 0.536373, accuracy: 85% <br>
Step: 7 loss: 0.402353, accuracy: 86% <br>
Step: 8 loss: 0.298182, accuracy: 87% <br>
Step: 9 loss: 0.315564, accuracy: 89% <br>
Step: 10 loss: 0.311348, accuracy: 88% <br>
Step: 11 loss: 0.320842, accuracy: 87% <br>
Step: 12 loss: 0.246658, accuracy: 86% <br>
Step: 13 loss: 0.237696, accuracy: 87% <br>
Step: 14 loss: 0.235519, accuracy: 90% <br>
Step: 15 loss: 0.244908, accuracy: 86% <br>
Step: 16 loss: 0.276714, accuracy: 88% <br>
Step: 17 loss: 0.249269, accuracy: 86% <br>
Step: 18 loss: 0.2421, accuracy: 90% <br>
Step: 19 loss: 0.224199, accuracy: 89% <br>
Step: 20 loss: 0.215995, accuracy: 90% <br>
Step: 21 loss: 0.210066, accuracy: 92% <br>
Step: 22 loss: 0.203923, accuracy: 91% <br>
Step: 23 loss: 0.200478, accuracy: 91% <br>
Step: 24 loss: 0.197947, accuracy: 90% <br>
Step: 25 loss: 0.193018, accuracy: 92% <br>
Step: 26 loss: 0.18841, accuracy: 91% <br>
Step: 27 loss: 0.184846, accuracy: 92% <br>
Step: 28 loss: 0.181122, accuracy: 92% <br>
Step: 29 loss: 0.176024, accuracy: 91% <br>
Step: 30 loss: 0.174941, accuracy: 92% <br>
Step: 31 loss: 0.173682, accuracy: 91% <br>
Step: 32 loss: 0.174956, accuracy: 92% <br>
Step: 33 loss: 0.176583, accuracy: 91% <br>
Step: 34 loss: 0.195091, accuracy: 92% <br>
Step: 35 loss: 0.211774, accuracy: 91% <br>
Step: 36 loss: 0.18377, accuracy: 91% <br>
Step: 37 loss: 0.159204, accuracy: 92% <br>
Step: 38 loss: 0.15763, accuracy: 92% <br>
Step: 39 loss: 0.166506, accuracy: 91% <br>
Step: 40 loss: 0.154767, accuracy: 92% <br>
Step: 41 loss: 0.157146, accuracy: 91% <br>
Step: 42 loss: 0.147984, accuracy: 92% <br>
Step: 43 loss: 0.178355, accuracy: 92% <br>
Step: 44 loss: 0.205238, accuracy: 92% <br>
Step: 45 loss: 0.152895, accuracy: 92% <br>
Step: 46 loss: 0.146516, accuracy: 93% <br>
Step: 47 loss: 0.142961, accuracy: 93% <br>
Step: 48 loss: 0.137603, accuracy: 94% <br>
Step: 49 loss: 0.14312, accuracy: 94% <br>
Step: 50 loss: 0.143986, accuracy: 94% <br>
Step: 51 loss: 0.123757, accuracy: 96% <br>
Step: 52 loss: 0.117185, accuracy: 95% <br>
Step: 53 loss: 0.117355, accuracy: 96% <br>
Step: 54 loss: 0.110652, accuracy: 95% <br>
Step: 55 loss: 0.132552, accuracy: 95% <br>
Step: 56 loss: 0.182891, accuracy: 92% <br>
Step: 57 loss: 0.114845, accuracy: 95% <br>
Step: 58 loss: 0.107504, accuracy: 96% <br>
Step: 59 loss: 0.103055, accuracy: 95% <br>
Step: 60 loss: 0.111771, accuracy: 95% <br>
Step: 61 loss: 0.12288, accuracy: 94% <br>
Step: 62 loss: 0.090195, accuracy: 97% <br>
Step: 63 loss: 0.0839456, accuracy: 98% <br>
Step: 64 loss: 0.0784126, accuracy: 97% <br>
Step: 65 loss: 0.0765423, accuracy: 97% <br>
Step: 66 loss: 0.117848, accuracy: 95% <br>
Step: 67 loss: 0.172703, accuracy: 92% <br>
Step: 68 loss: 0.0807665, accuracy: 97% <br>
Step: 69 loss: 0.0881302, accuracy: 96% <br>
Step: 70 loss: 0.128591, accuracy: 94% <br>
Step: 71 loss: 0.0717506, accuracy: 97% <br>
Step: 72 loss: 0.0747145, accuracy: 99% <br>
Step: 73 loss: 0.100832, accuracy: 95% <br>
Step: 74 loss: 0.0568122, accuracy: 99% <br>
Step: 75 loss: 0.084437, accuracy: 96% <br>
Step: 76 loss: 0.121941, accuracy: 94% <br>
Step: 77 loss: 0.065987, accuracy: 97% <br>
Step: 78 loss: 0.0605365, accuracy: 99% <br>
Step: 79 loss: 0.0638692, accuracy: 97% <br>
Step: 80 loss: 0.0528699, accuracy: 99% <br>
Step: 81 loss: 0.0629503, accuracy: 97% <br>
Step: 82 loss: 0.0468782, accuracy: 99% <br>
Step: 83 loss: 0.0588301, accuracy: 97% <br>
Step: 84 loss: 0.0429974, accuracy: 99% <br>
Step: 85 loss: 0.0488495, accuracy: 99% <br>
Step: 86 loss: 0.0397187, accuracy: 99% <br>
Step: 87 loss: 0.0431709, accuracy: 99% <br>
Step: 88 loss: 0.0376012, accuracy: 99% <br>
Step: 89 loss: 0.0369537, accuracy: 99% <br>
Step: 90 loss: 0.0372922, accuracy: 99% <br>
Step: 91 loss: 0.0385725, accuracy: 99% <br>
Step: 92 loss: 0.0353084, accuracy: 99% <br>
Step: 93 loss: 0.0348558, accuracy: 99% <br>
Step: 94 loss: 0.0352834, accuracy: 99% <br>
Step: 95 loss: 0.0368459, accuracy: 99% <br>
Step: 96 loss: 0.0343866, accuracy: 99% <br>
Step: 97 loss: 0.0333703, accuracy: 99% <br>
Step: 98 loss: 0.0330998, accuracy: 99% <br>
Step: 99 loss: 0.0324869, accuracy: 99% <br>


#### TODO:
- add functionality in "dunder methods" like in the original implementation
 if isistance(other, value):
	 Maybe use templates in every operator overloading?? so that i have a single function for every operation! 

- I HAVE TO IMPLEMENT +=, *+ !!!

- For the MLP training 
	- Add L2 regularization in model parameters. 
	- Add batch functionality. 

 
