public class particle{
  
    PVector pos = new PVector(0,0);
    PVector vel = new PVector(random(-1,1),random(-1,1));
    PVector acc = new PVector();
    PVector prevpos = pos.copy();
    
  
  
   void update(){
    pos.add(this.vel);
    vel.add(this.acc);
    acc.mult(0);
  }
  
  void show(){
    fill(0);
    stroke(0,5);
    line(pos.x, pos.y, prevpos.x, prevpos.y); 
    this.prevpos = pos.copy();
  }
  
  void applyForce(PVector force){
    acc.add(force);
  }
  
  void attract(PVector attractor){
    float G = 10;
    PVector dir = attractor.sub(pos);
    float dsqr = dir.magSq();
    dsqr = constrain(dsqr, 10, 5);
    dir.setMag(G / dsqr);
    if (dir.mag() > 50){
      dir.mult(-10);
    }
    applyForce(dir);
  }
}
