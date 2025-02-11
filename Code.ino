const int sensorPin = A0;   // Pin connected to MCP6004 output (Analog input)
const float vRef = 5;       // Arduino reference voltage (5V)
const float maxForce = 4.4; // Maximum force of FlexiForce sensor (N)
const float offsetVoltage = 1.25; // Reference voltage (-VREF)
const float sensorRange = 3.75;   // Voltage range of the sensor (1.25V - 5V)

float distance = 0.0; // Movement distance (mm)
const float motionPerSecond = 0.001; // Distance moved per second (mm)

void setup() {
  Serial.begin(9600); // Start serial monitor
}

void loop() {
  // 1. Read analog value (0~1023)
  int rawValue = analogRead(sensorPin);

  // 2. Convert analog value to voltage
  float voltage = rawValue * (vRef / 1023.0);

  // 3. Adjust for reference voltage (-VREF)
  voltage -= offsetVoltage; // Adjust for reference voltage
  if (voltage < 0) voltage = 0; // Prevent negative values

  // 4. Calculate force (Convert voltage to force)
  float force = (voltage / sensorRange) * maxForce; // 1.25V~5V -> 0~4.4N

  // 5. Calculate movement distance
  distance += motionPerSecond; // Increment by 1 micrometer per second

  // 6. Output results
  Serial.println(" mm"); // Print unit
  Serial.print("Raw Value: ");
  Serial.print(rawValue); // Print analog value
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2); // Print voltage (2 decimal places)
  Serial.print(" V | Force: ");
  Serial.print(force, 2); // Print force (2 decimal places)
  Serial.print(" N | Distance: ");
  Serial.print(distance, 2); // Print distance (2 decimal places)

  delay(1000); // Wait for 1 second
}