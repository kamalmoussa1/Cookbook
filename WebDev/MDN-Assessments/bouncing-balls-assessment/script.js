
// setup canvas

var canvas = document.querySelector('canvas');   // store a ref to canvas element
var ctx = canvas.getContext('2d');

// We are chaining multiple assignments together, to get the variables all set quicker — 
// this is perfectly OK
var width  = canvas.width  = window.innerWidth;
var height = canvas.height = window.innerHeight;


//setup counter 
var myScore = document.querySelector('p');
var scoreCount = 0;

// function to generate random number

function random(min,max) {
  var num = Math.floor(Math.random()*(max-min)) + min;
  return num;
}



// Shape constructor 
function Shape(x,y,velX,velY){

  this.x = x;
  this.y = y;
  this.velX = velX;
  this.velY = velY;
  this.exists; 
  
}

/*
Ball objec--inherit Shape prototype
*/
function Ball(x, y, velX, velY, color, size) {
  Shape.call(this, x, y, velX, velY);
  this.color = color;
  this.size  = size;
  this.exists = true;
  

}
Ball.prototype = Object.create(Shape.prototype);
Ball.prototype.constructor = Ball;

/*
method: Shape.draw();
*/
Ball.prototype.draw = function() {
  ctx.beginPath();
  ctx.fillStyle = this.color;
  ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
  // finish drawing the path we started with beginPath(),
  // and fill the area it takes up with the color we specified earlier in fillStyle."
  ctx.fill();
}

Ball.prototype.update = function() {
  if ((this.x + this.size) >= width) {
    this.velX = -(this.velX);
  }

  if ((this.x - this.size) <= 0) {
    this.velX = -(this.velX);
  }

  if ((this.y + this.size) >= height) {
    this.velY = -(this.velY);
  }

  if ((this.y - this.size) <= 0) {
    this.velY = -(this.velY);
  }

  this.x += this.velX;
  this.y += this.velY;

}

Ball.prototype.collisionDetect = function() {
  for (var j = 0; j < balls.length; j++) {
    if (!(this === balls[j])) {
      var dx = this.x - balls[j].x;
      var dy = this.y - balls[j].y;
      var distance = Math.sqrt(dx * dx + dy * dy);

      if (distance < this.size + balls[j].size) {
        balls[j].color = this.color = 'rgb(' + random(0, 255) + ',' + random(0, 255) + ',' + random(0, 255) +')';
      }
    }
  }
}

/*
 Create EvilCircle prototype-- inherits Shape 
*/
function EvilCircle(x,y){
  Shape.call(this,x,y);
  this.color = 'white';
  this.size  = 10;
  this.velX  = 20;
  this.velY  = 20;  
}

EvilCircle.prototype = Object.create(Shape.prototype);
EvilCircle.prototype.constructor = EvilCircle;

/*
 EvilCircle methods
*/

/* EvilCircle.draw() */

EvilCircle.prototype.draw = function() {
  ctx.beginPath();
  ctx.lineWidth = 3;
  ctx.strokeStyle = this.color;
  ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
  // finish drawing the path we started with beginPath(),
  // and fill the area it takes up with the color we specified earlier in fillStyle."
  ctx.stroke();
}

EvilCircle.prototype.checkBounds = function() {
  if ((this.x + this.size) >= width) {
    this.x -= this.size;
  }

  if ((this.x - this.size) <= 0) {
    this.x += this.size;
  }

  if ((this.y + this.size) >= height) {
    this.y -= this.size;
  }

  if ((this.y - this.size) <= 0) {
    this.y += this.size;
  }

}

EvilCircle.prototype.setControls = function(){
  
  var _this = this;
  window.onkeydown = function(e) {   //event listener 
    if (e.keyCode === 65) {         // A
      _this.x -= _this.velX;  
    } else if (e.keyCode === 68) {  // D
      _this.x += _this.velX;
    } else if (e.keyCode === 87) {  // W
      _this.y -= _this.velY; 
    } else if (e.keyCode === 83) { // S
      _this.y += _this.velY;
    }
  }
  
}



EvilCircle.prototype.collisionDetect = function() {
  for (var j = 0; j < balls.length; j++) {
    if (balls[j].exists) {

      var dx = this.x - balls[j].x;
      var dy = this.y - balls[j].y;
      var distance = Math.sqrt(dx * dx + dy * dy);

      if (distance < this.size + balls[j].size) {
        balls[j].exists = false;
        scoreCount--;
        myScore.textContent = scoreCount;
      }
    } 
  }
}


var evilCircle = new EvilCircle(300,400);
evilCircle.setControls();

var testBall = new Ball(50, 100, 4, 4, 'blue', 10);

var balls = [];


function loop() {
  ctx.fillStyle = 'rgba(0, 0, 0, 0.25)';
  ctx.fillRect(0, 0, width, height); // cover the previous frame of work

  while (balls.length < 25) { // create 25 balls
    var ball = new Ball(
      random(0,width), // random width within the screen range
      random(0,height), // random height within the screen range
      random(-7,7),    // random velocity in x
      random(-7,7),   // random velocity in y
      'rgb(' + random(0,255) + ',' + random(0,255) + ',' + random(0,255) +')', // random color in 0-255 range
      random(10,20)   // radius
    );
    balls.push(ball); // push created balls into the array
    scoreCount++;
    myScore.textContent = scoreCount;

  }

  for (var i = 0; i < balls.length; i++) { // draw and update each ball
    if(balls[i].exists)
    {
      balls[i].draw();
      balls[i].update();
      balls[i].collisionDetect(); // detect collision
      
    }
    evilCircle.draw();
    evilCircle.checkBounds();
    evilCircle.collisionDetect();
  }

  requestAnimationFrame(loop);  // animate
}



loop();