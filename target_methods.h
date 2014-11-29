#ifndef target_methods
#define target_methods

#include <Arduino.h>

struct target {
  int row[5];
  int col[5];
};

int track_position( );
int track_target( struct target, int );

#endif
