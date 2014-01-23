void ui() {

  if ( ! PC.available() )
    return;

  char c = PC.peek();

  if ( c == MY_CLAMP ) {
    // >>>>>>>>>>>>>> CODE FOR MY CLAMP !!!!!!!!!!!!!!!!!
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'r' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RESET
      if ( SLAVE ) Serial.print("Got R");
      PC.print(MY_CLAMP);
      PC.print("-motor moving to home trip switch ... ");
      go_home(HOME_SPEED);
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'w' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
      // Display initial values :
      if ( SLAVE ) Serial.print("Got W");
      PC.print(">>>>>>>>>> data for : ");
      PC.println(MY_CLAMP);
      PC.print("Trips - home : \t");
      PC.println(home_trip);
      PC.print("Trips - mid : \t");
      PC.println(middle_trip);
      PC.print("Trips - fixedclamp : \t");
      PC.println(fixedclamp_trip);
      PC.print("Trips - comm : \t");
      PC.println(comm_trip);
      PC.print("AVS Value : \t");
      PC.println(avs_value);
      PC.println(" >> begun");
      PC.print(PC_END);
    }
    else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      if ( SLAVE ) Serial.print("Got V");
      int vel = pc_get_int();
      PC.print(MY_CLAMP);
      PC.print("-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'f' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
      if ( SLAVE ) Serial.print("Got V");
      int vel = pc_get_int();
      PC.print(MY_CLAMP);
      PC.print("-motor moving (with fixed clamp) at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        if ( fixedclamp_trip ) {
          run ( STOP, 255 );
          PC.println("fixed clamp pressed");
          break;
        }
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        if ( SLAVE ) Serial.print("Got PC");
        PC.print("Closing piston  ");
        PC.println(MY_CLAMP);
        piston(CLOSE);
      }
      else {
        if ( SLAVE ) Serial.print("Got PO");
        PC.print("Opening piston ");
        PC.println(MY_CLAMP);
        piston(OPEN);
      }
      PC.print(PC_END);
    }
  }
  else if ( c == NEXT_CLAMP && SLAVE == 0 ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    delay(2);
    while (PC.available())
      NEXT.write(PC.read());
    listen();
  }

  if ( c == '4' ) {
    PC.read();
    NEXT.print(c);
    ladder () ;
  }

  q_stop();
}

