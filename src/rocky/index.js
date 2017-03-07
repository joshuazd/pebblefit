var rocky = require('rocky');

rocky.on('draw', function(event) {
  // Get the CanvasRenderingContext2D object
  var ctx = event.context;
  
  ctx.clearRect(0, 0, ctx.canvas.clientWidth, ctx.canvas.clientHeight);
  
  var w = ctx.canvas.unobstructedWidth;
  var h = ctx.canvas.unobstructedHeight;
  
  // Current date/time
  var d = new Date();

  // Set the text color
  ctx.fillStyle = 'white';

  // Center align the text
  ctx.textAlign = 'center';

  // Display the time, in the middle of the screen
  var time = '' + d.getHours() + ':' + d.getMinutes();
  console.log(time);
  ctx.fillText(time, w/2, h/2, w);
  //ctx.fillText(d.toLocaleTimeString(), w / 2, h / 2, w);
});

rocky.on('minutechange', function(event) {
  console.log("Another minute with your Pebble!");
  rocky.requestDraw();
});

