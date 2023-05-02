/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature YELLOWY = vex::vision::signature (1, 73, 435, 254, -4513, -4283, -4398, 3.3, 0);
vex::vision::signature REDY = vex::vision::signature (2, 9253, 10161, 9707, -1187, -593, -890, 3, 0);
vex::vision::signature BLUEY = vex::vision::signature (3, -3277, -2393, -2836, 11881, 14399, 13140, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT5, 50, YELLOWY, REDY, BLUEY, SIG_5, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/