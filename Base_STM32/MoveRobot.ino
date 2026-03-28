void MoveRobot(){
  /*------------------------Sistem Rangka Bawah------------------------------*/
  Vx = control.vx * target_linear_speed;
  Vy = control.vy * target_linear_speed;
  Wr = control.Wr * target_angular_speed;
  kinec.invers_kin(Vx, Vy, Wr);

  if(control.cmd == 'i'){
    target_linear_speed = 5000;
    target_angular_speed = 3000;
    Kp1 = 0.7, Ki1 = 20, Kd1 = 0;
    Kp2 = 0.7, Ki2 = 20, Kd2 = 0;
    Kp3 = 0.7, Ki3 = 20, Kd3 = 0;
    Kp4 = 0.7, Ki4 = 20, Kd4 = 0;

  }else{
    target_linear_speed = 1800;
    target_angular_speed = 900; 
    Kp1 = 0.5, Ki1 = 20, Kd1 = 0;
    Kp2 = 0.5, Ki2 = 20, Kd2 = 0;
    Kp3 = 0.5, Ki3 = 20, Kd3 = 0;
    Kp4 = 0.5, Ki4 = 20, Kd4 = 0;
  }

  if(control.cmd == 'h'){
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 80);

  }else if (control.cmd == 'g'){
    analogWrite(rpwm, 80);
    analogWrite(lpwm, 0);
  }else{
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
  }

  rodaFr.SetTunings(Kp1, Ki1, Kd1);
  rodaFl.SetTunings(Kp2, Ki2, Kd2);
  rodaBl.SetTunings(Kp3, Ki3, Kd3);
  rodaBr.SetTunings(Kp4, Ki4, Kd4);


  if(prevL2 != control.cmd){
    if(control.cmd == 'j'){
      mirror = !mirror;
    }
    prevL2 = control.cmd;
  }
  if(mirror){
    rangkaBawah.Movement(constrain(kinec.Vw[2], -4095, 4095), constrain(kinec.Vw[3], -4095, 4095), constrain(kinec.Vw[0], -4095, 4095), constrain(kinec.Vw[1], -4095, 4095));
    // rangkaBawah.Movement(Output2, Output3, Output1, Output2);
  }else{
    rangkaBawah.Movement(constrain(kinec.Vw[0], -4095, 4095), constrain(kinec.Vw[1], -4095, 4095), constrain(kinec.Vw[2], -4095, 4095), constrain(kinec.Vw[3], -4095, 4095));
    // rangkaBawah.Movement(Output1, Output2, Output3, Output4);
  }
}
  
