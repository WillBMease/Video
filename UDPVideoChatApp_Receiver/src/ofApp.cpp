#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    udpConnection.Create();
    udpConnection.Bind(11999);
    udpConnection.SetNonBlocking(true);
    
    texWidth = 160;
    texHeight = 120;
    
    videoTexture.clear();
    videoTexture.allocate(texWidth, texHeight, GL_RGB);
    if(!videoTexture.isAllocated())
        cout << "Texture has not been allocated!!" << endl;
    
    bool setReceiveBufferSize = udpConnection.SetReceiveBufferSize(200000);
    if(udpConnection.GetReceiveBufferSize()!=200000)
        cout << "Receive Buffer Size was not assigned!!" << endl;
    
    iSize = texWidth*texHeight*3;
}

//--------------------------------------------------------------
void ofApp::update(){
    /*
    char udpVideoPacket[1000];
    rowWidth = texWidth*3;
    udpConnection.Receive(udpVideoPacket,rowWidth);
    //videoTexture.loadData((const unsigned char *)udpVideoPacket, texWidth, texHeight, GL_RGB);
    videoTexture.loadData((const unsigned char *)udpVideoPacket, rowWidth, 1, GL_RGB);
    */
    
    char udpVideoPacket[1000];
    char udpVideo[iSize];
    rowWidth = texWidth*3;
    
    for(int i = 0; i < iSize; i+=rowWidth){
        vpIndex=0;
        for(int j=i; j < i+rowWidth; j++){
            udpConnection.Receive(udpVideoPacket, rowWidth);
            udpVideo[j] = udpVideoPacket[vpIndex];
            videoTexture.loadData(<#const unsigned char *const data#>, <#int w#>, <#int h#>, <#int glFormat#>)
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    videoTexture.draw(0, 0, texWidth, texHeight);

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
