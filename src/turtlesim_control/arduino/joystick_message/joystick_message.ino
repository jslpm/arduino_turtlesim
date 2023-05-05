#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>

// Pin mapping
int xPin = A0;
int yPin = A1;
int buttonPin = 2;

// State variables
unsigned int xJoystick = 0;
unsigned int yJoystick = 0;
bool buttonState;

// ROS node handle
ros::NodeHandle nh;

// ROS message and publisher
geometry_msgs::Twist cmd_msg;
ros::Publisher arduino_cmd("cmd_vel", &cmd_msg);

std_msgs::Bool button_state;
ros::Publisher arduino_button("button_state", &button_state);

// Function pre-definition
float linearTransform(float, float, float, float, float);
float linearTransformWithDeadZone(float, float, float, float, float, float, float);

void setup() {
  nh.initNode();
  nh.advertise(arduino_cmd);
  nh.advertise(arduino_button);

  while(!nh.connected()) {
    nh.spinOnce();
  }

  nh.loginfo("Startup complete!");
}

void loop() {
  // Read data from joystick
  xJoystick = analogRead(xPin);
  yJoystick = analogRead(yPin);

  // Scale x value
  float cmd_vel_x = linearTransformWithDeadZone(xJoystick, 0, -1, 500, 520, 1023, 1);
  float cmd_vel_y = linearTransformWithDeadZone(yJoystick, 0, -1, 510, 530, 1023, 1);

  cmd_msg.linear.x = cmd_vel_x;
  cmd_msg.angular.z = cmd_vel_y;

  button_state.data = digitalRead(buttonPin);

  arduino_cmd.publish(&cmd_msg);
  arduino_button.publish(&button_state);
  nh.spinOnce();
  delay(100);
}

float linearTransform(float x, float x1, float y1, float x2, float y2) {
  float m = (y2 - y1) / (x2 - x1);
  return m * (x - x1) + y1;  
}

float linearTransformWithDeadZone(float x, float x1, float y1, float deadx1, 
  float deadx2, float x2, float y2) {
  
  if ( x < deadx1 ) {
    return linearTransform(x, x1, y1, deadx1, 0);
  }
  else if ( x > deadx2 ) {
    return linearTransform(x, deadx2, 0, x2, y2);
  }
  else { //(x > deadx1 && x < deadx2)
    return 0;
  }
}
