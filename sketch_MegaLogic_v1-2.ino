int x = 3;
const int dbnc = 500;
unsigned long db22 = 0;
unsigned long db24 = 0;
unsigned long db26 = 0;
unsigned long db28 = 0;
unsigned long db30 = 0;
unsigned long db32 = 0;
unsigned long db33 = 0;
unsigned long db34 = 0;
unsigned long Ftime;
unsigned long Swdly = 0;
unsigned long OSdlyL = 0;
unsigned long OSdlyR = 0;
const int flashrate = 1000;
bool flash = true;
bool SwRev = false;
bool LblkOcc = false;
bool LappIN = false;
bool LadvappIN = false;
bool LappdivIN = false;
bool RblkOcc = false;
bool RappIN = false;
bool RadvappIN = false;
bool RappdivIN = false;
bool Osocc = false;
bool Lstop = false;
bool LstopTop = false;
bool LstopBot = false;
bool LflashYEL = false;
bool LflashRED = false;
bool Lappdiv = false;
bool Rstop = false;
bool RstopTop = false;
bool RstopBot = false;
bool RflashYEL = false;
bool RflashRED = false;
bool Rappdiv = false;
bool Llite = true;
bool LliteIN = true;
bool LliteBot = true;
bool Rlite = true;
bool RliteIN = true;
bool AliteFull = true;
bool AliteSP = true;
bool SpswDirR = false;
bool SpswDirL = false;
bool TumL = false;
bool TumR = false;
bool DirL = false;
bool DirR = false;
bool CTC = false;

void setup() {
  // put your setup code here, to run once:

// setup I/O pins:
  for (x = 19; x <= 53; x++) {
  pinMode (x, INPUT_PULLUP);
}
for (x = 2; x >= 13; x++) {
  pinMode (x, OUTPUT);
}
pinMode (23, OUTPUT);
pinMode (25, OUTPUT);
pinMode (27, OUTPUT);
pinMode (29, OUTPUT);
pinMode (31, OUTPUT);
pinMode (A7, INPUT_PULLUP);

digitalWrite (2, LOW);
digitalWrite (3, LOW);
digitalWrite (4, LOW);
digitalWrite (5, LOW);
digitalWrite (6, LOW);
digitalWrite (7, LOW);
digitalWrite (8, LOW);
digitalWrite (9, LOW);
digitalWrite (10, LOW);
digitalWrite (11, LOW);
digitalWrite (12, LOW);
digitalWrite (13, LOW);
digitalWrite (23, LOW);
digitalWrite (25, LOW);
digitalWrite (27, LOW);
digitalWrite (29, LOW);
digitalWrite (31, LOW);


}

