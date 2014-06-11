#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(20);
    
    vidGrabber.width = 320;
    vidGrabber.height = 240;

    camWidth = vidGrabber.width;
    camHeight = vidGrabber.height;
    frameSize = camWidth*camHeight;
    
    pixels.allocate(camWidth, camHeight, 3); //Allocating 3 channels of space for OfPixels pixels
                                             //since pixels receives from vidGrabber which is 3 channel
    vidFrame.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    vidTexture.allocate(camWidth, camHeight, GL_LUMINANCE);
    
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
//      pixels.setNumChannels(1);
        pixels.setImageType(OF_IMAGE_GRAYSCALE);
        pixels.mirror(false, true);
        vidFrame.setFromPixels(pixels);
        vidFrame.reloadTexture();
        vidFrame.bind();
//      vidFrame.setCompression(OF_COMPRESS_SRGB); //No compression method works
                                                   //It just takes a snapshot and then remains constant
        ptrArrPixels = vidFrame.getPixels();
        ofSleepMillis(15);
        
        char constpixels[frameSize];
        
        //constpixels = (char*) ptrArrPixels;
        for(int i=0; i<frameSize; i++) {
            constpixels[i] = ptrArrPixels[i];
        }
       // vidTexture.loadData((const unsigned char *)constpixels, camWidth, camHeight, GL_LUMINANCE);
        
        if (tcpServer.isClientConnected(0)) {
            //for(int i=0; i<frameSize; i++){
//              tcpServer.sendRawBytes(0, (const char *)(vidFrame.getPixels()), frameSize);
                tcpServer.sendRawBytes(0, constpixels, frameSize);
                ofSleepMillis(20);
            //}
        }
        vidFrame.unbind();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidFrame.draw(0, 0, camWidth, camHeight);
  //  vidTexture.draw(0+camWidth, 0, camWidth, camHeight);
    
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
    
/*    for(int i=0 ; i < (camWidth*camHeight) ; i++){
       cout << (int)pixels[i] << " ";
    }
    
    cout << "VidFrame Width:   " << vidFrame.getWidth()  << endl;
    cout << "VidFrame Height:  " << vidFrame.getHeight() << endl;*/
    
    cout << "PtrArrPixels: " << endl;
    for (int i=0; i<frameSize; i++) {
        cout << (int)ptrArrPixels[i] << " ";
    }
    cout << endl;
    
   /* cout << "intpixels: " << endl;
    for (int i=0; i<frameSize; i++) {
        cout << intpixels[i] << " ";
    }
    
    cout << endl;*/
    
    cout << "constpixels: " << endl;
 //   checkconstpixels = (unsigned char *)constpixels;
    for (int i=0; i<frameSize; i++) {
        cout << (int)checkconstpixels[i] << " ";
    }
   /* cout << "constpixels" << endl;
    for (int j=0; j<frameSize; j++) {
        cout << (int)constpixels[j] << " ";
    }*/
    
    cout << endl << endl;
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