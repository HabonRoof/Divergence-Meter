void random_display() {
  random0 = random(10);
  random1 = random(10);
  random2 = random(10);
  random3 = random(10);
  random4 = random(10);
  random5 = random(10);
  random6 = random(10);
  random7 = random(10);
  tubeupdate(random0, random1, random2, random3, random4, random5, random6, random7);
}

void tubeupdate(int num0, int num1, int num2, int num3, int num4, int num5, int num6, int num7) {
  digitalWrite(tube_EN, LOW);
  if (tube == 0) {
    digitalWrite(tube_a, LOW);
    digitalWrite(tube_b, LOW);
    digitalWrite(tube_c, LOW);
    digitalWrite(tube_EN, HIGH);
    digit_update(num0);
  }
  if (tube == 1) {
    digitalWrite(tube_a, HIGH);
    digitalWrite(tube_b, LOW);
    digitalWrite(tube_c, LOW);
    digitalWrite(tube_EN, HIGH);
    digit_update(num1);
  }
  if (tube == 2) {
    digitalWrite(tube_a, LOW);
    digitalWrite(tube_b, HIGH);
    digitalWrite(tube_c, LOW);
    digitalWrite(tube_EN, HIGH);
    digit_update(num2);
  }
  if (tube == 3) {
    digitalWrite(tube_a, HIGH);
    digitalWrite(tube_b, HIGH);
    digitalWrite(tube_c, LOW);
    digitalWrite(tube_EN, HIGH);
    digit_update(num3);
  }
  if (tube == 4) {
    digitalWrite(tube_a, LOW);
    digitalWrite(tube_b, LOW);
    digitalWrite(tube_c, HIGH);
    digitalWrite(tube_EN, HIGH);
    digit_update(num4);
  }
  if (tube == 5) {
    digitalWrite(tube_a, HIGH);
    digitalWrite(tube_b, LOW);
    digitalWrite(tube_c, HIGH);
    digitalWrite(tube_EN, HIGH);
    digit_update(num5);
  }
  if (tube == 6) {
    digitalWrite(tube_a, LOW);
    digitalWrite(tube_b, HIGH);
    digitalWrite(tube_c, HIGH);
    digitalWrite(tube_EN, HIGH);
    digit_update(num6);
  }
  if (tube == 7) {
    digitalWrite(tube_a, HIGH);
    digitalWrite(tube_b, HIGH);
    digitalWrite(tube_c, HIGH);
    digitalWrite(tube_EN, HIGH);
    digit_update(num7);
  }
}



void digit_update(int num) {
  if (num == 0) {
    digitalWrite(digit_a, HIGH);
    digitalWrite(digit_b, LOW);
    digitalWrite(digit_c, LOW);
    digitalWrite(digit_d, HIGH);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 1) {
    digitalWrite(digit_a, LOW);
    digitalWrite(digit_b, LOW);
    digitalWrite(digit_c, LOW);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 2) {
    digitalWrite(digit_a, HIGH);
    digitalWrite(digit_b, LOW);
    digitalWrite(digit_c, LOW);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 3) {
    digitalWrite(digit_a, LOW);
    digitalWrite(digit_b, HIGH);
    digitalWrite(digit_c, LOW);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 4) {
    digitalWrite(digit_a, HIGH);
    digitalWrite(digit_b, HIGH);
    digitalWrite(digit_c, LOW);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 5) {
    digitalWrite(digit_a, LOW);
    digitalWrite(digit_b, LOW);
    digitalWrite(digit_c, HIGH);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 6) {
    digitalWrite(digit_a, HIGH);
    digitalWrite(digit_b, LOW);
    digitalWrite(digit_c, HIGH);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 7) {
    digitalWrite(digit_a, LOW);
    digitalWrite(digit_b, HIGH);
    digitalWrite(digit_c, HIGH);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 8) {
    digitalWrite(digit_a, HIGH);
    digitalWrite(digit_b, HIGH);
    digitalWrite(digit_c, HIGH);
    digitalWrite(digit_d, LOW);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 9) {
    digitalWrite(digit_a, LOW);
    digitalWrite(digit_b, LOW);
    digitalWrite(digit_c, LOW);
    digitalWrite(digit_d, HIGH);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
  }
  if (num == 10) {
    digitalWrite(digit_c, HIGH);
    digitalWrite(digit_d, HIGH);
    digitalWrite(PR, LOW);
    digitalWrite(PL, LOW);
    digitalWrite(PR, HIGH);
  }
  if (num == 11) {
    digitalWrite(digit_c, HIGH);
    digitalWrite(digit_d, HIGH);
    digitalWrite(PR, LOW);
    digitalWrite(PL, HIGH);
  }
}

/*
   Clock function
*/
void nixie_clock_yrdate() {
  // Devide the year and date data into digit data
  byte year10 = year / 10;
  byte year1 = year % 10;
  byte mon10 = mon / 10;
  byte mon1 = mon % 10;
  byte date10 = date / 10;
  byte date1 = date % 10;
  tubeupdate(2, 0, year10, year1, mon10, mon1, date10, date1);
}

void nixie_clock_time() {
  // Devide the time data into digit data
  byte hour10 = hour / 10;
  byte hour1 = hour % 10;
  byte minute10 = minute / 10;
  byte minute1 = minute % 10;
  byte second10 = second / 10;
  byte second1 = second % 10;
  if (second1 % 2 == 0)
    tubeupdate(hour10, hour1, 10, minute10, minute1, 10, second10, second1);
  if (second1 % 2 == 1)
    tubeupdate(hour10, hour1, 11, minute10, minute1, 11, second10, second1);
}
/*
   Divergence meter function can generate the random number of world divergence number
*/
void divergence_meter() {
  if (random_count < random_time) {
    random_display();
    random_count++;
    if (random_count == random_time) {
      random0 = random(2);  //1
      random1 = 10; //.
      //random2 = 0;  //0
      //random3 = 4;  //4
      //random4 = 8;  //8
      //random5 = 5;  //5
      //random6 = 9;  //9
      //random7 = 6;  //6
    }
  }
  tubeupdate(random0, random1, random2, random3, random4, random5, random6, random7);
}

void nixie_sleep(){
    digitalWrite(tube_a, LOW);
    digitalWrite(tube_b, LOW);
    digitalWrite(tube_c, LOW);
    digitalWrite(tube_EN, LOW);
}
