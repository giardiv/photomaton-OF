#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 720;
    camHeight = 480;
    
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(20);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGBA);
    ofSetVerticalSync(true);
    finder.setup("haarcascade_frontalface_default2.xml");
    
    faceNb = 0;
    faceTurn = 0;
    waiter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100, 100, 100);
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        videoInverted = vidGrabber.getPixels();
        pixels = vidGrabber.getPixels();
//            for(int y = 0; y < camHeight; y++){
//                for(int x = 0; x < camWidth; x++){
//                    ofColor color = videoInverted.getColor(x, y);
//                    if(color.getHue() < 40 && color.getHue() > 10){
//                        pixels.setColor(x, y, ofColor::black);
//                    }
//                }
//            }
        pixels.mirror(false, true);
        haarImg.setFromPixels(pixels);
        finder.findHaarObjects(haarImg);
        keyed.setFromPixels(pixels);
        
        ofLogNotice() << faceTurn;
        
        if(waiter == 0){
            if(faceNb >= 2){
                faceTurn = faceTurn + 1;
            }else{
                faceTurn = 0;
            }
            faceNb = finder.blobs.size();
            if(faceTurn > 30){
                ofLogNotice() << " <<<<<<<<< PHOTOS !!";
                waiter = 100;
                faceTurn = 0;
                faceNb = 0;
            }
        }
        if(waiter > 0){
            waiter = waiter - 1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    keyed.draw(0, 0, 720,480);
    //vidGrabber.draw(0, 0, 420, 240);
    ofNoFill();
    for(int i = 0; i < finder.blobs.size(); i++){
        ofRectangle cur = finder.blobs[i].boundingRect;
        ofDrawRectangle(cur);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
