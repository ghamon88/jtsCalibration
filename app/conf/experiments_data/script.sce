stacksize(100000000)
//JTS_raw = fscanfMat('21_juillet\left_arm_J0_J3\dump_JTS\leftARM\raw\data.log')
//JTS_raw = fscanfMat('21_juillet\left_arm_J0_J3\idyn_torque\left_arm\data.log')
//JTS_raw = fscanfMat('21_juillet\left_arm_J1\dump_JTS\leftARM\raw\data.log')
//JTS_raw = fscanfMat('21_juillet\left_arm_J1\idyn_torque\left_arm\data.log')

//JTS_raw = fscanfMat('21_juillet\right_arm_J1\dump_JTS\rightARM\raw\data.log')
//JTS_raw = fscanfMat('21_juillet\right_arm_J0_J3_tau\idyn_torque\right_arm\data.log')
//JTS_raw = fscanfMat('21_juillet\right_arm_J1\idyn_torque\right_arm\data.log')
//JTS_raw = fscanfMat('offset_seeker\rightARM\raw\data.log')

//JTS_raw = fscanfMat('23_juillet\left_leg_J0_J3\dump_JTS\leftLowerLEG\raw\data.log')
//JTS_raw = fscanfMat('23_juillet\left_leg_J0_J3\dump_JTS\leftUpperLEG\raw\data.log')
//JTS_raw = fscanfMat('23_juillet\left_leg_J0_J3\idyn_torque\left_leg\data.log')

//JTS_raw = fscanfMat('23_juillet\right_leg_J0_J3\dump_JTS\rightLowerLEG\raw\data.log')
//JTS_raw = fscanfMat('23_juillet\right_leg_J0_J3\dump_JTS\rightUpperLEG\raw\data.log')
//JTS_raw = fscanfMat('23_juillet\right_leg_J0_J3\idyn_torque\right_leg\data.log')

//JTS_raw = fscanfMat('23_juillet\left_leg_J1\dump_JTS\leftUpperLEG\raw\data.log')
//JTS_raw = fscanfMat('23_juillet\left_leg_J1\idyn_torque\left_leg\data.log')

//JTS_raw = fscanfMat('23_juillet\right_leg_J1\dump_JTS\rightUpperLEG\raw\data.log')
//JTS_raw = fscanfMat('23_juillet\right_leg_J1\idyn_torque\right_leg\data.log')

//JTS_raw = fscanfMat('24_juillet\right_leg_J4\dump_JTS\rightLowerLEG\raw\data.log')
//JTS_raw = fscanfMat('24_juillet\right_leg_J4\idyn_torque\right_leg\data.log')

//JTS_raw = fscanfMat('24_juillet\left_leg_J4\dump_JTS\leftLowerLEG\raw\data.log')
//JTS_raw = fscanfMat('24_juillet\left_leg_J4\idyn_torque\left_leg\data.log')

//JTS_raw = fscanfMat('24_juillet\torso_J1\dump_JTS\torso\raw\data.log')
//JTS_raw = fscanfMat('24_juillet\torso_J1\idyn_torque\torso\data.log')

//JTS_raw = fscanfMat('24_juillet\torso_J2\dump_JTS\torso\raw\data.log')
//JTS_raw = fscanfMat('24_juillet\torso_J2\idyn_torque\torso\data.log')

JTS_raw_torso = fscanfMat('yoga_demo_final\dump_JTS\torso\raw\data.log')
JTS_calibrated_torso = fscanfMat('yoga_demo_final\dump_JTS\torso\calibrated\data.log')
JTS_idyn_torso = fscanfMat('yoga_demo_final\idyn_torque\torso\data.log')

JTS_raw_left_arm = fscanfMat('yoga_demo_final\dump_JTS\leftARM\raw\data.log')
JTS_calibrated_left_arm = fscanfMat('yoga_demo_final\dump_JTS\leftARM\calibrated\data.log')
JTS_idyn_left_arm = fscanfMat('yoga_demo_final\idyn_torque\left_arm\data.log')

JTS_raw_right_arm = fscanfMat('yoga_demo_final\dump_JTS\rightARM\raw\data.log')
JTS_calibrated_right_arm = fscanfMat('yoga_demo_final\dump_JTS\rightARM\calibrated\data.log')
JTS_idyn_right_arm = fscanfMat('yoga_demo_final\idyn_torque\right_arm\data.log')

JTS_raw_LUL = fscanfMat('yoga_demo_final\dump_JTS\leftUpperLEG\raw\data.log')
JTS_calibrated_LUL= fscanfMat('yoga_demo_final\dump_JTS\leftUpperLEG\calibrated\data.log')
JTS_idyn_left_leg = fscanfMat('yoga_demo_final\idyn_torque\left_leg\data.log')

