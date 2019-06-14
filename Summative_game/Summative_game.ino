/*
  Summative game for Computer engineering, RPG game on lcd arduino using thumb stick
  by youssef Zayed
  Date 13/01/2018
*/

// include the library code:
#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int mouseButton = 6;
int IUP = A0, world = 1;
int ILR = A1;
int dmg;
int x = 0;
int y = 0;
int tune = 0;
int MID = 20;
int LRMID = 0;
int UPMID = 0;
int UD = 0;
int LR = 0;
int enemyDmg = 5;
int accuracy = 0;
boolean canMove = true, inMenu = false;
int whole = 1000, half = 500, quarter = 250, eighth = 125;
double a2s = 116.541;
double b2 = 123.471;
double c3s = 130.813;
double d3 = 146.832;
double f3s = 184.997;
double g3 = 195.998;
int playerHealth = 995;
int enemyHealth = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// make some custom characters:


byte guardRight[8] = {
  0b11000,
  0b00100,
  0b01000,
  0b11110,
  0b11101,
  0b11100,
  0b00010,
  0b00001
};

byte guardLeft [8] = {
  0b00011,
  0b00100,
  0b00010,
  0b01111,
  0b10111,
  0b00111,
  0b01000,
  0b10000
};


byte armsUp[8] = {
  0b10001,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b00100,
  0b01010,
  0b00100
};

byte townLeft[8] = {
  0b00001,
  0b00010,
  0b00100,
  0b01000,
  0b10100,
  0b10010,
  0b10010,
  0b10010
};
byte townCentre[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b10001
};
byte townRight[8] = {
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00101,
  0b01001,
  0b01001,
  0b01001
};
byte kingBottomRight[8] = {
  0b00001,
  0b00010,
  0b00100,
  0b11000,
  0b00100,
  0b00010,
  0b00001,
  0b00000
};
byte kingTopRight[8] = {
  0b00111,
  0b01000,
  0b10100,
  0b10000,
  0b11111,
  0b10000,
  0b01000,
  0b01000
};
byte kingTopLeft[8] = {
  0b10000,
  0b01000,
  0b11000,
  0b01000,
  0b01001,
  0b01010,
  0b00110,
  0b00010
};
byte kingBottomLeft[8] = {
  0b01000,
  0b00110,
  0b00010,
  0b00011,
  0b00100,
  0b01000,
  0b10000,
  0b10000
};

void setup() {


  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  pinMode(mouseButton, INPUT_PULLUP);

  // create a new characters
  lcd.createChar(4, armsUp);
  lcd.createChar(5, townLeft);
  lcd.createChar(6, townCentre);
  lcd.createChar(7, townRight);
  //read where the mid point of controller is
  LRMID = analogRead(ILR);
  UPMID = analogRead(IUP);
  // set the cursor to the top left
  lcd.setCursor(0, 0);

  // Print a message to the lcd.
  lcd.print("Battle Bones ");
  for (int i = 0; 10 > i; i++) {
    music();
    tune++;
  }
  lcd.clear();


}
//main game script
void loop() {
  UD = analogRead(IUP);
  LR = analogRead(ILR);
  //move player if allowed and player wants to move
  move();
  //trigger character interactions at these locations
  if (x == 15 && y == 0 && world == 1) {
    createMenu();
  }
  if ((x > 9 && x < 14) && y == 0 && world == 2) {
    createMenu();
  }
  if ((x > 10 && x < 13) && y == 0 && world == 4) {
    createMenu();
  }
  if (x > 10  && world == 6) {
    createMenu();
  }
  //enter fight scene if available
  fight();
  //play tune
  music();
  // enter next tune
  tune++;
}

