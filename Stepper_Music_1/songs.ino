void playSong(String songFile, long userTempo){
  if (songFile == "Song of Storms"){
    long tempo;
    if (userTempo == 0){
      tempo = 250;
    } 
    else {
      tempo = userTempo;
    }
    /* Note Lenghts:
     62.5 - Sixteenth
     125 - Eight
     250 - Quarter
     500 - Half
     1000 - Whole */
    playNote(NOTE_Re2, 250, tempo);
    playNote(NOTE_La3, 250);
    playNote(NOTE_La3, 250);
    playNote(NOTE_Mi2, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Si3, 500);

    playNote(NOTE_Fa3, 250);
    playNote(NOTE_Do4, 250);
    playNote(NOTE_Do4, 250);
    playNote(NOTE_Mi2, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Si3, 500);

    playNote(NOTE_Re2, 250);
    playNote(NOTE_La3, 250);
    playNote(NOTE_La3, 250);
    playNote(NOTE_Mi2, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Si3, 500);

    playNote(NOTE_Fa3, 250);
    playNote(NOTE_Do4, 250);
    playNote(NOTE_Do4, 250);
    playNote(NOTE_Mi2, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Si3, 500);

    playNote(NOTE_Re3, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Re4, 500);
    playNote(NOTE_Re3, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Re4, 500);

    playNote(NOTE_Mi4, 375);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_La3, 500);

    playNote(NOTE_La3, 250);
    playNote(NOTE_Re3, 250);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Sol3, 125);
    playNote(NOTE_La3, 750);

    playNote(NOTE_La3, 250);
    playNote(NOTE_Re3, 250);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Sol3, 125);
    playNote(NOTE_Mi3, 750);

    playNote(NOTE_Re3, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Re4, 500);
    playNote(NOTE_Re3, 125);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Re4, 500);

    playNote(NOTE_Mi4, 375);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_La3, 500);

    playNote(NOTE_La3, 250);
    playNote(NOTE_Re3, 250);
    playNote(NOTE_Fa3, 125);
    playNote(NOTE_Sol3, 125);
    playNote(NOTE_La3, 500);
    playNote(NOTE_La3, 250);
    playNote(NOTE_Re3, 500);
  }
  else if(songFile == "Can Can"){
    long tempo;
    if (userTempo == 0){
      tempo = 180;
    } 
    else {
      tempo = userTempo;
    }
    /* Note Lenghts:
     62.5 - Sixteenth
     125 - Eight
     250 - Quarter
     500 - Half
     1000 - Whole */
    playNote(NOTE_Do4, 250, tempo);
    playNote(NOTE_Do4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 250);

    playNote(NOTE_Sol4, 125);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 250);

    playNote(NOTE_Re4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Do4, 125);

    playNote(NOTE_Do5, 125);
    playNote(NOTE_Si4, 125);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Re4, 125);

    playNote(NOTE_Do4, 250);
    playNote(NOTE_Do4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 250);

    playNote(NOTE_Sol4, 125);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 250);

    playNote(NOTE_Re4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Do4, 250);
  }
  else if(songFile == "He's a Pirate"){
    long tempo;
    if (userTempo == 0){
      tempo = 260;
    } 
    else {
      tempo = userTempo;
    }
    /* Note Lenghts:
     62.5 - Sixteenth
     125 - Eight
     250 - Quarter
     500 - Half
     1000 - Whole */
    playNote(NOTE_Re4, 250, tempo);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_La3, 125);
    playNote(NOTE_Do4, 125);
    
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Sol4, 125);
    
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_Re4, 375);
    playNote(NOTE_La3, 125);
    playNote(NOTE_Do4, 125);
    
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Sol4, 125);
    
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_Re4, 500);
    playNote(NOTE_La3, 125);
    playNote(NOTE_Do4, 125);
    
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 250);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_La4, 125);
    
    playNote(NOTE_LaS4, 250);
    playNote(NOTE_LaS4, 250);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Re4, 375);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Mi4, 125);
    
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Re4, 375);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Fa4, 125);
    
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Mi4, 500);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Do5, 125);
    
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Sol5, 125);
    
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Do5, 125);
    playNote(NOTE_Do5, 125);
    playNote(NOTE_Re5, 375);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Do5, 125);
    
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Sol5, 125);
    
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Do5, 125);
    playNote(NOTE_Re5, 500);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Do5, 125);
    
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_Sol5, 125);
    playNote(NOTE_La5, 125);
    
    playNote(NOTE_LaS5, 250);
    playNote(NOTE_LaS5, 250);
    playNote(NOTE_La5, 125);
    playNote(NOTE_Sol5, 125);
    playNote(NOTE_La5, 125);
    playNote(NOTE_Re5, 375);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_La5, 125);
    playNote(NOTE_Re5, 375);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Fa5, 125);
    
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Do5, 125);
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Mi5, 250);
    
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_La5, 500);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Re5, 125);
    
    playNote(NOTE_La4, 750);
    playNote(NOTE_LaS5, 500);
    playNote(NOTE_Sol5, 125);
    playNote(NOTE_Re5, 125);
    
    playNote(NOTE_LaS4, 750);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Fa4, 375);
    playNote(NOTE_Sol4, 500);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Sol4, 125);
    
    playNote(NOTE_La4, 250);
    playNote(NOTE_La4, 250);
    playNote(NOTE_La4, 250);
    playNote(NOTE_LaS4, 125);
    playNote(NOTE_La4, 625);
    
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_La4, 625);
    
    playNote(NOTE_La4, 250);
    playNote(NOTE_La4, 250);
    playNote(NOTE_La4, 250);
    playNote(NOTE_LaS4, 125);
    playNote(NOTE_La4, 625);
    
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Re4, 500);
    playNote(NOTE_Re4, 125);
    playNote(NOTE_Mi4, 125);
    
    playNote(NOTE_Fa4, 500);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_La4, 125);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Mi4, 250);
    
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Sol4, 250);
    playNote(NOTE_La4, 250);
    playNote(NOTE_Sol4, 500);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Sol4, 125);
    
    playNote(NOTE_La4, 500);
    playNote(NOTE_Sol4, 125);
    playNote(NOTE_Fa4, 125);
    playNote(NOTE_Mi4, 250);
    playNote(NOTE_Fa4, 250);
    playNote(NOTE_Mi4, 250);
    
    playNote(NOTE_Re4, 500);
    playNote(NOTE_Mi4, 125);
    playNote(NOTE_Do4, 125);
    playNote(NOTE_Re4, 500);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    
    playNote(NOTE_Fa5, 500);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Sol5, 250);
    
    playNote(NOTE_La5, 250);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Re5, 500);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Sol5, 250);
    playNote(NOTE_La5, 250);
    playNote(NOTE_LaS5, 250);
    playNote(NOTE_Re5, 250);
    playNote(NOTE_Sol5, 250);
    
    playNote(NOTE_Fa5, 500);
    playNote(NOTE_Sol5, 125);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Re5, 500);
    
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Do5, 125);
    playNote(NOTE_La5, 750);
    playNote(NOTE_LaS5, 750);
    playNote(NOTE_La5, 250);
    playNote(NOTE_La5, 250);
    playNote(NOTE_La5, 250);
    
    playNote(NOTE_La5, 125);
    playNote(NOTE_Sol5, 625);
    playNote(NOTE_Sol5, 750);
    
    playNote(NOTE_Fa5, 750);
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Mi5, 250);
    
    playNote(NOTE_Re5, 375);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_La5, 375);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Fa5, 125);
    
    playNote(NOTE_LaS5, 375);
    playNote(NOTE_Re5, 125);
    playNote(NOTE_Mi5, 125);
    playNote(NOTE_Fa5, 125);
    playNote(NOTE_La5, 250);
    playNote(NOTE_La5, 250);
    playNote(NOTE_Do6, 250);
    
    playNote(NOTE_La5, 125);
    playNote(NOTE_Sol5, 625);
    playNote(NOTE_Sol5, 750);
 
    playNote(NOTE_Fa5, 750);
    playNote(NOTE_Mi5, 250);
    playNote(NOTE_Fa5, 250);
    playNote(NOTE_Mi5, 250);
    
    playNote(NOTE_Re5, 750);
    playNote(NOTE_Re4, 1000);
  }
}
