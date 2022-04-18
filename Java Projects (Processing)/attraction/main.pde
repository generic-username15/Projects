PVector attractor;
particle[] objects;

void setup() {
  size(400, 400);
  background(220);
  attractor = new PVector(200,200);
  for (int i = 0; i < 10; i++){
    objects[i] = new particle();
    //objects[i] = new particle(random(width),random(height));
  }
}

void draw() {
  //background(220);
  //fill(0);
  //circle(attractor.x,attractor.y,10);
  for (int i = 0; i < objects.length; i++){
    objects[i].attract(attractor);
    objects[i].update();
    objects[i].show();
  }
}
