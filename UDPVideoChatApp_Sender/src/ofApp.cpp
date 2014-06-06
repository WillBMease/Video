#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    udpConnection.Create();
    udpConnection.Connect("10.120.91.147",11999);
    udpConnection.SetNonBlocking(true);

    vidGrabber.width = 110;
    vidGrabber.height = 90;
    //vidGrabber.setDesiredFrameRate(20);
    ofSetFrameRate(20); // Very IMPORANT. Without calling this function, there will be flickering on the receiver's side.
    //vidGrabber.setUseTexture(false); //gives better performance when this is set to false
    vidGrabber.initGrabber(vidGrabber.width,vidGrabber.height);
    if(!vidGrabber.isInitialized())
        cout << "Camera is not getting initialized.";
    
  //  videoTexture.clear();//clears/frees texture memory. Useful if you need to control the memory on the graphics card. Clears all the data from the texture.
    //videoTexture2.clear();
  //  videoTexture.allocate(vidGrabber.width, vidGrabber.height, GL_LUMINANCE); //good to allocate this in the setup function. It produces some delay if loadData is used directly without allocating during setup.
    // bool bAllocated = videoTexture.bAllocated();
   // bool isAllocated = videoTexture.isAllocated();
    //cout << "Is the texture allocated? For bAllocated: " << bAllocated << endl;
    //cout << "Is the texture allocated? For isAllocated: " << isAllocated << endl;
    
//  cout << udpConnection.GetMaxMsgSize() << endl;
    
//  int Rbuffersize = udpConnection.GetReceiveBufferSize();
//  cout << Rbuffersize << endl;
    
//  cout << sizeof(Sbuffersize) << endl;*/
    
    int setSendBufferSize = udpConnection.SetSendBufferSize(200000);
    int Sbuffersize = udpConnection.GetSendBufferSize();
    cout << "Send Buffer Size: " << Sbuffersize << endl;
    iSize = vidGrabber.width * vidGrabber.height * 3;
    //cout << "iSize = " << iSize << endl;
//  vidGrabber.videoSettings(); // Does not work on Mac 10.7+
//  ofAppUpdateCounter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //if(ofAppUpdateCounter==0){
    vidGrabber.update();
    //    ofAppUpdateCounter++;
    //}
    
    ptrArrPixels = vidGrabber.getPixels();
    
    rowWidth = vidGrabber.width*3;
    unsigned char framePacket[rowWidth];
    /*Incrementing i by rowWidth - j starts from next packet of frame using i's position
      j is incremented by 1 till j < sum of i and rowWidth (that enables to process the next packet in the frame)
      Then, a rowWidth segment of ptrArrPixels is stored in framePacket.
      Once, rowWidth size of data is stored in framePacket, it is sent through the UDP Connection
      vidGrabber.update() will be called again only after i = size of whole frame
      that is, after ensuring that the whole frame has been sent through UDP*/
   
    //if(vidGrabber.isFrameNew) // think if this needs to be included.
    for(i = 0; i < iSize; i += rowWidth){
        fpIndex=0;
        for(j = i; j < i+rowWidth ; j++){
            framePacket[fpIndex] = ptrArrPixels[j];
            fpIndex++;
        }
        udpConnection.Send((const char *)framePacket, rowWidth);//think whether to place this in the for loop or not
        //at the moment it is sending the whole frame and then going to the draw function
        //at the receiver's side draw will have to be called with each packet received.
    }
    
    /*if(i >= iSize)
        vidGrabber.update();*/ //try to dry run this
    
    
    /*
    vidGrabber.update();//Don't call this till all the pixels in frame are sent through UDP
    ptrArrPixels = vidGrabber.getPixels();
    
    
    udpConnection.Send((const char *)ptrArrPixels, iSize);
    */
    
    
  //  videoTexture.loadData((const unsigned char *)ptrArrPixels, vidGrabber.width, vidGrabber.height, GL_RGB);
 //   videoTexture2.loadData((const unsigned char *)ptrArrPixels, vidGrabber.width, vidGrabber.height, GL_LUMINANCE);
    
 //   if(vidGrabber.isFrameNew()){
 //       udpConnection.Send((const char *)ptrArrPixels, iSize);
 //   }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidGrabber.draw(0, 0, vidGrabber.width, vidGrabber.height);
    //videoTexture.draw(0+vidGrabber.width, 0, vidGrabber.width, vidGrabber.height);
    //videoTexture2.draw(0+2*vidGrabber.width,0,vidGrabber.width,vidGrabber.height);
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
/*    for(int i=0; i<vidGrabber.width*vidGrabber.height*3; i++){
        cout << ptrArrPixels[i] << endl;
    }*/
/*    cout << sizeof(ptrArrPixels[1]) << endl;
    cout << (int) ptrArrPixels[1] << endl;*/
    
    for (int i=0; i<iSize; i++){
    //    cout << "Pixel " << i+1 << ": " << (int)ptrArrPixels[i] << endl;
          cout << (int)ptrArrPixels[i] << " ";
    }
    cout << endl;
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
