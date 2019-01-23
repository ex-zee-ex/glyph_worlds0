/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#include "ofApp.h"


#include <iostream>

//midicontrols
float c1=0;
float c2=0;
float c3=0;
float c4=0;
float c5=0;
float c6=0;
float c7=0;
float c8=0;
float c9=0;
float c10=0;
float c11=0;



float ss=1;
float dd=1;
float ff=1;
float gg=1;
float hh=0;
float kk=1;
float pp=1;
float ii=.01;

Boolean env_switch=0;

int sw1=0;
float out_env=0;

int countt=0;
int lineswitch=0;

int ll=0;
float theta=0;

float frequency=0;

float sine_lold;
float sine_rold;

float pix0[256][256];
float pix1[256][256];

float pixxx[256][256];


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    
    /**MIDIBIX***/
    
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
    
    /*******/
    
    
    /**audiobiz***/
    
    
    
    
    int bufferSize		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 0.1f;
    bNoise 				= false;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
    soundStream.printDeviceList();
    
    ofSoundStreamSettings settings;
    
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    countt++;
    
    
    
    
/*midimessagesbiz**/
    
    
    
    
    //ofTranslate(0,0,-100);
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
        
      //  status=message.status;
		//int x = 10;
		//int y = i*40 + 40;
        
        int N= message.pitch;
        int FN=N-69;
        frequency=pow(2.0,FN/12.0)*440;
        
        //cout << "MIDI_NOTE_ON="<< MIDI_NOTE_ON<< endl;
        //cout << "MIDI_NOTE_OFF="<< MIDI_NOTE_OFF<< endl;

        if(message.status==MIDI_NOTE_ON){
           // out_env=ofLerp(out_env,1,0.3);
            
          
            env_switch=1;
        }
        if(message.status==MIDI_NOTE_OFF){env_switch=0;}
        
        if(env_switch==1){
            if(out_env<1){
                out_env=ofLerp(out_env,1,0.5);
            }
        }

        
       // if(env_switch==0){
            if(out_env>0){
           out_env=ofLerp(out_env,0,.05);
           }
       // }
        
        
            out_env=ofClamp(out_env,0,1);
     	//cout << "out_env="<< out_env<< endl;
		// draw the last recieved message contents to the screen,
		// this doesn't print all the data from every status type
		// but you should get the general idea
		//stringstream text;
		//text << ofxMidiMessage::getStatusString(message.status);
	//	while(text.str().length() < 16) { // pad status width
			//text << " ";
	//	}

		//ofSetColor(127);
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
			if(message.status == MIDI_CONTROL_CHANGE) {
                cout << "message.control"<< message.control<< endl;
                 cout << "message.value"<< message.value<< endl;
                
                
                if(message.control==7){
                    c1=(message.value-63)/63.0000;
                
                }
                
                if(message.control==94){
                    c2=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==95){
                    c3=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==96){
                    c4=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==97){
                    c5=(message.value-63)/63.00000;
                    
                }
                if(message.control==20){
                    c6=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==73){
                    c10=(message.value-63)/63.00000;
                    
                }
                if(message.control==21){
                    c7=(message.value-63)/63.00000;
                    
                }
                if(message.control==22){
                    c8=(message.value-63)/63.00000;
                    
                }
                
                
				//text << "\tctl: " << message.control;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
				//	ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
			}
			else if(message.status == MIDI_PITCH_BEND) {
				//text << "\tval: " << message.value;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
					//ofMap(message.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()*0.2), 10);
			}
			else {
				//text << "\tpitch: " << message.pitch;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
					//ofMap(message.pitch, 0, 127, 0, ofGetWidth()*0.2), 10);
              
               // int N= message.pitch;
              //  int FN=N-69;
              //   frequency=pow(2.0,FN/12.0)*440;
                
                
                //text << "frequency: " << frequency;

				////text << "\tvel: " << message.velocity;
				//ofDrawRectangle(x + (ofGetWidth()*0.2 * 2), y + 12,
					//ofMap(message.velocity, 0, 127, 0, ofGetWidth()*0.2), 10);
			}
			//text << " "; // pad for delta print
		}//

		//text << "delta: " << message.deltatime;
		//ofSetColor(0);
		//ofDrawBitmapString(text.str(), x, y);
		//text.str(""); // clear
	}
   /******* endmidimessagesbiz*********/
   
    
    
   // ofTranslate(0,0,100);
    /***AUDIODRAWBIXZ******/
    
    theta+=.005;
    
    ofSetColor(0);
    //ofDrawBitmapString("AUDIO OUTPUT EXAMPLE", 32, 32);
    //ofDrawBitmapString("press 's' to unpause the audio\npress 'e' to pause the audio", 31, 92);
    
    ofNoFill();
    
    /*
    
    // draw the left channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 10, 0);
    
    ofSetColor(225);
    //ofDrawBitmapString("Left Channel", 4, 18);
    
    ofSetLineWidth(1);
    //	ofDrawRectangle(0, 0, 900, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < lAudio.size(); i++){
        float x =  ofMap(i, 0, lAudio.size(), 0, 900, true);
        ofVertex(x, 100 -lAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    
    */
    
    //draw lissajou	ofPushStyle();
    ofPushMatrix();
   // ofTranslate(512, 512, 0);
    
    //ofSetColor(225);
    //ofDrawBitmapString("lissajou", 4, 18);
    
    ofSetLineWidth(3);
    //ofDrawRectangle(0, 0, 900, 200);
    
   
    
    
    
    
        int cs=5;

    
    for (unsigned int i = 0; i < rAudio.size()*2/cs; i++){
         //cout << "rAudio.size()="<< rAudio.size()<< endl;
        float x =  4*(lAudio[i*cs/2]*180.0f)+512;
        float y = 4*(rAudio[i*cs/2]*180.0f)+512;
        
        float xold=0;
        float yold=0;
        
        if(i>0){
        xold =  4*(lAudio[(i-1)*cs/2]*180.0f)+512;
        yold = 4*(rAudio[(i-1)*cs/2]*180.0f)+512;
        }//endifi>
        if(i==0){
            xold =  4*(lAudio[(rAudio.size()*2/cs-1)*cs/2]*180.0f)+512;
            yold = 4*(rAudio[(rAudio.size()*2/cs-1)*cs/2]*180.0f)+512;
        }
        
        
        float z=hh*sqrt(x*x*cos(theta)+y*y*sin(theta));
        //ofVertex(x, 100 -rAudio[i]*180.0f);
        
       
     
        ofColor c;
        float hue=fmod(240*(1-.5*(lAudio[i])),255);
        float sat=255;
        float bright=255*(1-(lAudio[i]+rAudio[i]));
        c.setHsb(hue,sat, bright);
        
       // ofSetLineWidth(1);
        ofFill();
        ofSetColor(c);
        //ofVertex(x,y);
        
       // ofDrawRectangle(x,y,cs,cs);
        
        int pix_x=ofMap(x,0,1024,0,253)-24;
        int pix_y=ofMap(y,0,1024,0,253)-24;
        
        
        /**so this bit here was to try and interpolate between points i dont know how i feel ab0out it**/
       // int pix_xold=ofMap(xold,0,1024,0,253)-24;
       // int pix_yold=ofMap(yold,0,1024,0,253)-24;
        
        
        //float interpolatex=ofLerp(xold,x,.5);
       // float interpolatey=ofLerp(yold,y,.5);
        
       // pix_x=ofMap(interpolatex,0,1024,0,253)-24;
       // pix_y=ofMap(interpolatey,0,1024,0,253)-24;
        //pix_x=(pix_x-pix_xold)
       // pix_y=abs(int(ofLerp(yold,y,.5)));
        
        
        pixxx[pix_x][pix_y]=255;
        
        for(int j=0;j<rAudio.size()*2/cs;j++){
            int xx=i*cs;
            int yy=j*cs;
            float b=pix0[i][j];
            
          
            
            /**this version is toroidal universe**/
            //int up=(j-1)%(rAudio.size()*2/cs);
            //int down=(j+1)%(rAudio.size()*2/cs);
            //int left=(i-1)%(rAudio.size()*2/cs);
           // int right=(i+1)%(rAudio.size()*2/cs);
            
            /**thisversion is not wrapping around**/
            int up=ofClamp(j-1,0,rAudio.size()*2/cs);
            int down=ofClamp(j+1,0,rAudio.size()*2/cs);
            int left=ofClamp(i-1,0,rAudio.size()*2/cs);
            int right=ofClamp(i+1,0,rAudio.size()*2/cs);

            
            
            float b_u=pix0[i][up];
            float b_ul=pix0[left][up];
            float b_ur=pix0[right][up];
            float b_d=pix0[i][down];
            float b_dl=pix0[left][down];
            float b_dr=pix0[right][down];
            float b_r=pix0[right][j];
            float b_l=pix0[left][j];

            
            /**RULLEES*/
            
            /**rugruless!!**/
            
            /*
            float rug=(b_u+b_d+b_ul+b_ur+b_r+b_l+b_dr+b_dl)/8.0;
            rug=rug+c1;
            b=((1-c2)*b+(2*c2)*rug);
            */
            
            /**discrete reaction diffusion experients**/
            
            float r_d=(1-4*c1-4*c4)*(b)+c1*(b_u+b_d+b_ul+b_l+b_dr)+c4*(b_ur+b_r+b_dl)+c2*b*sin(theta/1.0*b/255)+.01*c7*(b*b*b);
            
            b=(1-2*c5-2*c6)*r_d+2*b*c5*((xx-512)/512)+2*b*c6*((yy-512)/512);
            //b=r_d;
            
            if(b<pixxx[i][j]){
                b=pixxx[i][j];
                
            }
            if(b>=pix0[i][j]){b=b*(1-c3/4.0);}
            
            
            /**heres where we do some stuffs to overflow**/
          
            /*
            if(b<-1000){
             b=0;
            }
            
            if(b>1000){
                b=255;}
            */
            
          //  b=abs(b);
            
            if(b<0){
              //  b=255-abs(b);
               b=abs(b);
            }
            
            if(sw1==1){
                b=fmod(b,255);
            }//ifsw1
            
            if(sw1==0){
            
            if(b>255*(1+10*c8)){
                b=255;
                
            }
            }//ifsw1
            
            
            
            ofColor c;
            float hue=0;
            float sat=255;
            float alph=0;
            
            hue=fmod(4*c10*b,255);
            alph=b*.8;
            
            c.setHsb(hue,sat,b,alph);
            
            ofSetColor(c);
            
           // float dist=sqrt((xx-x)*(xx-x)+(yy-y)*(yy-y));
            
           // if(dist<=cs){
              //  ofSetColor(255);
            //}
            
            
           // ofSetColor(pixxx[i][j]);
            ofDrawRectangle(xx,yy,cs,cs);
            
            pix1[i][j]=b;
            
        
        }//endjfor
    }//endifor
   // ofEndShape(false);
    
    if(lineswitch==1){
    
    ofBeginShape();
    
    for (unsigned int i = 0; i < rAudio.size(); i++){
        //cout << "rAudio.size()="<< rAudio.size()<< endl;
        float x =  5*(lAudio[i]*180.0f)+512;
        float y = 5*(rAudio[i]*180.0f)+512;
      //  float z=10;
        //ofVertex(x, 100 -rAudio[i]*180.0f);
        
        
        
        ofColor c;
        float hue=fmod(240*(1-.5*(lAudio[i])),255);
        float sat=255;
        float bright=255*(1-(lAudio[i]+rAudio[i]));
        c.setHsb(hue,sat, bright);
        
        ofSetLineWidth(1);
        ofNoFill();
        ofSetColor(c);
        ofVertex(x,y);
        
    }//endifor
    ofEndShape(false);
    
    }//endiflineswitch
    ofPopMatrix();
    ofPopStyle();
    
    
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
           // pixxx[i][j]=0;
             pix0[i][j]=pix1[i][j];
        }//endjfor
    }//endifor
    
    
    
    if(countt>10){
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            pixxx[i][j]=0;
            //pix0[i][j]=pix1[i][j];
        }//endjfor
    }//endifor
        countt=0;
    }//endifcountt
    
    /*
    
    //rightchanel
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 748, 0);
    
    ofSetColor(225);
    // ofDrawBitmapString("Right Channel", 4, 18);
    
    ofSetLineWidth(1);
    //ofDrawRectangle(0, 0, 900, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < rAudio.size(); i++){
        float x =  ofMap(i, 0, rAudio.size(), 0, 900, true);
        ofVertex(x, 100 -rAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    */
    
    
    
    
    /*
    ofSetColor(225);
    string reportString = "volume: ("+ofToString(volume, 2)+") modify with -/+ keys\npan: ("+ofToString(pan, 2)+") modify with mouse x\nsynthesis: ";
    if( !bNoise ){
        reportString += "sine wave (" + ofToString(targetFrequency, 2) + "hz) modify with mouse y";
    }else{
        reportString += "noise";
    }
    ofDrawBitmapString(reportString, 32, 579);
     
     
     */
