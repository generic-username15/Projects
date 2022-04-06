float xprl, yprl, zprl;
float changeX ,changeY, changeZ;
int cols, rows;
int scl = 20;
ArrayList<particle> particles = new ArrayList<particle>();
PVector[] flowfield;

void setup() {
  
  size(2500, 2500);
  background(255);
  colorMode(HSB, 255);
  cols = floor(width / scl) + 1;
  rows = floor(height / scl) + 1;
  changeX = 0.1;
  changeY = 0.1;
  changeZ = 0.0005;
  zprl = 0;
  flowfield = new PVector[cols * rows];
  for ( int i = 0; i < 50000; ++i){
    particles.add(new particle());
  }
}

void mousePressed(){
  noLoop();
}

void draw() {
  //background(255);
  yprl = 0;
  for (int x = 0; x < cols; x++){
    xprl = 0;
    for (int y = 0; y < rows; y++){
      PVector tmp = PVector.fromAngle(map(noise(xprl,yprl,zprl), 0, 1, 0, 4*PI));
      tmp.setMag(0.5);
      int index = x + y * cols;
      flowfield[index] = tmp;
      
      xprl += changeX;
    }
    yprl += changeY;
    zprl += changeZ;
  }
  
  for (particle p : particles){
    p.display();
    p.edges();
    p.followVectors(flowfield);
    p.move();
    p.update();
  }
  save("canvas.jpg");
}
