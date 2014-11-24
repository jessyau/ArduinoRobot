#include "line_sensors.h"
#define lightThresh 300

int init_lineTracker( struct line_tracker _newTracker ) {
    pinMode(_newTracker.left_pin, INPUT);
    pinMode(_newTracker.mid_pin, INPUT);
    pinMode(_newTracker.right_pin, INPUT);
    
    return 0;
}

int check_light( int light_pin ) {
    return analogRead( light_pin );
}

int is_turn( struct line_tracker tracker ) {
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

