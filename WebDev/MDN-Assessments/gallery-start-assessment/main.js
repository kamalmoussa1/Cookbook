var displayedImage = document.querySelector('.displayed-img');
var thumbBar = document.querySelector('.thumb-bar');

btn = document.querySelector('button');
var overlay = document.querySelector('.overlay');

/* Looping through images */
for(var i=1; i <= 5; i++){
  var imgSrc = 'images/pic' + i.toString() +'.jpg';
  var newImage = document.createElement('img');
  newImage.setAttribute('src', imgSrc);
  thumbBar.appendChild(newImage);
}

function changeImage(e){
  displayedImage.setAttribute('src',e.target.getAttribute('src'));
}

thumbBar.addEventListener('click',changeImage); // event delegation! 


/* Wiring up the Darken/Lighten button */


function toggleLighting(){
  
  var mode = btn.getAttribute('class');
  if( mode === 'dark'){
    btn.setAttribute('class','light');
    btn.textContent = "Lighten";
    overlay.style.background = "rgba(0,0,0,0.5)";
  }
  else{
    btn.setAttribute('class','dark');
    btn.textContent = "Darken";
    overlay.style.background = "rgba(0,0,0,0)";
  }

}
btn.addEventListener('click', toggleLighting)