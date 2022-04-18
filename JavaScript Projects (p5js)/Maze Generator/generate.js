// https://en.wikipedia.org/wiki/Maze_generation_algorithm
//Deep First Search Maze Generator

let wymiarX = 40;
let wymiarY = 40;
let unit = 10;
let cells = [];
let current;
let places = [];

function setup() {
  current = 0;
  createCanvas(unit*wymiarX, unit*wymiarY);
  let pom = 0;
  for (let j = 0; j < wymiarX; j++){
    for (let i = 0; i < wymiarY; i++){
      cells[pom] = new Cell(i,j);
      pom++;
    }
  }
}

function draw() {
  frameRate(60);
  cells[current].visited = true;
  background(0);
  for (let i = 0; i < cells.length; i++){
    cells[i].show();
    cells[current].glow();
  }
  if (cells[current].check() != -1){
    places.push(current);
  let next = cells[current].check();
  removeWalls(cells[current],cells[next]);
  current = next;
  }
  else{
    if(places.length == 0){
      noLoop();
    }
    current = places[places.length - 1];
    places.pop();
  }
}

function Cell(x,y){
  this.x = x;
  this.y = y; //up,right,down,left
  this.walls = [true,true,true,true];
  this.visited = false;
  
  this.show = function(){
    stroke(255);
    if (this.walls[0]){     
      line(x*unit,y*unit,x*unit+unit,y*unit);
    }
    if(this.walls[1]){
      line(x*unit+unit,y*unit,x*unit+unit,y*unit+unit);
    }
    if(this.walls[2]){
      line(x*unit,y*unit+unit,x*unit+unit,y*unit+unit);
    }
    if(this.walls[3]){
      line(x*unit,y*unit,x*unit,y*unit+unit);
    }
   
  }
  this.check = function(){
    let nextMove = [];
    if (y - 1 >= 0 && cells[(y-1)*wymiarX + x].visited == false){
      nextMove.push((y-1)*wymiarX + x);
    }
    if (x+1 < wymiarX && cells[y*wymiarX + x + 1].visited == false){
      nextMove.push(y*wymiarX + x + 1);
    }
    if (y+1  < wymiarY && cells[(y+1)*wymiarX + x].visited == false){
      nextMove.push((y+1)*wymiarX + x);
    }
    if (x - 1 >= 0 && cells[y*wymiarX + x - 1].visited == false){
      nextMove.push(y*wymiarX + x - 1);
    }
    if (nextMove.length == 0){
      return -1;
    }
    let pom = floor(random(0,nextMove.length));
    return nextMove[pom];
  }
  this.glow = function(){
    fill(255,255,255);
      noStroke();
      rect(x*unit,y*unit,unit)
  }
}

function removeWalls(cell,nextCell){
  if ((cell.y-1)*wymiarX + cell.x == nextCell.y * wymiarX + nextCell.x){
      cell.walls[0] = false;
      nextCell.walls[2] = false;
     }
    else if (cell.y*wymiarX + cell.x + 1 == nextCell.y * wymiarX + nextCell.x){
      cell.walls[1] = false;
      nextCell.walls[3] = false;
    }
    else if ((cell.y+1)*wymiarX + cell.x == nextCell.y * wymiarX + nextCell.x){
      cell.walls[2] = false;
      nextCell.walls[0] = false;
    }
    else{
      cell.walls[3] = false;
      nextCell.walls[1] = false;
    }
}