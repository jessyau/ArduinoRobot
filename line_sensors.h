#ifndef line_sensors
#define line_sensors

#include <Arduino.h>

// Struct will be used to store references to line tracker pins
struct line_tracker {
  int left_pin;
  int mid_pin;
  int right_pin;
};

int init_lineTracker( struct line_tracker );
int check_light( int );
int is_target( struct line_tracker );
int is_left_target( struct line_tracker );
int is_right_target( struct line_tracker );

#endif


