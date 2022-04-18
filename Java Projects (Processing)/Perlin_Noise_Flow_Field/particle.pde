class particle{
  
    PVector pos = new PVector(random(width),random(height));
    PVector vel = new PVector(0,0);
    PVector acc = new PVector(0,0);
    PVector prev = pos.copy();
    int maxSpeed = 4;
    int h = 0;
  
  
  void move(){
    pos.add(vel);
    vel.add(acc);
    vel.limit(maxSpeed);
    acc.mult(0);
  }
  
  void applyForce(PVector force){
    acc.add(force);
  }
  
  void display(){
    //stroke(h, 255, 255, 50);
    stroke(0,10);
    h ++;
    if (h > 255){h = 0;}
    line(pos.x, pos.y, prev.x, prev.y);
    //point(pos.x, pos.y)
  }
  
  void followVectors(PVector[] flowfield){
    int x = floor(pos.x / scl);
    int y = floor(pos.y / scl);
    int idx = x + y * cols;
    PVector vec = flowfield[idx];
    applyForce(vec);
  }
  
  void edges(){
    if (pos.x > width){
      pos.x = 0;
      update();}
    if (pos.x < 0){
      pos.x = width;
      update();}
    if (pos.y > height){
      pos.y = 0;
      update();}
    if (pos.y < 0){
      pos.y = height;
      update();}
  }
  
  void update(){
    prev = pos.copy();
  }
}