//creates each scene in the game
void createWorld()
{
  switch (world) {
    case 1:
      lcd.setCursor(15, 0);
      lcd.write((byte)4);
      lcd.setCursor(0, 0);
      break;
    case 2:
      lcd.setCursor(10, 0);
      lcd.write((byte)5);
      lcd.setCursor(11, 0);
      lcd.write((byte)6);
      lcd.setCursor(12, 0);
      lcd.write((byte)7);
      break;
    case 4:
      lcd.createChar(1, guardLeft);
      lcd.createChar(2, guardRight);
      lcd.setCursor(11, 0);
      lcd.write((byte)1);
      lcd.setCursor(12, 0);
      lcd.write((byte)2);
      break;
    case 6:
      lcd.createChar(8, kingBottomLeft);
      lcd.createChar(9, kingTopLeft);
      lcd.createChar(10, kingBottomRight);
      lcd.createChar(11, kingTopRight);
      lcd.setCursor(11, 0);
      lcd.write((byte)11);
      lcd.setCursor(12, 0);
      lcd.write((byte)9);
      lcd.setCursor(11, 1);
      lcd.write((byte)8);
      lcd.setCursor(12, 1);
      lcd.write((byte)10);
      break;
  }

}

// method that plays music in the background
void music() {

  switch (tune) {

    case 0:
      tone(7, g3, eighth);
      delay(300);
      break;
    case 1:
      tone(7, g3, eighth);
      delay(300);
      break;
    case 2:
      tone(7, f3s, eighth);
      delay(300);
      break;
    case 3:
      tone(7, f3s, eighth);
      delay(300);
      break;
    case 4:
      tone(7, b2, quarter);
      delay(300);
      break;
    case 5:
      tone(7, d3, eighth);
      delay(200);
      break;
    case 6:
      tone(7, b2, half);
      delay(500);
      break;
    case 7:
      tone(7, b2, quarter);
      delay(300);
      break;
    case 8:
      tone(7, g3, eighth);
      delay(300);
      break;
    case 9:
      tone(7, g3, eighth);
      delay(300);
      break;
    case 10:
      tone(7, f3s, eighth);
      delay(300);
      break;
    case 11:
      tone(7, f3s, eighth);
      delay(300);
      break;
    case 12:
      tone(7, b2, half);
      delay(1000);
      break;
    case 13:
      tone(7, b2, eighth);
      delay(300);
      break;
    case 14:
      tone(7, g3, eighth);
      delay(300);
      break;
    case 15:
      tone(7, g3, eighth);
      delay(300);
      break;
    case 16:
      tone(7, f3s, eighth);
      delay(300);
      break;
    case 17:
      tone(7, f3s, eighth);
      delay(300);
      break;
    case 18:
      tone(7, b2, quarter);
      delay(300);
      break;
    case 19:
      tone(7, d3, eighth);
      delay(200);
      break;
    case 20:
      tone(7, b2, half);
      delay(500);
      break;
    case 21:
      tone(7, b2, eighth);
      delay(300);
      break;
    case 22:
      tone(7, c3s, eighth);
      delay(300);
      break;
    case 23:
      tone(7, d3, eighth);
      delay(300);
      break;
    case 24:
      tone(7, a2s, eighth);
      delay(300);
      break;
    case 25:
      tone(7, c3s, quarter);
      delay(300);
      break;
    case 26:
      tone(7, b2, half);
      delay(1000);
      break;
  }
  if (tune >= (27)) {
    tune = 0;
  }
}

