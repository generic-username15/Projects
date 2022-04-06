PImage img, sorted;


void setup(){
  size(2320, 4128);
  //fullScreen();
  img = loadImage("niebo.jpg");
  sorted = createImage(img.width,img.height,RGB);
  sorted.loadPixels();
  img.loadPixels();
  for ( int i = 0; i < sorted.pixels.length; i++){
    sorted.pixels[i] = img.pixels[i];
  }

 
sortIt(900,300,600,600);
sortIt(2500,600,1000,1500);

  sorted.updatePixels();
}

void sortRandom(int iterations, int stripeWidth, int stripeLength, int topprc, int bottomprc, int rightprc, int leftprc){
  
  int top = floor(map(topprc,0,100,0,img.width));
  int bottom = floor(map(bottomprc,0,100,0,img.width));
  int right = floor(map(rightprc,0,100,0,img.height));
  int left = floor(map(leftprc,0,100,0,img.height));
  
   for(int i = 0; i < iterations; i++){
    int x = floor(random(left,img.height  - stripeWidth - right));
    int y = floor(random(top,img.width  - stripeLength - bottom));
    sortIt(x,y,stripeWidth,stripeLength);
  }
}

void sortIt(int x, int y, int w, int h){
  int right = x;
  int top = y;
  int left = sorted.height - w - x;
  int bot = sorted.width - h - y;
   
  for (int i = left; i < sorted.height - right; i+=1){
      quickSort(top + i*sorted.width,(i+1)*sorted.width - 1 - bot);
  }
}
void draw(){
  //background(255);
  //push();
  //translate(600,0);
  //rotate(PI/2);
  //image(img,0,0,600,600);
  //pop();
  //push();
  //translate(1200,0);
  //rotate(PI/2);
  //image(sorted,0,0,600,600);
  //pop();
  
  
  //image(img,0,0,600,600);
  //image(sorted,600,0,600,600);
  
  
  image(sorted,0,0);
  save("sorted.png");
}



void quickSort(int start,int end){
  if ( start >= end){return;}
  int idx = particion(start,end);
  
  quickSort(start,idx-1);
  quickSort(idx+1,end);
}

int particion(int start,int end){
  int pidx = start;
  float p = (sorted.pixels[end]);
  for(int i = start; i < end; i++){
    if ( (sorted.pixels[i]) > p){
      swap(i,pidx);
      pidx++;
    }
  }
  swap(pidx,end);
  return pidx;
}

void swap(int a, int b){
  int pom = sorted.pixels[b];
  sorted.pixels[b] = sorted.pixels[a];
  sorted.pixels[a] = pom;
}