JTS_raw_RUL = fscanfMat('yoga_demo_final\dump_JTS\rightUpperLEG\raw\data.log')
JTS_calibrated_RUL= fscanfMat('yoga_demo_final\dump_JTS\rightUpperLEG\calibrated\data.log')
JTS_idyn_right_leg= fscanfMat('yoga_demo_final\idyn_torque\right_leg\data.log')

JTS_raw_LLL = fscanfMat('yoga_demo_final\dump_JTS\leftLowerLEG\raw\data.log')
JTS_calibrated_LLL= fscanfMat('yoga_demo_final\dump_JTS\leftLowerLEG\calibrated\data.log')

JTS_raw_RLL = fscanfMat('yoga_demo_final\dump_JTS\rightLowerLEG\raw\data.log')
JTS_calibrated_RLL= fscanfMat('yoga_demo_final\dump_JTS\rightLowerLEG\calibrated\data.log')


JTS_raw_J2_torso = JTS_raw_torso(:,3); 
JTS_raw_J1_torso = JTS_raw_torso(:,4); 
JTS_calibrated_J2_torso = JTS_calibrated_torso(:,3); 
JTS_calibrated_J1_torso = JTS_calibrated_torso(:,4); 
JTS_idyn_J2_torso = JTS_idyn_torso(:,6); 
JTS_idyn_J1_torso = JTS_idyn_torso(:,5); 

JTS_raw_J0_left_arm = JTS_raw_left_arm(:,3); 
JTS_raw_J1_left_arm = JTS_raw_left_arm(:,4); 
JTS_raw_J3_left_arm = JTS_raw_left_arm(:,5); 
JTS_calibrated_J0_left_arm = JTS_calibrated_left_arm(:,3); 
JTS_calibrated_J1_left_arm = JTS_calibrated_left_arm(:,4); 
JTS_calibrated_J3_left_arm = JTS_calibrated_left_arm(:,5); 
JTS_idyn_J0_left_arm = JTS_idyn_left_arm(:,4); 
JTS_idyn_J1_left_arm = JTS_idyn_left_arm(:,5); 
JTS_idyn_J3_left_arm = JTS_idyn_left_arm(:,7); 

JTS_raw_J0_right_arm = JTS_raw_right_arm(:,3); 
JTS_raw_J1_right_arm = JTS_raw_right_arm(:,4); 
JTS_raw_J3_right_arm = JTS_raw_right_arm(:,5); 
JTS_calibrated_J0_right_arm = JTS_calibrated_right_arm(:,3); 
JTS_calibrated_J1_right_arm = JTS_calibrated_right_arm(:,4); 
JTS_calibrated_J3_right_arm = JTS_calibrated_right_arm(:,5); 
JTS_idyn_J0_right_arm = JTS_idyn_right_arm(:,4); 
JTS_idyn_J1_right_arm = JTS_idyn_right_arm(:,5); 
JTS_idyn_J3_right_arm = JTS_idyn_right_arm(:,7);


JTS_raw_J0_LUL = JTS_raw_LUL(:,3); 
JTS_raw_J1_LUL = JTS_raw_LUL(:,4); 
JTS_calibrated_J0_LUL = JTS_calibrated_LUL(:,3); 
JTS_calibrated_J1_LUL = JTS_calibrated_LUL(:,4); 
JTS_idyn_J0_left_leg = JTS_idyn_left_leg(:,4); 
JTS_idyn_J1_left_leg = JTS_idyn_left_leg(:,5); 

JTS_raw_J0_RUL = JTS_raw_RUL(:,3); 
JTS_raw_J1_RUL = JTS_raw_RUL(:,4); 
JTS_calibrated_J0_RUL = JTS_calibrated_RUL(:,3); 
JTS_calibrated_J1_RUL = JTS_calibrated_RUL(:,4); 
JTS_idyn_J0_right_leg = JTS_idyn_right_leg(:,4); 
JTS_idyn_J1_right_leg = JTS_idyn_right_leg(:,5); 

JTS_raw_J3_LLL = JTS_raw_LLL(:,3); 
JTS_raw_J4_LLL = JTS_raw_LLL(:,4); 
JTS_calibrated_J3_LLL = JTS_calibrated_LLL(:,3); 
JTS_calibrated_J4_LLL = JTS_calibrated_LLL(:,4); 
JTS_idyn_J3_left_leg = JTS_idyn_left_leg(:,7); 
JTS_idyn_J4_left_leg = JTS_idyn_left_leg(:,8); 

