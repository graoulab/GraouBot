#include <GraouBotSphere.h>
//déclaration du robot
GraouBotSphere bot;

void setup() {
  //initialisation du robot
  bot.Init();

  //on commence par régler la position sortie du bras
  int sorti;
  bot.SortBras();

  while ( !bot.BoutonAppuye()); // on attend l'appuis sur le bouton
  delay(100); //anti rebond du bouton

  while (bot.BoutonAppuye()) // tant que le bouton du robot est appuyé
  {
    sorti = map(bot.LitPotentiometre(), 0, 1023, 0, 180); // on lit la valeur du potetionmètre et on la rededéfini entre 0 et 180
    bot.BougeBras(sorti); //
    delay(100);
  }

  //on régle la position rentrée du bras
  int rentre;
  bot.RentreBras();

  while ( !bot.BoutonAppuye()); // on attend l'appuis sur le bouton
  delay(100); //anti rebond du bouton

  while (bot.BoutonAppuye()) // tant que le bouton du robot est appuyé
  {
    rentre = map(bot.LitPotentiometre(), 0, 1023, 0, 180); // on lit la valeur du potetionmètre et on la rededéfini entre 0 et 180
    bot.BougeBras(rentre); //
    delay(100);
  }

  bot.DefinitValeursBras(rentre, sorti); //on stocke les valeurs dans le robot



}

void loop() {
  // put your main code here, to run repeatedly:
  bot.SortBras();
  delay(1000);
  bot.RentreBras();
  delay(1000);

}
