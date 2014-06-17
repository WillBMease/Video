#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(20);
    
    frameWidth = 640;
    frameHeight = 480;
    frameSize = frameWidth*frameHeight;
    
    frameTex.allocate(frameWidth, frameHeight, GL_LUMINANCE);
    
    serverIP = "10.120.241.26";
    serverPort = 11999;
    tcpClient.setup(serverIP, serverPort);
    
    /*while (!tcpClient.isConnected()) {
        tcpClient.setup(serverIP, serverPort);
        ofSleepMillis(2000);
    }*/
    
    packetSize = 100; // 100 bytes for 1 packet.
    for (i=0; i<packetSize; i++) {
        packet[i] = '\0';
    }
    
    packetArrFlag = 1; //flag is for resetting char packet array to NULL - 0: edited, 1: Set to Null
    totalBytesReceived = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (tcpClient.isConnected()) {
       
        bytesReceived = 0;
        /*if (packetArrFlag==0) {
            for (i=0; i<packetSize; i++) {
                packet[i] = '\0';
            }
            packetArrFlag = 1;
        }*/
        
        //This coding will produce gaps in final image if packets are lost.
        //Not currently programming it to show a frame only if all packets are received...
        //in order to keep the latency low
        
        //The code below basically ignores a packet if it has less bytes than packetSize.
        //Not sure about using it right now.
        //Would be better to leave a gap in the final image if bytes Received are less than PacketSize
        
        /*while (bytesReceived<packetSize) {
            if (packetArrFlag==0) {
                for (i=0; i<packetSize; i++) {
                    packet[i] = '\0';
                }
                packetArrFlag = 1;
            }
            ofSleepMillis(5);//Toggle with the amount of time the function must sleep if required
            bytesReceived = tcpClient.receiveRawBytes(packet, packetSize);
            packetArrFlag = 0;
        }*/
        
        //Below code calculates totalBytesReceived mathematically and not by the actual number received.
        //Using this method just to set the number of times the TCP receive should loop...
        //and not to check if it receives all the bytes.
        //Once totalBytesReceived mathematically equals packetSize, show Image to receiver.
        
        while (totalBytesReceived<frameSize) {
            pIndex=0;
            if (packetArrFlag==0) {
                for (i=0; i<packetSize; i++) {
                    packet[i] = '\0';
                }
                packetArrFlag = 1;
            }
            
            bytesReceived = tcpClient.receiveRawBytes(packet, packetSize);
            if (bytesReceived > 0) {
                packetArrFlag=0;
            }
            
            for (j=totalBytesReceived; j<totalBytesReceived+packetSize; j++) {
                recvdFrame[j] = packet[pIndex];
                pIndex++;
            }
            totalBytesReceived += packetSize;
        }
        
        totalBytesReceived=0;
        
        usc_frame = (unsigned char *)recvdFrame;
        frameTex.loadData(usc_frame, frameWidth, frameHeight, GL_LUMINANCE);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    frameTex.draw(0, 0, frameWidth, frameHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='x') {
        tcpClient.close();
        exitApp();
    }
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
