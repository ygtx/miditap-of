#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

    ofLog(OF_LOG_NOTICE, "w is %d", ofGetWidth());
    ofLog(OF_LOG_NOTICE, "h is %d", ofGetHeight());
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