//NPC dialog for interactions
void createMenu()
{
  String menu0[5] = {"\"Hello Traveler!\"", "\"You must have a bone to pick \"", "\"with skeleton   king\"", "\"Here HAVE THIS\"", "You got sword"};
  String menu1[8] = {"You arrive  in a small town", "an old fortress", "\"Come here lad\" ", "\"you look like a bad egg\"", "\"fight the       skeleton king?\"", "\"was that a     yoke?\"", "\"you shall fight me\"", "\"win and you can have my shield\""};
  String menu2[5] = {"\"I protect the  king\"", "\"stay on the straight and marrow\"", "\"go home\"", "\"not leaving huh\"", "\"WELL THEN\""};
  String menu3[2] = {"\"I am the king\"", "\"fight me for my crown\""};
  canMove = false;
  inMenu = true;
  switch (world)
  {
    case 1:
      for (int i = 0; i < 5; i++)
      {
        String line1 = "              ";
        String line2 = "               ";

        if (menu0[i].length() > 16)
        {
          line1 = menu0[i].substring(0, 16);
          line2 = menu0[i].substring(16);
        } else
        {
          line1 = menu0[i];
          line2 = "               ";
        }

        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
        for (int j = 0;  10 > j; j++ ) {
          music();
          tune++;
        }
        lcd.clear();
        x = 0; y = 1; world = 2;
        canMove = true;
        inMenu = false;
      }
      break;
    case 2:
      for (int i = 0; i < 8; i++)
      {
        String line1 = "              ";
        String line2 = "               ";

        if (menu1[i].length() > 16)
        {
          line1 = menu1[i].substring(0, 16);
          line2 = menu1[i].substring(16);
        } else
        {
          line1 = menu1[i];
          line2 = "               ";
        }

        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
        for (int j = 0; 10 > j; j++ ) {
          music();
          tune++;
        }
        lcd.clear();
        x = 0; y = 1; world = 3; enemyHealth = 25; playerHealth = 25; enemyDmg = 7; accuracy = 0;
        canMove = false;
        inMenu = false;
      }
      break;
    case 4:
      for (int i = 0; i < 5; i++)
      {
        String line1 = "              ";
        String line2 = "               ";

        if (menu2[i].length() > 16)
        {
          line1 = menu2[i].substring(0, 16);
          line2 = menu2[i].substring(16);
        } else
        {
          line1 = menu2[i];
          line2 = "               ";
        }

        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
        for (int j = 0;  10 > j; j++ ) {
          music();
          tune++;
        }
        lcd.clear();
        x = 0; y = 1; world = 5; accuracy = 0; enemyHealth = 30; playerHealth = 25; enemyDmg = 7;
        canMove = false;
        inMenu = false;
      }
      break;
    case 6:
      for (int i = 0; i < 5; i++)
      {
        String line1 = "              ";
        String line2 = "               ";

        if (menu3[i].length() > 16)
        {
          line1 = menu3[i].substring(0, 16);
          line2 = menu3[i].substring(16);
        } else
        {
          line1 = menu3[i];
          line2 = "               ";
        }

        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
        for (int j = 0;  10 > j; j++ ) {
          music();
          tune++;
        }
        lcd.clear();
        x = 0; y = 1; world = 7; accuracy = 0; enemyHealth = 40; playerHealth = 30; enemyDmg = 11;
        canMove = false;
        inMenu = false;
      }
      break;

  }

}