JTS_raw_J3_RLL = JTS_raw_RLL(:,3); 
JTS_raw_J4_RLL = JTS_raw_RLL(:,4); 
JTS_calibrated_J3_RLL = JTS_calibrated_RLL(:,3); 
JTS_calibrated_J4_RLL = JTS_calibrated_RLL(:,4); 
JTS_idyn_J3_right_leg = JTS_idyn_right_leg(:,7); 
JTS_idyn_J4_right_leg = JTS_idyn_right_leg(:,8); 

xset("window",1);// 3=vert(raw) 4=bleu ciel(calibrated) 5=rouge (idyn)
plot2d(JTS_raw_J2_torso, style=[3,3])
plot2d(JTS_calibrated_J2_torso, style=[4,3])
plot2d(JTS_idyn_J2_torso, style=[5,3])
xtitle('torso J2')
xset("window",2);
plot2d(JTS_raw_J1_torso, style=[3,3])
plot2d(JTS_calibrated_J1_torso, style=[4,3])
plot2d(JTS_idyn_J1_torso, style=[5,3])
xtitle('torso J1')
xset("window",3);
plot2d(JTS_raw_J0_left_arm, style=[3,3])
plot2d(JTS_calibrated_J0_left_arm, style=[4,3])
plot2d(JTS_idyn_J0_left_arm, style=[5,3])
xtitle('left arm J0')
xset("window",4);
plot2d(JTS_raw_J1_left_arm, style=[3,3])
plot2d(JTS_calibrated_J1_left_arm, style=[4,3])
plot2d(JTS_idyn_J1_left_arm, style=[5,3])
xtitle('left arm J1')
xset("window",5);
plot2d(JTS_raw_J3_left_arm, style=[3,3])
plot2d(JTS_calibrated_J3_left_arm, style=[4,3])
plot2d(JTS_idyn_J3_left_arm, style=[5,3])
xtitle('left arm J3')
xset("window",6);
plot2d(JTS_raw_J0_right_arm, style=[3,3])
plot2d(JTS_calibrated_J0_right_arm, style=[4,3])
plot2d(JTS_idyn_J0_right_arm, style=[5,3])
xtitle('right arm J0')
xset("window",7);
plot2d(JTS_raw_J1_right_arm, style=[3,3])
plot2d(JTS_calibrated_J1_right_arm, style=[4,3])
plot2d(JTS_idyn_J1_right_arm, style=[5,3])
xtitle('right arm J1')
xset("window",8);
plot2d(JTS_raw_J3_right_arm, style=[3,3])
plot2d(JTS_calibrated_J3_right_arm, style=[4,3])
plot2d(JTS_idyn_J3_right_arm, style=[5,3])
xtitle('right arm J3')
xset("window",9);
plot2d(JTS_raw_J0_RUL, style=[3,3])
plot2d(JTS_calibrated_J0_RUL, style=[4,3])
plot2d(JTS_idyn_J0_right_leg, style=[5,3])
xtitle('right leg J0')
xset("window",10);
plot2d(JTS_raw_J1_RUL, style=[3,3])
plot2d(JTS_calibrated_J1_RUL, style=[4,3])
plot2d(JTS_idyn_J1_right_leg, style=[5,3])
xtitle('right leg J1')
xset("window",11);
plot2d(JTS_raw_J3_RLL, style=[3,3])
plot2d(JTS_calibrated_J3_RLL, style=[4,3])
plot2d(JTS_idyn_J3_right_leg, style=[5,3])
xtitle('right leg J3')
xset("window",12);
plot2d(JTS_raw_J4_RLL, style=[3,3])
plot2d(JTS_calibrated_J4_RLL, style=[4,3])
plot2d(JTS_idyn_J4_right_leg, style=[5,3])
xtitle('right leg J4')
xset("window",13);
plot2d(JTS_raw_J0_LUL, style=[3,3])
plot2d(JTS_calibrated_J0_LUL, style=[4,3])
plot2d(JTS_idyn_J0_right_leg, style=[5,3])
xtitle('left leg J0')
xset("window",14);
plot2d(JTS_raw_J1_LUL, style=[3,3])
plot2d(JTS_calibrated_J1_LUL, style=[4,3])
plot2d(JTS_idyn_J1_left_leg, style=[5,3])
xtitle('left leg J1')
xset("window",15);
plot2d(JTS_raw_J3_LLL, style=[3,3])
plot2d(JTS_calibrated_J3_LLL, style=[4,3])
plot2d(JTS_idyn_J3_left_leg, style=[5,3])
xtitle('left leg J3')
xset("window",16);
plot2d(JTS_raw_J4_LLL, style=[3,3])
plot2d(JTS_calibrated_J4_LLL, style=[4,3])
plot2d(JTS_idyn_J4_left_leg, style=[5,3])
xtitle('left leg J4')


