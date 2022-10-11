#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();


	music.load("Interstellar Main Theme - Hans Zimmer_70k.mp3");
	music.setLoop(true);
	music.setVolume(0.7);
	music.play();

	
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{

	//these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		;
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].update();
	}

	//lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
	{
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
    // Yo quiero crear un counter con un numero, ese numero llegue a 0  en 3 segundos. 
	// counter = 90
	// apply the same for loop and counter y el nuevo bool. 



 	if (isReplay)
		{
			counter--;
			if(counter == 0){
		    // runs for todo instantaneamente . Y me voy a quedar con el ultimo que me quedo
                    
                   if(iterator != record.size()){

                    keyPressed(record[iterator]);
					iterator += 1;    // increment the interator after loop. 

				   }else if(iterator == record.back() || record.empty() || iterator == record.size()){
					   	isReplay = false;
				   }else{
					    isReplay = false;
				   }

					counter = 90;		
					// lo unico que me falta es borrar el key. 
					// hacer un check para ver si el record esta vacio , por que cuando el record esta vacio es cuando se hace el replay. 
					// cuando el size este vacio. Is record is false . 
				
				 //record[i] = NULL;     
				 //while (counter < 90)   
				 ///	counter++;
			
			// quitar el primer elmentyo y ponerselo aatras , erase vector 
			// llegar hast ael counter 0 yo quero que la teca que acabo de tocar la borre y quite. 
			// erase es para borrar el elemento que acabo de correr .
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(0,0,0), ofColor(0,0,0));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);

	if (isRecording == true)
	{
		ofSetColor(255, 0, 0);
		ofDrawCircle(1000, 15, 10);
	}

	if (isReplay == true)
	{
		ofSetColor(0, 200, 0);
		ofDrawCircle(1000, 15, 10);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{


	if (key == '1')
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if (key == '2')
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if (key == '3')
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
	}
	if (key == '4')
	{
		currentMode = PARTICLE_MODE_NOISE;


		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
		resetParticles();
	}
	if( key == 'a' || key == 'A'){
		currentMode = PARTICLE_MODE_PAUSE;
		currentModeStr = "A - PARTICLE_MODE_PAUSE: paused";
	}	
		
	
	if (key == ' ')
	{
		resetParticles();
	}

	if (key == 'I' || key == 'i')
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].doubleSize();
		}
	}

	if (key == 'D' || key == 'd')
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].decreaseSize();
		}
	}
	if (key == 'F' || key == 'f')
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].increaseVelocity();
			p[i].update();
		}
	}
	if (key == 'S' || key == 's')
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].decreaseVelocity();
			p[i].update();
		}
	}
	

	if (key == 'R' || key == 'r')
	{
		

        if(isRecording == true){

			 isRecording = false;

		 }else{

			 isRecording = true;
			 record.clear(); 

		 }
		
		// hacer esto en draw method
	
	}
	if (isRecording == true && key != 'R' &&  key != 'r')     // If replay is true then record is false .
	{
	
		record.push_back(key);
		//vector to push in . NO necesito el foor loop. Pero si voy a necesitar un foor loop para iterar en cada key. Tendre que iterara en el vecotr
	}
	 // Ya como tengo is recording i need a nother one that tells me its playing . Hay cosas que quiero hacer mientras esta recording o playing 
	if (key == 'P' || key == 'p' )
	{
	   isRecording = false;
       isReplay = true;
	   counter = 90;
	   iterator = 0;
	   
	}
	

	if( key == 'c' || key == 'C'){
		isReplay = false;
	}


	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
