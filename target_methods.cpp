#include "target_methods.h"

int count = 0;
int col = 0;
int row = 0;
int targetNum = 0;


int track_position( struct target _Target, int is_target ) {
  if ( count < 6) {
    count++;
    col++;
    
    Serial.print("Column count: ");
    Serial.println(col);
    
    if( is_target == 1 ) {
      row = random(4,5);
      
      Serial.print("Registers target...row: ");
      Serial.println( row );
      
      track_target( _Target, targetNum );
    } 
    
  } else if ( count > 5 ) {
    count++;
    col--;
     
     Serial.print("Column count: ");
     Serial.println(col);
     
     if( is_target == 1 ) {
       row = random(2,3);
       
       Serial.print("Registers target...row: ");
       Serial.println( row );
       
       track_target( _Target, targetNum );
       
     } 
  } else if ( count > 9  ) {
    
     count++;
     col++;
     
    Serial.print("Column count: ");
    Serial.println(col);
     
    if( is_target == 1 ) {
       row = 1;
       
       Serial.print(" Registers target...row: ");
       Serial.println( row );
       
       track_target( _Target, targetNum );
    }
  } 
  
  return 0;
}

int get_col() {
  return col;
}

int track_target( struct target _newTarget, int targetNum ) {
    _newTarget.row[targetNum] = row;
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
