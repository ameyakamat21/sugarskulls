/**
  * This sketch demonstrates how to use the BeatDetect object song SOUND_ENERGY mode.<br />
  * You must call <code>detect</code> every frame and then you can use <code>isOnset</code>
  * to track the beat of the music.
  * <p>
  * This sketch plays an entire song, so it may be a little slow to load.
  * <p>
  * For more information about Minim and additional features, 
  * visit http://code.compartmental.net/minim/
  */
  
import ddf.minim.*;
import ddf.minim.analysis.*;
import http.requests.*;

Minim minim;
AudioPlayer song;
BeatDetect beat;

float eRadius;

void setup()
{
  size(200, 200, P3D);
  minim = new Minim(this);
  //song = minim.loadFile("/Users/ameya/Downloads/Voyager.mp3", 2048);
  song = minim.loadFile("/Users/ameya/Downloads/thursday-afternoon.mp3");
  song.play();
  // a beat detection object song SOUND_ENERGY mode with a sensitivity of 10 milliseconds
  beat = new BeatDetect();
  beat.setSensitivity(5);
  
  ellipseMode(RADIUS);
  eRadius = 20;
}

void draw()
{
  background(0);
  beat.detect(song.mix);
  float a = map(eRadius, 20, 80, 60, 255);
  fill(60, 255, 0, a);
  if ( beat.isOnset() ) { 
    eRadius = 80;
    sendRandomUpdate();
  }
  ellipse(width/2, height/2, eRadius, eRadius);
  eRadius *= 0.95;
  if ( eRadius < 20 ) eRadius = 20;
}

void sendRandomUpdate() {
  sendColorUpdate(c2hex(getRandomColor()), c2hex(getRandomColor()), c2hex(getRandomColor()), c2hex(getRandomColor()), c2hex(getRandomColor()));
}

color getRandomColor() {
  return color(int(random(256)), int(random(256)), int(random(256)));
}

String c2hex(color c) {
   return "#" + hex(c).substring(2); 
}

void sendColorUpdate(String c0, String c1, String c2, String c3, String c4) {
    PostRequest post = new PostRequest("http://10.0.0.203:80/setstripto");
    post.addData("p0", c0);
    post.addData("p1", c1);
    post.addData("p2", c2);
    post.addData("p3", c3);
    post.addData("p4", c4);
    post.send();
}