/********endaudiodrawbiz****/
   
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
    

    // cout <<" c1="<<c1<< endl;
    
    pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
   
    
    if ( bNoise == true){
        // ---------------------- noise --------------
        for (size_t i = 0; i < buffer.getNumFrames(); i++){
            lAudio[i] = buffer[i*buffer.getNumChannels()    ] = ofRandom(0, 1) * volume * leftScale;
            rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = ofRandom(0, 1) * volume * rightScale;
        }
    } else {
        
        
        //this is to keep phase from just incrementing absurdly
        //for some reaason if the mod is just twopi then it restarts phase in rythmic glitchy bits
        //maybe i can turn this on and off or swtich values?
        phase=fmod(phase,4*TWO_PI);
        phaseAdderTarget=(frequency/10000.0 ) * TWO_PI;
        
        
        phaseAdder = 0.5f * phaseAdder + 0.5f *phaseAdderTarget;
        for (size_t i = 0; i < buffer.getNumFrames(); i++){
            phase += phaseAdder;
           float  phase_r=phase+TWO_PI*(sin(theta));
            
            /*basic waveforms*/
            
            /*samplel and sampler are what get fed into the buffer at the end*/
            float samplel=0;
            float sampler=0;
            
            
            /*pm are the dummy variables for phase modulation*/
            
            float pm_l=0;
            float pm_r=0;
            
            //sines
            float sine_l = sin(phase/2.0)*(ss);
            float sine_r = sin(phase_r/2.0)*(ss);
            //float sampler=-1*samplel;
            
            //squares//
            //to try pulsewidth modulationtry just adding a constant to the sinewave to make it that much more above zero yo!!
            float ee=.72*sin(theta/3.0);
           // float ee=0;
            float  pulse_l=ofSign(sine_l+ee);
            float pulse_r=ofSign(sine_r+ee);
            
            
            //sawws
            float saw_l=(phase/4.0-floor(phase/4.0))*ss;
            float saw_r=(phase_r/4.0-floor(phase_r/4.0))*ss;
            
           // samplel=saw_l;
           // sampler=saw_r;
            
            
            //triangle
           
           // float tri_l=abs(fmod((phase-1),4)-2)-1;
           // float tri_r=abs(fmod(ff*(phase_r-1),4)-2)-1;
            
            
            //shapedtriangle
            
            
            float q=16*sin(theta/2.0);
            
            if(q<2&&q>=0){q=2;}
            if(q>-2&&q<0){q=-2;}

            
            int quant_l=int(pow(sine_l*ff,3)*q);
            int quant_r=int(pow(sine_r*ff,3)*q);
            
            float tri_l=quant_l/q;
            float tri_r=quant_r/q;
            
           // tri_l=ofLerp(sine_lold,tri_l,1);
           // tri_r=ofLerp(sine_rold,tri_r,1);
           // samplel=tri_l;
           // sampler=tri_r;
            
            //parabola
            
            float para_l=sine_l*sine_l*2-1;
            float para_r=sine_r*sine_r*2-1;
            
           
            //tanwave
            //def need to clamp or wrap or fold this one! asssymptopticall~~
            
            pm_l=ff*para_l;
            pm_r=ff*para_r;
            float tan_l=ofClamp(ss*tan(phase/2.0+pm_l),-1,1);
            float tan_r=ofClamp(ss*tan(phase_r/2.0+pm_r),-1,1);
            
            
           // samplel=tan_l*tan_l*tan_l;
           //sampler=tan_r*tan_r*tan_r;
            
            
            //experimentalwaves
            
            
            //logwave!
           // samplel=log(abs(sine_l*(1+ff)+1))-1;
           // sampler=log(abs(sine_r*(1+ff)+1))-1;
            
            
            //squrtsine
           // samplel=sqrt(abs(sine_l*(1+ff)+1))-1;
           // sampler=sqrt(abs(sine_r*(1+ff)+1))-1;

            
            
            //i want like a wavier square
            
            //float ee=.72*sin(theta/3.0);
            // float ee=0;
            float  pulsew_l=ofSign(sine_l+ee)*.75+.25*sine_l;
            float pulsew_r=ofSign(sine_r+ee)*.75+.25*sine_r;
            
            //samplel=pow(pulsew_l,3);
            //sampler=pow(pulsew_r,3);
            
            
            
            
            
            /***interpolate between waves**/
          
            
            float ww=sin(theta/2.0);
            float interp_l=(ww*sine_l+(1-ww)*pulse_l)/2.0;
            float interp_r=(ww*sine_r+(1-ww)*pulse_r)/2.0;
            
          //  samplel=interp_l;
           // sampler=interp_r;
            
            
          
            
            
           //samplel=tan_l*tan_l*tan_l;
           //sampler=tan_r*tan_r*tan_r;
            
            
            
            
     
            
            
            
            
            
            /*frequencymod*/
            float fm_l=sin(phase*sin(ff*phase));
            float fm_r=sin(phase_r*sin(ff*phase_r));
            
            
            
            /*fphasemod*/
            float phm_l=sin(phase+sin(int(kk)*ff*phase));
            float phm_r=sin(phase_r+sin(int(kk)*ff*phase_r));
            
            // samplel=fm_l;
           // sampler=fm_r;
            
            
            /**ringmod**/
            
            samplel=interp_l*phm_l;
           sampler=interp_r*phm_r;
            
            
            /**ampmod**/
            
            
            //the divide by 2 and plus .5 is transforming the bipolar modulator into a unipolar modulator
            
            // samplel=pulse_l*(tri_l/2+.5);
            // sampler=pulse_r*(tri_r/2+.5);
            
            
            
            
            
            /**wavesubtract**/
            
           // float subtract_l=(sine_l-saw_l)/2.0+1/2;
           //  float subtract_r=(sine_r-saw_r)/2.0+1/2;
            
          //  samplel=subtract_l;
           // sampler=subtract_r;
            
            /**addwaves**/
            
          //  float add_l=(saw_l+pulse_l)/2.0;
          //  float add_r=(saw_r+pulse_r)/2.0;
            
           // samplel=add_l;
           //  sampler=add_r;

            
            /**foldover**/
            
            
           // samplel=sine_l;
           // sampler=sine_r;
            
            /*
            
            if(samplel>1){
                samplel=1-fmod(samplel,1);
            
            }
            if(samplel<-1){
                samplel=fmod(abs(samplel),1)-1;
                
            }
            
            if(sampler>1){
                sampler=1-fmod(sampler,1);
                
            }
            if(sampler<-1){
                sampler=fmod(abs(sampler),1)-1;
                
            }
            */
            
            
            
         /**clammpp_clipp**/
            
            samplel=ofClamp(samplel,-1,1);
             sampler=ofClamp(sampler,-1,1);
            
     
            
            //smoothe the ringmodding maybe?
            
           // samplel=samplel*samplel*samplel;
            //sampler=sampler*sampler*sampler;
            
            
            
            /**phasemodulation**/
           // samplel=sin(ss*phase+sampler);
           // sampler=sin(dd*phase+samplel);
            
            /*quantise*/
            //samplel=int(samplel*ff);
            //sampler=int(sampler*gg);
            
            
            
            
           // int x1=int(gg*samplel);
           // int x2=int(gg*sampler);
            
           // samplel=x1/gg;
           // sampler=x2/gg;
            
            
            /**chebeyshev_polynomials**/
            /* T_k+1(x)=2*x*T_k(x)-T_k-1(x)*/
            
           // float xl=samplel;
          //  float xr=sampler;
            
            /*
            
            //T_2//
            float T_2l=2*xl*xl-1;
            float T_2r=2*xr*xr-1;
            
            //T_3//
            float T_3l=4*pow(xl,3)-3*xl;
            float T_3r=4*pow(xr,3)-3*xr;
            
            //T_4//
            float T_4l=8*pow(xl,4)-8*pow(xl,2)+1;
            float T_4r=8*pow(xr,4)-8*pow(xl,2)+1;

            
            samplel=(T_4l+T_3l+T_2l+xl)/4.0;
            sampler=(T_4r+T_3r+T_2r+xr)/4.0;
            */
            
            
            
            /**feedingchebyshevstochebyshevs**/
            //T_2//
           // float T_2l=2*xl*xl-1;
           // float T_2r=2*xr*xr-1;
            
            //T_3//
          //  float T_3l=4*pow(T_2l,3)-3*T_2l;
          //  float T_3r=4*pow(T_2r,3)-3*T_2r;
            
            //T_4//
          ////  float T_4l=8*pow(T_3l,4)-8*pow(T_3l,2)+1;
          //  float T_4r=8*pow(T_3r,4)-8*pow(T_3r,2)+1;
            
            
            //samplel=(T_4l);
           // sampler=(T_4r);
            
            
            
       
            
            
            
            volume=out_env;
            
            // volume = MAX(volume, 0);
            //volume = MIN(volume, 1);
            
            lAudio[i] = buffer[i*buffer.getNumChannels()    ] = samplel * volume * leftScale;
            rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = sampler * volume * rightScale;
            
            
         
            
            /**lerpingexperiment**/

            /*
            if(i>0){
            if(abs(lAudio[i]-lAudio[i-1])>.05){
                lAudio[i]=ofLerp(lAudio[i-1],lAudio[i],.5);
            }//endifabsl
                
                if(abs(rAudio[i]-rAudio[i-1])>.25){
                    rAudio[i]=ofLerp(rAudio[i-1],rAudio[i],.5);
                }//endifabs

            }//endifi
            */
            sine_lold=quant_l;
            sine_rold=quant_r;
            
        }
    }
    
}

