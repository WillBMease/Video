#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(20);
    
    frameWidth = 160;
    frameHeight = 120;
    
    frameSize = frameWidth*frameHeight;
    
    pixels.allocate(frameWidth, frameHeight, 1);
    vidFrame.allocate(frameWidth, frameHeight, OF_IMAGE_GRAYSCALE);
    
    bool connected = tcpClient.setup("10.120.21.246", 11999);
    
    while (!connected) {
        connected = tcpClient.setup("10.120.21.246", 11999);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    char receivedBytes[frameSize];
    
    if (tcpClient.isConnected()) {
        tcpClient.receiveRawBytes(receivedBytes, frameSize);
        cout << "No. of Recvd Bytes: " << tcpClient.getNumReceivedBytes() <<  endl;
        ofSleepMillis(15);
    }
    
    for (int i=0; i<frameSize; i++) {
        usc_recvdBytes[i] = receivedBytes[i];
    }
    
    pixels.setFromExternalPixels(usc_recvdBytes, frameWidth, frameHeight, 1);
//    vidFrame.setFromPixels(usc_recvdBytes, frameWidth, frameHeight, OF_IMAGE_GRAYSCALE);
    vidFrame.setFromPixels(pixels);
    vidFrame.reloadTexture();
}

//--------------------------------------------------------------
void ofApp::draw(){
    vidFrame.draw(0, 0, frameWidth, frameHeight);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
