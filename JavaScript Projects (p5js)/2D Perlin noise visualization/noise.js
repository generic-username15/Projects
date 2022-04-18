let grid = [];
let grid2 = [];
let grid3 = [];
let xprl, yprl;
let changeX ,changeY;
let r,g,b;

function setup() {
  changeX = 0.01;
  changeY = 0.01;
  r = 205;
  g = 155;
  b = 255;
  noiseDetail(15,0.75);
  pixelDensity(1);
  createCanvas(400, 400);
  xprl = 0;
  for (let x = 0; x < width; x++){
    grid[x] = [];
    yprl = 0;
    for (let y = 0; y < height; y++){
      if (y == 0){yprl = 0;}
      grid[x][y] = noise(xprl,yprl);
      yprl += changeY;
    }
    xprl += changeX;
  }
   for (let x = 0; x < width; x++){
    grid2[x] = [];
    yprl = 0;
    for (let y = 0; y < height; y++){
      if (y == 0){yprl = 0;}
      grid2[x][y] = noise(xprl,yprl);
      yprl += changeY;
    }
     xprl += changeX;
  }
   for (let x = 0; x < width; x++){
    grid3[x] = [];
    yprl = 0;
    for (let y = 0; y < height; y++){
      if (y == 0){yprl = 0;}
      grid3[x][y] = noise(xprl,yprl);
      yprl += changeY;
    }
     xprl += changeX;
  }
}

function draw() {
  background(255);
  loadPixels();
  for (let x = 0; x < width; x++){
    for (let y = 0; y < height; y++){
      let idx = (y * width + x) * 4;
      pixels[idx    ] = grid [x][y] * r;
      pixels[idx + 1] = grid [x][y] * g;
      pixels[idx + 2] = grid2[x][y] * b;
    }
  }
  updatePixels();
  noLoop();
}