//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch(key) {
		case '?':
			midiIn.listInPorts();
			break;
	}
    
    if (key == '-' || key == '_' ){
        volume -= 0.05;
        volume = MAX(volume, 0);
    } else if (key == '+' || key == '=' ){
        volume += 0.05;
        volume = MIN(volume, 1);
    }
    
    //if( key == 's' ){
    //soundStream.start();
    //}
    
    //if( key == 'e' ){
    //	soundStream.stop();
    //}
    
    if(key=='s'){ss+=.005;}
    if(key=='x'){ss-=.005;}
    
    if(key=='d'){dd+=.005;}
    if(key=='c'){dd-=.005;}
    
    if(key=='f'){ff+=.01;}
    if(key=='v'){ff-=.01;}
    
    
    if(key=='g'){gg+=.1;}
    if(key=='b'){gg-=.1;}
    if(key=='h'){hh+=.1;}
    if(key=='n'){hh-=.1;}
    
    if(key=='k'){kk+=.1;}
    if(key==','){kk-=.1;}
    
    if(key=='p'){pp+=.01;}
    if(key=='['){pp-=.01;}
    if(key=='i'){ii+=.1;}
    if(key=='o'){ii-=.1;}
    
    
    if(key=='1'){sw1=1;}
    if(key=='q'){sw1-=0;}
    
    if(key=='l'){ll+=1; cout << "ll="<< ll<< endl;}
    if(key=='.'){ll-=1; cout << "ll="<< ll<< endl;}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
   
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
    float height = (float)ofGetHeight();
    float heightPct = ((height-y) / height);
    targetFrequency = 2000.0f * heightPct;
    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
