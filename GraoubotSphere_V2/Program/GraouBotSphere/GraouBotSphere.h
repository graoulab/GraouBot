/**********************************************
** librairie de pilotage du GraouBotSphere
**
** Le son utilise le tutoriel Arduino toneMelody (http://www.arduino.cc/en/Tutorial/Tone)
** La LED RGB est pilotée par la librairie Adafruit_NeoPixel (https://github.com/adafruit/Adafruit_NeoPixel)
**
** created 06 March 2018
** by Régis GRASSE
** For the Groulab - Fablab in Metz - France
** 
** GraouBotSphere is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as
** published by the Free Software Foundation, either version 3 of
** the License, or (at your option) any later version.
** 
** GraouBotSphere is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public
** License along with GraouBotSphere.  If not, see
** <http://www.gnu.org/licenses/>.
**************************************************/

#ifndef GRAOUBOT_SPHERE_H
#define GRAOUBOT_SPHERE_H

#include "includes\pitches.h"
#include "includes\Adafruit_NeoPixel.h"

#include <Servo.h>
#include <EEPROM.h>

#define PIN_BOUTON 2
#define PIN_LED_BRAS 5
#define PIN_SERVO_BRAS 9
#define PIN_SERVO_TETE 10
#define PIN_BUZZER 3
#define PIN_LED_RGB 6

#define PIN_POTENTIOMETRE A4
#define PIN_PHOTO_R1 A0
#define PIN_PHOTO_R2 A1
#define PIN_PHOTO_R3 A2
#define PIN_PHOTO_R4 A3

#define NUMPIXELS      1

#define ADRESSE_EEPROM_BRAS_MIN 0
#define ADRESSE_EEPROM_BRAS_MAX 2


class GraouBotSphere
{
	public :
	GraouBotSphere();
	~GraouBotSphere();
		
	void Init();
	
	// bouton
	bool BoutonAppuye();
	
	// controles de la Tete
	void SecoueTete(int nombreDeFois,int vitesse);
	void BougeTete(int angle);
	void AlumeTete(uint8_t r,uint8_t g,uint8_t b);
	void EteindTete();
	
	// controles du bras
	void SortBras();
	void RentreBras();
	void AllumeLED();
	void EteindLED();
	void ClignoteLED(int duree, int nombreClignotements);
	void DefinitValeursBras(char rentre, char sorti);
	void BougeBras(int position);
	
	// sons
	void JoueSon();
	void DefiniSons(int *notes, int *durees, int nombreNotes);
	
	//capteurs lumiere
	void InitSuivit();
	void LoopSuitLumiere();
	void LoopSuitOmbre();
	void Litvaleurs(int valeurs[4]);

	//potentiometre
	int LitPotentiometre();
	
	private :
	Adafruit_NeoPixel *ledTete;
	Servo servoTete; 
	Servo servoBras; 
	
	int *melody;
	int *noteDurations;
	int nbNotes;
	
	int posBrasSorti;
	int posBrasRentre;
	
	
	//capteurs de lumiere
	int valeurCapteurs[4];
	int valeurCMoyen;
	int triCapteurs[4];
	void LitValeursPhotoR();
	int angleServoTeteSuivit;
	
};

#endif	
