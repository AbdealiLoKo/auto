#define MASTER              Serial

// Slave Pin chars
char MOTOR_1             = 3,
     MOTOR_2             = 2,
     MOTOR_PWM           = 9,
     PISTON_PIN          = 10,
     PP_PIN              = A0,
     HOME_TRIP           = A4, // -1 means no trip available
     MID_IR              = 12,
     HOME_TRIPPED        = LOW,
     MID_IR_FOUND        = LOW;


// Basic variables
#define HOME  2
#define MID   1

// MY HASH TABLE
#define COMM_END    '~'
#define CLOSE       'p'
#define OPEN        'o'
#define MOVE        'v'
#define MOVE_MID    'i'
#define MOVE_LADDER 'f'
#define DATA        'd'
#define EXTEND      'e'
#define SHRINK      's'
#define STOP        'q'


int home_trip = 0, mid_ir = 0;

void setup() {
  // Init serial
  Serial.begin(19200);
  MASTER.begin(19200);

  MASTER.println(F("Serial started"));

  // Pinmodes
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(PISTON_PIN, OUTPUT);
  pinMode(HOME_TRIP, INPUT);
  pinMode(MID_IR, INPUT);

  // Init state
  run(STOP, 255);
  piston(OPEN);
  digitalWrite(PP_PIN, LOW);

  // Init basic variables
  home_trip = mid_ir =  0;

  // Display initial values :
  update_home_trip();
  MASTER.print(F("SLAVE > home-trip : \t"));
  MASTER.println(home_trip);
  update_mid_ir();
  MASTER.print(F("SLAVE > mid-ir : \t"));
  MASTER.println(mid_ir);
  MASTER.print(COMM_END);
}

void loop() {
  slave_commands();

  while ( MASTER.available() )
    MASTER.read();
/*
  Serial.print("\tHOME_TRIP : ");
  Serial.print(digitalRead(HOME_TRIP));
  Serial.print("\tMID_IR : ");
  Serial.print(digitalRead(MID_IR));

  Serial.println(F("slave"));
  */

  delay(20);

}

