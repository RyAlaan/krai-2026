void PID_init(){
  rodaFr.SetOutputLimits(-4095, 4095);
  rodaFl.SetOutputLimits(-4095, 4095);
  rodaBl.SetOutputLimits(-4095, 4095);
  rodaBr.SetOutputLimits(-4095, 4095);

  rodaFr.SetSampleTimeUs(10000);
  rodaFl.SetSampleTimeUs(10000);
  rodaBl.SetSampleTimeUs(10000);
  rodaBr.SetSampleTimeUs(10000);

  rodaFr.SetTunings(Kp1, Ki1, Kd1);
  rodaFl.SetTunings(Kp2, Ki2, Kd2);
  rodaBl.SetTunings(Kp3, Ki3, Kd3);
  rodaBr.SetTunings(Kp4, Ki4, Kd4);

  rodaFr.SetMode(rodaFr.Control::automatic);
  rodaFl.SetMode(rodaFl.Control::automatic);
  rodaBl.SetMode(rodaBl.Control::automatic);
  rodaBr.SetMode(rodaBr.Control::automatic);
}

void PID_compute(){
  rodaFr.Compute();
  rodaFl.Compute();
  rodaBl.Compute();
  rodaBr.Compute();
}

void PID_reset(){
  rodaFr.Reset();
  rodaFl.Reset();
  rodaBl.Reset();
  rodaBr.Reset();
}