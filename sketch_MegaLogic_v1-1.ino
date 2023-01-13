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
unsigned long Swdly;
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
bool LtiteIN = true;
bool Rlite = true;
bool RliteIN = true;
bool SpswDirR = false;
bool SpswDirL = false;
bool TumL = false;
bool TumR = false;

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

 if (digitalRead(42) == false) {
  Llite = false;
  Rlite = false;
 }
 else {
 Llite = true;
 Rlite = true;
 }

 
 
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

if ((digitalRead(46) == true) && (Lappdiv == false) && (Llite == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

if ((digitalRead(46 == true) && (LstopTop == false) && (digitalRead(48) == true) && (Lappdiv == true) && Llite == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

if ((digitalRead(46) == true) && (LstopBot == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

if ((digitalRead(46) == false) && (LstopBot == true) && (Llite == true)) {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

if ((digitalRead(46) == false) && (LstopBot == false) && (LflashYEL == true) && (Llite == true) && (digitalRead(46) == false) && (LappdivIN == false)) {
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  if(flash == true) {
    digitalWrite(6, HIGH);
  }
  else
  digitalWrite(6, LOW);  
  }

  if ((digitalRead(46) == false) && (LstopBot == false) && (LflashYEL == false) && (RappIN == true) && (Llite == true)) {
   digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW); 
  }

   if ((digitalRead(46) == false) && (LstopBot == false)  && (LflashYEL == false) && (RappIN == false) && (Llite == true)) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }

  if (Llite == false) {
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

  if ((RstopTop == false)  && (RflashYEL == false) && (LappIN == false) && (Llite == true)) {
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

if ((RstopBot == true)) {
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

if (Llite == false) {
  digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);  
  }
  
 
}
