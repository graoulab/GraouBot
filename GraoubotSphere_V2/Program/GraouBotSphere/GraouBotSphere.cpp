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

#include "GraouBotSphere.h"


GraouBotSphere::GraouBotSphere()
{
	int m[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
	int t[]= {  4, 8, 8, 4, 4, 4, 4, 4};
	nbNotes=8;	
	melody=new int[8];
	noteDurations=new int[8];

	for( int i=0;i<nbNotes;i++)
	{
		melody[i] = m[i];
		noteDurations[i] =t[i];
	}

}

GraouBotSphere::~GraouBotSphere() 
{
  delete melody;
  delete noteDurations;
}

	bool GraouBotSphere::BoutonAppuye()
	{
		return (!digitalRead(PIN_BOUTON));
	}


void GraouBotSphere::Init()
{
	ledTete=new Adafruit_NeoPixel(NUMPIXELS, PIN_LED_RGB, NEO_RGB + NEO_KHZ800);
	ledTete->begin();
	ledTete->setPixelColor(0,0,0,0);
	ledTete->show();
	
	
  	servoBras.attach(PIN_SERVO_BRAS);
  	servoTete.attach(PIN_SERVO_TETE);
  	
    pinMode(PIN_BOUTON, INPUT_PULLUP);
  	pinMode(PIN_BUZZER, OUTPUT);

	posBrasSorti=EEPROM.read(ADRESSE_EEPROM_BRAS_MAX);
	posBrasRentre=EEPROM.read(ADRESSE_EEPROM_BRAS_MIN);
	
	RentreBras();
	BougeTete(90);
	
}

void GraouBotSphere::SecoueTete(int nombreDeFois,int vitesse)
{
	int duree=vitesse/32;
	for (int nb=0;nb<nombreDeFois;nb++)
	{
		for(int i=90;i<=170;i=i+10)
		{
			servoTete.write(i);
			delay(duree);
		}
		
		for(int i=170;i>=10;i=i-10)
		{
			servoTete.write(i);
			delay(duree);
		}
		
		for(int i=10;i<=90;i=i+10)
		{
			servoTete.write(i);
			delay(duree);
		}
	}
}

void GraouBotSphere::BougeTete(int angle)
{
	servoTete.write(angle);
}

void GraouBotSphere::AlumeTete(uint8_t r,uint8_t g,uint8_t b)
{
	ledTete->setPixelColor(0,r,g,b);
	ledTete->show();
}

void GraouBotSphere::EteindTete()
{
	ledTete->setPixelColor(0,0,0,0);
	ledTete->show();
}

void GraouBotSphere::SortBras()
{
	servoBras.write(posBrasSorti);
}

void GraouBotSphere::RentreBras()
{
	servoBras.write(posBrasRentre);
}

void GraouBotSphere::AllumeLED()
{
	analogWrite(PIN_LED_BRAS,255);
}	

void GraouBotSphere::EteindLED()
{
	analogWrite(PIN_LED_BRAS,0);
}

void GraouBotSphere::ClignoteLED(int duree, int nombreClignotements)
{
	int temps=duree/51;
	for(int nbCligne=0;nbCligne<nombreClignotements;nbCligne++)
	{
		for (int i=0;i<255;i=i+10)
		{
			analogWrite(PIN_LED_BRAS,i);
			delay(temps);
		}
		
		for (int i=255;i>0;i=i-10)
		{
			analogWrite(PIN_LED_BRAS,i);
			delay(temps);
		}		
	}
	EteindLED();
	
}

void GraouBotSphere::DefinitValeursBras(char rentre, char sorti)
{
	posBrasSorti=sorti;
	posBrasRentre=rentre;

	EEPROM.write(ADRESSE_EEPROM_BRAS_MIN, rentre);
	EEPROM.write(ADRESSE_EEPROM_BRAS_MAX, sorti);
}

void GraouBotSphere::BougeBras(int position)
{
	servoBras.write(position);
}

void GraouBotSphere::JoueSon()
{
  for (int thisNote = 0; thisNote < nbNotes; thisNote++)
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(PIN_BUZZER, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(PIN_BUZZER);

  }
}

void GraouBotSphere::DefiniSons(int *notes, int *durees, int nombreNotes)
{
	delete melody;
	delete noteDurations;
  
	nbNotes=nombreNotes;
	melody=new int[nbNotes];
	noteDurations=new int[nbNotes];
	
	for(int i=0;i<nbNotes;i++)
	{
		melody[i]=notes[i];
		noteDurations[i]=durees[i];
		
	}
}

void GraouBotSphere::Litvaleurs(int valeurs[4])
{
	valeurs[0]=analogRead(PIN_PHOTO_R1);
	valeurs[1]=analogRead(PIN_PHOTO_R2);
	valeurs[2]=analogRead(PIN_PHOTO_R3);
	valeurs[3]=analogRead(PIN_PHOTO_R4);
}

void GraouBotSphere::LitValeursPhotoR()
{
	valeurCapteurs[0]=analogRead(PIN_PHOTO_R1);
	valeurCapteurs[1]=analogRead(PIN_PHOTO_R2);
	valeurCapteurs[2]=analogRead(PIN_PHOTO_R3);
	valeurCapteurs[3]=analogRead(PIN_PHOTO_R4);
	
	valeurCMoyen=(valeurCapteurs[0]+valeurCapteurs[1]+valeurCapteurs[2]+valeurCapteurs[3])/4;
	int tmp;
	
	//tri dans l'ordre croissant
	if(valeurCapteurs[triCapteurs[0]] > valeurCapteurs[triCapteurs[1]])
	{
		tmp= triCapteurs[0];
		triCapteurs[0]=triCapteurs[1];
		triCapteurs[1]=tmp;
	}
		
	if(valeurCapteurs[triCapteurs[2]] > valeurCapteurs[triCapteurs[3]])
	{
		tmp= triCapteurs[2];
		triCapteurs[2]=triCapteurs[3];
		triCapteurs[3]=tmp;
	}
	
	if(valeurCapteurs[triCapteurs[1]] > valeurCapteurs[triCapteurs[2]])
	{
		tmp= triCapteurs[1];
		triCapteurs[1]=triCapteurs[2];
		triCapteurs[2]=tmp;
	}
		
	if(valeurCapteurs[triCapteurs[0]] > valeurCapteurs[triCapteurs[1]])
	{
		tmp= triCapteurs[0];
		triCapteurs[0]=triCapteurs[1];
		triCapteurs[1]=tmp;
	}
		
	if(valeurCapteurs[triCapteurs[2]] > valeurCapteurs[triCapteurs[3]])
	{
		tmp= triCapteurs[2];
		triCapteurs[2]=triCapteurs[3];
		triCapteurs[3]=tmp;
	}	
}

void GraouBotSphere::InitSuivit()
{
	LitValeursPhotoR();
	triCapteurs[0]=1;
	triCapteurs[1]=2;
	triCapteurs[2]=3;
	triCapteurs[3]=4;
	angleServoTeteSuivit=90;
	
	servoTete.write(angleServoTeteSuivit);
	delay(100);
}

void GraouBotSphere::LoopSuitLumiere()
{
	
	LitValeursPhotoR();
	if(valeurCapteurs[triCapteurs[3]]==1)
	{
		if(angleServoTeteSuivit>90)
		{	
			angleServoTeteSuivit=angleServoTeteSuivit-1;
		}
		else
		{	if(angleServoTeteSuivit<90)
			{angleServoTeteSuivit=angleServoTeteSuivit+1;}
		}
	}		
	
	

}

void GraouBotSphere::LoopSuitOmbre()
{
	LitValeursPhotoR();

}


int  GraouBotSphere::LitPotentiometre()
{
	return analogRead(PIN_POTENTIOMETRE);
}