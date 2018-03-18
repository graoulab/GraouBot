#include <GraouBotSphere.h>

// note : les positions du servo pour la rentrée et la sortie du bras sont stockées dans la mémoire EEPROM de l'Arduino
//        Il est possible des rélger avec l'exemple "Configure_Bras"

//déclaration du robot
GraouBotSphere bot;

void setup() {
  //initialisation du robot
  bot.Init();

  

}

void loop() {
  if (bot.BoutonAppuye()) // si le bouton du robot est appuyé
  {
    bot.SortBras(); //Sortie du bras
    bot.ClignoteLED(1000, 2); // la led clignote 2 fois, chaque cycle dure 1000ms (mille millisecondes) = 1s (une seconde)
    bot.RentreBras();//rentrée du bras
  }
}
