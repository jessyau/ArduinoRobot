#include "line_sensors.h"
#define lightThresh 300

// Initializes line tracker pins for input
int init_lineTracker( struct line_tracker _newTracker ) {
    pinMode(_newTracker.left_pin, INPUT);
    pinMode(_newTracker.mid_pin, INPUT);
    pinMode(_newTracker.right_pin, INPUT);
    
    return 0;
}

// Checks analog value from referenced line tracker pin
int check_light( int light_pin ) {
    return analogRead( light_pin );
}

// If line tracker detects black on all 3 sensors, will return 1 to signify that it is a turn
int is_target( struct line_tracker tracker ) {
    if( check_light( tracker.left_pin ) < lightThresh && check_light( tracker.mid_pin ) < lightThresh && check_light( tracker.right_pin ) < lightThresh ) 
        return 1;
    else 
        return 0;
}

int is_left_target( struct line_tracker tracker ) {
    if( check_light( tracker.left_pin ) < lightThresh && check_light( tracker.mid_pin ) < lightThresh )
        return 1;
    else
        return 0;
}

int is_right_target( struct line_tracker tracker ) {
    if( check_light( tracker.right_pin ) < lightThresh && check_light( tracker.mid_pin ) < lightThresh )
        return 1;
    else
        return 0;
}
