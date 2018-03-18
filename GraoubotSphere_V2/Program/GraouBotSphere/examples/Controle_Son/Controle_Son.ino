#include <GraouBotSphere.h>


//déclaration du robot
GraouBotSphere bot;

void setup() {
  //initialisation du robot
  bot.Init();
}


void loop() {
  if (bot.BoutonAppuye()) // si le bouton du robot est appuyé
  {
    bot.JoueSon(); //Joue le son défini dans la librairie
  }
}
