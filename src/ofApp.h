#pragma once

#include "ofMain.h"

#include "ofxGif.h"

#define NUM 3000

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // 画面サイズ
    int w;
    int h;
    
    // power pad
    vector<string> thisInputs;
    vector<string> poolInputs;
    vector<string> fullInputs;
    ofSerial serial;
    bool controllEnable();
    
    int nBytesRead;
    int nRead;
    char bytesReadString[30];
    char bytesRead[30];
    unsigned char bytesReturned[30];
    
    bool steppedFlag;
    int steppedPadCount;
    int legs[3];
    int lastLegs[3];
    
    // image groups
    ofImage imgGroup[2][12];
    
    int stepSum;
    int nextStepSum;
    
    // curesor
    int photoCursor;
    int nextPhotoCursor;
    int albumCursor;
    int albumCursorCandidate;
    int albumCursorChangedFlag;
    int albumCursorChangedTimer;
    
    // bases
    float displayPhotoWidth;
    float displayPhotoHeight;
    void setDisplayPhotoSize(float actualPhotoWidth, float actualPhotoHeight);
    
    ofImage currentImage;
    ofImage nextImage;
    
    int drawPositionX;
    int drawPositionY;
    
    int fadeLevel;
};