void loop() {
  // put your main code here, to run repeatedly:
// master flasher:
  if (millis() - Ftime >= flashrate) {
    Ftime = millis();
    if (flash == false)
    flash = true;
    else
    flash = false;
  }
// delay Swpos:
if ((digitalRead(19) == true) || (digitalRead(20) == true) || (digitalRead(21) == true)) {
  SwRev = true;
  Swdly = millis();}
  else
  if (millis() - Swdly >= 2500) {
    SwRev = false;
  }

  // OS Occ Output:
  if (Osocc == false) {
    digitalWrite(23, LOW);
    digitalWrite(27, LOW);

  }

  if ((Osocc == true) && (SwRev == false)) {
    if (millis() - OSdlyL > 100) {
      digitalWrite(23, HIGH);
    }
  }
  else {
  OSdlyL = millis();
  }
  
  if ((Osocc == true) && ((SwRev == false) || (digitalRead(46) == false))) {
    if (millis() - OSdlyR > 100) {
      digitalWrite(27, HIGH);
      
    }
  }
  else {
  OSdlyR = millis();
  }

  // Directional latch:
  if ((LblkOcc == true) && (Osocc == true) && (DirL == false) && (SwRev == false) && (RblkOcc == false)) {
    DirR = true; 
   
  }

  if ((RblkOcc == true) && (Osocc == true) && (DirR == false) && (SwRev == false) && (LblkOcc == false)) {
    DirL = true;
    
  }

  if ((LappIN == false) && (LblkOcc == false) && (RblkOcc == false) && (RappIN == false)) {
    DirR = false;
    DirL = false;
   
  }

  if (SwRev == true) {
    DirL = false;
  }
  
   if ((digitalRead(44) == false) && (RappIN == true) && (DirR == false)) {
      TumL = true;
     
    }
    else
    TumL = false;

    if ((digitalRead(45) == false) && (LappIN == true)  && (DirL == false)) {
      TumR = true;
      
    }
    else
    TumR = false;

    // Set direction of spsw exit signals STOP

    if ((digitalRead(46) == false) && ((LappIN == true) || (LblkOcc == true))) {
      if (DirL == true) {
      SpswDirL = true;
     }}
    else
    SpswDirL = false;

    if ((digitalRead(46) == false) && (SwRev == false) && ((LappIN == true) || (LblkOcc == true))) {
      if (DirL == false) {
        SpswDirR = true;
      }}
    
    else
    SpswDirR = false;

    if ((SpswDirR == true) && (SpswDirL == true)) {
      SpswDirL = false;
    }

  // debounce left inputs:
 if (digitalRead(22) == LblkOcc) {
  db22 = millis();
 }
  if ((digitalRead(22) != LblkOcc) && ((millis() - db22) > dbnc)) {
    LblkOcc = digitalRead(22);
  }

   if (digitalRead(24) == LappIN) {
  db24 = millis();
 }
  if ((digitalRead(24) != LappIN) && ((millis() - db24) > dbnc)) {
    LappIN = digitalRead(24);  
  }

  if (digitalRead(26) == LadvappIN) {
  db26 = millis();
 }
  if ((digitalRead(26) != LadvappIN) && ((millis() - db26) > dbnc)) {
    LadvappIN = digitalRead(26);  
  }

  if (digitalRead(28) != LappdivIN) {
  db28 = millis();
 }
  if ((digitalRead(28) == LappdivIN) && ((millis() - db28) > dbnc)) {
    if (LappdivIN == true) { LappdivIN = false; 
  }else { LappdivIN = true; }
  }

  // debounce right inputs:
   if (digitalRead(30) == RblkOcc) {
  db30 = millis();
 }
  if ((digitalRead(30) != RblkOcc) && ((millis() - db30) > dbnc)) {
    RblkOcc = digitalRead(30);
  }

   if (digitalRead(32) == RappIN) {
  db32 = millis();
 }
  if ((digitalRead(32) != RappIN) && ((millis() - db32) > dbnc)) {
    RappIN = digitalRead(32);  
  }

  if (digitalRead(33) == RadvappIN) {
  db33 = millis();
 }
  if ((digitalRead(33) != RadvappIN) && ((millis() - db33) > dbnc)) {
    RadvappIN = digitalRead(33);  
  }

  if (digitalRead(34) != RappdivIN) {
  db34 = millis();
 }
  if ((digitalRead(34) == RappdivIN) && ((millis() - db34) > dbnc)) {
  if (RappdivIN == true) { RappdivIN = false; 
  }else { RappdivIN = true; }
  }

  if (digitalRead(35) == true) {
    Osocc = true;
  }
  else
  Osocc = false;

  if (digitalRead(A7) == false) {
    CTC = true;
  }
  else {CTC = false; }

  
  // Stop Logic left:
  if ((SpswDirL == true) || (RblkOcc == true) || (Osocc == true) || (digitalRead(36) == true) || (SwRev == true) || (digitalRead(37) == true) || (TumL == true)) {
    LstopTop = true;
    digitalWrite(25, HIGH);
  }
    else {
    LstopTop = false;
    digitalWrite(25, LOW);
  }
  if ((SpswDirR == true) || (RblkOcc == true) || (Osocc == true) || (digitalRead(36) == true) || (digitalRead(37) == true) || (TumL == true)) {
    LstopBot = true;
  }
    else {
    LstopBot = false;
  }
  if (((RadvappIN == true) && (digitalRead(49) == false) && (RappIN == false)) || ((RappdivIN == true) && (digitalRead(48) == false))) {
    LflashYEL = true;
  }
    else {
    LflashYEL = false;
  }
  if ((RappdivIN == true) && (digitalRead(47) == false)) {
    Lappdiv = true;
  }
    else {
    Lappdiv =false;
  }
  // Stop Ligic right:
  if ((LblkOcc == true) || (Osocc == true) || (digitalRead(39) == true) || (SwRev == true) || (digitalRead(40) == true) || (TumR == true)) {
    RstopTop = true;
    digitalWrite(29, HIGH);
  }
    else {
    RstopTop = false;
    digitalWrite(29, LOW);
  }
  if ((LblkOcc == true) || (Osocc == true) || (digitalRead(39) == true) || (SwRev == true) || (digitalRead(40) == true) || (TumR == true)) {
    RstopBot = true;
  }
    else {
    RstopBot = false;
  }
  if (((LadvappIN == true) && (digitalRead(52) == false) && (LappIN == false)) || ((LappdivIN == true) && (digitalRead(51) == false))) {
    RflashYEL = true;
  }
    else {
    RflashYEL = false;
  }
  if ((LappdivIN == true) && (digitalRead(40) == false)) {
    Rappdiv = true;
  }
    else {
    Rappdiv = false;
  }

  
  // Approach Lighting

  if ((digitalRead(42) == false) && (digitalRead(43) == true)) {
    AliteFull = false;
   
  }
  else AliteFull = true;

  if ((digitalRead(42) == true) && (digitalRead(43) == false)) {
    AliteSP = false;
  }
  else AliteSP = true;

 // Left Approach Lighting

 if (((AliteFull == false) && (LblkOcc == true)) || ((AliteSP == false) && ((LblkOcc == true) || (RblkOcc == true) || (RappIN == true)))) {
  LliteIN = true;
  Llite = true;
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
 }
 else {LliteIN =false;
 pinMode(38, INPUT_PULLUP);
 }

 if ((LliteIN == false) && ((AliteFull == false) || (AliteSP == false)) && (digitalRead(38) == false)) {
  Llite = true;
 }
 else if ((LliteIN == false) && (AliteFull == true) && (AliteSP == true)) {
  Llite = true; 
 }
 else if (LliteIN == false) {Llite = false;}

 if ((digitalRead(46) == true) && (CTC == false))  {
  LliteBot = Llite;
 }
 else if (digitalRead(53) == false) {
 LliteBot = Llite; 
 }
 else { LliteBot = true; }

 // Right Approach lighting
 
 if (((AliteFull == false) && (RblkOcc == true)) || ((AliteSP == false) && ((RblkOcc == true) || (LblkOcc == true) || (LappIN == true)))) {
  RliteIN = true;
  Rlite = true;
  pinMode(41, OUTPUT);
  digitalWrite(41, LOW);
 }
 else {RliteIN =false;
 pinMode(41, INPUT_PULLUP);
 }

 if ((RliteIN == false) && ((AliteFull == false) || (AliteSP == false)) && (digitalRead(41) == false)) {
  Rlite = true;
 }
 else if ((RliteIN == false) && (AliteFull == true) && (AliteSP == true)) {
  Rlite = true; 
 }
 else if (RliteIN == false) {Rlite = false;}

 
 
 // Left signal Lights Top:

if ((LstopTop == true) && (Llite == true) && (digitalRead(37) == false)) {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH); 
}

