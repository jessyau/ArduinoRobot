#include "target_methods.h"
#include <LinkedList.h>

int col = 0;
int row = 0;
int targetNum = 0;


int track_position( struct target _Target, int turn, int target_left, int target_right ) {
  if ( turn == 1 ) {
    col++;
    
    Serial.print("Column count: ");
    Serial.println(col);
    
    if( target_right == 1 ) {
      row = 5;
      track_target( _Target, targetNum );
    } else if ( target_left == 1 ) {
        row = 4;
        track_target( _Target, targetNum );
    }
  } else if ( turn == 3) {
     col--;
     
     Serial.print("Column count: ");
     Serial.println(col);
     
     if( target_right == 1 ) {
       row = 3;
       track_target( _Target, targetNum );
       
     } else if( target_right == 1 ) {
       row = 2;
       track_target( _Target, targetNum );
     }
  } else if ( turn < 6 && turn > 4 ) {
     col++;
    if( target_right == 1 ) {
       row = 1;
       track_target( _Target, targetNum );
    }
  } 
  
  return 0;
}

int track_target( struct target _newTarget, int targetNum ) {
    _newTarget.row[targetNum] = row - 1;
    _newTarget.col[targetNum] = col + 1;
    targetNum++;
  
  return 0; 
}

int print_target ( struct target _Target ) {
  int i;
    for( i = 0; i < 5 && _Target.row[i] != 0; i++ ) {
      Serial.print( "There is a target at [ ");
      Serial.print( _Target.row[i] );
      Serial.print( ", ");
      Serial.print( _Target.col[i] );
      Serial.println( " ]" );
    }
    
    return 0;
}
