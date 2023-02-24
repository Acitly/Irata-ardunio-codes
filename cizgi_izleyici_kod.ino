//bu kod irata aracimizin meb robotik ileri seviye cizgi izleyen robot yarismasinda kullanmasi uzerine, pistin belirtilen acilarina ve pistin yapisina ozel olarak yazdigim kod(farkli renkler, u seklindeki duvar, donulen o yuvarlak yerler.)
int left_motor = 6; // Pin for left motor
int right_motor = 5; // Pin for right motor
int left_sensor = A0; // Pin for left sensor
int right_sensor = A1; // Pin for right sensor
int front_sensor = A2; // Pin for front sensor
int bot_speed = 120; // Set the speed of the bot (range from 0-255)
int inside_turn_speed = 80; // Set the speed for inside turns
int outside_turn_speed = 120; // Set the speed for outside turns
int inside_turn_duration = 500; // Set the duration for inside turns (in milliseconds)
int outside_turn_duration = 1000; // Set the duration for outside turns (in milliseconds)
bool on_circular_road = false; // Set initial state of the bot

void move_forward(int duration) {
  digitalWrite(left_motor, HIGH); // Turn left motor on
  digitalWrite(right_motor, HIGH); // Turn right motor on
  delay(duration); // Move forward for the specified duration
}

void turn_left(int angle) {
  digitalWrite(left_motor, LOW); // Stop left motor
  digitalWrite(right_motor, HIGH); // Turn right motor on
  delay((long)(1000.0 * angle / 360.0)); // Delay for the appropriate amount of time to achieve the desired angle
}

void turn_right(int angle) {
  digitalWrite(left_motor, HIGH); // Turn left motor on
  digitalWrite(right_motor, LOW); // Stop right motor
  delay((long)(1000.0 * angle / 360.0)); // Delay for the appropriate amount of time to achieve the desired angle
}

void setup() {
  pinMode(left_motor, OUTPUT); // Set left motor pin as output
  pinMode(right_motor, OUTPUT); // Set right motor pin as output
  pinMode(left_sensor, INPUT); // Set left sensor pin as input
  pinMode(right_sensor, INPUT); // Set right sensor pin as input
  pinMode(front_sensor, INPUT); // Set front sensor pin as input
}

void loop() {
  int left_value = analogRead(left_sensor); // Read left sensor value
  int right_value = analogRead(right_sensor); // Read right sensor value
  int front_value = analogRead(front_sensor); // Read front sensor value

  if (front_value > 800) { // If front sensor detects a wall
    if (on_circular_road) { // If bot is on the circular road
      turn_left(108); // Turn left by 108 degrees
      move_forward(outside_turn_duration);
      turn_right(36); // Turn right by 36 degrees to align with the U-shaped transparent plexi wall
      on_circular_road = false; // Bot is no longer on the circular road
    } else if (left_value < 500 && right_value > 800) { // If left sensor detects black
      turn_right(36); // Turn right by 36 degrees
      move_forward();
    } else if (left_value > 800 && right_value < 500) { // If right sensor detects black
      turn_left(36); // Turn left by 36 degrees
      move_forward();
    } else { // If both sensors detect black or both sensors detect white
      move_forward();
    }
  } else { // If front sensor doesn't detect a wall
    if (!on_circular_

