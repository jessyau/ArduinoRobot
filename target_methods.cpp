#include "target_methods.h"
#include <LinkedList.h>

int col = 0;
int count = 0;
int row = 0;
int targetNum = 0;


int track_position() {
    col++; 
    
    
    
    Serial.print("Column count: ");
    Serial.println(col);

  
  return 0;
}

int track_target( struct target _newTarget, int targetNum ) {
    if( col < 6 ) {
      row = random(3,5);
    } else if( col < 11 ) {
      row = random(1,4);
    } else if( col > 10 ) {
      row = 1;
    }
    
    Serial.print( "[ " );
    Serial.print( row );
    
    _newTarget.row[targetNum] = row;
    
    if( col < 6 ) {
      _newTarget.col[targetNum] = col + 1;
      Serial.print( " , " );
      Serial.print( col + 1 );
      Serial.println( " ]");
    } else if( col > 5 && col < 11 ) {
      _newTarget.col[targetNum] = 5 - col % 5;
      Serial.print( " , " );
      Serial.print( (5 - col % 5) );
      Serial.println( " ]");
    } else if( col > 10 ) {
      _newTarget.col[targetNum] = col - 10;
      Serial.print( " , " );
      Serial.print( col - 9 );
      Serial.println( " ]");
    }
    
    
    
    
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

int get_col() {
  return col;
}
