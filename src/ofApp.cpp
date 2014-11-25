#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /* ------------
     basic -- base
     ------------ */
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(255, 255, 255);

    ofEnableAlphaBlending();
    fadeLevel = 255;
    
    w = ofGetWidth();
    h = ofGetHeight();

    /* ------------
     powerpad
     ------------ */
    
    photoCursor = 0; // 0 ~ 11
    steppedPadCount = 0;
    steppedFlag = true;
    
    stepSum = 1;
    nextStepSum = 0;
    
    /* ------------
     basic -- images
     ------------ */

    for (int i = 0; i < 12; i++) {
        imgGroup[0][i].loadImage("jpg01/" + ofToString(i + 1) + ".jpg");
    }
    
    for (int i = 0; i < 12; i++) {
        imgGroup[1][i].loadImage("jpg02/" + ofToString(i + 1) + ".jpg");
    }
    
    albumCursor = 1;
    photoCursor = 0;
    nextPhotoCursor = 0;
    
    /* ------------
     basic -- power pad
     ------------ */

    poolInputs.reserve(12);
    fullInputs.reserve(12);
    
    thisInputs.clear();
    poolInputs.clear();
    fullInputs.clear();
    
    serial.setup("/dev/tty.usbmodemfa131",9600);
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    /* ------------
     power pad
     ------------ */
    

            ofLog(OF_LOG_WARNING, "num is %d" , fullInputs.size());
    
    if (controllEnable() && !fullInputs.empty() && fullInputs.size() == 12) {
        
        ofLog(OF_LOG_WARNING, "stepped");
        
        if (steppedPadCount == 1) {
            stepSum++;
            
            if (stepSum > 100) {
                stepSum = nextStepSum + 1;
                nextStepSum = 0;
                photoCursor++;
                if (photoCursor > 11) {
                    photoCursor = 0;
                }
            }
            
            if (stepSum > 80) {
                nextStepSum++;
                if (nextStepSum > 100) {
                    nextStepSum = 1;
                }
                nextPhotoCursor = photoCursor + 1;
                if (nextPhotoCursor > 11) {
                    nextPhotoCursor = 0;
                }
            }
            
            
//            imgGroup[albumCursor][photoCursor].setAnchorPercent(0.05 * stepSum, 0.05 * stepSum);
        }
        ofLog(OF_LOG_WARNING, "stepSum is %d", stepSum);
        ofLog(OF_LOG_WARNING, "photoCursor is %d", photoCursor);
            
        
    }
    
    /* ------------
     gif animation
     ------------ */
    
    
    /* ------------
     gif animation
     ------------ */
    fadeLevel--;
    if (fadeLevel <= 100) {
        fadeLevel = 255;
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
 
    /* ------------
     Photos
     ------------ */
    
    ofPushMatrix();
    
    float actualWidth;
    float actualHeight;
    
    currentImage = imgGroup[albumCursor][photoCursor];
    actualWidth = currentImage.getWidth() / 2 *  0.01 * stepSum;
    actualHeight = currentImage.getHeight() / 2 * 0.01 * stepSum;
    
    currentImage.draw(w / 2 - actualWidth / 2
                      ,h / 2 - actualHeight / 2
                      , actualWidth
                      , actualHeight);
    ofPopMatrix();
    
    
    if (nextStepSum > 0) {
        ofPushMatrix();
        float nextActualWidth;
        float nextActualHeight;
        nextImage = imgGroup[albumCursor][nextPhotoCursor];
        nextActualWidth = nextImage.getWidth() / 2 *  0.01 * nextStepSum;
        nextActualHeight = nextImage.getHeight() / 2 * 0.01 * nextStepSum;
        
        nextImage.draw(w / 2 - nextActualWidth / 2
                       ,h / 2 - nextActualHeight / 2
                       , nextActualWidth
                       , nextActualHeight);
        
        ofPopMatrix();
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key){
        case 'q':
            photoCursor = 0;
            steppedFlag = true;
            break;
        case 'w':
            photoCursor = 1;
            steppedFlag = true;
            break;
        case 'e':
            photoCursor = 2;
            steppedFlag = true;
            break;
        case 'r':
            photoCursor = 3;
            steppedFlag = true;
            break;
        case 'a':
            photoCursor = 4;
            steppedFlag = true;
            break;
        case 's':
            photoCursor = 5;
            steppedFlag = true;
            break;
        case 'd':
            photoCursor = 6;
            steppedFlag = true;
            break;
        case 'f':
            photoCursor = 7;
            steppedFlag = true;
            break;
        case 'z':
            photoCursor = 8;
            steppedFlag = true;
            break;
        case 'x':
            photoCursor = 9;
            steppedFlag = true;
            break;
        case 'c':
            photoCursor = 10;
            steppedFlag = true;
            break;
        case 'v':
            photoCursor = 11;
            steppedFlag = true;
            break;
//        case 'i':
//            backgroundSwitcher = 0;
//            break;
//        case 'o':
//            backgroundSwitcher = 1;
//            break;
//        case 'p':
//            backgroundSwitcher = 2;
//            break;
        default:
            steppedFlag = false;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}




//--------------------------------------------------------------
bool ofApp::controllEnable() {
    
    /* ------------
     power pad
     ------------ */
    
    nBytesRead = 0;
    nRead = 0;
    memset(bytesReturned, 0, 30);
    memset(bytesReadString, 0, 30);
    
    // シリアル通信で受け取ったデータを読み込む
    while ((nRead = serial.readBytes(bytesReturned, 30)) > 0) {
        nBytesRead = nBytesRead + nRead;
    }
    string x;
    if (nBytesRead > 0) {
        memcpy(bytesReadString, bytesReturned, 27);
        x = bytesReadString;
    }
    
    string signal = ofToString(bytesReadString);
    
    ofLog(OF_LOG_WARNING, "x is " + x);
    ofLog(OF_LOG_WARNING, "signal is " + signal);
    
    thisInputs.clear();
    thisInputs = ofSplitString(signal, ",");
    bool fullFlag = false;
    // sが来たら記録開始
    if (!thisInputs.empty()) {
        for (string aResult : thisInputs) {
            if (aResult == "s") {
//                ofLog(OF_LOG_NOTICE, "start : ");
                
                fullInputs.clear();
                
                steppedPadCount = 0;
                continue;
                
            } else if ((aResult == "0") || (aResult == "1")) {
//                ofLog(OF_LOG_NOTICE, "progress : " + aResult);
//                poolInputs.push_back(aResult);
//                steppedPadCount += atoi(aResult.c_str());
                
                if (poolInputs.size() <= 12) {
                    poolInputs.push_back(aResult);
                    steppedPadCount += atoi(aResult.c_str());
                } else {
                    fullFlag = true;
                }
                
                
            }
            
            else if (aResult == "e") {
                //                ofLog(OF_LOG_NOTICE, "done : " + aResult);
                
                //                ofLog(OF_LOG_WARNING, "1. fullInputs.size() is %d", fullInputs.size());
                //                ofLog(OF_LOG_WARNING, "1. poolInputs.size() is %d", poolInputs.size());
                
                // tまでたどり着いたらそこで次へ
                fullInputs.clear();
                //                fullInputs.swap(poolInputs);
                
                //                ofLog(OF_LOG_WARNING, "2. fullInputs.size() is %d", fullInputs.size());
                //                ofLog(OF_LOG_WARNING, "2. poolInputs.size() is %d", poolInputs.size());
                
                //                fullInputs.insert(fullInputs.end(),poolInputs.begin(),poolInputs.end());
                
                fullInputs.swap(poolInputs);
                
                //                ofLog(OF_LOG_WARNING, "3. fullInputs.size() is %d", fullInputs.size());
                //                ofLog(OF_LOG_WARNING, "3. poolInputs.size() is %d", poolInputs.size());
                
                poolInputs.clear();
                
                //                ofLog(OF_LOG_WARNING, "4. fullInputs.size() is %d", fullInputs.size());
                //                ofLog(OF_LOG_WARNING, "4. poolInputs.size() is %d", poolInputs.size());
                
                fullFlag = true;
            }
        }
    }
    
//    ofLog(OF_LOG_WARNING, "steppedPadCount is %d", steppedPadCount);
    
    // tまでたどり着いてない場合はreturn
    return fullFlag;
    
}
