
import http.requests.*;

void setup() {
}

void draw() {
}

void mouseClicked() {
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