//fighting mechanic in game
void fight() {
  int listSize;
  if (world == 3 || world == 5 || world == 7) {
    if (enemyHealth <= 0 && world == 3 ) {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("You Win,go forth");
      lcd.setCursor(0, 1);
      lcd.print("take my shield");
      for (int j = 0; 10 > j; j++ ) {
        music();
        tune++;
      }
      lcd.clear();
      canMove = true;
      inMenu = false;
      world++;
    } else if (enemyHealth <= 0 && world == 5 ) {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("You Win,go forth");
      lcd.setCursor(0, 1);
      lcd.print("fight the king");
      for (int j = 0; 10 > j; j++ ) {
        music();
        tune++;
      }
      lcd.clear();
      canMove = true;
      inMenu = false;
      world++;
    } else if (enemyHealth <= 0 && world == 7 ) {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("You Win,go forth");
      lcd.setCursor(0, 1);
      lcd.print("claim the crown");
      for (int j = 0; 10 > j; j++ ) {
        music();
        tune++;
      }
      lcd.clear();
      lcd.print("hope you enjoyed");
      lcd.setCursor(0, 1);
      lcd.print("By:Youssef Zayed");
      lcd.setCursor(10, 1);
      lcd.write((byte)4);
      while (true) {
        music();
        tune++;
      }

    } else if (playerHealth <= 0) {
      playerHealth = 25;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You Lose");
      lcd.setCursor(0, 1);
      lcd.print(" TRY AGAIN");
      for (int j = 0; 10 > j; j++ ) {
        music();
        tune++;
      }
      canMove = true;
      inMenu = false;
      world--;
    } else {
      String hp = "your hp:" + (String)playerHealth;
      String enemyHp = "Enemy hp:" + (String)enemyHealth;
      String fightText[7] = {"man is fierce", hp, enemyHp, "sword swing ", "head strike", "focus", "shield UP"};
      if (world == 3) {
        listSize = 5;
      } else if (world == 5) {
        fightText[0] = "on guard";
        listSize = 6;
      } else if (world == 7) {
        fightText[0] = "To Death";
        listSize = 6;
      }
      lcd.setCursor(0, 0);
      lcd.print(fightText[y - 1]);
      lcd.setCursor(0, 1);
      lcd.print("->" + fightText[y]);
      if (digitalRead(mouseButton) == 0 )
      {
        switch (y) {
          case 3:
            if (random(0, 100) > (15 - accuracy)) {
              dmg = random(1, 500);
              enemyHealth -= dmg;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("you attacked");
              lcd.setCursor(0, 1);
              lcd.print((String)dmg + " damage done");
              for (int j = 0; 10 > j; j++ ) {
                music();
                tune++;
              }
            } else
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("you missed");
              lcd.setCursor(0, 1);
              lcd.print("NO damage done");
              for (int j = 0; 10 > j; j++ ) {
                music();
                tune++;
              }
            }
            break;
          case 4:
            if (random(0, 100) > (75 - accuracy)) {
              int dmg = random(0, 1);
              enemyHealth -= dmg;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Major attack");
              lcd.setCursor(0, 1);
              lcd.print((String)dmg + " damage done");
              for (int j = 0; 10 > j; j++ ) {
                music();
                tune++;
              }
            } else
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("you missed");
              lcd.setCursor(0, 1);
              lcd.print("NO damage done");
              for (int j = 0; 10 > j; j++ ) {
                music();
                tune++;
              }
            }
            break;
          case 5:
            dmg = random(5, 10);
            accuracy += dmg;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("mind focused");
            lcd.setCursor(0, 1);
            lcd.print((String)dmg + " focus gained");
            for (int j = 0; 10 > j; j++ ) {
              music();
              tune++;
            }
            break;
          case 6:
            int dmg = 2;
            if (enemyDmg > 5) {
              enemyDmg -= dmg;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("shield used");
            } else {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("shield use");
              lcd.setCursor(0, 1);
              lcd.print("diminished");
            }
            for (int j = 0; 10 > j; j++ ) {
              music();
              tune++;
            }
            break;

        }

        lcd.clear();
        int dmg = random(0, enemyDmg);
        playerHealth -= dmg;
        lcd.setCursor(0, 0);
        lcd.print("enemy attacked");
        lcd.setCursor(0, 1);
        lcd.print((String)dmg + " damage done");
        for (int j = 0; 10 > j; j++ ) {
          music();
          tune++;
        }
        lcd.clear();

      } else {
        if (UD < UPMID - MID) {
          y--;
          lcd.clear();
        }
        if (UD > UPMID + MID) {
          y++;
          lcd.clear();
        }
        if (y > listSize) {
          //makes sure player can't access special moves at times where they shoukd have
          y = listSize;
        } else if (y < 1) {
          y = 1;
        }
      }
    }

  }
}
//moves the player on the lcd
void move() {
  if (canMove) {
    if (UD < UPMID - MID) {
      y--;
      lcd.clear();
    }

    if (UD > UPMID + MID) {
      y++;
      lcd.clear();
    }
    // LEFT-RIGHT
    if (LR < LRMID - MID) {
      x++;
      lcd.clear();
    }
    if (LR > LRMID + MID) {
      x--;
      lcd.clear();
    }
    if (x > 15)
    {
      x = 15;
    }
    if (x < 0)
    {
      x = 0;
    }
    if (y > 1)
    {
      y = 1;
    }
    if (y < 0)
    {
      y = 0;
    }
    createWorld();
    lcd.setCursor(x, y);
    lcd.write((byte)4);

  }
}




