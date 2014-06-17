#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(20);//Try to increase or decrease this framerate later.
    
    camWidth = vidGrabber.width = 640;
    camHeight = vidGrabber.height = 480;
    camFrameSize = camWidth*camHeight;

    vidFrame.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    
    vidGrabber.initGrabber(camWidth, camHeight);
    if (!vidGrabber.isInitialized()) {
        cout << "CAMERA IS NOT INITIALIZED" << endl;
        exitApp();
    }
    
    tcpServer.setup(11999);
    
    packetSize = 100; //100 bytes for 1 packet. Should be consistent with char tcpFramePacket.
    flag = 0; //To check if TCP connection is present or not.
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()) {
        //Even though getPixelsRef() has definition with return type ofPixelsRef...
        //we can use ofImage vidFrame because Image includes both ofPixels and ofTexture (in simple words).
        vidFrame = vidGrabber.getPixelsRef();
        vidFrame.setImageType(OF_IMAGE_GRAYSCALE);
        vidFrame.mirror(false, true);
        vidFrame.reloadTexture();
        
        
        if (tcpServer.isClientConnected(0)) {
            flag = 1;
            
            //Convert ofImage vidFrame to char array for easy chunking
         
            ptrVidFrame = vidFrame.getPixels();
            for (i=0; i<camFrameSize; i++) {
                vidFramePixels[i] = ptrVidFrame[i];
            }
        
            //Start chunking above frame to send across TCP network.
            
            for (i=0; i<camFrameSize; i+packetSize) {
                fpIndex=0;
                for (j=i; j<i+packetSize; j++) {
                    tcpFramePacket[fpIndex] = vidFramePixels[j];
                    fpIndex++;
                }
                tcpServer.sendRawBytes(0, tcpFramePacket, packetSize); //Sending packets of size 100 bytes
            }
            
        }
        else if ((!tcpServer.isClientConnected(0)) && flag==1) {
            tcpServer.disconnectClient(0);
            tcpServer.close();
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
