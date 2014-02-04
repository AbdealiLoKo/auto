void polewalk() {

  PC.print(F("............. Pole Walk start "));

  // move both motors to middle
  PC.println(F("Right clamp needs to go to the middle position."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE_MID);
  SLAVE.print(255);
  listen();
  
  PC.println(F("Left clamp needs to go to middle now."));
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
  }
  
  // clamp right piston
  PC.println(F("Need to clamp right poston to the second pole."));
  QUIT_OR_CONTINUE;
  SLAVE.print(CLOSE);
  
  // move left to extreme, move right to extreme
  PC.println(F("Need to move left clamp to the extreme."));
  QUIT_OR_CONTINUE;
  while(SLAVE.available()) SLAVE.read();
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  listen();
  
  PC.println(F("Need to move right clamp to the extreme."));
  QUIT_OR_CONTINUE;
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  
  
  // clamp left
  PC.println(F("Left clamp needs to be clamped now."));
  QUIT_OR_CONTINUE;
  piston(CLOSE);
  delay(500);
  SLAVE.print(OPEN);
  
  // move right to middle and left to middle
  PC.println(F("Right clamp needs to go to the middle position."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE_MID);
  SLAVE.print(255);
  listen();
  
  PC.println(F("Left clamp needs to go to middle now."));
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
  }
  Serial.println(F("Right clamp needs to clamp now"));
  QUIT_OR_CONTINUE;
  SLAVE.print(CLOSE);
  Serial.println(F("Both clamps need to unclamp now"));
  QUIT_OR_CONTINUE;
  piston(OPEN);
  SLAVE.print(OPEN);
 
 
  
  PC.println(F("Polewalk completed .... "));
  
}
