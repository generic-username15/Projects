//https://www.karlsims.com/rd.html
//settings:
//1. difiusion rate
let dfA = 1.0;
let dfB = 0.5;
//2. how fast u add A
let adA = 0.055;
//3. how fast B disappears
let k = 0.062;
//4. time
let t = 1.0;



let cells = [];
let next = [];

function cell(a,b){
  this.a = a;
  this.b = b;
  this.clicked = false;
}

function mousePressed(){
  let x = mouseX;
  let y = mouseY;
  for ( let i = x-5 ; i < x+5; i++){
    for ( let j = y-5; j < y+5; j++){
      cells[j][i].b = 1;
    } 
  }
}

function setup() {
  createCanvas(500, 500);
  pixelDensity(1);
  for (let x = 0; x < width; x++){
    cells[x] = [];
    next[x] = [];
    for(let y = 0; y < height; y++){
      cells[x][y] = new cell(1,0);
      next[x][y] = new cell(1,0);
    }
  }
  // for ( let i = 225; i < 275; i++){
  //   for ( let j = 100; j < 400; j++){
  //     cells[i][j].b = 1;
  //   } 
  // }
}
  
function draw() {
  background(150);
  loadPixels();
  for (let x = 0; x < width; x++){
    for(let y = 0; y < height; y++){
      let idx = (x * width + y) * 4;
      let a = cells[x][y].a;
      let b = cells[x][y].b;
      let c = (a - b) * 255;
      pixels[idx    ] = c;
      pixels[idx + 1] = c;
      pixels[idx + 2] = c;
      pixels[idx + 3] = 255;
    }
  }
  updatePixels();
   for (let x = 1; x < width - 1; x++){
    for(let y = 1; y < height - 1; y++){
      let a = cells[x][y].a;
      let b = cells[x][y].b;
      next[x][y].a = a + (dfA*laplaceA(x,y) - a*b*b + adA*(1-a))*t;
      next[x][y].b = b + (dfB*laplaceB(x,y) + a*b*b - (adA+k)*b)*t;
    }
  }
  let tmp = cells;
  cells = next;
  next = tmp;
}
  
  
function laplaceA(x,y){
  let newA = 0;
  
  newA += cells[x][y].a * -1;
  newA += cells[x + 1][y].a * 0.2;
  newA += cells[x - 1][y].a * 0.2;
  newA += cells[x][y + 1].a * 0.2;
  newA += cells[x][y - 1].a * 0.2;
  newA += cells[x + 1][y + 1].a * 0.05;
  newA += cells[x + 1][y - 1].a * 0.05;
  newA += cells[x - 1][y + 1].a * 0.05;
  newA += cells[x - 1][y - 1].a * 0.05;
  return newA;
} 
  
  function laplaceB(x,y){
  let newB = 0;
  
  newB += cells[x][y].b * -1;
  newB += cells[x + 1][y].b * 0.2;
  newB += cells[x - 1][y].b * 0.2;
  newB += cells[x][y + 1].b * 0.2;
  newB += cells[x][y - 1].b * 0.2;
  newB += cells[x + 1][y + 1].b * 0.05;
  newB += cells[x + 1][y - 1].b * 0.05;
  newB += cells[x - 1][y + 1].b * 0.05;
  newB += cells[x - 1][y - 1].b * 0.05;
  return newB;
} 