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
    //allume la tête du robot  : couleur RGB entre 0,0,0 et 255,255,255
    //(vous pouvez trouver des couleur sur https://htmlcolorcodes.com/fr/ ou https://www.rapidtables.com/web/color/RGB_Color.html)
    bot.AlumeTete(170, 15, 15); //rose
    bot.SecoueTete(2, 1500);
    bot.AlumeTete(120, 0, 220); //mauve
    delay(1000);
    bot.EteindTete();
  }


}
