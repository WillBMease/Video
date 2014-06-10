#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(20);
    
    vidGrabber.width = 640;
    vidGrabber.height = 480;
    
    camWidth = vidGrabber.width;
    camHeight = vidGrabber.height;
    
    vidFrame.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    
    tcpServer.setup(11999);
    
    vidGrabber.initGrabber(camWidth, camHeight);
    if(!vidGrabber.isInitialized()){
        cout << "CAMERA IS NOT INITIALIZED!!" << endl << endl;
        exitApp();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()) {
        pixels = vidGrabber.getPixelsRef();
        pixels.setNumChannels(1);
        pixels.setImageType(OF_IMAGE_GRAYSCALE);
        pixels.mirror(false, true);
        vidFrame.setFromPixels(pixels);
        
        if (tcpServer.isClientConnected(0)) {
            tcpServer.sendRawBytes(0, (const char *)vidFrame.getPixels(), camWidth*camHeight);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidFrame.draw(0, 0, camWidth, camHeight);
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
    
    for(int i=0 ; i < (camWidth*camHeight) ; i++){
       cout << (int)pixels[i] << " ";
    }

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