if ((LstopTop == false) && (LflashYEL == true) && (Llite == true)) {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  if(flash == true) {
    digitalWrite(3, HIGH);
  }
  else
  digitalWrite(3, LOW);  
  }
  

if ((digitalRead(37) == true) && (Llite == true)) {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  if(flash == true) {
    digitalWrite(4, HIGH);
  }
  else {
  digitalWrite(4, LOW);
  }
}



  if ((LstopTop == false) && (LflashYEL == false) && (RappIN == true) && (Llite == true)) {
   digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW); 
  }

  if ((LstopTop == false)  && (LflashYEL == false) && (RappIN == false) && (Llite == true)) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }

  if (Llite == false) {
  digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);  
  }

// Left signal lights Bottom:

if ((digitalRead(46) == true) && (Lappdiv == false) && (LliteBot == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

if ((digitalRead(46) == true) && (LstopTop == false) && (digitalRead(48) == true) && (Lappdiv == true) && (LliteBot == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

if ((digitalRead(46) == true) && (LstopBot == true) && (LliteBot == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

if ((digitalRead(46) == false) && (LstopBot == true) && (LliteBot == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

if ((digitalRead(46) == false) && (LstopBot == false) && (LflashYEL == true) && (LliteBot == true) && (digitalRead(46) == false) && (LappdivIN == false)) {
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  if(flash == true) {
    digitalWrite(6, HIGH);
  }
  else
  digitalWrite(6, LOW);  
  }

  if ((digitalRead(46) == false) && (LstopBot == false) && (LflashYEL == false) && (RappIN == true) && (LliteBot == true)) {
   digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW); 
  }

   if ((digitalRead(46) == false) && (LstopBot == false)  && (LflashYEL == false) && (RappIN == false) && (LliteBot == true)) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }

  if (LliteBot == false) {
  digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);  
  }


  // Right signal lights Top:
 if ((RstopTop == true) && (Rlite == true) && (digitalRead(40) == false)) {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH); 
}

if ((RstopTop == false) && (RflashYEL == true) && (Rlite == true)) {
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  if(flash == true) {
    digitalWrite(9, HIGH);
  }
  else
  digitalWrite(9, LOW);  
  }
  

if ((digitalRead(40) == true) && (Rlite == true)) {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  if(flash == true) {
    digitalWrite(10, HIGH);
  }
  else {
  digitalWrite(10, LOW);
  }
}



  if ((RstopTop == false) && (RflashYEL == false) && (LappIN == true) && (Rlite == true)) {
   digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW); 
  }

  if ((RstopTop == false)  && (RflashYEL == false) && (LappIN == false) && (Rlite == true)) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }

  if (Rlite == false) {
  digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);  
  }

  // Right Signal Lights Bottom:
if ((Rappdiv == false) && (Rlite == true)) {
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

if ((RstopTop == false) && (digitalRead(51) == true) && (Rappdiv == true) && (Rlite == true)) {
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

if ((RstopBot == true) && (Rlite == true)) {
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

if (Rlite == false) {
  digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);  
  }
  
 
}
